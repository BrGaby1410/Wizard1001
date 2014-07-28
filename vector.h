#define PI 3.14159
#define DEG_TO_RAD PI/180 

typedef struct _vector
{
	GLfloat x, y, z;
} Vector;

Vector createVector(GLfloat x, GLfloat y, GLfloat z);
Vector substractVectors(Vector a, Vector b);
void normalizeVector(Vector &a);
Vector addVectors(Vector a, Vector b);
Vector rotateVector(Vector v, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);