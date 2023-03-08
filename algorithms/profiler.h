#ifndef PROFILER_H
#define PROFILER_H
#include <chrono>
#include <iostream>
using namespace std::chrono;
using namespace std;
struct Profiler{
     std::chrono::time_point<std::chrono::system_clock>  time{system_clock::now()};
     const char* name;
     Profiler(const char* nm):name(nm){}
     ~Profiler(){
         cout << "time elapsed for " << name <<"=" <<duration_cast<milliseconds>(chrono::system_clock::now() - time).count()<<"\n";
     }
};

#endif // PROFILER_H
