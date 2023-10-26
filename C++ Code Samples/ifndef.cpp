/*
  Filename   : ifndef.cpp
  Author     : Peter Freedman
  Description: Demo of some uses of ifndef/define blocks.
*/

//use -D macroname to define a macro at compile time (with other compile flags on g++)
//each macro needs its own -D flag

#include <iostream>
#include <cstring>

void method2(int argc);


int main(int argc, char** argv)
{
    //if DEBUGINFO exists, compile the code under ifdef
    #ifdef DEBUGINFO
    std::cout << "hello from debuginfo\n";
    //if DEBUGINFO does not exist, compile this code instead
    #else
    std::cout << "debuginfo undefined\n";
    //endif to end this block of conditional processing
    #endif

    //ifndef executes the block if the name is undefined
    #ifndef debug
    std::cout << "baby debug not defined\n";
    #endif

    method2(argc);
}

void method2(int argc)
{
  //can use macro names globally even if they aren't defined globally
    #ifdef DEBUGINFO 
    std::cout << "method2 sees DEBUGINFO\n";
    //#elif allows condition eval to define
    #elif argc > 2
    std::cout << "too many args"
    #endif
}