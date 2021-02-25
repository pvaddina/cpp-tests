#pragma once

const int VAL = 100;  // Const global variables have internal linkage by default
                      // This means every compilation unit that includes this file will have one instance
                      // of VAL which is only visible in that compilation/translation unit
                      //
                      // 