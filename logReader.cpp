//
// Created by null on 15.10.2017.
//

#include "logReader.h"


#include <iostream>

bool CLogReader::open(const char* aPath){

    mStream.open(aPath, std::ifstream::in);
    if(mStream.fail())
    {
        std::cerr << "Unable to open file " << aPath << std::endl;
        return false;
    }
    return true;
}

void CLogReader::close(){
    mStream.close();
}

bool CLogReader::addFilter(const char* aFilter){
    // replace
    // order*closed => (order)(.*)(closed)
    //
    // add slashes before special chars
    // [ { ( ) } ] . \ / ^

    bool isChar = false;
    std::string out;
    std::string src(aFilter);

    for(u_long i = 0; i < src.length(); i++){
        switch (src.at(i)){
            case '[':
            case ']':
            case '(':
            case ')':
            case '{':
            case '}':
            case ':':
            case '.':
            case '/':
            case '\\':
                if (!isChar)
                    out += '(';

                out += '\\';
                out += src.at(i);
                isChar = true;
                break;

            case '*':
            case '?':
                if (isChar)
                    out += ')';
                out += '(';
                out += '.';
                out += src.at(i);
                out += ')';
                isChar = false;

                break;
            default:
                if (!isChar)
                    out += '(';
                out += src.at(i);
                isChar = true;
                break;
        }
    }
    if(isChar)
        out += ')';

    std::regex filter;
    filter.assign(out, std::regex::ECMAScript);

    mFilters.push_back(filter);

    return true;
}

bool CLogReader::getNextLine(char* aBuf, const int aSize){
    if(!mStream.is_open() || mStream.fail())
        return false;

    std::string line;
    bool result = false;
    do {
        std::getline(mStream, line);
        if (mStream.fail())
            return false;

        std::smatch what;
        for(const auto& filter : mFilters){
            result = std::regex_search(line, what, filter);
            if (result) {
                auto rest = line.length() - what.position();
                if (aSize < rest)
                    rest = aSize;
                memcpy(aBuf, line.substr(what.position(), rest).c_str(), rest);
                break;
            }
        }

    }
    while (!result);

    return true;
}