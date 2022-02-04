#include "Sorts.h"
#include "Visualizer/Visualizer.h"

void heapify(std::vector<uint32_t>* data, const int& length, const int& index, uint32_t& step) {
    int largest = index;
    int left    = 2 * index + 1;
    int right   = 2 * index + 2;
   
    State state;
    // If left child is larger than root
    if (left < length && data->at(left) > data->at(largest))
        largest = left;

    // If right child is larger than largest so far
    if (right < length && data->at(right) > data->at(largest))
        largest = right;

    state.first_value = index;
    state.second_value = largest;
    // If largest is not root
    if (largest != index) {
        std::swap(data->at(index), data->at(largest));      
        state.swap = true;  
        state.step = step;
        state.step = step;
        Visualizer::AddState(state);
        step++;
        // Recursively heapify the affected sub-tree
        heapify(data, length, largest, step);
    }
}

void Sorts::HeapSort(std::vector<uint32_t>* data) {
    uint32_t length = data->size();
    // Build heap (rearrange array)
    static uint32_t step;
    for (int i = length / 2 - 1; i >= 0; i--)
        heapify(data, length, i, step);
    State state;
    // One by one extract an element from heap
    for (int i = length - 1; i > 0; i--) {
        // Move current root to end
        std::swap(data->at(0), data->at(i));     
        state.first_value = 0;
        state.second_value = i;
        state.swap = true;
        Visualizer::AddState(state);
        // call max heapify on the reduced heap
        heapify(data, i, 0, step);
    }
    state.first_value = -1;
    state.second_value = -1;
    Visualizer::AddState(state);
}