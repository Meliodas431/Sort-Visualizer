#include "Sorts.h"
#include "Visualizer/Visualizer.h"

inline uint32_t getMaxShift(const std::vector<uint32_t>& data, const uint32_t& length) {
    uint32_t mx = data.at(0);
    for (uint32_t i = 0; i < length; i++)
        if (data.at(i) > mx)
            mx = data.at(i);
    uint32_t max{ 0 };
    for (uint32_t exp = 1; mx / exp > 0; exp *= 10)
        max++;
    return max;
}

void Sorts::RadixSort256(std::vector<uint32_t>* data) {
    uint32_t length = data->size();
    auto Output = new std::vector<uint32_t>(length, 0);
    uint32_t i, count[256] = { 0 };
    auto OriginalArr = data;
    uint32_t max = getMaxShift(*data, length);

#define index (data->at(i) >> s) & 0xff
    for (uint32_t shift = 0, s = 0; shift < max; shift++, s += 8) {
        // Zero the counts
        //memset(count, 0, 256);
         for (i = 0; i < 256; i++)
             count[i] = 0;

         // Store count of occurrences in count[]
        for (i = 0; i < length; i++) {
            count[index]++;
            State state;
            state.first_value = i;
            Visualizer::AddState(state);
        }

        // Change count[i] so that count[i] now contains actual
        // position of this digit in output[]
        for (i = 1; i < 256; i++)
            count[i] += count[i - 1];

        // Build the output data
        for (int i = length - 1; i >= 0; i--) {
            int a = data->at(i) >> s;
            int b = a & 0xff;
            Output->at(--count[index]) = data->at(i); 
        }

        State state;
        state.rebuilded = *Output;
        Visualizer::AddState(state);

        // switch pointers
        auto tmp = data;
        data = Output;
        Output = tmp;
    }

    if (OriginalArr == Output) {
        auto tmp = data;
        data = Output;
        Output = tmp;
    }
    delete Output;
}