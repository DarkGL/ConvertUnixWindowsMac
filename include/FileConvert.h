#pragma once

#include <iostream>

#include <string>
#include <fstream>
#include <cstdio>

#include <boost/filesystem.hpp>

class FileConvert
{
    public:
        FileConvert( std::string filePath );
        ~FileConvert();

        bool replace();

        void setTypeReplace( int type );
        int getType();
    private:
        int typeConvert = 0;

        std::fstream streamFile;

        std::string filePath;
};
