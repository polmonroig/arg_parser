#ifndef AP_ARGUMENT_H 
#define AP_ARGUMENT_H 

#include <string>
#include <list>

namespace ap{



    enum class ArgumentType{
        String,
        Integer,
        Real,
        Boolean,
        Enum 
    };


    /**
     * An argument contains different attributes such as a name,
     * a shorthand, a description, a type
     * */
    class Argument{

        public:

            Argument() = default;

            Argument(std::string const& name, char shorthand,
                    std::string const& description,
                    ArgumentType const& t, bool required);

            std::string getName() const;
            std::string getShorthand() const;
            std::string getDescription() const; 
            bool isRequired() const;
            bool typeCheck(std::string const& value) const;
            void addValue(std::string const& val); 
            std::string print() const; 


        private:

            bool checkEnum(std::string const& value) const; 
            static bool checkInteger(std::string const& value);
            static bool checkReal(std::string const& value);
            static bool isInteger(char c);
            

            /*Possible values that an argument can take, just for enums*/
            std::list<std::string> values; 
            /*Complete name of the argument*/
            std::string name;
            /*Shorthand for the argument*/
            char shorthand;
            /*Description of what the argument need to be*/
            std::string description;
            /*Specifies the type of argument that must be enterd*/
            ArgumentType type;
            /* Specifies if the argument is required as inpu*/
            bool required;

    };




}

#endif 
