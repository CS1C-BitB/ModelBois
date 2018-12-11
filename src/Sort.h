#ifndef SORT_H
#define SORT_H

#include "Shape.h"
#include "vector.h"
#include <functional>

bool validArea(Shape* shape);
bool validPerimeter(Shape* shape);
bool validID(Shape* shape);

/**
 * @brief Copies items that meet a condition
 * @arg first Iterator to the first item to copy
 * @arg last Iterator one past the last item to copy
 * @arg out Iterator to the first item to copy to
 * @arg condition Unary predicate that returns true for items to copy
 * @return Iterator one after the last item copied
 */
template<class InputIterator, class OutputIterator, class Predicate>
OutputIterator copy_if(InputIterator first, InputIterator last, OutputIterator out, Predicate condition)
{
	for (; first != last; ++first) {
		if (condition(*first)) {
			*(out++) = *first;
		}
	}
	
	return out;
}

bool compareID(Shape* left, Shape* right);
bool compareArea(Shape* left, Shape* right);
bool comparePerimeter(Shape* left, Shape* right);

/**
 * @brief Sorts a range using a comparison object
 * @arg first Iterator to first item to sort
 * @arg last Iterator one past the last item to sort
 * @arg compare A binary comparison object
 * @return One past last item sorted (last)
 */
template<class Iterator, class Compare>
Iterator selection_sort(Iterator first, Iterator last, Compare compare)
{
	for (; first != last; ++first) {
		Iterator low = first;
		for (Iterator current = first; current != last; ++current) {
			if (compare(*current, *low)) {
				low = current;
			}
		}
		std::swap(*low, *first);
	}
	
	return last;
}

#endif // SORT_H
