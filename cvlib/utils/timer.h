#ifndef CVCRAYON_UTILS_TIMER_H
#define CVCRAYON_UTILS_TIMER_H

#include <chrono>
#include <functional>
#include <map>
#include <iostream>
#include <string>

#define GUARDED_TIMER \
	utils::GuardedTimer guarded_timer(__FUNCTION__)

#define TOTAL_TIMER \
	utils::TotalTimer total_timer(__FUNCTION__)

namespace utils
{
	class Timer
	{
	public:
		using Clock = std::chrono::high_resolution_clock;

		Timer() { restart(); }

		// return current unix timestamp
		void restart() {
			start_time = Clock::now();
		}

		// return duration in seconds
		double duration() const {
			const auto now = Clock::now();
			const auto m = std::chrono::duration_cast<std::chrono::microseconds>(now - start_time).count();
			return m * 1.0 / 1e6;
		}

	protected:
		std::chrono::time_point<Clock> start_time;
	};

	class GuardedTimer : public Timer
	{
	public:
		GuardedTimer(const char* msg, bool enabled = true) :
			GuardedTimer(std::string(msg), enabled) {}

		GuardedTimer(const std::string& msg, bool enabled = true) :
			GuardedTimer([msg](double duration) {
			std::cout << msg << ": " << std::to_string(duration * 1000.) << " milliseconds." << std::endl;
		})
		{
			enabled_ = enabled;
		}

		GuardedTimer(std::function<void(double)> callback) :
			m_callback(callback)
		{ }

		~GuardedTimer() {
			if (enabled_)
				m_callback(duration());
		}

	private:
		std::function<void(double)> m_callback;
		bool enabled_;
	};

	// record the total running time of a region across the lifecycle of the whole program
	// call TotalTimer::print() before exiting main()
	class TotalTimer
	{
	public:
		std::string msg;
		Timer timer;

		TotalTimer(const std::string& msg) :
			msg(msg) {
			timer.restart();
		}

		~TotalTimer();
		static void print();
		static std::map<std::string, std::pair<int, double>> rst;
	};

	// Build a global instance of this class, to call print() before program exit.
	struct TotalTimerGlobalGuard {
		~TotalTimerGlobalGuard() { TotalTimer::print(); }
	};
}




#endif // !CV_CRAYON_UTILS_TIMER_H

