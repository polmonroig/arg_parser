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
    return std::to_string(shorthand);
}


bool Argument::isRequired() const{
    return required; 
}

/***************
 *   PRIVATE
 ***************/
