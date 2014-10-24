#pragma once

#include <string>

class Config
{
    public:
        void setInput( std::string inputString );

        std::string getInput();

        void setType( int type );

        int getType();

    private:
        std::string input;

        int type = 0;
};
