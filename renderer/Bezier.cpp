#include "Bezier.h"
#include "glfw3_glew/glfw3_glew.h"


	void Bezier::DrawCurve()
	{

			Vector2 p0;
			Vector2 p1;
			Vector2 p2;
			Vector2 p3;

			float cx;
			float bx;
			float ax;

			float cy;
			float by;
			float ay;

			float oldX = -1;
			float oldY = -1;
			float tSquared;
			float tCubed;
			float resultX = 1;
			float resultY = 1;


			glBegin(GL_TRIANGLE_FAN);
			//glBegin(GL_POLYGON);
			for (int i = 0; i < Points.size(); i++)
			{


				p0 = Points[i].pos;
				p1 = Points[i].handleOut;

				if (i == Points.size() - 1)
				{
					if (closed)
					{
						p2 = Points[0].handleIn;
						p3 = Points[0].pos;
					}
					else
						break;
				}
				else
				{
					p2 = Points[i+1].handleIn;
					p3 = Points[i+1].pos;
				}

				//--drawing the Bezier curve, based on http ://en.wikipedia.org/wiki/B%C3%A9zier_curve
				cx = 3.0 * (p1.x - p0.x);
				bx = 3.0 * (p2.x - p1.x) - cx;
				ax = p3.x - p0.x - cx - bx;

				cy = 3.0 * (p1.y - p0.y);
				by = 3.0 * (p2.y - p1.y) - cy;
				ay = p3.y - p0.y - cy - by;


				for (float t = 0.0f; t < 1.0f; t += 0.025)
				{

					tSquared = t * t;
					tCubed = tSquared * t;
					resultX = (ax * tCubed) + (bx * tSquared) + (cx * t) + p0.x;
					resultY = (ay * tCubed) + (by * tSquared) + (cy * t) + p0.y;

					if (oldX != -1)
					{
						glVertex2f(oldX, oldY);
					}
					oldX = resultX;
					oldY = resultY;
				}
			}
			glEnd();
	}
