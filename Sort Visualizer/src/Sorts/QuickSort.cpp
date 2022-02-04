#include "Sorts.h"
#include "Visualizer/Visualizer.h"
#include <iostream>

int partition(std::vector<uint32_t>* data, const int& low, const int& high) {
    int pivot = data->at(high); // pivot 
    int i = low - 1; // Index of smaller element and indicates the right position of pivot found so far
    static uint32_t step = 1;
    State state;
    for (int j = low; j <= high - 1; j++) {     
        state.first_value = j;
        state.second_value = i+1;   
        // If current element is smaller than the pivot 
        if (data->at(j) < pivot) {
            // increment index of smaller element 
            std::swap(data->at(++i), data->at(j));
            state.swap = true;
        }   
        else {
            state.swap = false;
        }
        state.step = step++;
        Visualizer::AddState(state);
    }
    std::swap(data->at(i + 1), data->at(high));

    state.first_value = i + 1;
    state.second_value = high;
    state.swap = true;
    state.step = step++;
    Visualizer::AddState(state);
    return ++i;
}

void QuickSort(std::vector<uint32_t>* data, const int& low, const int& high) {
    if (low < high) {
        // pi is partitioning index, arr[p] is now at right place 
        int pi = partition(data, low, high);

        QuickSort(data, low, pi - 1);
        QuickSort(data, pi + 1, high);
    }
}

void Sorts::QuickSortEntry(std::vector<uint32_t>* data) {
	QuickSort(data, 0, data->size()-1);
    Visualizer::AddState({});
}
