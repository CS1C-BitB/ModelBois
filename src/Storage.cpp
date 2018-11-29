#include "Storage.h"

Storage::Storage()
    : shapes{}, model{&shapes}
{ }

Storage::~Storage()
{
	for (Shape* s : shapes) {
		delete s;
	}
}

