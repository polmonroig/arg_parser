#include "../include/arg_parser.h"


using namespace ap;


/**********
 *  PUBLIC
 ***********/

ArgParser::ArgParser(){
    args.push_back(Argument("help", 'h', "show help for arguments", ArgumentType::Boolean, false));
}

void ArgParser::addArgument(Argument const& arg){
    args.push_back(arg);
}

bool ArgParser::parse(int argc, char* argv[]){
    for(auto i = 1; i < argc; ++i){
        if(!parseArg(argv[i])){
            logIncorrectFormat(argv[i]);
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

void ArgParser::setPrefix(char c){
    prefix = c;
}

std::string ArgParser::usage(std::string const& prog) const{
    std::string u = "\nusage: " + prog + " [options]\n";
    for(auto const& a : args){
        u += a.getName() + " ("+ a.getShorthand() +") " + a.getDescription() + "\n";
    }
    return u + "\n";
}



/**********
 *  PRIVATE
 ***********/

bool ArgParser::compareArguments(){
    if(args.size() < argumentReference.size())
        logTooManyArguments();
    for(auto const& a : args){
        auto name = a.getName();
        auto it = argumentReference.find(name);
        auto sh = a.getShorthand();
        it = argumentReference.find(name);
        auto sit = argumentReference.find(sh);
        if(it != argumentReference.end()){
            if(!a.typeCheck(it->second)){
                logIncorrectType(a);
            }
        }
        else if(sit != argumentReference.end()){
            if(!a.typeCheck(sit->second)){
                logIncorrectType(a);
            }
            if(sit != argumentReference.end()){
                auto val = sit->second;
                argumentReference.erase(sit);
                argumentReference.insert({name,  val});
            }
        }
        else if(a.isRequired()){
            logMissingArgument(a);
        }
    }
    return errorLog.empty();
}


bool ArgParser::parseArg(std::string const& arg){
    if(arg.size() < MIN_ARG_SIZE)return false;
    if(arg[0] == prefix && arg[1] == prefix){ // completename
        auto name = getName(arg);
        auto value = getValue(arg);
        argumentReference.insert({name, value});
        return true;
    }
    else if(arg[0] == prefix){ // shorthand
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



void ArgParser::logIncorrectFormat(std::string const& a){
    errorLog += "Incorrect argument format found at " + a + "\n";
}

void ArgParser::logIncorrectType(Argument const& a){
    errorLog += "Incorrect type found for argument " + a.getName() + "\n";
}

void ArgParser::logMissingArgument(Argument const& a){
    errorLog += "Missing required argument " + a.getName() + "\n";
}

void ArgParser::logTooManyArguments(){
    errorLog += "Passing too many arguments\n";
}
