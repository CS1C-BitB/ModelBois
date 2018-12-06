#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "Shapes.h"
#include "Storage.h"

#include <ostream>

std::ostream& operator<<(std::ostream& out, const vector_t &shapes);

#endif // SERIALIZER_H
