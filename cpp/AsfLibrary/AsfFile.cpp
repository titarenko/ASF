#include "AsfFile.h"
#include "Exception.h"
#include "from_string.h"

#include <fstream>
#include <numeric>
#include <algorithm>
#include <string>

#include "gzstream.h"

AsfFile::AsfFile(const char *fileName, int memoryLimitInBytes)
    : _memoryLimitInBytes(memoryLimitInBytes)
{
    char last = *std::string(fileName).rbegin();
    if (last == 'z')
    {
        _stream = (std::istream*) new igzstream(fileName,
            std::ios::in | std::ios::binary);
    }
    else if (last == 'f')
    {
        _stream = new std::ifstream(fileName,
            std::ios::in | std::ios::binary);
    }
    else
    {
        THROW_EXCEPTION("Unknown file format.");
    }

    if (!_stream->good())
    {
        THROW_EXCEPTION("Can't open ASF file.");
    }

    readHead();
    readBody();
}

AsfFile::~AsfFile()
{
    delete _stream;
}

int AsfFile::getFramesCount() const
{
    return _body.size();
}

int addUsedBytesCount(int totalAmount, const AsfFrame& frame)
{
   return totalAmount + frame.getUsedBytesCount();
}

void shrink(AsfFrame& frame)
{
    frame.shrink();
}

AsfFrame& AsfFile::getFrame(int index)
{
    if (_memoryLimitInBytes && _memoryLimitInBytes <
            std::accumulate(_body.begin(), _body.end(), 0, addUsedBytesCount))
    {
        std::for_each(_body.begin(), _body.end(), shrink);
    }

    return _body[index];
}

const asf_head& AsfFile::getHead() const
{
    return _head;
}

void AsfFile::readHead()
{
    bool foundAsciiData = false;

    std::string line;
    while (!foundAsciiData && std::getline(*_stream, line))
    {
        int index = line.find(' ');

        std::string key(line.begin(), line.begin() + index);
        std::string value(line.begin() + index + 1, line.end());

        if (_head.find(key) != _head.end())
        {
            THROW_EXCEPTION("Duplicate key was found in ASF head.");
        }

        if (key == "ASCII_DATA")
        {
            foundAsciiData = true;
        }
        else
        {
            _head[key] = value;
        }
    }

    if (!foundAsciiData)
    {
        THROW_EXCEPTION("ASF head is not followed by ASF body.");
    }
}

void AsfFile::readBody()
{
    int frameWidth = from_string<int>(_head["COLS"]);
    int frameHeight = from_string<int>(_head["ROWS"]);

    int framesCount = from_string<int>(_head["END_FRAME"]) -
            from_string<int>(_head["START_FRAME"]) + 1;

    std::string line;
    while (framesCount--)
    {
        if (!std::getline(*_stream, line))
        {
            THROW_EXCEPTION("There is no blank line before ASF frame definition.");
        }

        if (!std::getline(*_stream, line))
        {
            THROW_EXCEPTION("There is no ASF frame header.");
        }

        int timestamp = -1;

        int index = line.find("p");
        if (index >= 0)
        {
            std::string string(line.begin() + index + 1, line.end());
            timestamp = from_string<int>(string);
        }

        _body.push_back(AsfFrame(frameWidth, frameHeight,
                                 timestamp, *_stream));
    }
}
