#include <iostream>                // comentariu
#include <GL/glut.h>
#include <math.h>
#include "vector.h"

using namespace std;

GLfloat light_poz[] = { 10, 10, 10, 1 };
GLfloat white_light[] = { 1, 1, 1, 1 };

GLint width, height;

Vector eye;
Vector target;
Vector dir;
Vector player;

GLfloat angleY_player = 0;
GLfloat angleX_player = 0;

typedef struct _cube
{
    int x, y, z;
} cube;

cube ****world;
bool visited[100][100][100];

void draw_player()
{
	glColor3f(0, 0, 1);
	// glPushMatrix();
	// 	glTranslatef(player.x, player.y - 1, player.z + 0.5)
	glPushMatrix();
		glTranslatef(player.x, player.y + 0.5, player.z);
		glRotatef(270, 1, 0, 0);
		glutSolidCone(0.75, 1, 100, 101);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(player.x + sin(angleY_player * DEG_TO_RAD)*0.5, player.y - 1, player.z + cos(angleY_player * DEG_TO_RAD)*0.5);
		glRotatef(angleY_player, 0, 1, 0);
		glutSolidCone(0.25, 0.5, 100, 101);
	glPopMatrix();
	glPushMatrix();

		glTranslatef(player.x, player.y, player.z);
		glRotatef(angleY_player, 0, 1, 0);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		
		glTranslatef(player.x, player.y - 1, player.z);
		glRotatef(angleY_player, 0, 1, 0);
		glutSolidCube(1);
	glPopMatrix();
	if (angleY_player >= 360 || angleY_player <= -360) angleY_player = 0;
//	cout << angleY_player << "\n";
//	angleY_player = 0;
}

void draw_temp_world()
{
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glVertex3f(0, 1, 0);
		glVertex3f(0, 1, 100);
		glVertex3f(100, 1, 100);
		glVertex3f(100, 1, 0);
	glEnd();
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 1, 30);
		glVertex3f(50, 1, 30);
		glVertex3f(50, 2.5, 30);
		glVertex3f(0, 2.5, 30);
	glEnd();
	draw_player();
	glColor3f(1, 0, 1);
	glBegin(GL_POINTS);
		glVertex3f(2, 2, 0);
		glVertex3f(3, 2, 0);
		glVertex3f(4, 2, 0);
	glEnd();
	glBegin(GL_POLYGON);
		glNormal3f(0, 0, 1);
		glVertex3f(5, 3, 0);
		glVertex3f(6, 4, 0);
		glVertex3f(8, 4, 0);
		glVertex3f(9, 3, 0);
		glVertex3f(8, 2, 0);
		glVertex3f(6, 2, 0);
	glEnd();
	glColor3f(1,0,0);
	
}

void draw_cube(GLfloat x, GLfloat y, GLfloat z)
{
    glPushMatrix();
        glTranslatef(x, y, z);
        glutSolidCube(1);
    glPopMatrix();
}

// void draw_world(int x, int y, int z)
// {
//     if (x >= 100 || x < 0 ||
//         y >= 100 || y < 0 ||
//         z >= 100 || z < 0)
//         return;

//     if (visited[x][y][z])
//         return;

//     visited[x][y][z] = true;

//     if (world[x][y][z] != 0) {
//         draw_cube(*world[x][y][z]);
//         return;
//     }

//     draw_world(x - 1, y - 1, z - 1);
//     draw_world(x - 1, y - 1, z);
//     draw_world(x - 1, y - 1, z + 1);
//     draw_world(x, y - 1, z - 1);
//     draw_world(x, y - 1, z);
//     draw_world(x, y - 1, z + 1);
//     draw_world(x + 1, y - 1, z - 1);
//     draw_world(x + 1, y - 1, z);
//     draw_world(x + 1, y - 1, z + 1);

//     draw_world(x - 1, y + 1, z - 1);
//     draw_world(x - 1, y + 1, z);
//     draw_world(x - 1, y + 1, z + 1);
//     draw_world(x, y + 1, z - 1);
//     draw_world(x, y + 1, z);
//     draw_world(x, y + 1, z + 1);
//     draw_world(x + 1, y + 1, z - 1);
//     draw_world(x + 1, y + 1, z);
//     draw_world(x + 1, y + 1, z + 1);

//     draw_world(x - 1, y, z - 1);
//     draw_world(x - 1, y, z);
//     draw_world(x - 1, y, z + 1);
//     draw_world(x, y, z - 1);
//     draw_world(x, y, z + 1);
//     draw_world(x + 1, y, z - 1);
//     draw_world(x + 1, y, z);
//     draw_world(x + 1, y, z + 1);
// }

void display(void)
{
    // Clear the color buffer, restore the background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Load the identity matrix, clear all the previous transformations
    glLoadIdentity();
    // Set up the camera
    gluLookAt(eye.x, eye.y, eye.z, player.x, player.y, player.z, 0, 1, 0);

    draw_cube(0,0,0);
    draw_cube(0.5,1.5,0.5);
    // glPushMatrix();
    //     glTranslatef(5,3,5);
    //     glutSolidCube(1);
    // glPopMatrix();
    // glPushMatrix();
    //     glTranslatef(5,2,5);
    //     glutSolidCube(1);
    // glPopMatrix();
    // glPushMatrix();
    //     glTranslatef(5,1,5);
    //     glutSolidCube(1);
    // glPopMatrix();
    // glPushMatrix();
    //     glTranslatef(5,2,6);
    //     glutSolidCube(1);
    // glPopMatrix();
    // Set the drawing color to white
    glColor3f(0, 1, 1);

 //	draw_world(10, 3, 10);
    draw_temp_world();
    draw_cube(15, 30, 15);
    
    // Swap buffers in GPU
    glutSwapBuffers();
}

void reshape(int _width, int _height)
{
    // Set the viewport to the full window size
    glViewport(0, 0, (GLsizei) _width, (GLsizei) _height);
    // Load the projection matrix
    glMatrixMode(GL_PROJECTION);
    // Clear all the transformations on the projection matrix
    glLoadIdentity();
    // Set the perspective according to the window size
    gluPerspective(60, (GLdouble) _width / (GLdouble) _height, 0.1, 60000);
    // Load back the modelview matrix
    glMatrixMode(GL_MODELVIEW);

    width = _width;
    height = _height;
}

void keyboard(unsigned char key, int x, int y)
{
	cout << eye.x << " " << eye.y << " " << eye.z << "\n";
	switch (key)
	{
		case 'w':
		case 'W':
			dir = substractVectors(target, eye);
			normalizeVector(dir);
			eye = addVectors(eye, dir);
			target = addVectors(target, dir);
			player = addVectors(player, dir);
//			glTranslatef(player.x + sin(angleY_player * DEG_TO_RAD)*0.5, player.y - 1, player.z + cos(angleY_player * DEG_TO_RAD));

//			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			break;
		case 's':
		case 'S':
			dir = substractVectors(target, eye);
			normalizeVector(dir);
			eye = substractVectors(eye, dir);
			target = substractVectors(target, dir);
			player = substractVectors(player, dir);
			break; 
		case 'a':
		case 'A':
			// dir = substractVectors(target, eye);
			// normalizeVector(dir);
			// dir = rotateVector(dir, 90, 0, 1, 0);
			// eye = addVectors(eye, dir);
			// target = addVectors(target, dir);
			// player = addVectors(player, dir);
			angleY_player++;
			eye.x = player.x + sin(angleY_player * DEG_TO_RAD)*7.5;
			eye.z = player.z + cos(angleY_player * DEG_TO_RAD)*7.5;
			target.x = player.x - sin(angleY_player * DEG_TO_RAD)*13;
			target.z = player.z - cos(angleY_player * DEG_TO_RAD)*13;
			
			break;
		case 'd':
		case 'D':
			// dir = substractVectors(target, eye);
			// normalizeVector(dir);
			// dir = rotateVector(dir, -90, 0, 1, 0);
			// eye = addVectors(eye, dir);
			angleY_player--;
			eye.x = player.x + sin(angleY_player * DEG_TO_RAD)*7.5;
			eye.z = player.z + cos(angleY_player * DEG_TO_RAD)*7.5;
			target.x = player.x - sin(angleY_player * DEG_TO_RAD)*13;
			target.z = player.z - cos(angleY_player * DEG_TO_RAD)*13;
			
			// target = addVectors(target, dir);
			// player = addVectors(player, dir);
			break;
	}
}

void motion(int x, int y)
{
	GLfloat angleX;
	GLfloat angleY;
	// cout << x << " " << y << "\n";

	angleY = 90 - (x * (180 / (GLfloat) width));
	angleX = 90 - (y * (180 / (GLfloat) height));

	// dir = substractVectors(target, eye);
	// dir = rotateVector(dir, angleY, 0, 1, 0);
	// target = addVectors(eye, dir);

	// dir = substractVectors(player, eye);
	// dir = rotateVector(dir, angleY, 0, 1, 0);
	// player = addVectors(eye, dir);
	angleY_player += angleY;
	eye.x = player.x + sin(angleY_player * DEG_TO_RAD)*7.5;
	eye.z = player.z + cos(angleY_player * DEG_TO_RAD)*7.5;
	target.x = player.x - sin(angleY_player * DEG_TO_RAD)*13;
	target.z = player.z - cos(angleY_player * DEG_TO_RAD)*13;
	// dir = substractVectors(target, eye);
	// dir = rotateVector(dir, angleX, 1, 0, 0);
	// target = addVectors(eye, dir);
	// angleX_player += angleX;
	// target.y = player.y 

	if (x != width / 2 || y != height / 2) 
		glutWarpPointer(width / 2, height / 2);
	glutPostRedisplay();
}

 // int auxs = 0;
 // int auxm = 0;
 // int auxh = 0;
 // int aux = -1;

void tick(int val)
{
	// if (aux!=val) { aux = val; auxs = aux/100;
	// 				if (auxs >= 60) { auxs = 0; auxm++; }
	// 				if (auxm >= 60) { auxm = 0; auxh++; }
	// 				cout << auxh << " : ";
	// 				if (auxm<10) cout << "0" << auxm << " : ";
	// 					else cout << auxm << " : ";
	// 				if (auxs<10) cout << "0" << auxs << " : ";
	// 					else cout << auxs << " : ";
	// 				if (aux%100<10) cout << "0" << aux%100 << "\n";
	// 					else cout << aux%100 << "\n";
	// 			  }
	glutPostRedisplay();
	glutTimerFunc(1, tick, val + 1);
}

void initialize(void)
{
    // Set the background to black
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_POSITION, light_poz);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white_light);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT);

    eye = createVector (15, 5, 20.5);
    target = createVector (15, 5, 0);
    player = createVector (15, 2.5, 13);

    // world = (cube****) calloc (100, sizeof (cube***));
    // for (int i = 0; i < 100; i++)
    // {
    //     world[i] = (cube***) calloc (100, sizeof(cube**));
    //     for (int j = 0; j < 100; j++)
    //     {
    //         world[i][j] = (cube**) calloc (100, sizeof (cube*));
    //     }
    // }

    // for (int i = 0; i < 100; i++)
    // {
    //     for (int j = 0; j < 2; j++)
    //     {
    //         for (int k = 0; k < 100; k++)
    //         {
    //             visited[i][j][k] = false;
    //             world[i][j][k] = (cube*) malloc (sizeof(cube));
    //             (*world[i][j][k]).x = i;
    //             (*world[i][j][k]).y = j;
    //             (*world[i][j][k]).z = k;
    //         }
    //     }
    // }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 900);
    glutCreateWindow("Wizard102");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1, tick, 0);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);
	glutPassiveMotionFunc(motion);
    initialize();
    glutMainLoop();
    return 0;
}