#include "AsfFrame.h"
#include "Exception.h"
#include "csv_istream_iterator.h"

AsfFrame::AsfFrame(int width, int height, int timestamp, std::istream& stream)
    : _stream(&stream)
    , _offset(stream.tellg())
    , _width(width)
    , _height(height)
    , _timestamp(timestamp)
    , _loaded(false)
{
    read();
}

int AsfFrame::getWidth() const
{
    return _width;
}

int AsfFrame::getHeight() const
{
    return _height;
}

int AsfFrame::getTimestamp() const
{
    return _timestamp;
}

int AsfFrame::getData(int x, int y)
{
    if (!_loaded)
    {
        load();
    }

    return _data[y*_width + x];
}

char* AsfFrame::getData()
{
    if (!_loaded)
    {
        load();
    }

    return &_data[0];
}

int AsfFrame::getUsedBytesCount() const
{
    return _width*_height*_loaded;
}

void AsfFrame::shrink()
{
    std::vector<char> other;
    _data.swap(other);
    _loaded = false;
}

void AsfFrame::read()
{
    std::string line;
    for (int rowIndex = 0; rowIndex < _height; ++rowIndex)
    {
        if (!std::getline(*_stream, line))
        {
            THROW_EXCEPTION("Can't read next row of ASF frame.");
        }
    }
}

void AsfFrame::load()
{
    std::string line;
    std::istringstream substream;

    _stream->seekg(_offset, std::ios::beg);
    _data.resize(_width*_height);

    for (int rowIndex = 0; rowIndex < _height; ++rowIndex)
    {
        if (!std::getline(*_stream, line))
        {
            THROW_EXCEPTION("Can't read next row of ASF frame.");
        }

		substream.clear();
        substream.str(line);
		
        std::copy(csv_istream_iterator<int>(substream),
                  csv_istream_iterator<int>(),
                  _data.begin() + rowIndex*_width);
    }

    _loaded = true;
}
