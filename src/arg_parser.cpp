#include "../include/arg_parser.h"


using namespace ap;


/**********
 *  PUBLIC
 ***********/

void ArgParser::addArgument(Argument const& arg){
    args.push_back(arg);
}

bool ArgParser::parse(int argc, char* argv[]){
    for(auto i = 1; i < argc; ++i){
        if(!parseArg(argv[i])){
            errorLog += "Incorrect argument format found at ";
            errorLog += argv[i];
            errorLog += "\n";
        }
    }
    return compareArguments();
}


std::string ArgParser::log() const{
    return errorLog;
}




/**********
 *  PRIVATE
 ***********/

bool ArgParser::compareArguments(){
    for(auto const& a : args){
        auto name = a.getName();
        auto it = argumentReference.find(name);
        auto sh = a.getShorthand();
        it = argumentReference.find(name);
        if(it != argumentReference.end()){
            if(!a.typeCheck(*it)){
                errorLog += "Incorrect type found for argument " + name + "\n"; 
            }
        }
        else if(a.isRequired()){
            errorLog += "Missing required argument " + name + "\n";
        }
    }
    return errorLog.empty();
}


bool ArgParser::parseArg(std::string const& arg){
    if(arg.size() < MIN_ARG_SIZE)return false;
    if(arg[0] == DASH && arg[1] == DASH){ // completename
        auto value = getValue(arg);
    }
    else if(arg[0] == DASH){ // shorthand
        char shorthand = arg[1];
        auto value = getValue(arg);
    }

    return false;
}

std::string ArgParser::getValue(std::string const& arg){
    std::string value;
    unsigned int i = 0;
    while(i < arg.size() && arg[i] != '=')++i;
    if(i < arg.size()){
        while(i < arg.size())value += arg[i];
    }
    return value;
}
