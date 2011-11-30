#ifndef ASFFILE_H
#define ASFFILE_H

#include <istream>
#include <map>
#include <string>
#include <vector>

#include "AsfFrame.h"

/*!
    ASF header as key/value storage.
*/
typedef std::map<std::string, std::string> asf_head;

/*!
    Represents ASF file. Consists of header (key/value storage)
    and body (ASF frames themselves). Provides methods for
    reading and writing of ASF files (both plain and compressed).
    Determines format (plain or compressed) using file extension.
*/
class AsfFile
{
public:
    /*!
        Opens ASF file with provided fileName. If file supports
        positioning then memory limit can be applied in order
        not to load all the frames of file, but only necessary.
        Supports both plain (.asf) and compressed (.asf.gz) files.
        Compressed files don't support positioning, thus memory
        limit would be ignored while operating on them.
    */
    AsfFile(const char* fileName, int memoryLimitInBytes = 0);

    /*!
        Closes ASF file. Frees allocated resources.
    */
    ~AsfFile();

    /*!
        Returns number of frames.
    */
    int getFramesCount() const;

    /*!
        Returns frame with provided index starting from 0.
    */
    AsfFrame& getFrame(int index);

    /*!
        Returns header (key/value storage).
    */
    const asf_head& getHead() const;

    /*!
        Writes ASF file (both plain and gzipped ones
        are supported - format is determined using file
        extension).
    */
    void save(const char* fileName);

private:
    std::istream* _stream;
    bool _isPositioningDenied;

    asf_head _head;
    std::vector<AsfFrame> _body;

    int _memoryLimitInBytes;

    void readHead();
    void readBody();
};

#endif // ASFFILE_H
