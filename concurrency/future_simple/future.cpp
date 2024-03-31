#include <iostream>
#include <future>
#include <chrono>
#include <thread>

int sleepyhead()
{
    auto num = 0;
    while( num < 10 )
    {
        std::cout << num << std::endl;
        std::chrono::milliseconds m(1000);
        std::this_thread::sleep_for(m);
        ++num;
    }

    return num;
}

int main()
{
    auto f = std::async(std::launch::async, sleepyhead);
    std::cout << "Value returned after the async task has finished = " << f.get() << std::endl;

    f = std::async(std::launch::deferred, sleepyhead);
    std::cout << "Value returned after the deferred task has finished = " << f.get() << std::endl;

    return 0;
}




