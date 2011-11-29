#ifndef FROM_STRING_H
#define FROM_STRING_H

#include <string>
#include <sstream>

template <class T>
T from_string(const std::string& string)
{
    std::istringstream stream(string);
    T value;
    stream >> value;
    return value;
}

#endif // FROM_STRING_H
