#pragma once


class Point
{
public:
	Point() : x(0), y(0) {};
	Point(float x, float y) : x(x), y(y){};
	Point(const Point& other) : x(other.x), y(other.y) {};
	~Point() {};


	float x, y;

};