//
// Created by null on 15.10.2017.
//

#ifndef MAILRU_LOGMANAGER_H
#define MAILRU_LOGMANAGER_H

#include <vector>

typedef std::vector<std::string> tVecPath;


class CLogManager {

public:
    CLogManager() = default;
    ~CLogManager() = default;

    CLogManager& operator=(const CLogManager&) = delete; // disallow use of assignment operator
    CLogManager& operator= (CLogManager &&) = default; // move assignment operator
    CLogManager(const CLogManager&) = delete; // disallow copy construction

    CLogManager(CLogManager&&) = delete; // disallow move construction

    bool readLogDir(const char*);
    tVecPath getFiles(){
        return mLogFiles;
    }

private:
    tVecPath mLogFiles;

};


#endif //MAILRU_LOGMANAGER_H
