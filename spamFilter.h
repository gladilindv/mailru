//
// Created by null on 15.10.2017.
//

#ifndef MAILRU_SPAMFILTER_H
#define MAILRU_SPAMFILTER_H


class CSpamFilter {

public:
    explicit CSpamFilter() = default;
    ~CSpamFilter() = default;

    CSpamFilter& operator=(const CSpamFilter&) = delete; // disallow use of assignment operator
    CSpamFilter& operator= (CSpamFilter &&) = default; // move assignment operator
    CSpamFilter(const CSpamFilter&) = delete; // disallow copy construction

    CSpamFilter(CSpamFilter&&) = delete; // disallow move construction

    bool check(const char*);


};


#endif //MAILRU_SPAMFILTER_H
