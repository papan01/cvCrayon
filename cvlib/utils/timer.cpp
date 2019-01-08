#include "timer.h"
#include <mutex>
#include "debugutils.h"


namespace utils
{


	TotalTimer::~TotalTimer()
	{
		static std::mutex mt;
		std::lock_guard<std::mutex> lg(mt);
		auto& p = rst[msg];
		p.second += timer.duration();
		p.first++;
	}

	void TotalTimer::print()
	{
		for (auto& itr : rst)
			PRINT_DEBUG("%s spent %lf secs in total, called %d times.\n",
				itr.first.c_str(), itr.second.second, itr.second.first);
	}
}