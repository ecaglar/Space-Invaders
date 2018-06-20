#include "Vector2.h"
#include <math.h>
#ifndef PI
#define PI 3.14159265
#endif

Vector2::Vector2()
{
x = 0;
y = 0;
}
Vector2::Vector2(float ix, float iy)
{
x = ix;
y = iy;
}
Vector2 Vector2::Set(Vector2 vect)
{
x = vect.x;
y = vect.y;
return *this;
}
Vector2 Vector2::Add(Vector2 vect)
{
x += vect.x;
y += vect.y;
return *this;
}
Vector2 Vector2::Sub(Vector2 vect)
{
x -= vect.x;
y -= vect.y;
return *this;
}
Vector2 Vector2::Mult(Vector2 vect)
{
x *= vect.x;
y *= vect.y;
return *this;
}
Vector2 Vector2::ScalMult(float scal)
{
x *= scal;
y *= scal;
return *this;
}
float Vector2::Lenght()
{
	float s1 = sqrt((x*x+y*y));
	float l = sqrt((s1*s1));
	return l;
}
Vector2 Vector2::Lerp(Vector2 vect, float scal)
{
	Vector2 temp = Vector2(x, y);
	Vector2 temp2 = Vector2(vect.x, vect.y);
	temp.Sub(temp2);
	temp.ScalMult(scal);
	temp.Add(temp2);
	return temp;
}
float Vector2::Distance(Vector2 vect)
{
	Vector2 temp = Vector2(vect.x, vect.y);
	temp.Sub(*this);

	return sqrt(temp.x * temp.x + temp.y * temp.y);
}
float Vector2::AngleDegrees(Vector2 vect)
{
	float angle = atan2((-1*(vect.y - y)), (vect.x - x));
	angle = angle/PI*180;
	return -1*(angle);
}
float Vector2::AngleRad(Vector2 vect)
{
	float angle = atan2((-1*(vect.y - y)), (vect.x - x));
	return -1*(angle);
}
Vector2 Vector2::Normalize()
{
	float len = this->Lenght();
	x = x/len;
	y = y/len;
	return *this;
}
Vector2 Vector2::NormalizeWith(Vector2 vect)
{
	this->Sub(vect);
	float len = this->Lenght();
	x = x/len;
	y = y/len;
	return *this;
}
Vector2 Vector2::RandPointRect(Vector2 vect1, Vector2 vect2)
{
	float width = vect2.x - vect1.x;
	float height = vect2.y - vect1.y;

	if(width == 0 && height == 0)
	{
		return vect1;
	}

	this->Set(Vector2(vect1.x + rand()%(int)width, vect1.y + rand()%(int)height));
	return *this;
}
Vector2 Vector2::RandPointCircle(Vector2 vect, float rad)
{
	Vector2 a = Vector2(vect.x - rad, vect.y - rad);
	Vector2 b = Vector2(vect.x + rad, vect.y + rad);

	this->Set(Vector2().RandPointRect(a, b));

	while(vect.Distance(*this) > rad)
	{
		this->Set(Vector2().RandPointRect(a, b));
	}

	return *this;
}
bool Vector2::Equal(Vector2 vect)
{
	bool ret = false;
	if(this->x == vect.x && this->y == vect.y)
	{
		ret = true;
	}
	return ret;
}

bool Vector2::LineIntersectLine( Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4 )
{
    float denom = ((v4.y - v3.y) * (v2.x - v1.x)) - ((v4.x - v3.x) * (v2.y - v1.y));
    float numerator = ((v4.x - v3.x) * (v1.y - v3.y)) - ((v4.y - v3.y) * (v1.x - v3.x));

    float numerator2 = ((v2.x - v1.x) * (v1.y - v3.y)) - ((v2.y - v1.y) * (v1.x - v3.x));

    if ( denom == 0.0f )
    {
        if ( numerator == 0.0f && numerator2 == 0.0f )
        {
            return false;;
        }
        return false;;
    }
    float ua = numerator / denom;
    float ub = numerator2/ denom;

    return (ua >= 0.0f && ua <= 1.0f && ub >= 0.0f && ub <= 1.0f);
}

bool Vector2::LineIntersectRect( Vector2 v1, Vector2 v2, Vector2 r, float height, float width )
{
        Vector2 lowerLeft( r.x, r.y+height );
        Vector2 upperRight( r.x+width, r.y );
        Vector2 upperLeft( r.x, r.y );
        Vector2 lowerRight( r.x+width, r.y+height);
        if (v1.x > lowerLeft.x && v1.x < upperRight.x && v1.y < lowerLeft.y && v1.y > upperRight.y &&
            v2.x > lowerLeft.x && v2.x < upperRight.x && v2.y < lowerLeft.y && v2.y > upperRight.y )
        {   
            return true;
        }
        if (LineIntersectLine(v1,v2, upperLeft, lowerLeft ) ) return true;
        if (LineIntersectLine(v1,v2, lowerLeft, lowerRight) ) return true;
        if (LineIntersectLine(v1,v2, upperLeft, upperRight) ) return true;
        if (LineIntersectLine(v1,v2, upperRight, lowerRight) ) return true;
        return false;
}

float Vector2::DotProduct(Vector2 vect)
{
	Vector2 temp = Vector2(*this).Mult(vect);
	return (temp.x+temp.y);
}