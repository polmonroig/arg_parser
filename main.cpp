/**
 * main.cpp: Just for testing purposes, of the
 * argument parser library
 * */
#include <iostream>

#include <arg_parser.h>


int main(int argc, char* argv[]){
    // create the argument parser
    ap::ArgParser parser;
    // add desired arguments
    parser.addArgument(ap::Argument("seed", 's', "Random number generator", ap::ArgumentType::Real, true));
    parser.addArgument(ap::Argument("readOnly", 'r', "Specifies a readonly file", ap::ArgumentType::Boolean, true));
    auto enumeration = ap::Argument("size", 'S', "Size of the input", ap::ArgumentType::Enum, false); 
    enumeration.addValue("small"); // an enumeration can have different values  
    enumeration.addValue("medium");
    enumeration.addValue("big"); 
    parser.addArgument(enumeration); 
    // parse the arguments when you need to
    auto parsed = parser.parse(argc, argv);
    // if help asked print it
    if(parser.find("help")){
        std::cerr << parser.usage("example");
        return EXIT_SUCCESS;
    }
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
    // verify optional parameter 
    if(parser.find("size"))
        std::cout << "Size: " << parser.get("size") << std::endl; 

    return 0;
}
