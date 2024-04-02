#include <iostream>
#include <future>
#include <chrono>
#include <thread>

class TTest
{
    public:
        void sleepyhead(std::promise<int>&& myprom)
        {
            std::chrono::seconds m(3);
            std::this_thread::sleep_for(m);
            myprom.set_value(324);
        }
};

int main()
{
    std::promise<int> prom;
    std::future<int> myfut = prom.get_future();

    TTest obj;
    std::thread t{&TTest::sleepyhead, obj, std::move(prom)};

    std::cout << "Waiting for the thread to provide the data:";
    std::cout << myfut.get() << std::endl;

    t.join();
    return 0;
}
