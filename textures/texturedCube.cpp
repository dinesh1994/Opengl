#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include <GL/freeglut.h>
#include <GL/gl.h>

#include "imageloader.h"

using namespace std;

//Global variables
GLuint textureID;
GLfloat BOX_SIZE = 10.0;
GLfloat theta = 0.0;

GLuint getTexID(Image *image);
void update(int value);
void myInit();
void myDisplay();
void myReshape(int x, int y);
void myKeyboard(unsigned char key, int x, int y);


int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(700,0);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	
	glutCreateWindow("Cube Texture");
	myInit();
	
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(myKeyboard);
	glutTimerFunc(25, update ,0);
	glutMainLoop();
	return 1;
}

void myDisplay()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();

	//glPushMatrix();
	glTranslatef(0.0 , 0.0 , -20.0);

	GLfloat ambientLight[] = {0.2 , 0.2, 0.2, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat lightColor0[] = {0.3, 0.3, 0.3};
	GLfloat lightPos0[] = {-2*BOX_SIZE, BOX_SIZE, 4*BOX_SIZE, 1.0};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	glRotatef(-theta , 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);

	//top face
	glColor3f(1.0 , 1.0, 0.0);
	glNormal3f(0.0 , 1.0, 0.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(5.0 , 5.0, 5.0);
	glVertex3f(5.0 , 5.0, -5.0);
	glVertex3f(-5.0 , 5.0, -5.0);

	//Bottom face
	glColor3f(0.0 , 1.0, 0.0);
	glNormal3f(0.0 , -1.0, 0.0);
	glVertex3f(-5.0 , -5.0, 5.0);
	glVertex3f(5.0 , -5.0, 5.0);
	glVertex3f(5.0 , -5.0, -5.0);
	glVertex3f(-5.0 , -5.0, -5.0);

	//left face
	glColor3f(0.0 , 0.5, 0.5);
	glNormal3f(-1.0 , 0.0, 0.0);
	glVertex3f(-5.0 , -5.0, 5.0);
	glVertex3f(-5.0 , 5.0, 5.0);
	glVertex3f(-5.0 , 5.0, -5.0);
	glVertex3f(-5.0 , -5.0, -5.0);

	//right face
	glColor3f(0.0 , 0.0, 1.0);
	glNormal3f(1.0 , 0.0, 0.0);
	glVertex3f(5.0 , -5.0, 5.0);
	glVertex3f(5.0 , 5.0, 5.0);
	glVertex3f(5.0 , 5.0, -5.0);
	glVertex3f(5.0 , -5.0, -5.0);

	//back face
	glColor3f(1.0 ,0.0,0.0);
	glNormal3f(0.0 , 0.0 , -1.0);
	glVertex3f(-5.0 , -5.0, -5.0);
	glColor3f(0.0,0.5,1.0);
	glVertex3f(5.0 , -5.0, -5.0);
	glColor3f(0.0 ,1.0,0.0);
	glVertex3f(5.0 , 5.0, -5.0);
	glColor3f(0.0,1.0,1.0);
	glVertex3f(-5.0 , 5.0, -5.0);

	glEnd();

	//front face
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor3f(1.0,1.0,1.0);

	glBegin(GL_QUADS);

	glNormal3f(0.0 , 0.0 , 1.0);
	glTexCoord2f(0.0 , 0.0);
	glVertex3f(-5.0 , -5.0, 5.0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(5.0 , -5.0, 5.0);

	glTexCoord2f(1.0 , 1.0);
	glVertex3f(5.0 , 5.0, 5.0);

	glTexCoord2f(0.0 ,1.0);
	glVertex3f(-5.0 , 5.0, 5.0);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();

}

void update(int value)
{
	theta += 1.0;
	if(theta>=360){
		theta -= 360;
	}
	glutPostRedisplay();
	glutTimerFunc(25,update,0);
}

GLuint getTexID(Image *image)
{
	GLuint texID;
	glGenTextures(1,&texID);
	glBindTexture( GL_TEXTURE_2D, texID);
	glTexImage2D( GL_TEXTURE_2D,
				  0,
				  GL_RGB,				//Format 
				  image->width,
				  image->height,
				  0,
				  GL_RGB,				//pixels are stored in RGB format
				  GL_UNSIGNED_BYTE,
				  image->pixels);		//Image data
	return texID;
}

void myInit()
{
	glClearColor(1.0,1.0,1.0,1.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 200.0);
	
	Image* img = loadBMP("tiles.bmp");
	textureID = getTexID(img);
	delete img;				//becoz BMP image uses lots of memory
}


void myReshape(int w,int h)
{
	glViewport(0.0,0.0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w/(float)h,1.0,200);

}

void myKeyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27: 
				exit(0);
	}
}