/**
 * @file QuickSort.h
 * @date 2026-10-08
 */
#pragma once
#include "DoublyLinkedList.h"

 //---------------------------------------------------------------------------------
 // 参考文献
 // https://ja.wikipedia.org/wiki/%E3%82%AF%E3%82%A4%E3%83%83%E3%82%AF%E3%82%BD%E3%83%BC%E3%83%88
 // https://coddy.tech/visualize/ja/sorting/quick-sort
 // https://inzkyk.xyz/algorithms/recursion/quicksort/
 //---------------------------------------------------------------------------------

 //---------------------------------------------------------------------------------
 // 実装時メモ
 // Lomuto方式とHoare方式の2つがあるが、Hoare方式は既存の実装だと判定が複雑になる
 // Lomuto方式なら改修なしで実装できるため今回はLomuto方式を採用します。
 // 同じキーが多い場合に分割が偏るため、2パスの3分割にしました。
 // 再帰は小さい側の区間だけにし、大きい側はループで処理して再帰の深さをO(log n)に抑える
 //---------------------------------------------------------------------------------

 /**
  * @brief ソート順
  */
enum class SortOrder {
	Ascending, ///< 昇順
	Descending ///< 降順
};

/**
 * @brief クイックソートの内部実装（外部から直接呼ばない）
 */
namespace QuickSortDetail {

	/**
	 * @brief 2つの値を入れ替える
	 * @note 同じものを渡された場合はなにもしない
	 *
	 * @tparam T 値の型
	 * @param a 値1
	 * @param b 値2
	 */
	template <typename T>
	void swapValue(T& a, T& b);

	/**
	 * @brief キーaがキーbより前に並ぶべきかを判定する
	 *
	 * @tparam Key キーの型（operator<で比較できること）
	 * @param a キー1
	 * @param b キー2
	 * @param order ソート順
	 * @return true a が b より前に並ぶべきなら true
	 * @return false それ以外の場合
	 */
	template <typename Key>
	bool comesBefore(const Key& a, const Key& b, SortOrder order);

	/**
	 * @brief 先頭・中央・末尾の中央値を区間の末尾に移動する
	 *
	 * @tparam Iterator イテレータの型
	 * @tparam KeyFunc 要素からキーを取り出す関数の型
	 * @param first 区間の先頭
	 * @param last 区間の末尾 (この要素は含まない)
	 * @param count 区間の要素数（3以上）
	 * @param getKey 要素からキーを取り出す関数
	 * @param order ソート順
	 */
	template <typename Iterator, typename KeyFunc>
	void moveMedianToBack(Iterator first, Iterator last, int count,
		const KeyFunc& getKey, SortOrder order);

	/**
	 * @brief 区間をクイックソートする
	 *
	 * @tparam Iterator イテレータの型
	 * @tparam KeyFunc 要素からキーを取り出す関数の型
	 * @param first 区間の先頭
	 * @param last 区間の末尾 (この要素は含まない)
	 * @param count 区間の要素数（firstからlastまでの要素数と一致すること）
	 * @param getKey 要素からキーを取り出す関数
	 * @param order ソート順
	 */
	template <typename Iterator, typename KeyFunc>
	void quickSortRange(Iterator first, Iterator last, int count, const KeyFunc& getKey, SortOrder order);

} // namespace QuickSortDetail

/**
 * @brief リストをクイックソートする
 *
 * 安定ソートではない（同じキーの要素の順序は保たれない）。
 * ノードではなく値を入れ替えるため、ソート前に取得したイテレータが指す値は変わる。
 *
 * @tparam T 要素の型
 * @tparam KeyFunc 要素からキーを取り出す関数の型（戻り値はoperator<で比較できること）
 * @param list ソートするリスト
 * @param getKey 要素からキーを取り出す関数
 * @param order ソート順
 */
template <typename T, typename KeyFunc>
void quickSort(DoublyLinkedList<T>& list, KeyFunc getKey, SortOrder order = SortOrder::Ascending);

//テンプレートの実装はinlに記述する
#include "QuickSort.inl"
