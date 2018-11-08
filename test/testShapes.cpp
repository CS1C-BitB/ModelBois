
#include "Tests.h"

#include "Ellipse.h"
#include "Line.h"
#include "Polygon.h"
#include "PolyLine.h"
#include "Rectangle.h"
#include "Text.h"

#include <cmath>

bool value_within(double val, double target, double margin)
{
	return std::abs(val - target) < margin;
}

template<class Shape_T>
bool compare(const Shape_T &first, const Shape_T &second);

template<>
bool compare(const Shape &first, const Shape &second)
{
	return    first.getPos() == second.getPos()
	       && first.getBrush() == second.getBrush()
	       && first.getPen() == second.getPen();
}

template<>
bool compare(const Ellipse &first, const Ellipse &second)
{
	return    compare<Shape>(first, second)
	       && first.getWidth() == second.getWidth()
	       && first.getHeight() == second.getHeight();
}

template<>
bool compare(const Line &first, const Line &second)
{
	return    compare<Shape>(first, second)
	       && first.getStart() == second.getStart()
	       && first.getEnd() == second.getEnd();
}

template<>
bool compare(const Polygon &first, const Polygon &second)
{
	if (!compare<Shape>(first, second))
		return false;
	if (first.getCount() != second.getCount())
		return false;
	for (std::size_t i = 0; i < first.getCount(); ++i)
		if (first.getPoint(i) != second.getPoint(i))
			return false;
	
	return true;
}

template<>
bool compare(const PolyLine &first, const PolyLine &second)
{
	if (!compare<Shape>(first, second))
		return false;
	if (first.getCount() != second.getCount())
		return false;
	for (std::size_t i = 0; i < first.getCount(); ++i)
		if (first.getPoint(i) != second.getPoint(i))
			return false;
	
	return true;
}

template<>
bool compare(const Rectangle &first, const Rectangle &second)
{
	return    compare<Shape>(first, second)
	       && first.getWidth() == second.getWidth()
	       && first.getHeight() == second.getHeight();
}

template<>
bool compare(const Text &first, const Text &second)
{
	return    compare<Shape>(first, second)
	       && first.getString() == second.getString();
}

template<class Shape_T>
int testCopyMove(Shape_T &shape)
{
	int result = 0;
	auto s2 = shape;
	
	TEST(compare(shape, s2));
	
	auto s3 = std::move(shape);
	
	TEST(compare(s2, s3));
	TEST(!compare(s3, shape));
	
	shape = std::move(s2);
	return result;
}

int testShapes()
{
	int result = 0;
	std::printf("Testing shapes...\n");
	{
		Ellipse elli {10, 5};
		
		RUN_TEST(testCopyMove(elli));
		
		TEST(value_within(elli.getArea(), 39.27, .01));
		TEST(value_within(elli.getPerimeter(), 24.22, .01));
	}
	
	{
		Line line {QPoint{1, 2}, QPoint{3, 4}};
		
		RUN_TEST(testCopyMove(line));
		
		TEST(value_within(line.getArea(), -1, .0001));
		TEST(value_within(line.getPerimeter(), -1, .0001));
		
		TEST((line.getStart() == QPoint{1, 2}));
		TEST((line.getPos() == QPoint{2, 3}));
		TEST((line.getEnd() == QPoint{3, 4}));
		
		line.setEnd(QPoint{5, 6});
		
		TEST((line.getStart() == QPoint{1, 2}));
		TEST((line.getPos() == QPoint{3, 4}));
		TEST((line.getEnd() == QPoint{5, 6}));
		
		line.move(1, 1);
		
		TEST((line.getStart() == QPoint{2, 3}));
		TEST((line.getPos() == QPoint{4, 5}));
		TEST((line.getEnd() == QPoint{6, 7}));
	}
	
	{
		const int high = 2, low = 0;
		Polygon poly {std::vector<QPoint>{QPoint{low, low}, QPoint{high, low}, QPoint{high, high}, QPoint{low, high}}};
		
		RUN_TEST(testCopyMove(poly));
		
		TEST(poly.getCount() == 4);
		
		TEST(value_within(poly.getArea(), 4, .001));
		TEST(value_within(poly.getPerimeter(), 8, .001));
		
		TEST((poly.getPos() == QPoint{1, 1}));
		TEST((poly.getPoint(0) == QPoint{0, 0}));
		TEST((poly.getPoint(3) == QPoint{0, 2}));
		
		poly.setPos(0, 0);
		
		TEST((poly.getPoint(0) == QPoint{-1, -1}));
		TEST((poly.getPoint(3) == QPoint{-1, 1}));
		
		poly.setPoint(0, QPoint{low, low});
		poly.setPoint(1, QPoint{high, low});
		poly.setPoint(2, QPoint{high, high});
		poly.setPoint(3, QPoint{low, high});
		
		TEST((poly.getPos() == QPoint{1, 1}));
		TEST((poly.getPoint(0) == QPoint{0, 0}));
		TEST((poly.getPoint(3) == QPoint{0, 2}));
	}
	
	{
		const int high = 2, low = 0;
		PolyLine poly {std::vector<QPoint>{QPoint{low, low}, QPoint{high, low}, QPoint{high, high}, QPoint{low, high}}};
		
		RUN_TEST(testCopyMove(poly));
		
		TEST(value_within(poly.getArea(), -1, .0001));
		TEST(value_within(poly.getPerimeter(), -1, .0001));
		
		TEST(poly.getCount() == 4);
		
		TEST((poly.getPos() == QPoint{1, 1}));
		TEST((poly.getPoint(0) == QPoint{0, 0}));
		TEST((poly.getPoint(3) == QPoint{0, 2}));
		
		poly.setPos(0, 0);
		
		TEST((poly.getPoint(0) == QPoint{-1, -1}));
		TEST((poly.getPoint(3) == QPoint{-1, 1}));
		
		poly.setPoint(0, QPoint{low, low});
		poly.setPoint(1, QPoint{high, low});
		poly.setPoint(2, QPoint{high, high});
		poly.setPoint(3, QPoint{low, high});
		
		TEST((poly.getPos() == QPoint{1, 1}));
		TEST((poly.getPoint(0) == QPoint{0, 0}));
		TEST((poly.getPoint(3) == QPoint{0, 2}));
	}
	
	{
		Rectangle rect {10, 5};
		
		RUN_TEST(testCopyMove(rect));
		
		TEST(value_within(rect.getArea(), 50, .0001));
		TEST(value_within(rect.getPerimeter(), 30, .0001));
	}
	
	{
		Text text{"Hello world!"};
		
		RUN_TEST(testCopyMove(text));
		
		TEST(value_within(text.getArea(), -1, .0001));
		TEST(value_within(text.getPerimeter(), -1, .0001));
	}
	
	return result;
}

