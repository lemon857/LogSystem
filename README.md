This is a *simple* library for comfort logging some text in console
# Using  
In format string `{0}` `{1}` ... was a random object, which can use in `std::to_string`.  
`0`, `1` ... sign index in arguments list after format string, for example:   
```cpp
int a = 1;
int b = 12;
LogSystem::info("A: {0}, B: {1}", a, b);
// out string: 
// A: 1, B: 12
```
# Settings  
Enable debugging in console:  
`#define __LOG_CONSOLE__`  
Enable debugging in file:  
`#define __LOG_FILE__`  
Enable debugging with date and time:  
`#define __LOG_DATETIME__`  
`#define __LOG_DATETIME_FORMAT__ "%Y-%m-%d %H:%M:%S"`

use `add_compile_definitions(param)` in CMakeLists.txt for set params