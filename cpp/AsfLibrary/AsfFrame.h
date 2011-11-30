#ifndef ASFFRAME_H
#define ASFFRAME_H

#include <istream>
#include <vector>

/*!
    Represents ASF frame as timestamp
    and data as rectangular matrix of values
    (unwrapped to linear array - row by row).
*/
class AsfFrame
{
public:
    /*!
        Constructs frame of given size, with provided timestamp
        using given stream as data source. If positioning is not
        prohibited then frame will support load-on-demand (possibility
        to dynamically load/unload frame when needed in order to
        meet lower memory requirements).
    */
    AsfFrame(int width, int height,
             int timestamp, std::istream& stream,
             bool isPositioningDenied);

    /*!
        Returns width of frame.
    */
    int getWidth() const;

    /*!
        Returns height of frame.
    */
    int getHeight() const;

    /*!
        Returns timestamp of frame.
    */
    int getTimestamp() const;

    /*!
        Returns pointer to linear array with frame data.
        Loads frame if it is not loaded (but only when stream
        supports positioning).
    */
    char* getData();

    /*!
        Returns number of bytes occupied by frame data
        (size of supplementary data structures are not counted).
    */
    int getUsedBytesCount() const;

    /*!
        Unloads frame from memory (if stream supports positioning).
    */
    void shrink();

    /*!
        Saves frame using provided stream. Second parameter is
        frame number.
    */
    void save(std::ostream& stream, int number);

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
