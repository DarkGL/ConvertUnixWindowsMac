#include "Config.h"

void Config::setInput( std::string inputString ){
    this -> input = inputString;
}

std::string Config::getInput(){
    return this -> input;
}

 void Config::setType( int newType ){
    this -> type = newType;
 }

int Config::getType(){
    return this -> type;
}
