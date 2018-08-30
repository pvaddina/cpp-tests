#include <iostream>
#include <string>
#include <functional>
#include <memory>

template <typename T, typename... Ts>
T* make_it(Ts... ts)
{
    return new T(std::forward<Ts>(ts)...);
}

class SomeLogger
{
    public:
		SomeLogger(int arg1, std::string&& arg2)
		{
		    std::cout << "In constructor" << std::endl; 
		}

		template <typename T>
		void PrintSomeThing(const T s)
		{
		    std::cout << s << std::endl;
		}
		
		virtual void DoSomething() 
		{
		    std::cout << "Doing something in the base" << std::endl;
		}
		
        static SomeLogger* get() 
        {
            std::cout << "Getting the resource" << std::endl;
        	if (!res) 
        	{ 
        	    res = make_it<SomeLogger>(4, std::string("Some temp string")); 
        	}
        	return res;
        }

	private:
	    static SomeLogger* res;

};

SomeLogger* SomeLogger::res = nullptr;

class SpecializedLogger : public SomeLogger
{
    public:
        SpecializedLogger(std::string name, int v, std::string&& s) : SomeLogger(v, std::move(s)), mName(name) {}
        virtual void DoSomething() override
        {
            std::cout << "Doing something in the derived class" << std::endl;
        }
    private:
        std::string mName;
};

void Time2PrintStr()
{
    std::cout << "In Time2PrintStr" << std::endl;
    SomeLogger::get()->PrintSomeThing("Random blabla");
}

void Time2PrintInt()
{
    std::cout << "In Time2Printint" << std::endl;
    SomeLogger::get()->PrintSomeThing(437);
}


int main()
{
    Time2PrintStr();
    Time2PrintInt();
    return 0;
}
