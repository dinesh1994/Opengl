#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>


void Init(){
	glClearColor(1.0,1.0,1.0,1.0);						//OpenGL window clear color
	glColor3f(1.0,0.0,0.0);							//Graphic color i.e RED
/* setup viewing */

	glMatrixMode(GL_PROJECTION);					//
	glLoadIdentity();								//loading identity matrix in PROJECTION matrix
	glOrtho(0.0,50.0,0.0,50.0,10.0,0.0);					//glOrtho2D(left,right,bottom,top)
	glMatrixMode(GL_MODELVIEW);						//
	}

void display(){
	GLfloat vertices[4][3]={{0.0,0.0,0.0},{25.0,50.0,0.0},{50.0,0.0,0.0},{10.0,10.0,10.0}};
	
	int i,j,k;
	int rand();
	GLfloat p[3]={7.5,5.0,10.0};

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);

	for(k=0;k<1000000;k++){
		j=rand()%4;

		p[0] = (vertices[j][0]+p[0])/2;
		p[1] = (vertices[j][1]+p[1])/2;
		p[3] = (vertices[j][2]+p[2])/2;
		glVertex2fv(p);
		}
	
	glEnd();
	glFlush();
}

int main(int argc,char **argv){

glutInit(&argc ,argv);								//initiating interaction with window system
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);		//usig single buffer and RGB color
glutInitWindowSize(500,500);
glutInitWindowPosition(0,0);
glutCreateWindow("sierpinski triangle");
glutDisplayFunc(display);
Init();
glutMainLoop();

return 1;
}

