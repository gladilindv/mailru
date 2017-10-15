//
// Created by null on 15.10.2017.
//

#ifndef MAILRU_LOGREADER_H
#define MAILRU_LOGREADER_H


#include <fstream>
#include <regex>

class CLogReader {
public:
    explicit CLogReader() = default;
    ~CLogReader() = default;

    CLogReader& operator=(const CLogReader&) = delete; // disallow use of assignment operator
    CLogReader& operator= (CLogReader &&) = default; // move assignment operator
    CLogReader(const CLogReader&) = delete; // disallow copy construction

    CLogReader(CLogReader&&) = delete; // disallow move construction


    bool open(const char*);
    void close();

    bool setFilter(const char*);
    bool getNextLine(char*, const int);

private:
    std::regex mFilter;
    std::ifstream mStream;
};



#endif //MAILRU_LOGREADER_H
