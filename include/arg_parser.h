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

            ArgParser(); 

            void addArgument(Argument const& arg);

            bool parse(int argc, char* argv[]);

            std::string log() const;

            bool find(std::string const& arg) const;

            std::string get(std::string const& arg) const;

            void setPrefix(char c);

            std::string usage(std::string const& prog) const;

        private:


            void logIncorrectFormat(std::string const& a);
            void logIncorrectType(Argument const& a);
            void logMissingArgument(Argument const& a);
            void logTooManyArguments();

            bool compareArguments();
            bool parseArg(std::string const& arg);
            static std::string getValue(std::string const& arg);
            static std::string getName(std::string const& arg);

            static const unsigned int MIN_ARG_SIZE = 2;
            char prefix = '-';



            std::map<std::string, std::string> argumentReference;
            std::list<Argument> args;
            std::string errorLog;

    };


}
