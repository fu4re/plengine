#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <sstream>

template <typename data>
std::string toString(const data& value);

#include "ToString.inl"
#endif // !STRINGHELPER_H

