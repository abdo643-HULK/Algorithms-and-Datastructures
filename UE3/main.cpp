#include <iostream>
#include "MinHeap.hpp"

using namespace std;

int main() {
    const auto end = "\n";

    MinHeap heap(20);


    heap.insert(5);
    heap.insert(3);
    heap.insert(19);
    heap.insert(10);
    heap.insert(88);
    heap.insert(16);
    heap.insert(6);
    heap.insert(22);
    heap.insert(8);



    cout << "Empty: " << (heap.isEmpty() ? "true" : "false") << end;
    cout << "Size: " << heap.size() << end;

    cout << end;
    cout << heap.toString() << end;
    cout << end;

    cout << "Min: " << heap.min() << end;

    cout << "RemovedMin: " << heap.removeMin() << end;

    cout << end;
    cout << heap.toString() << end;
    cout << end;

    return 0;
}


// Early Test functions
//int64_t parent(const int heap[], int nrElements, int index) {
//    const int idx = (int) (index - 1) / 2;
//    if (idx < 0 || idx > nrElements - 1) return numeric_limits<int64_t>::min();
//    return heap[idx];
//}
//
//int64_t leftChild(const int heap[], int nrElements, int index) {
//    const int idx = (2 * index) + 1;
//    if (idx < 0 || idx > nrElements - 1) return numeric_limits<int64_t>::min();
//    return heap[idx];
//}
//
//int64_t rightChild(const int heap[], int nrElements, int index) {
//    const int idx = (2 * index) + 2;
//    if (idx < 0 || idx > nrElements - 1) return numeric_limits<int64_t>::min();
//    return heap[idx];
//}
