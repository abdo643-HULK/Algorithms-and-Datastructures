#include <iostream>
#include "MinHeap.hpp"

using namespace std;

int main() {
    const auto end = "\n";

    MinHeap heap(20);

    heap.insert(12);
    heap.insert(5);
    heap.insert(15);
    heap.insert(8);
    heap.insert(53);
    heap.insert(74);
    heap.insert(35);
    heap.insert(76);
    heap.insert(4);
    heap.insert(26);
    heap.insert(7);
    heap.insert(62);
    heap.insert(7);
    heap.insert(85);
    heap.insert(25);
    heap.insert(24);
    heap.insert(75);
    heap.insert(38);
    heap.insert(8);
    heap.insert(26);
    heap.insert(77);
    heap.insert(9);
    heap.insert(5);
    heap.insert(4);

//    4 5 4 8 5 7 25 24 8 26 7 15 62 85 35 76 75 38 12 53 77 26 9 74
    cout << heap.arrayString() << end;



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
