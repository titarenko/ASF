#ifndef ASFFRAME_H
#define ASFFRAME_H

#include <istream>
#include <vector>

class AsfFrame
{
public:
    AsfFrame(int width, int height,
             int timestamp, std::istream& stream,
             bool isPositioningDenied);

    int getWidth() const;
    int getHeight() const;
    int getTimestamp() const;

    char* getData();

    int getUsedBytesCount() const;

    void shrink();

private:
    std::istream* _stream;
    int _offset;

    int _width;
    int _height;
    int _timestamp;

    std::vector<char> _data;

    bool _loaded;

    void read();
    void load();
};

#endif // ASFFRAME_H
