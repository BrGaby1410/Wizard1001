#include <GL/glut.h>
#include <math.h>
#include "vector.h"

Vector createVector(GLfloat x, GLfloat y, GLfloat z)
{
	Vector v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

Vector substractVectors(Vector a, Vector b)
{
	Vector c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return c;
}

Vector multiplyVector(Vector v, GLfloat a)
{
	Vector r; 
	r.x = v.x * a;
	r.y = v.y * a;
	r.z = v.z * a;
	return r;
}

GLfloat module(Vector a)
{
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

void normalizeVector(Vector &a)
{
	GLfloat module = sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
	a.x /= module;
	a.y /= module; 
	a.z /= module;
}

Vector addVectors (Vector a, Vector b)
{
	Vector c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}

Vector rotateVector(Vector v, GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	// Normalizes the rotation vector
	Vector n = createVector(x, y, z);
	normalizeVector(n);
	x = n.x;
	y = n.y;
	z = n.z;

	GLfloat r = angle * DEG_TO_RAD;
	GLfloat c = cos(r);
	GLfloat s = sin(r);

	// Rotates the vector
	Vector out;
	out.x = (x * x * (1 - c) + c) * v.x + (x * y * (1 - c) - z * s) * v.y + (x * z * (1 - c) + y * s) * v.z;
	out.y = (y * x * (1 - c) + z * s) * v.x + (y * y * (1 - c) + c) * v.y + (y * z * (1 - c) - x * s) * v.z;
	out.z = (x * z * (1 - c) - y * s) * v.x + (y * z * (1 - c) + x * s) * v.y + (z * z * (1 - c) + c) * v.z;

	return out;
}