#ifndef ASFFILE_H
#define ASFFILE_H

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "AsfFrame.h"

typedef std::map<std::string, std::string> asf_head;

class AsfFile
{
public:
    AsfFile(const char* fileName, int memoryLimitInBytes = 0);

    int getFramesCount() const;

    AsfFrame& getFrame(int index);

    const asf_head& getHead() const;

private:
    std::ifstream _stream;
    asf_head _head;
    std::vector<AsfFrame> _body;

    int _memoryLimitInBytes;

    void readHead();
    void readBody();
};

#endif // ASFFILE_H
