#include "Sorts.h"
#include "Visualizer/Visualizer.h"

std::vector<uint32_t> st;
void CopyArray(std::vector<uint32_t>& A, const uint32_t& Begin, const uint32_t& End, std::vector<uint32_t>& B) {
    for (uint32_t i = Begin; i < End; i++)
        B[i] = A[i];
}

#include <iostream>
void TopDownMerge(std::vector<uint32_t>* A, const uint32_t& Begin, const uint32_t& Middle, const uint32_t& End, std::vector<uint32_t>* B) {
    uint32_t i = Begin, j = Middle;
    State state;
    // While there are elements in the left or right runs
    for (uint32_t k = Begin; k < End; k++) {
        // If left run head exists and is <= existing right run head
        if (i < Middle && (j >= End || A->at(i) <= A->at(j))) {
            B->at(k) = A->at(i);
            st[k] = A->at(i);
            i++;
        }
        else {
            B->at(k) = A->at(j);
            st[k] = A->at(j);
            j++;
        }  
        state.first_value = i;
        state.second_value = j;
        state.rebuilded = st;
        Visualizer::AddState(state);
    }
}

void TopDownSplitMerge(std::vector<uint32_t>* B, const uint32_t& Begin, const uint32_t& End, std::vector<uint32_t>* A) {
    if (End - Begin <= 1)
        return;
    uint32_t Middle = (End + Begin) / 2;
    TopDownSplitMerge(A, Begin, Middle, B);
    TopDownSplitMerge(A, Middle, End, B);
    TopDownMerge(B, Begin, Middle, End, A);
}

void Sorts::TopDownMergeSort(std::vector<uint32_t>* data) {
    uint32_t length = data->size();
    std::vector<uint32_t> B(length);
    st.resize(length);
    CopyArray(*data, 0u, length, st);
    CopyArray(*data, 0u, length, B);

    //from B to A
    TopDownSplitMerge(&B, 0u, length, data);
    State state;
    Visualizer::AddState(state);
}