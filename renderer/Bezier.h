#pragma once

#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
#define M_PI_4     0.785398163397448309616  // pi/4

#include <vector>

struct Vector2 {
public:
	float x, y;
	void Set(const float in_x, const float in_y)
	{
		x = in_x;
		y = in_y;
	}
};

struct Bezier {

	struct Point {
		Vector2 pos, handleIn, handleOut;
		int parentCurve;
		int midPointID;
		Point() 
		{
		}
		Point(Vector2 in_pos)
		{
			pos = in_pos;
			handleIn.Set(M_PI, 0.1f);
			handleOut.Set(0.0f, 0.1f);
		}
		~Point() {};
	};
	std::vector<Point> Points;
	int fillResolution = 6;
	float fillColor[4] = { 0.0f,1.0f,0.0f,1.0f };
	bool closed = true;

	void DrawCurve();


	Bezier() { 
		//Point p(Vector2(-0.5,-0.5f));
		//Points.emplace_back(p);
	};
	~Bezier() 
	{ 
		// @todo MEMORYLEAK add function to destroy the segments
	};

};

