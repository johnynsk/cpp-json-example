#ifndef SUPEREXCEPTION_INCLUDED
#define SUPEREXCEPTION_INCLUDED

#include <string>

class SuperException
{
    protected:
        std::string message;

    public:
        SuperException() : message("invalid operation")
        {
        }

        SuperException(const std::string &reason) : message(reason)
        {
        }

        virtual const std::string &getMessage() const
        {
            return message;
        }
};

class TypesEqualSuperException: SuperException
{
};

#endif

