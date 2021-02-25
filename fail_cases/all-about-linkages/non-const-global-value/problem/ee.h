#pragma once

int VAL = 100;  // Non-Const global variables have external linkage by default
                // Every compilation unit that includes this file will define 'VAL'
                // whose scope if global. Meaning every compilation unit is happy
                // and compiles as expected but during linking stage, the linker does
                // not know whose definition to use, and will complain saying it sees
                // duplicate definitions
                //
                // Note the same thing also applies to functions
                //