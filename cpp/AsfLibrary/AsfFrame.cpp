#include "AsfFrame.h"
#include "Exception.h"
#include "csv_istream_iterator.h"

#include <algorithm>

AsfFrame::AsfFrame(int width, int height, int timestamp, std::istream& stream,
                   bool isPositioningDenied = false)
    : _stream(&stream)
    , _offset(isPositioningDenied ? -1 : (int) stream.tellg())
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
    // don't perform shrink as frame won't be loaded
    // again since positioning is denied
    if (_offset == -1) return;

    std::vector<char> other;
    _data.swap(other);

    _loaded = false;
}

class writer
{
public:
    writer(std::ostream& stream, int width)
        : _stream(stream)
        , _width(width)
        , _index(0) {}

    void operator () (unsigned char value)
    {
        _stream << (int) value;
        if (++_index == _width)
        {
            _stream << std::endl;
            _index = 0;
        }
        else
        {
            _stream << ",";
        }
    }

private:
    std::ostream& _stream;
    int _width;
    int _index;
};

void AsfFrame::save(std::ostream &stream, int number)
{
    if (!_loaded)
    {
        getData();
    }

    stream << std::endl;
    stream << "Frame " << number;
    if (_timestamp != -1)
    {
        stream << ", timestamp " << _timestamp;
    }
    stream << std::endl;

    std::for_each(_data.begin(), _data.end(), writer(stream, _width));
}

void AsfFrame::read()
{
    if (_offset != -1)
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
    // eagerly load data because frame won't be loaded
    // later since positioning is denied
    else
    {
        load();
    }
}

void AsfFrame::load()
{
    std::string line;
    std::istringstream substream;

    // if positioning is not denied
    if (_offset > 0)
    {
        _stream->seekg(_offset, std::ios::beg);
    }

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
