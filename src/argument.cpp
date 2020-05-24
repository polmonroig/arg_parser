#include "../include/argument.h"


using namespace ap;


/***************
 *   PUBLIC
 ***************/

Argument::Argument(std::string const& n, char s, std::string const& d, ArgumentType const& t, bool r){
    name = n;
    shorthand = s;
    description = d;
    type = t;
    required = r;
}

std::string Argument::getName() const{
    return name;
}

std::string Argument::getShorthand() const{
    return std::string(1, shorthand);
}


bool Argument::isRequired() const{
    return required;
}

bool Argument::typeCheck(std::string const& value) const{
    switch (type) {
        case ArgumentType::String:
            return !value.empty();
        break;
        case ArgumentType::Integer:
            return checkInteger(value);
        break;
        case ArgumentType::Real:
            return checkReal(value);
        break;
        case ArgumentType::Boolean:
            return value.empty();
        break;
    }
}

std::string Argument::getDescription() const{
    return description;
}

/***************
 *   PRIVATE
 ***************/

bool Argument::checkInteger(std::string const& value){
    for(auto const& c : value){
        if(!isInteger(c))return false;
    }
    return true;
}

bool Argument::checkReal(std::string const& value){
    bool dotFound = false;
    for(auto const& c : value){
        if(c == '.' && !dotFound)dotFound = true;
        else if(c == '.' || !isInteger(c))return false; // too many dots or not int
    }
    return true;
}

bool Argument::isInteger(char c){
    int a = int(c);
    return a >= 48 && a <= 57;
}
