/**
 * main.cpp: Just for testing purposes, of the
 * argument parser library
 * */
#include <iostream>

#include "include/arg_parser.h"


int main(int argc, char* argv[]){
    // create the argument parser
    ap::ArgParser parser;
    // add desired arguments
    parser.addArgument(ap::Argument("seed", 's', "Random number generator", ap::ArgumentType::Real, true));
    parser.addArgument(ap::Argument("readOnly", 'r', "Specifies a readonly file", ap::ArgumentType::Boolean, true));
    // parse the arguments when you need to
    auto parsed = parser.parse(argc, argv);
    // if there was an error, print the log saved in
    // the parser and exit the program
    if(!parsed){
        std::cerr << parser.log();
        return EXIT_FAILURE;
    }
    // if an argument named readOnly was found
    // get the argument seed
    // note: seed is a required arument so we don't need to call find first 
    if(parser.find("readOnly"))
        std::cout << "Seed: " << parser.get("seed") << std::endl;

    return 0;
}
