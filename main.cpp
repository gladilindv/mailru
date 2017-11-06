#include <iostream>

#include "logManager.h"
#include "logReader.h"
#include "spamFilter.h"

const int gBufSize = 1024;

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)> SOURCE\n"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-f,--rules file\t\tSpecify the spam rules file"
              << std::endl;
}
int main(int argc, char* argv[]) {

    // work with args
    // - path
    // - filter
    if (argc != 4) {
        show_usage(argv[0]);
        return 1;
    }

    std::string path = "./msg.log";
    std::string fltr = "./spam.xml";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help")) {
            show_usage(argv[0]);
            return 0;
        } else if ((arg == "-f") || (arg == "--filter")) {
            if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                fltr = argv[++i];
            } else { // Uh-oh, there was no argument to the destination option.
                std::cerr << "--filter option requires one argument." << std::endl;
                return 1;
            }
        } else
            path = argv[i];
    }


    auto mgr = std::make_shared<CLogManager>();
    auto rdr = std::make_shared<CLogReader>();
    //auto spam = std::make_shared<CSpamFilter>(fltr);


    bool ok = mgr->readLogDir(path.c_str());
    if(!ok)
        return 1;


    // add spam msg templates
    rdr->addFilter("отправьте смс (бесплатно)");
    rdr->addFilter("работа на дому");


    auto files = mgr->getFiles();
    for(const auto& p : files){
        if(!rdr->open(p.c_str()))
            return 2;

        char sBuf[gBufSize + 1] = {0};
        while (rdr->getNextLine(sBuf, gBufSize)){
            //int rule = spam->check(sBuf);
            //if(rule != 0)
            //    std::cout << "spam [" << rule << "] file: " << p << " data: " << sBuf << std::endl;

            std::cout << "file: " << p << " spam: " << sBuf << std::endl;

            memset(sBuf, 0, sizeof(sBuf));
        }

        rdr->close();
    }

    return 0;
}
