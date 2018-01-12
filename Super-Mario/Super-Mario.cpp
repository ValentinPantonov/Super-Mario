// Super-Mario.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GL/freeglut.h"
#include <SOIL.h>
#include <iostream>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void init();
void draw();

float milisecs = 0.001f;
float texWidth = 1.0f;
float directionTop = 1.0 / 2.0;
float directionBot = 0.01;
float moveX = 0.0f;

void keyboard(unsigned char key, int x, int y);
void timer(int);
int LoadTexture(const char*);
int texID;
int bgID;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GL_RGB | GL_DOUBLE | GL_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Glut 2nd");

	init();

	glutDisplayFunc(draw);

	glutKeyboardFunc(keyboard);
	//	glutIdleFunc(draw);
	glutTimerFunc(milisecs, timer, 0);
	glutMainLoop();

	return 0;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 22:
		exit(0);
		break;
	case '+':
		moveX += 0.02;
		directionTop = 1.0 / 2.0;
		directionBot = 0.01;
		if (texWidth > 9)texWidth = 0;
		texWidth += 1.0;
		break;
	case '-':
		moveX -= 0.02;
		directionBot = 1.0 / 2.0;
		directionTop = 0.999;
		if (texWidth < 2)texWidth = 10;
		texWidth -= 1.0;
		break;
	}
}

void timer(int val)
{
	glutPostRedisplay();
	glutTimerFunc(milisecs, timer, val);
}

void DrawMario(float width)
{


	float wd2 = width / 2;
	glColor3f(1, 1, 1);
	//Draw a square
	glBegin(GL_QUADS);

	glTexCoord2f((texWidth - 1) / 10.0 + 0.01, directionTop);
	glVertex2f(-wd2, -wd2);
	glTexCoord2f(((texWidth / 10.0) - 0.01), directionTop);
	glVertex2f(wd2, -wd2);
	glTexCoord2f(((texWidth / 10.0) - 0.01), directionBot);
	glVertex2f(wd2, wd2);
	glTexCoord2f((texWidth - 1) / 10.0 + 0.01, directionBot);
	glVertex2f(-wd2, wd2);

	glEnd();
}

void DrawBackground(float x, float y)
{


	float wd2 = x / 2;
	float ht2 = y / 2;
	glColor3f(1, 1, 1);
	//Draw a square
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 1.0);
	glVertex2f(-wd2, -ht2);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(wd2, -ht2);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(wd2, ht2);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(-wd2, ht2);

	glEnd();
}

int LoadTexture(int a, const char* tex) {
	a = SOIL_load_OGL_texture(tex, 4, 0, 0);
	if (!a) {
		printf("Texture not loaded!\n");

	}
	return a;
}



void init()
{
	glClearColor(0.0, 0.545, 0.765, 0.29); //specify background color

										   //	GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	//	GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};

	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	//	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	GLfloat pos[] = { 5.0, 5.0, 5.0, 0.0 };
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	glEnable(GL_TEXTURE_2D);





	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


}

void draw()
{
	glDrawBuffer(GL_BACK);  //specify buffer to draw to


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer



	glMatrixMode(GL_MODELVIEW);
	glColor3ub(0, 1, 0.5); //specify color to draw with
						   //	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	glTranslatef(3.5, 0.05, 0);
	bgID = LoadTexture(bgID, "background.png");
	glBindTexture(GL_POLYGON, bgID);
	DrawBackground(9, 1.9);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(moveX, 0, 0);
	texID = LoadTexture(texID, "atlas.png");
	glBindTexture(GL_QUADS, texID);
	DrawMario(0.2);

	glPopMatrix();

	glutSwapBuffers(); //swap front and back buffer

}
