#include <boost/filesystem.hpp>

#include <iostream>

#include <cstring>
#include <cstdio>

#include <windows.h>

#include "Config.h"
#include "FileConvert.h"

using namespace std;

void printHelp();

BOOL checkFileOrFolderExists( LPCTSTR szPath , bool checkFolder = false );

int main( int argc , char * argv[] ){

    Config currentConfig;

    if( argc == 1 ){
        printHelp();

        return 0;
    }

    for( int i = 1 ; i < argc ; i++ ){
        if( strcmp( argv[ i ] , "--help" ) == 0 ){
            printHelp();

            return 0;
        }
        else if( strcmp( argv[ i ] , "-i" ) == 0 ){
            if( i + 1 >= argc ){
                printHelp();

                return 0;
            }

            currentConfig.setInput( argv[ i + 1 ] );

            i += 1;
        }
        else if( strcmp( argv[ i ] , "-t" ) == 0 ){
            if( i + 1 >= argc ){
                printHelp();

                return 0;
            }

            int value = 0;

            sscanf( argv[ i + 1 ] , "%d", &value );

            currentConfig.setType( value );

            if( currentConfig.getType() < 1 || currentConfig.getType() > 3 ){
                printHelp();

                return 0;
            }

            i += 1;
        }
    };

    if( checkFileOrFolderExists( currentConfig.getInput().c_str() , true ) ){
        for ( boost::filesystem::recursive_directory_iterator end, dir(currentConfig.getInput().c_str());
            dir != end; ++dir ) {

            std::cout << dir -> path().string() << std::endl;

            std::string pathString( dir -> path().string() );

            FileConvert fileConvert( pathString );

            fileConvert.setTypeReplace( currentConfig.getType() );

            fileConvert.replace();
        }
    }else{
        FileConvert fileConvert( currentConfig.getInput() );

        fileConvert.setTypeReplace( currentConfig.getType() );

        fileConvert.replace();
    }

    return 0;
}

void printHelp(){
    std::cout << "Usage : exe <params>" << std::endl;
    std::cout << "\t" << "-i\t input file or directory" << std::endl;
    std::cout << "\t" << "-t\t to which type convert 1 - mac 2 - unix 3 - windows" << std::endl;
}

BOOL checkFileOrFolderExists( LPCTSTR szPath , bool checkFolder ){
	DWORD dwAttrib = GetFileAttributes( szPath );

    if( dwAttrib == INVALID_FILE_ATTRIBUTES ){
        return false;
    }

    if( checkFolder && dwAttrib & FILE_ATTRIBUTE_DIRECTORY ){
        return true;
    }

    if( !checkFolder && !( dwAttrib & FILE_ATTRIBUTE_DIRECTORY ) ){
        return true;
    }

    return false;
}
