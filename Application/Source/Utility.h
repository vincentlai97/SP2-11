#ifndef UTILITY_H
#define UTILITY_H

#include "Mtx44.h"
#include "Vertex.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

Position operator*(const Mtx44& lhs, const Position& rhs);

template <typename T>
std::string to_string(T const& value)
{
	std::stringstream sstr;
	sstr << std::setprecision(5) << value;
	return sstr.str();
}
template <typename T>
std::string to_price(T const& value)
{
	std::stringstream sstr;
	sstr << std::fixed << std::setprecision(2) << value;
	return sstr.str();
}

#endif