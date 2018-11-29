#include "Storage.h"

Storage::Storage()
{ }

Storage::~Storage()
{
	for (Shape* s : shapes) {
		delete s;
	}
}

