#ifndef GETTABLE_H
#define GETTABLE_H

#include "Object.h"

class Gettable : public Object
{
private:
public:
	float price;
	bool taken;

	Gettable();

	bool isGettable() {return true;};
	float getPrice() {return price;};
	virtual bool getTaken() {return taken;};
	void setTaken(bool taken) {this->taken = taken;};
};

#endif