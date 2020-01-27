#include <iostream>
#include <string>
#include <vector>

void Test1()
{
    // The string to be printed
    std::string printString = "Dummy String\xfe";
    const char *pcstr = printString.c_str();
    
    std::cout << printString << ": \"";
    for (size_t i=0; i<printString.size(); ++i)
        std::cout << std::hex << "\\x" << ((int32_t)(pcstr[i]) & 0xFF);
    std::cout << "\"\n\n";
    
    // Initialize a string object with hex characters
    std::string name {"\x44\x75\x6d\x6d\x79\x20\x53\x74\x72\x69\x6e\x67\xfe"};
    std::cout << name << std::endl;
}

int main()
{
    Test1();
    return 0;
}
