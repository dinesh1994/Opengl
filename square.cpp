#include <GL/freeglut.h>
#include <GL/gl.h>

GLsizei ww=500,wh=500;
GLfloat size = 3.0;

void drawSquare(int x, int y){

	y = wh - y;					/*we have to invert the y coordinate becoz 
								  for pointing device top-left is origin 
								  n in openGL bottom-left is origin*/
	glBegin(GL_POLYGON);
		glVertex2f(((GLfloat)x)-(size/2),((GLfloat)y)-(size/2));
		glVertex2f(((GLfloat)x)+(size/2),((GLfloat)y)-(size/2));
		glVertex2f(((GLfloat)x)+(size/2),((GLfloat)y)+(size/2));
		glVertex2f(((GLfloat)x)-(size/2),((GLfloat)y)+(size/2));
	glEnd();
	glFlush();
	}

void myDisplay(){							//Although there was no such need of this funtion
	glClear(GL_COLOR_BUFFER_BIT);			//But openGL restrict us to provide a display callback function
	}

void myInit(){

	glClearColor(0.0,0.0,0.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0.0,0.0,ww,wh);				//glViewPort(x,y,GLsizei x,GLsizer y)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,wh,0.0,ww);				//glOrtho(bottom,top,left,right,near,far)
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	
	}

void myMouse(int key, int state, int x, int y){

	if(key==GLUT_LEFT_BUTTON && state==GLUT_DOWN) drawSquare(x,y);
	if(key==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN) exit(0);

	}

void myMouse1(int x, int y){
	 drawSquare(x,y);
	}

void myReshape(GLsizei w, GLsizei h){

	//adjusting clipping box
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,h,0.0,w);
	glMatrixMode(GL_MODELVIEW);

	//adjusting clear and viewport
	glViewport(0.0,0.0,w,h);

	ww= w;
	wh= h;
	}

int main(int argc,char **argv){

	glutInit(&argc,argv);
	glutInitWindowSize(ww,wh);
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutCreateWindow("Draw Squares");
	myInit();
	glutReshapeFunc(myReshape);				//Calling window reshape func
	glutMouseFunc(myMouse);					//registering mouse function
	glutMotionFunc(myMouse1);
	glutDisplayFunc(myDisplay);				//OpenGL requires this func regardless it may contain nothing significant
	glutMainLoop();

return 1;
	}

