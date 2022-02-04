#pragma once
#include <chrono>

class Timer {
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> mTimePoint;
		std::chrono::time_point<std::chrono::high_resolution_clock> endTimePoind;
	public:
		Timer() {
			mTimePoint = std::chrono::high_resolution_clock::now();
		}
		Timer(const Timer& t) = delete;
		~Timer() {
			stop();
		}
		void reset() { mTimePoint = std::chrono::high_resolution_clock::now(); }
		double stop() {		
			auto start = std::chrono::time_point_cast<std::chrono::milliseconds>(mTimePoint).time_since_epoch().count();
			endTimePoind = std::chrono::high_resolution_clock::now();
			auto end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoind).time_since_epoch().count();
	
			auto ms = end - start;
			return ms;
		}
};