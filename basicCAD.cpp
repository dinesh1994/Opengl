#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_POLYGONS 10
#define MAX_VERTICES 10

/* global variable decl to handle unexpected mouse clicks */

bool picking = false;
bool moving = false;
int in_polygon = -1;			
int present_color = 0;			//default color index
GLsizei ww=500,wh=500;			//for dynamic window size
GLfloat colors[8][3] = {{0.0, 0.0, 0.0},{1.0, 0.0, 0.0},{0.0, 1.0, 0.0},{0.0,0.0,1.0},{0.0,1.0,1.0},{1.0,0.0,1.0},{1.0,1.0,0.0},{1.0,1.0,1.0}};

typedef struct polygon 			//this will hold info of polygon
{
	int color;
	bool used;
	int xmin, xmax, ymin, ymax;
	int nvertices;
	float xc,yc;
	int x[MAX_VERTICES];
	int y[MAX_VERTICES];
} polygon;

polygon polygons[MAX_POLYGONS];

void myReshape(int w, int h);
void myDisplay();
void myMouse(int btn, int state, int x, int y);
void myInit();
void myMotion(int x, int y);
void main_menu(int index);
int pick_polygon(int x, int y);
void color_menu(int id);

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(ww,wh);
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutCreateWindow("Draw Squares");
	glutDisplayFunc(myDisplay);
	myInit();

	int c_menu;
	c_menu = glutCreateMenu(color_menu);
	glutAddMenuEntry("Black",0);
	glutAddMenuEntry("Red",1);
	glutAddMenuEntry("Green",2);
	glutAddMenuEntry("Blue",3);
	glutAddMenuEntry("Cyan",4);
	glutAddMenuEntry("Magenta",5);
	glutAddMenuEntry("Yellow",6);
	glutAddMenuEntry("White",7);

	glutCreateMenu(main_menu);
	glutAddMenuEntry("new polygon",1);
	glutAddMenuEntry("end polygon",2);
	glutAddMenuEntry("delete polygon",3);
	glutAddMenuEntry("move polygon",4);
	glutAddMenuEntry("quit",5);
	glutAddSubMenu("Colors", c_menu);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	glutReshapeFunc(myReshape);
	glutMotionFunc(myMotion);
	glutMouseFunc(myMouse);
	glutMainLoop();

return 1;
}

int pick_polygon(int x, int y)
{
	int i;
	for(i=0; i<MAX_POLYGONS; i++)
	{
		if(polygons[i].used)
		{
			if((x>=polygons[i].xmin)&&(x<=polygons[i].xmax)&&
				(y>=polygons[i].ymin)&&(y<=polygons[i].ymax))
			{
				in_polygon = i;
				moving = true;
				return i;
			}
		}
	}
	printf("no polygon is selected\n");
	return -1;
}

void myDisplay()
{
	for(int i=0;i<MAX_POLYGONS; i++)
	{
		if(polygons[i].used)
		{
			glColor3fv(colors[polygons[i].color]);
			glBegin(GL_POLYGON);
				for(int j=0; j<polygons[i].nvertices; j++)
					glVertex2i(polygons[i].x[j],polygons[i].y[j]);
			glEnd();
		}
	}
}


void color_menu(int id)
{
	present_color = id;
	if(in_polygon>=0) polygons[in_polygon].color = id;
}

void main_menu(int index)
{
	switch(index)
	{
		case 1:	
				moving = false;
				int i;
				for(i=0; i<MAX_POLYGONS; i++)
					if(polygons[i].used == false) break;
				if(i == MAX_POLYGONS)
				{
					printf("max no of polygons NO MORE ALLOWED\n");
					exit(0);
				}
				polygons[i].color = present_color;
				polygons[i].used = true;
				polygons[i].nvertices = 0;
				in_polygon = i;
				picking = false;
				break;
		case 2: 
				moving = false;
				if(in_polygon>=0)
				{	
					polygons[in_polygon].xmax = polygons[in_polygon].xmin = polygons[in_polygon].x[0];
					polygons[in_polygon].ymax = polygons[in_polygon].ymin = polygons[in_polygon].y[0];
					polygons[in_polygon].xc = polygons[in_polygon].x[0];
					polygons[in_polygon].yc = polygons[in_polygon].y[0];

					for(int i=0;i<polygons[in_polygon].nvertices;i++)
					{
						if(polygons[in_polygon].x[i]<polygons[in_polygon].xmin)
								polygons[in_polygon].xmin = polygons[in_polygon].x[i];
						else if(polygons[in_polygon].x[i]>polygons[in_polygon].xmax)
								polygons[in_polygon].xmax = polygons[in_polygon].x[i];

						if(polygons[in_polygon].y[i]<polygons[in_polygon].ymin)
								polygons[in_polygon].ymin = polygons[in_polygon].y[i];
						else if(polygons[in_polygon].y[i]>polygons[in_polygon].ymax)
								polygons[in_polygon].ymax = polygons[in_polygon].y[i];	
					
						polygons[in_polygon].xc += polygons[in_polygon].x[i];
						polygons[in_polygon].yc += polygons[in_polygon].y[i];						
					}

					polygons[in_polygon].xc = (polygons[in_polygon].xmin / polygons[in_polygon].nvertices);
					polygons[in_polygon].yc = (polygons[in_polygon].ymin / polygons[in_polygon].nvertices);
				}
				in_polygon = -1;
				glutPostRedisplay();
				break;
		case 3: 
				picking = true;
				moving = false;
				break;
		case 4:
				moving = true;
				break;
		case 5:
				exit(0);
				break;
		default:
			printf("no match ERROR\n");
			exit(0);
	}
}

void myMouse(int btn,int state,int x,int y)
{	
	int i;
	y = (int)wh - y;			//inverting y as for pointing device top-left is origin

	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&!picking && !moving)
	{
		moving = false;
		if(in_polygon>=0)
		{
			if(polygons[in_polygon].nvertices == MAX_VERTICES)
			{
				printf("exceeds max number vertices\n");
				exit(0);
			}
			
			i=polygons[in_polygon].nvertices;
			polygons[in_polygon].x[i] = x;
			polygons[in_polygon].y[i] = y;
			polygons[in_polygon].nvertices++;
		}
	}

	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN && picking && !moving)
	{
		picking = false;
		moving = false;
		int j = pick_polygon(x,y);
		if(j>=0)
		{
			polygons[j].used = false;		//Selected object deleted by turning used to false
			in_polygon = -1;
			glutPostRedisplay();
		}
	}		
}

void myInit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	for(int i=0;i<MAX_POLYGONS;i++)
		polygons[i].used = false;
}

void myMotion(int x,int y)
{
	float dx, dy;
	int i,j;
	if(moving)
	{
		y = (int)wh - y;
		j = pick_polygon(x, y);
		if(j<0) return;
		dx = x - polygons[j].xc;
		dy = y - polygons[j].yc;

		for(i=0; i<polygons[j].nvertices; i++)
		{
			polygons[j].x[i] += dx;
			polygons[j].y[i] += dy;
		}
		polygons[j].xc += dx;
		polygons[j].yc += dy;

		polygons[j].xmin += dx;			//if(dx>0)
		polygons[j].xmax += dx;			//else
		polygons[j].ymin += dy;			//if(dy>0)
		polygons[j].ymax += dy;			//else
		glutPostRedisplay();
	}
}

void myReshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0.0,0.0,w,h);

	ww = w;
	wh = h;
}