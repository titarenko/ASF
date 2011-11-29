#ifndef CSV_ISTREAM_ITERATOR_H
#define CSV_ISTREAM_ITERATOR_H

#include <iterator>

#include "from_string.h"

template <class T>
class csv_istream_iterator : public std::iterator<std::input_iterator_tag, T>
{
public:
    csv_istream_iterator(char delimiter = ',')
        : _input(0)
        , _delimiter(delimiter) {}

    csv_istream_iterator(std::istream& in, char delimiter = ',')
        : _input(&in)
        , _delimiter(delimiter) { ++*this; }

    csv_istream_iterator(const csv_istream_iterator<T>& rhs)
        : _input(rhs._input)
        , _delimiter(rhs._delimiter)
        , _value(rhs._value) {}

    const T operator * () const
    {
		return from_string<T>(_value);
    }

    std::istream& operator ++ ()
    {
        if(!getline(*_input, _value, _delimiter))
        {
            _input = 0;
        }

        return *_input;
    }

    bool operator != (const csv_istream_iterator & rhs) const
    {
        return _input != rhs._input;
    }

    bool operator == (const csv_istream_iterator & rhs) const
    {
        return _input == rhs._input;
    }

private:
    std::istream* _input;
    char _delimiter;
    std::string _value;
};

template <>
const std::string csv_istream_iterator<std::string>::operator * () const
{
    return _value;
}

#endif // CSV_ISTREAM_ITERATOR_H
