#include <iostream>
#include <string>
#include "helpers.hpp"

void debug(std::string s){
    if(debugmode){
        std::cout<<s<<std::endl;
    }
}
