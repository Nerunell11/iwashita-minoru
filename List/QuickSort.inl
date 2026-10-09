/**
 * @file QuickSort.inl
 * @date 2026-10-08
 */
#pragma once

 //--------------------------------------------------------
 // QuickSortDetail
 //--------------------------------------------------------

template <typename T>
void QuickSortDetail::swapValue(T& a, T& b) {
	//自己ムーブ代入を避ける
	if (&a == &b) {
		return;
	}

	T temp = static_cast<T&&>(a);
	a = static_cast<T&&>(b);
	b = static_cast<T&&>(temp);
}

template <typename Key>
bool QuickSortDetail::comesBefore(const Key& a, const Key& b, SortOrder order) {
	if (order == SortOrder::Ascending) {
		return a < b;
	}
	return b < a;
}

template <typename Iterator, typename KeyFunc>
void QuickSortDetail::moveMedianToBack(Iterator first, Iterator last, int count,
	const KeyFunc& getKey, SortOrder order) {
	//中央の要素まで進める
	Iterator mid = first;
	for (int i = 0; i < count / 2; ++i) {
		++mid;
	}
	Iterator back = last;
	--back;

	//first <= mid <= back の順に並べる
	if (comesBefore(getKey(*mid), getKey(*first), order)) {
		swapValue(*mid, *first);
	}
	if (comesBefore(getKey(*back), getKey(*first), order)) {
		swapValue(*back, *first);
	}
	if (comesBefore(getKey(*back), getKey(*mid), order)) {
		swapValue(*back, *mid);
	}

	//中央値を末尾に移動する
	swapValue(*mid, *back);
}

template <typename Iterator, typename KeyFunc>
void QuickSortDetail::quickSortRange(Iterator first, Iterator last, int count, const KeyFunc& getKey, SortOrder order) {
	//要素数が2以上の間、分割を繰り返す
	while (count >= 2) {

		//3つ以上なら中央値をピボットにする（2つなら末尾をそのまま使う）
		if (count >= 3) {
			moveMedianToBack(first, last, count, getKey, order);
		}

		Iterator pivot = last;
		--pivot;
		//ピボットはループ中に動かさないので、参照で保持してよい
		const auto& pivotKey = getKey(*pivot);

		//1周目：ピボットより前に並べる要素を先頭に詰める
		Iterator lessEnd = first;
		int lessCount = 0; //ピボットより前に並ぶ要素数
		for (Iterator it = first; it != pivot; ++it) {
			if (comesBefore(getKey(*it), pivotKey, order)) {
				swapValue(*it, *lessEnd);
				++lessEnd;
				++lessCount;
			}
		}

		//2周目：残りのうちピボットと等しい要素をlessEndの後ろに詰める
		//残りはピボットより前に並ばない要素だけなので、ピボットより後ろに並ばなければ等しいと判定できる
		Iterator equalEnd = lessEnd;
		int equalCount = 0; //ピボットと等しい要素数（ピボット自身を含む）
		for (Iterator it = lessEnd; it != pivot; ++it) {
			if (!comesBefore(pivotKey, getKey(*it), order)) {
				swapValue(*it, *equalEnd);
				++equalEnd;
				++equalCount;
			}
		}

		//ピボットを等しい区間の末尾に置く
		swapValue(*equalEnd, *pivot);
		++equalEnd;
		++equalCount;

		const int greaterCount = count - lessCount - equalCount; //ピボットより後ろに並ぶ要素数

		//等しい区間は確定済み。小さい側だけ再帰し、大きい側はループで処理する
		if (lessCount < greaterCount) {
			quickSortRange(first, lessEnd, lessCount, getKey, order);
			first = equalEnd;
			count = greaterCount;
		}
		else {
			quickSortRange(equalEnd, last, greaterCount, getKey, order);
			last = lessEnd;
			count = lessCount;
		}
	}
}

//--------------------------------------------------------
// quickSort
//--------------------------------------------------------

template <typename T, typename KeyFunc>
void quickSort(DoublyLinkedList<T>& list, KeyFunc getKey, SortOrder order) {
	QuickSortDetail::quickSortRange(list.begin(), list.end(), list.size(), getKey, order);
}

template <typename T>
void quickSort(DoublyLinkedList<T>& /*list*/, std::nullptr_t, SortOrder /*order*/) {
	//キー指定がない場合は何もしない
}
