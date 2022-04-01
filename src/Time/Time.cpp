#include "Time.hpp"

#include <chrono>
#include <ctime>
#include <stdlib.h>

double Time::Since(Time* time)
{
    std::chrono::duration<double> elapsed = Now() - time->Started();

    return elapsed.count();
}

const char* Time::String()
{
    time_t tt = std::chrono::high_resolution_clock::to_time_t(_started);
    auto lc = localtime(&tt);
    char* strTime = (char*) malloc( sizeof(char) * 20 ); 
    strftime(strTime, 20, "%Y-%m-%d %H:%M:%S", lc);
    return strTime;
}
