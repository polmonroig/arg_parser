#include <string>

namespace ap{



    enum class ArgumentType{
        String,
        Integer,
        Real,
        Boolean
    };;


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
            bool isRequired() const;
            bool typeCheck(std::string const& value) const; 



        private:


            std::string name;
            char shorthand;
            std::string description;
            ArgumentType type;
            bool required;

    };




}
