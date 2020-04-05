#include <limits>
#include <math.h>
#include "point.h"
using namespace std;
Point operator+(const Point& p1, const Point& p2){
	Point pt;
	pt.x = p1.x + p2.x;
	pt.y = p1.y + p2.y;
	return pt;
}

Point operator-(const Point& p1, const Point& p2) {
	Point pt;
	pt.x = p1.x - p2.x;
	pt.y = p1.y - p2.y;
	return pt;
}

ostream& operator<<(ostream& out, const Point& p) {
	out << p.x << ' ' << p.y;
	return out;
}

bool pointsInSameLine(Point& u, Point& v, Point& w) {
	if (u.x == v.x && u.x != w.x)//u and v are in a vetical line but w not
		return false;
	if (u.x == w.x && u.x != v.x)//u and w are in a vetical line but v not
		return false;
	//no need to test v and w, since (v.x - w.x) will be not calculate
	//if line uv and uw have same slope, then the three points are in a line

	double slope1 = (u.y - v.y) / (u.x - v.x);
	double slope2 = (u.y - w.y) / (u.x - w.x);
	if (slope1 == slope2) return true;
	return false;
}

//The center of the line formed by one point and the center of the other two points must be in the triangle.
Point getPointInTriangle(Point& u, Point& v, Point& w) {
	double x = ((u.x + v.x) / 2 + w.x) / 2;
	double y = ((u.y + v.y) / 2 + w.y) / 2;
	return Point(x, y);
}

double calTangent(Point& pole, Point& p) {
	if (p.y == pole.y) return (numeric_limits<double>::max)();
	return (p.x - pole.x) / (pole.y - p.y);
}

double calPoler(Point& pole, Point& p, double tangent) {
	double angle = atan(abs(tangent));
	if (pole.y == p.y && pole.x <= p.x) angle = M_PI / 2;
	else if (pole.y == p.y && pole.x > p.x) angle = M_PI * 3 / 2;
	else if (pole.x == p.x && pole.y < p.y) angle = M_PI;
	else if (pole.y < p.y && pole.x < p.x) angle = M_PI - angle;
	else if (pole.y < p.y && pole.x > p.x) angle += M_PI;
	else if (pole.y > p.y && pole.x > p.x) angle = M_PI *2 - angle;
	return angle;
}

double lengthOfTwoPoints(Point& p1, Point& p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double angleOfThreePoints(Point& u, Point& v, Point& w) {//use cosA = (c*c +b*b-a*a) / (2*b*c);
	double uv = lengthOfTwoPoints(u, v);//c
	double uw = lengthOfTwoPoints(u, w);//a
	double vw = lengthOfTwoPoints(v, w);//b

	return acos((uv*uv + vw*vw - uw*uw)/(2*uv*vw));
}

double slope(Point& p1, Point& p2) {
	if (p1.x == p2.x) return numeric_limits<double>::max();
	return (p2.y - p1.y) / (p2.x - p1.x);
}

double angleOfThreePointsCounterClockwise(Point& u, Point& v, Point& w) {
	double angle = angleOfThreePoints(u, v, w);
	double convexAngle = M_PI * 2 - angle;
	double slopeuv = slope(u,v);
	double slopevw = slope(v,w);

	//consider v as the original point, calculate accorrding to which quandrant the other two points are
	if (u.x >= v.x && u.y >= v.y){//u is in first quandrant
		if (w.y >= v.y) {//w also in 1st & 2nd quandrant
			if (w.x >= v.x) {//w in 1st quandrant
				if (slopeuv <= slopevw) return angle;
				else return convexAngle;
			}
			else {//w in positive Y axis or 2nd quandrant
				return angle;
			}
		}else {//w in 3rd or 4th quandrant
			if(w.x<=v.x){//w in 3rd quandrant
				if (slopeuv >= slopevw) return angle;
				else return convexAngle;
			}
			else {//w in negative Y axis or 4th quandrant
				return convexAngle;
			}
		}
	}else if (u.x < v.x && u.y >= v.y) {//u is in 2nd quandrant
		if (w.y >= v.y) {//w also in 1st & 2nd quandrant
			if (w.x >= v.x) {//w in 1st quandrant
				return convexAngle;
			}
			else {//w in positive Y axis or 2nd quandrant
				if (slopeuv <= slopevw) return angle;
				else return convexAngle;
			}
		}
		else {//w in 3rd or 4th quandrant
			if (w.x <= v.x) {//w in 3rd quandrant
				return angle;
			}
			else {//w in negative Y axis or 4th quandrant
				if (slopeuv >= slopevw) return angle;
				else return convexAngle;
			}
		}
	}
	else if (u.x <= v.x && u.y < v.y) {//u is in 3rd quandrant
		if (w.y >= v.y) {//w in 1st & 2nd quandrant
			if (w.x >= v.x) {//w in 1st quandrant
				if (slopeuv >= slopevw) return angle;
				else return convexAngle;
			}
			else {//w in positive Y axis or 2nd quandrant
				return convexAngle;
			}
		}
		else {//w in 3rd or 4th quandrant
			if (w.x <= v.x) {//w in 3rd quandrant
				if (slopeuv > slopevw) return convexAngle;
				else return angle;
			}
			else {//w in negative Y axis or 4th quandrant
				return angle;
			}
		}
	}else {//u is in 4th quandrant
		if (w.y >= v.y) {//w also in 1st & 2nd quandrant
			if (w.x >= v.x) {//w in 1st quandrant
				return angle;
			}
			else {//w in positive Y axis or 2nd quandrant
				if (slopeuv >= slopevw) return angle;
				else return convexAngle;
			}
		}
		else {//w in 3rd or 4th quandrant
			if (w.x <= v.x) {//w in 3rd quandrant
				return convexAngle;
			}
			else {//w in negative Y axis or 4th quandrant
				if (slopeuv > slopevw) return convexAngle;
				else return angle;
			}
		}
	}
}
