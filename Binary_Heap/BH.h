#pragma once
#include <string>	
#include "DA.h"

namespace BH {

	template <typename T>
	class BinHeap {

		DA::DynArr<T> heap;

		size_t NodeParentIndex(size_t index) const {
			return (index - 1) / 2;
		}

		size_t NodeLeftIndex(size_t index) const {
			return (2 * index + 1);
		}

		size_t NodeRightIndex(size_t index) const {
			return (2 * index + 2);
		}

		void HeapifyUp() {

		}

		void HeapifyDown() {

		}

	public:
		BinHeap() {

		}

		~BinHeap() {
			heap.Erase();
		}

		size_t Size() const {
			return heap.Size();
		}

		size_t Capacity() const {
			return heap.Capacity();
		}

		bool IsEmpty() const {
			return heap.IsEmpty();
		}

		bool Push(T data, bool (*cmp)(T, T) = nullptr) {

		}

		bool Pop(size_t index = size - 1) {

		}

		T ExtractRoot(bool (*cmp)(T, T) = nullptr) {

		}

		bool Erase() {
			return heap.Erase();
		}

		const T& operator[](size_t index) const {
			return heap[index];
		}

		std::string ToString(unsigned int limit = 0, std::string(*str)(T) = nullptr) const {
			std::string text = ">>> Binary Heap <<<\n";
			text += "based on: \n";

			text += heap.ToString(limit, str);

			return text;
		}
	};
}