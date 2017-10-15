#include <iostream>

#include "logManager.h"
#include "logReader.h"
#include "spamFilter.h"

const int gBufSize = 1024;

int main() {
    std::cout << __cplusplus << std::endl;

    auto mgr = std::make_shared<CLogManager>();

    bool ok = mgr->readLogDir(".");
    if(!ok)
        return 1;

    auto files = mgr->getFiles();

    auto spam = std::make_shared<CSpamFilter>();

    auto rdr = std::make_shared<CLogReader>();
    //rdr->setFilter("from=*&to=*&message=*");
    rdr->setFilter("Xcode*");
    for(const auto& p : files){
        if(!rdr->open(p.c_str()))
            return 2;

        char sBuf[gBufSize + 1] = {0};
        while (rdr->getNextLine(sBuf, gBufSize)){
            spam->check(sBuf);
            std::cout << sBuf << std::endl;
            memset(sBuf, 0, sizeof(sBuf));
        }

        rdr->close();
    }



    return 0;
}