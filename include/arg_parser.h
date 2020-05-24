#include <list>
#include <map>

#include "argument.h"


namespace ap{
    /**
    * The ArgParser class makes all the heavy work into
    * interpreting the input from the user
    * */
    class ArgParser{


        public:


            void addArgument(Argument const& arg);

            bool parse(int argc, char* argv[]);

            std::string log() const;



        private:

            bool compareArguments();
            bool parseArg(std::string const& arg);
            static std::string getValue(std::string const& arg);
            static std::string getName(std::string const& arg);

            static const unsigned int MIN_ARG_SIZE = 2;
            static const char DASH = '-';



            std::map<std::string, std::string> argumentReference;
            std::list<Argument> args;
            std::string errorLog;

    };


}
