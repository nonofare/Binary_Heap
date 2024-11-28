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

		bool HeapifyUp(size_t index, bool (*cmp)(T, T) = nullptr) {
			if (index >= heap.Size()) {
				return false;
			}

			if (cmp) {
				if (cmp(heap[index], heap[NodeParentIndex(index)])) {
					Swap(index, NodeParentIndex(index));
					return HeapifyUp(NodeParentIndex(index), cmp);
				}

				return true;
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				if (heap[index] > heap[NodeParentIndex(index)]) {
					Swap(index, NodeParentIndex(index));
					return HeapifyUp(NodeParentIndex(index), cmp);
				}

				return true;
			}
			else {
				return false;
			}
		}

		bool HeapifyDown(size_t index, bool (*cmp)(T, T) = nullptr) {
			if (index >= heap.Size()) {
				return false;
			}

			if (cmp) {
				if (cmp(heap[index], heap[NodeLeftIndex(index)])) {
					Swap(index, NodeLeftIndex(index));
					return HeapifyDown(NodeLeftIndex(index), cmp);
				}
				if (cmp(heap[index], heap[NodeRightIndex(index)])) {
					Swap(index, NodeRightIndex(index));
					return HeapifyDown(NodeRightIndex(index), cmp);
				}

				return true;
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				if (heap[index] > heap[NodeLeftIndex(index)]) {
					Swap(index, NodeLeftIndex(index));
					return HeapifyDown(NodeLeftIndex(index), cmp);
				}
				if (heap[index] > heap[NodeRightIndex(index)]) {
					Swap(index, NodeRightIndex(index));
					return HeapifyDown(NodeRightIndex(index), cmp);
				}

				return true;
			}
			else {
				return false;
			}
		}

		void Swap(size_t index1, size_t index2) {
			T temp = heap[index1];

			heap[index1] = heap[index2];
			heap[index2] = temp;
		}

	public:
		BinHeap() {

		}

		~BinHeap() {
			Erase();
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
			if (!heap.Push(data)) {
				return false;
			}
			if (!HeapifyUp(heap.Size() - 1)) {
				return false;
			}

			return true;
		}

		void Pop(size_t index = 0, bool (*cmp)(T, T) = nullptr) {
			if (heap.IsEmpty()) {
				throw std::out_of_range("Heap is empty!");
			}

			T node = heap[index];
			Swap(index, heap.Size() - 1);
			heap.Pop(heap.Size() - 1);
			HeapifyDown(index, cmp);
		}

		T Poll(bool (*cmp)(T, T) = nullptr) {
			if (heap.IsEmpty()) {
				throw std::out_of_range("Heap is empty!");
			}

			T root = heap[0];
			Pop(0, cmp);

			return root;
		}

		bool Erase() {
			return heap.Erase();
		}

		std::string ToString(unsigned int limit = 0, std::string(*str)(T) = nullptr) const {
			std::string text = ">>> Binary Heap <<<\n";
			text += "is based on\n";

			text += heap.ToString(limit, str);

			return text;
		}
	};
}