# Modern Argument Parser for C++
This is a modern and lightweight argument parser for C++17,
made to ease the programming of any program I am building

# Usage  
The argument accepts 4 types of arguments, string, integer, float, and
boolean. Specifying the arguments to the parser ensures that a type
check is enforced. Each argument must be passed with a single dash
or a double dash, a single dash requires the user to write the
shorthand for the argument as a single character, otherwise the complete
name is required. If you wish to change the dash for another character,
it is as easy as calling the  `void setPrefix(char c)` function

To pass add an argument is as simple as creating it and adding its
properties, such as its name, shorthand, description, type and if
it is required or not.

`parser.addArgument(ap::Argument("seed", 's', "Random number generator", ap::ArgumentType::Real, true));`

To parse the arguments the `parser.parse(argc, argv)` function must be used, this function returns a boolean specifying if the parsing was
completed succesfully; in case it wasn't an error log can be queried.

A complete example of the usage of the argument parser is in the main.cpp
file.
