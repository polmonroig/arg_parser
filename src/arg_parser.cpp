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


bool ArgParser::find(std::string const& arg) const{
    return argumentReference.find(arg) != argumentReference.end();
}

std::string ArgParser::get(std::string const& arg) const{
    return argumentReference.find(arg)->second;
}




/**********
 *  PRIVATE
 ***********/

bool ArgParser::compareArguments(){
    if(args.size() < argumentReference.size())
        errorLog += "Passing too many arguments\n";
    for(auto const& a : args){
        auto name = a.getName();
        auto it = argumentReference.find(name);
        auto sh = a.getShorthand();
        it = argumentReference.find(name);
        auto sit = argumentReference.find(sh);
        if(it != argumentReference.end()){
            if(!a.typeCheck(it->second)){
                errorLog += "Incorrect type found for argument " + name + "\n";
            }
        }
        else if(sit != argumentReference.end()){
            if(!a.typeCheck(sit->second)){
                errorLog += "Incorrect type found for argument " + name + "\n";
            }
            if(sit != argumentReference.end()){
                auto val = sit->second;
                argumentReference.erase(sit);
                argumentReference.insert({name,  val});
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
        auto name = getName(arg);
        auto value = getValue(arg);
        argumentReference.insert({name, value});
        return true;
    }
    else if(arg[0] == DASH){ // shorthand
        char shorthand = arg[1];
        auto value = getValue(arg);
        argumentReference.insert({std::to_string(shorthand), value});
        return true;
    }

    return false;
}

std::string ArgParser::getName(std::string const& arg){
    std::string value;
    bool isEqual = false;
    for(int i = 2; i < arg.size() && !isEqual; ++i){
        if(arg[i] == '=')isEqual = true;
        else value += arg[i];
    }
    return value;
}

std::string ArgParser::getValue(std::string const& arg){
    std::string value;
    unsigned int i = 0;
    while(i < arg.size() && arg[i] != '=')++i;
    if(i < arg.size()){
        ++i;
        while(i < arg.size()){
            value += arg[i];
            ++i;
        }
    }
    return value;
}
