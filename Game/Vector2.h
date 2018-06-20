#pragma once
#include <stdlib.h>

class Vector2
{
public:
	float x;
	float y;
	Vector2();
	Vector2(float ix, float iy);
	Vector2 Set(Vector2 vect);
	Vector2 Add(Vector2 vect);
	Vector2 Sub(Vector2 vect);
	Vector2 Mult(Vector2 vect);
	Vector2 ScalMult(float scal);
	float Lenght();
	float Distance(Vector2 vect);
	float AngleDegrees(Vector2 vect);
	float AngleRad(Vector2 vect);
	Vector2 Normalize();
	Vector2 NormalizeWith(Vector2 vect);
	Vector2 Lerp(Vector2 vect, float scal);
	Vector2 RandPointRect(Vector2 vect1, Vector2 vect2);
	Vector2 RandPointCircle(Vector2 vect, float rad);
	bool Equal(Vector2 vect);
	bool LineIntersectLine(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4);
	bool LineIntersectRect(Vector2 v1, Vector2 v2, Vector2 r, float width, float height);
	float DotProduct(Vector2 vect);
};