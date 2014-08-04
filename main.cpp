#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
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

Vector res = createVector(0, 0, 0);
Vector jumpForce = createVector(0, 0, 0);

GLfloat angleY_player = 0;
GLfloat globalAngleX = 0;
GLfloat globalAngleY = 0;
GLfloat angle = 0;

GLfloat DRAG_FORCE = 0.5;
GLfloat EYE_HEIGHT = 51.5;

GLfloat SPEED = 0.25;

bool right_button_state = 0;
bool left_button_state = 0;
short int button_order = 0;  // 0 - NOTHING; 1 - LEFT, RIGHT; 2 - RIGHT, LEFT; 3 - LEFT; 4 - RIGHT;

bool keyState[256] = {false};


typedef struct _cube
{
    int x, y, z;
} cube;

void draw_player()
{
	glColor3f(0, 0, 1);
	glPushMatrix();
		glTranslatef(player.x, player.y + 0.75 , player.z);
		glRotatef(270, 1, 0, 0);
		glutSolidCone(0.75, 0.5, 100, 101);
	glPopMatrix();
		glPushMatrix();
		glTranslatef(player.x, player.y + 0.5, player.z);
		glutSolidSphere(0.5, 100, 100);
	glPopMatrix();
	// glPushMatrix();
	// 	glTranslatef(player.x + sin(angleY_player * DEG_TO_RAD)*0.5, player.y - 1, player.z + cos(angleY_player * DEG_TO_RAD)*0.5);
	// 	glRotatef(angleY_player, 0, 1, 0);
	// 	glutSolidCone(0.25, 0.5, 100, 101);
	// glPopMatrix();
	glPushMatrix();
		glTranslatef(player.x, player.y - 0.6, player.z);
		glRotatef(angleY_player, 0, 1, 0);
		glutSolidCube(1.2);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(player.x, player.y - 1.4, player.z);
		glRotatef(angleY_player, 0, 1, 0);
		glutSolidCube(1.2);
	glPopMatrix();
	glColor3f(1, 0, 0);
	float aux = 0.3;
	for (int i = 1; i <= 10; i++)
	{
		glPushMatrix();
			glTranslatef(player.x - cos(angleY_player * DEG_TO_RAD)*0.7, 
						player.y - aux, 
						player.z + sin(angleY_player * DEG_TO_RAD)*0.7);
			glRotatef(angleY_player, 0, 1, 0);
			glutSolidCube(0.2);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(player.x + cos(angleY_player * DEG_TO_RAD)*0.7, 
						player.y - aux, 
						player.z - sin(angleY_player * DEG_TO_RAD)*0.7);
			glRotatef(angleY_player, 0, 1, 0);
			glutSolidCube(0.2);
		glPopMatrix();
		aux += 0.2;
	}
	aux = 2.2;
	for (int i=1; i<= 5; i++)
	{
		glPushMatrix();
			glTranslatef(player.x - cos(angleY_player * DEG_TO_RAD)*0.3, 
						player.y - aux, 
						player.z + sin(angleY_player * DEG_TO_RAD)*0.3);
			glRotatef(angleY_player, 0, 1, 0);
			glutSolidCube(0.4);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(player.x + cos(angleY_player * DEG_TO_RAD)*0.3, 
						player.y - aux, 
						player.z - sin(angleY_player * DEG_TO_RAD)*0.3);
			glRotatef(angleY_player, 0, 1, 0);
			glutSolidCube(0.4);
		glPopMatrix();
		aux += 0.4;
	}
	glColor3f(0, 0, 1);
	glPushMatrix();
		glTranslatef(player.x - cos(angleY_player * DEG_TO_RAD)*0.3 - sin(angleY_player * DEG_TO_RAD)*0.4, 
					player.y - 3.8, 
					player.z + sin(angleY_player * DEG_TO_RAD)*0.3 - cos(angleY_player * DEG_TO_RAD)*0.4);
		glRotatef(angleY_player, 0, 1, 0);
		glutSolidCube(0.4);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(player.x + cos(angleY_player * DEG_TO_RAD)*0.3 - sin(angleY_player * DEG_TO_RAD)*0.4, 
					player.y - 3.8, 
					player.z - sin(angleY_player * DEG_TO_RAD)*0.3 - cos(angleY_player * DEG_TO_RAD)*0.4);
		glRotatef(angleY_player, 0, 1, 0);
		glutSolidCube(0.4);
	glPopMatrix();
	if (angleY_player >= 360 || angleY_player <= -360) angleY_player = 0;
//	cout << angleY_player << "\n";
//	angleY_player = 0;
}

void draw_temp_world()
{
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 100);
		glVertex3f(100, 0, 100);
		glVertex3f(100, 0, 0);
	glEnd();
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, 30);
		glVertex3f(50, 0, 30);
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

void move()
{
	res = createVector(0, 0, 0);

	if (button_order == 2)
		{	
			dir = substractVectors(target, eye);
			dir.y = 0;
			normalizeVector(dir);
			dir = multiplyVector(dir, SPEED);
			res = addVectors(res, dir);
		}

	if (keyState['w'] == true) {
		dir = substractVectors(target, eye);
		dir.y = 0;
		normalizeVector(dir);
		dir = multiplyVector(dir, SPEED);
		res = addVectors(res, dir);
	}

	if (keyState['s'] == true) {
		dir = substractVectors(target, eye);
		dir.y = 0;
		normalizeVector(dir);
		dir = multiplyVector(dir, SPEED);
		res = substractVectors(res, dir);
	}

	if (keyState['a'] == true) {
		angleY_player++;
		eye.x = player.x + sin(angleY_player * DEG_TO_RAD)*4.33;
		eye.z = player.z + cos(angleY_player * DEG_TO_RAD)*4.33;
		target.x = player.x - sin(angleY_player * DEG_TO_RAD)*16;
		target.z = player.z - cos(angleY_player * DEG_TO_RAD)*16;
			
		// dir = substractVectors(target, eye);
		// dir.y = 0;
		// normalizeVector(dir);
		// dir = multiplyVector(dir, SPEED);
		// dir = rotateVector(dir, 90, 0, 1, 0);
		// res = addVectors(res, dir);
	}

	if (keyState['d'] == true) {
		angleY_player--;
		eye.x = player.x + sin(angleY_player * DEG_TO_RAD)*4.33;
		eye.z = player.z + cos(angleY_player * DEG_TO_RAD)*4.33;
		target.x = player.x - sin(angleY_player * DEG_TO_RAD)*16;
		target.z = player.z - cos(angleY_player * DEG_TO_RAD)*16;

		// dir = substractVectors(target, eye);
		// dir.y = 0;
		// normalizeVector(dir);
		// dir = multiplyVector(dir, SPEED);
		// dir = rotateVector(dir, -90, 0, 1, 0);
		// res = addVectors(res, dir);
	}

	// if (keyState[32] == true && jumpForce.y == 0)
	// {
	// 	jumpForce = createVector(0, 0.5, 0);                   // 0.171
	// }
	// // if (res.x != 0 && res.y != 0 && res.z != 0) {
	// // 	// Vector dragForce = rotateVector(res, 180, 0, 1, 0);
	// // 	// dragForce = multiplyVector(dragForce, 0.5);

	// // 	// res = addVectors(res, dragForce);
	// // }


	// if (eye.y > EYE_HEIGHT) {
	// 	jumpForce = substractVectors(jumpForce, createVector(0, 0.07, 0));           // 0.011
	// } else if (jumpForce.y != 0.5) {                   // 0.171
	// 	keyState[32] = false;
	// 	res.y = 0;
	// 	jumpForce = createVector(0, 0, 0);
	// 	eye.y = EYE_HEIGHT;
	// }

	res = multiplyVector(res, 0.9);
// 	if (jumpForce.y != 0)
// 		res = addVectors(res, jumpForce);
// 	else if (res.x != 0 || res.y != 0 || res.z != 0) {
// 		// res = addVectors(res, createVector(0, 0.5 * sin(angle * DEG_TO_RAD), 0));
// 	}
// //	cout << res.x << " " << res.y << " " << res.z << "\n";
// 	cout << eye.x << " " << eye.y << " " << eye.z << "\n";
// 	cout << jumpForce.y << "\n\n";

	eye = addVectors(eye, res);
	target = addVectors(target, res);
	player = addVectors(player, res);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
		case 'W':
			keyState['w'] = true;
			break;
		case 's':
		case 'S':
			keyState['s'] = true;
			break; 
		case 'a':
		case 'A':
			keyState['a'] = true;
			break;
		case 'd':
		case 'D':
			keyState['d'] = true;
			break;
		case 32:
			keyState[32] = true;
			break;
		case 27:
			exit(0);
	}
}

void specialKeyboard(int key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit(0);
	}
}

void keyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
		case 'W':
			keyState['w'] = false;
			break;
		case 's':
		case 'S':
			keyState['s'] = false;
			break; 
		case 'a':
		case 'A':
			keyState['a'] = false;
			break;
		case 'd':
		case 'D':
			keyState['d'] = false;
			break;
	}
}

void motion_passive(int x, int y)
{
//	if (x > width - 50 && y > height - 50) cout << "Here should be a picture\n"; 
}

void motion(int x, int y)
{
		GLfloat angleX;
		GLfloat angleY;
		// cout << x << " " << y << "\n";

		// if (x != width / 2 || y != height / 2) 
		// 			glutWarpPointer(width / 2, height / 2);

		angleY = 90 - (x * (180 / (GLfloat) width));
		angleX = 90 - (y * (180 / (GLfloat) height));

		// dir = substractVectors(target, eye);
		// dir = rotateVector(dir, angleY, 0, 1, 0);
		// target = addVectors(eye, dir);	

		// dir = substractVectors(player, eye);
		// dir = rotateVector(dir, angleY, 0, 1, 0);
		// player = addVectors(eye, dir);

		globalAngleY += angleY;
		if (globalAngleY >= 360 || globalAngleY <= -360) globalAngleY = 0;

		if (angleX + globalAngleX > 35)
		{
			angleX = 35 - globalAngleX;
			globalAngleX = 35;
		}
		else if (angleX + globalAngleX < -67)
		{
			angleX = -67 - globalAngleX;
			globalAngleX = -67;
		}
		else globalAngleX += angleX;	

		if (button_order == 4 || button_order == 2) angleY_player += angleY;

		
		if (button_order == 1)
		{
			
			eye.x = player.x + sin(globalAngleY * DEG_TO_RAD)*4.33;
			eye.y = player.y + sin(globalAngleX * DEG_TO_RAD)*4.33;
			eye.z = player.z + cos(globalAngleY * DEG_TO_RAD)*4.33;
			target.x = player.x - sin(globalAngleY * DEG_TO_RAD)*16;
			target.y = player.y - sin(globalAngleX * DEG_TO_RAD)*16;
			target.z = player.z - cos(globalAngleY * DEG_TO_RAD)*16;
		} else if (button_order == 2)
				{
					eye.x = player.x + sin(angleY_player * DEG_TO_RAD)*4.33;
					eye.y = player.y + sin(globalAngleX * DEG_TO_RAD)*4.33;
					eye.z = player.z + cos(angleY_player * DEG_TO_RAD)*4.33;
					target.x = player.x - sin(angleY_player * DEG_TO_RAD)*16;
					target.y = player.y - sin(globalAngleX * DEG_TO_RAD)*16;
					target.z = player.z - cos(angleY_player * DEG_TO_RAD)*16; 
				} else {
							eye.x = player.x + sin(globalAngleY * DEG_TO_RAD)*4.33;
			eye.y = player.y + sin(globalAngleX * DEG_TO_RAD)*4.33;
			eye.z = player.z + cos(globalAngleY * DEG_TO_RAD)*4.33;
			target.x = player.x - sin(globalAngleY * DEG_TO_RAD)*16;
			target.y = player.y - sin(globalAngleX * DEG_TO_RAD)*16;
			target.z = player.z - cos(globalAngleY * DEG_TO_RAD)*16;
						}
		if (x != width / 2 || y != height / 2) 
			glutWarpPointer(width / 2, height / 2);
		cout << globalAngleX << "\n";
		glutPostRedisplay();

}

void mouse_wheel(int wheel, int direction, int x, int y)
{
	cout << "Se roteste...\n";
}

int numar = 0;
void mouse(int button, int state, int x, int y)
{
	// if (button == 3) cout << "SUUUUS\n";
	// if (button == 4) cout << "JOOOOS\n";                        // N, LR, RL, L, R
	if (button == GLUT_RIGHT_BUTTON) 
		{
			if (state == GLUT_DOWN) {right_button_state = 1;
			                         if (left_button_state) button_order = 1;
			                     		else button_order = 4;}
				else {right_button_state = 0;
					  if (left_button_state) button_order = 3;
			            else button_order = 0;}
			cout << ++numar << "\n";
			if (x != width / 2 || y != height / 2) 
				glutWarpPointer(width / 2, height / 2);
			
		}
	if (button == GLUT_LEFT_BUTTON) 
	{
		if (state == GLUT_DOWN) {left_button_state = 1;
								 if (right_button_state) button_order = 2;
			                     		else button_order = 3;}
			else {left_button_state = 0;
				  if (right_button_state) button_order = 4;
			       	else button_order = 0;}
	}
}

void tick(int val)
{
	move();
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
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);

    eye = createVector (15, 6.48, 19.55);
    target = createVector (15, 6.48, 0);
    player = createVector (15, 4, 16);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 900);
    glutCreateWindow("Wizard1001");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1, tick, 0);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseWheelFunc(mouse_wheel);
    glutMotionFunc(motion);
	glutPassiveMotionFunc(motion_passive);
	glutMouseFunc(mouse);
    initialize();
    glutMainLoop();
    return 0;
}