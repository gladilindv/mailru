//
// Created by null on 15.10.2017.
//

#include "logManager.h"

#include <iostream>
#include <dirent.h>


bool CLogManager::readLogDir(const char* aLogPath) {

    DIR* d = opendir(aLogPath);

    // Check it was opened
    if (d == nullptr) {
        std::cerr << "Cannot open directory '" << aLogPath << "': " <<  strerror(errno) << std::endl;
        return false;
    }

    while (true) {

        struct dirent* entry;

        // "Readdir" gets subsequent entries from "d"
        entry = readdir(d);
        if (entry == nullptr) {
            // There are no more entries in this directory, so break out of the while loop
            break;
        }


        // only regular files
        if(entry->d_type & DT_REG) {

            size_t len = strlen(entry->d_name);
            const char *last_four = &entry->d_name[len - 4];

            if (strcmp(last_four, ".log") == 0) {
                int path_length;
                char path[PATH_MAX];

                path_length = snprintf(path, PATH_MAX, "%s/%s", aLogPath, entry->d_name);
                if (path_length >= PATH_MAX) {
                    std::cerr << "Path length has got too long" << std::endl;
                    continue;
                }

                mLogFiles.emplace_back(path);
            }
        }


        if (entry->d_type & DT_DIR) {

            // check for current or parent dir
            if (strcmp (entry->d_name, "..") == 0 ||
                strcmp (entry->d_name, ".") == 0)
                continue;

            int path_length;
            char path[PATH_MAX];

            path_length = snprintf(path, PATH_MAX, "%s/%s", aLogPath, entry->d_name);
            if (path_length >= PATH_MAX) {
                std::cerr << "Path length has got too long" << std::endl;
                continue;
            }

            // Recursively call with the new path
            readLogDir(path);
        }


    }

    /* After going through all the entries, close the directory. */
    if (closedir(d)) {
        std::cerr << "Could not close '" << aLogPath << "': " <<  strerror(errno) << std::endl;
        return false;
    }

    return true;
}
