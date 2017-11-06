//
// Created by null on 15.10.2017.
//

#include <string>
#include <iostream>
#include <fstream>

#include "spamFilter.h"

CSpamFilter::CSpamFilter(const std::string& aCfgFile) {
    std::ifstream stream;
    stream.open(aCfgFile, std::ifstream::in);
    if(stream.fail())
    {
        std::cerr << "Unable to open file " << aCfgFile << std::endl;
    }

    // parse xml rules


}


int CSpamFilter::check(const char*){
    // check rules

    return 0;
}