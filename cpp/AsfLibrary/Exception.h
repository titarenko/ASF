#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

/*!
    For internal use.
*/
class Exception : public std::exception
{
public:
    Exception(const char* what) : _what(what) {}
    ~Exception() throw() {}

    const char* what() const throw() { return _what.c_str(); }

private:
    std::string _what;
};

/*!
    For internal use.
*/
#define __TO_STRING(what) #what

/*!
    For internal use.
*/
#define __WHAT(message, file, line, date, time) \
        message " (" file ": " __TO_STRING(line) ", built at " date " " time ")"

/*!
    Throws standard exception with given message and
    information about source file name, line and build date.
*/
#define THROW_EXCEPTION(message) throw Exception( \
        __WHAT(message, __FILE__, __LINE__, __DATE__, __TIME__))


#endif // EXCEPTION_H
