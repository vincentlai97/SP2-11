#include "Gettable.h"

Gettable::Gettable(): Object()
{
	price = 0;
	taken = false;
}

void Gettable::set(Object other)
{
	this->price = other.getPrice();
	this->Object::set(other);
}