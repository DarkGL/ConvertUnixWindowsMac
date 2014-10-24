#include "FileConvert.h"

FileConvert::FileConvert( std::string currentFilePath ){
    this -> streamFile.open( currentFilePath , std::fstream::in | std::fstream::out | std::fstream::binary );

    this -> filePath = currentFilePath;
}

FileConvert::~FileConvert(){
    if( this -> streamFile.is_open() ){
        this -> streamFile.close();
    }
}

bool FileConvert::replace(){
    if( !( this -> streamFile.is_open() ) ){
        return false;
    }

    char dataBuffer;

    boost::filesystem::path tempPath = boost::filesystem::unique_path();

    std::ofstream outputStream;

    outputStream.open( tempPath.string() , std::ofstream::out | std::ofstream::binary );

    this -> streamFile.unsetf( std::ios_base::skipws );
    outputStream.unsetf( std::ios_base::skipws );

    bool replaceNew = false;

    while( !( this -> streamFile.eof() ) ){
        this -> streamFile >> dataBuffer;

        if( replaceNew && dataBuffer == '\n' ){
            replaceNew = false;

            continue;
        }
        else if( dataBuffer != '\r' && dataBuffer != '\n' ){
            outputStream << dataBuffer;
        }
        else{
            if( dataBuffer == '\r' ){
                replaceNew = true;
            }

            switch( this -> getType() ){
                case 1:{
                    outputStream << '\r';
                    break;
                }
                case 2:{
                    outputStream << '\n';
                    break;
                }
                case 3:{
                    outputStream << '\r' << '\n';
                    break;
                }
            }
        }
    }

    streamFile.close();
    outputStream.close();

    std::ifstream currentFile;
    std::ofstream newFile;

    currentFile.open( tempPath.string() , std::ifstream::in | std::ifstream::binary );
    newFile.open( this -> filePath , std::ofstream::out | std::ofstream::binary | std::ofstream::trunc );

    currentFile.unsetf( std::ios_base::skipws );
    newFile.unsetf( std::ios_base::skipws );

    while( !( currentFile.eof() ) ){
        currentFile >> dataBuffer;

        newFile << dataBuffer;
    }

    currentFile.close();
    newFile.close();

    if( boost::filesystem::exists( tempPath ) ){
        boost::filesystem::remove( tempPath );
    }

    return true;
}

void FileConvert::setTypeReplace( int type ){
    this -> typeConvert = type;
}

int FileConvert::getType(){
    return this -> typeConvert;
}
