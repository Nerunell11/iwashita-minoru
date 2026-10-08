/**
 * @file DoublyLinkedList.h
 * @date 2026-10-08
 */
#pragma once


 /**
  * @brief 双方向リスト
  *
  * コピーとムーブは禁止し、所有権はリスト自身が持つ
  * @tparam T 格納するデータの型
  */
template <typename T>
class DoublyLinkedList final {
private:

	/**
	* @brief リストの1要素を表すノード
	*
	*/
	struct Node final {
		Node* prev; ///<前のノード
		Node* next; ///<次のノード
		T data; ///<格納データ
		Node(Node* prev, Node* next, const T& data)
			: prev(prev), next(next), data(data) {}
	};

public:

	/**
	 * @brief リスト操作の結果
	 */
	enum class Result {
		Success, ///<成功
		NoOwner, ///<どのリストにも属さないイテレータ
		OtherList, ///<別のリストのイテレータ
		EndIterator ///<末尾を示すイテレータは削除できない
	};

	/**
	 * @brief リスト操作の結果を文字列に変換する
	 *
	 * @param[in] result リスト操作の結果
	 * @return const char* 文字列に変換した結果
	 */
	static const char* toMessage(Result result);

	/**
	* @brief 読み取り専用のイテレータ
	*/
	class ConstIterator {
		friend class DoublyLinkedList;

	public:
		ConstIterator() = default;
		ConstIterator(const ConstIterator&) = default;
		ConstIterator& operator=(const ConstIterator&) = default;
		ConstIterator(ConstIterator&&) = default;
		ConstIterator& operator=(ConstIterator&&) = default;
		virtual ~ConstIterator() = default;

		/**
		* @brief イテレータをインクリメントする
		*
		* @return ConstIterator& インクリメント後のイテレータ
		*/
		ConstIterator& operator++();

		/**
		* @brief イテレータを後置インクリメントする
		*
		* @return ConstIterator インクリメント前のイテレータ
		*/
		ConstIterator operator++(int);

		/**
		* @brief イテレータを前置デクリメントする
		*
		* @return ConstIterator& デクリメント後のイテレータ
		*/
		ConstIterator& operator--();

		/**
		* @brief イテレータを後置デクリメントする
		*
		* @return ConstIterator デクリメント前のイテレータ
		*/
		ConstIterator operator--(int);

		/**
		* @brief イテレータの現在のデータを取得する
		*
		* @return const T& 現在のデータ
		*/
		const T& operator*() const;

		/**
		* @brief イテレータが等しいかどうかを比較する
		*
		* @param other 比較するイテレータ
		* @return true 等しい場合
		* @return false 等しくない場合
		*/
		bool operator==(const ConstIterator& other) const;

		/**
		* @brief イテレータが等しくないかどうかを比較する
		*
		* @param other 比較するイテレータ
		* @return true 等しくない場合
		* @return false 等しい場合
		*/
		bool operator!=(const ConstIterator& other) const;

	protected:
		ConstIterator(Node* node, const DoublyLinkedList* owner);

		/**
		* @brief イテレータが所有者を持っているかどうかを返す
		*
		* @return true 所有者を持っている場合
		* @return false 所有者を持っていない場合
		*/
		bool hasOwner() const;

		/**
		* @brief イテレータが末尾を示すかどうかを返す
		*
		* @return true 末尾を示す場合
		* @return false 末尾を示していない場合
		*/
		bool isEnd() const;

		/**
		* @brief イテレータが先頭を示すかどうかを返す
		*
		* @return true 先頭を示す場合
		* @return false 先頭を示していない場合
		*/
		bool isBegin() const;

		Node* current_ = nullptr; ///< 現在のノード
		const DoublyLinkedList* owner_ = nullptr;///< このイテレータが属するリスト
	};

	/**
	* @brief 読み書き可能なイテレータ
	*/
	class Iterator final : public ConstIterator {
		friend class DoublyLinkedList;

	public:
		Iterator() = default;
		Iterator(const Iterator&) = default;
		Iterator& operator=(const Iterator&) = default;
		Iterator(Iterator&&) = default;
		Iterator& operator=(Iterator&&) = default;
		~Iterator() override = default;

		/**
		* @brief イテレータの現在のデータを取得する
		*
		* @return T& 現在のデータ
		*/
		T& operator*() const;

	private:
		explicit Iterator(Node* node, const DoublyLinkedList* owner);
	};

	DoublyLinkedList();
	virtual ~DoublyLinkedList();

	DoublyLinkedList(const DoublyLinkedList&) = delete;
	DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
	DoublyLinkedList(DoublyLinkedList&&) = delete;
	DoublyLinkedList& operator=(DoublyLinkedList&&) = delete;

	/**
	 * @brief 指定位置にデータを挿入する
	 *
	 * @param[in] pos 挿入位置のイテレータ
	 * @param[in] data 挿入するデータ
	 * @param[out] outIt 挿入した要素を指すイテレータの格納先
	 * @retval Success 成功
	 * @retval NoOwner posがどのリストにも属していない
	 * @retval OtherList posが別のリストのイテレータ
	 */
	Result insert(ConstIterator pos, const T& data, Iterator* outIt = nullptr);

	/**
	 * @brief 指定位置のデータを削除する
	 *
	 * @param[in] pos 削除する位置のイテレータ
	 * @param[out] outNext 削除した要素の次の要素を指すイテレータの格納先
	 * @retval Success 成功
	 * @retval NoOwner posがどのリストにも属していない
	 * @retval OtherList posが別のリストのイテレータ
	 * @retval EndIterator posが末尾を示すイテレータ
	 */
	Result erase(ConstIterator pos, Iterator* outNext = nullptr);


	/**
	 * @brief 先頭のデータの位置のイテレータを取得する
	 *
	 * @return Iterator 先頭のデータの位置のイテレータ
	 */
	Iterator begin();

	/**
	 * @brief （読み取り専用）先頭のデータの位置のイテレータを取得する
	 *
	 * @return ConstIterator 先頭のデータの位置のイテレータ
	 */
	ConstIterator begin() const;

	/**
	 * @brief （読み取り専用）先頭のデータの位置のイテレータを取得する
	 *
	 * @return ConstIterator 先頭のデータの位置のイテレータ
	 */
	ConstIterator cbegin() const;

	/**
	 * @brief 末尾のデータの位置のイテレータを取得する
	 *
	 * @return Iterator 末尾のデータの位置のイテレータ
	 */
	Iterator end();

	/**
	 * @brief （読み取り専用）末尾のデータの位置のイテレータを取得する
	 *
	 * @return ConstIterator 末尾のデータの位置のイテレータ
	 */
	ConstIterator end() const;

	/**
	 * @brief （読み取り専用）末尾のデータの位置のイテレータを取得する
	 *
	 * @return ConstIterator 末尾のデータの位置のイテレータ
	 */
	ConstIterator cend() const;

	/**
	 * @brief 保持している要素数を返す
	 *
	 * @return int 保持している要素数
	 */
	int size() const;
private:
	Node sentinel_; ///<ダミーノード 空のときは自分自身を指す
	int count_ = 0; ///<現在のリストの要素数

};

//テンプレートの実装はinlに記述する
#include "DoublyLinkedList.inl"
