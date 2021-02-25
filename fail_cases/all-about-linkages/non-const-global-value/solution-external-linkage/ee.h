#pragma once

#include <string>
#include <map>

// With 'static' keyword force internal linkage. This means there will be one instance of 
// VAL in every 'Translation Unit'/'Compilation Unit'. And this variable's scope is only that
// particular unit and is not visible anywhere else.
extern int VAL;


// For smaller global values as integers it is fine to make them static with internal linkage,
// but for larger ones like a huge map this will result in a new instance 
// of the whole map in every compilation unit where it is added. This will result in significant
// memory bloat. So extreme caution is necessary!
extern std::map<int,std::string> NUM_MAP;


namespace T1
{
    extern std::string NON_CONST_NAME;
    extern const std::string NAME;
}