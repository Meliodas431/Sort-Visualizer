#pragma once
#include <vector>

struct State {
    uint32_t step    =  0;
    int first_value  = -1;
    int second_value = -1;
   bool swap         = false;
   std::vector<uint32_t> rebuilded;
};

class Sorts {
public:
    void RadixSort256(std::vector<uint32_t>* data);
    void TopDownMergeSort(std::vector<uint32_t>* data);
    void BubbleSort(std::vector<uint32_t>* data);
    void HeapSort(std::vector<uint32_t>* data);
    void QuickSortEntry(std::vector<uint32_t>* data);
};