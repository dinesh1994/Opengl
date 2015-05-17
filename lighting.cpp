#include <GL\glut.h>
#include <GL\freeglut.h>
#include <iostream>

GLsizei ww=500,wh=500;
//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
					int x, int y) {    //The current mouse coordinates
	switch (key) {
		case 27: //Escape key
			exit(0); //Exit the program
	}
}

//Initializes 3D rendering
void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);			//Automatically normalize the light
	glShadeModel(GL_SMOOTH);
	glClearColor(1.0, 1.0, 1.0, 1.0);


}

//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
				   (double)w / (double)h, //The width-to-height ratio
				   1.0,                   //The near z clipping coordinate
				   200.0);                //The far z clipping coordinate
	// glOrtho(0.0, ww, 0.0, wh, 0.0, 200);
	
}

float rot = 30.0f;
float cam_angle = 0.0f;
//Draws the 3D scene
void drawScene() {
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	glTranslatef(0.0f,0.0f, -10.0f);

	//Add Ambient Light
	GLfloat ambientColor[] = {0.2 , 0.2, 0.2, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Setting Position of light
	GLfloat lightColor0[] = { 0.5, 0.5, 0.5, 1.0};
	GLfloat lightPos0[] = { 4.0, 0.0, 8.0, 1.0};		//4th parameter=1 tells that light has position
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	//direct the light
	GLfloat lightColor1[] = {0.5, 0.2, 0.2, 1.0};
	GLfloat lightPos1[] = { -1.0, 0.5, 0.5, 0.0};		//4th parameter=0 tells that light has direction

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	glPushMatrix();
	glRotatef( rot, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	
	//Front
	//glNormal3f( 0.0, 0.0, 1.0);
	glNormal3f( -1.0, 0.0, 1.0);
	glVertex3f(-1.5, -1.0, 1.5);
	glNormal3f( 1.0, 0.0, 1.0);
	glVertex3f(1.5, -1.0, 1.5);
	glNormal3f( 1.0, 0.0, 1.0);
	glVertex3f(1.5, 1.0, 1.5);
	glNormal3f( -1.0, 0.0, 1.0);
	glVertex3f(-1.5, 1.0, 1.5);
 
	//Right
	//glNormal3f(1.0, 0.0, 0.0);
	glNormal3f( -1.0, 0.0, -1.0);
	glVertex3f( 1.5 , -1.0, -1.5);
	glNormal3f( -1.0, 0.0, -1.0);
	glVertex3f( 1.5, 1.0, -1.5);
	glNormal3f( -1.0, 0.0, -1.0);
	glVertex3f( 1.5, 1.0, 1.5);
	glNormal3f( -1.0, 0.0, -1.0);
	glVertex3f( 1.5, -1.0, 1.5);

	//Back
	//glNormal3f(0.0, 0.0, -1.0);
	glNormal3f( -1.0, 0.0, -1.0);
	glVertex3f(1.5 , -1.0, -1.5);
	glNormal3f( -1.0, 0.0, -1.0);
	glVertex3f(1.5 , 1.0, -1.5);
	glNormal3f( 1.0, 0.0, -1.0);
	glVertex3f(-1.5, 1.0, -1.5);
	glNormal3f( 1.0, 0.0, -1.0);
	glVertex3f(-1.5, -1.0, -1.5);

	//Left
	//glNormal3f(-1.0, 0.0, 0.0);
	glNormal3f( -1.0, 0.0, -1.0);
	glVertex3f( -1.5, -1.0, -1.5);
	glNormal3f( -1.0, 0.0, 1.0);
	glVertex3f( -1.5, 1.0, -1.5);
	glNormal3f( -1.0, 0.0, 1.0);
	glVertex3f( -1.5, 1.0, 1.5);
	glNormal3f( -1.0, 0.0, -1.0);
	glVertex3f( -1.5, -1.0, 1.5);
	glEnd();
	glFlush();

	glPopMatrix();
	glutSwapBuffers(); //Send the 3D scene to the screen
}

void update(int value)
{
	rot += 2.0f;
	if(rot > 360)
	{
		rot -=360;
	}

	glutPostRedisplay();					//redisplaying scene
	glutTimerFunc(25, update, 0);			//calling update in 25ms
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400); //Set the window size
	glutInitWindowPosition(700,0);
	//Create the window
	glutCreateWindow("Basic Shapes - videotutorialsrock.com");
	initRendering(); //Initialize rendering
	
	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutTimerFunc(25, update, 0);			//calling update in 25ms
	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	
	return 1;								//This line is never reached
}