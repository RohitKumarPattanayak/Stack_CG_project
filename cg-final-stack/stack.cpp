#include<iostream>
#include<cstring>
#include<string>
#include<Windows.h>
#include<GL/glut.h>
#include <cstdlib>

using namespace std;

struct elem
{
	char c[20];
};

int MAX;
int tos = -1;
int width = 200;
int height = 25;
elem a[20];
int SCREEN_WIDTH = 500;
int SCREEN_HEIGHT = 500;

bool init()
{
	glClearColor(0, 0, 0, 1); 
	glViewport(0, 0, 500, 500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-250, 250, -250, 250, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLenum error = glGetError();

	if (error != GL_NO_ERROR) 
	{
		return false; 
	}

	return true;  
}
void show();

void drawBitmap(char* string, int x, int y)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < strlen(string); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void push()
{
	if (tos >= MAX)
	{
		drawBitmap("STACK IS FULL", -100, 220);
		glutSwapBuffers();
		Sleep(100);
	}
	else {
		tos++;
		printf("\nEnter the Element: ");
		cin >> a[tos].c;
		cout << endl;
		show();
	}
}
void show()
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(0, -200, 0);

	int k = 0;

	for (int i = 0; i <= tos; i++) {

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
		glVertex2f(-100, k);
		glVertex2f(100, k);
		glVertex2f(100, k + 50);
		glVertex2f(-100, k + 50);
		glEnd();

		glRasterPos2f(-2, (k + 10));

		for (int j = 0; j < strlen(a[i].c); j++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a[i].c[j]);
		}
		k += 50;
	}
	glutSwapBuffers();
	glPopMatrix();
	

}
void render() 
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (tos == -1)
	{
		char* c;
		
		c = "WORKING OF STACK'S";
		glRasterPos2i(-120, 196);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		c = "---------------------";
		glRasterPos2i(-130, 178);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		c = "1)Press button-(i) for Push().";
		glRasterPos2i(-130, 160);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		 c = "2)Press button-(r) for Pop().";
		glRasterPos2i(-130, 130);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		c = "3)Press button-(p) for peek().";
		glRasterPos2i(-130, 100);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		c = "4)Press button-(q) for exit().";
		glRasterPos2i(-130, 70);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		c = "---------------------";
		glRasterPos2i(-130, 50);
		for (int i = 0; i < strlen(c); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
		glFlush();
		glutSwapBuffers();
	}
	else {
		glFlush();
		show();
	}
}
void pop()
{
	if (tos < 0)
	{
		drawBitmap("STACK IS EMPTY", -100, 220);
		glutSwapBuffers();
		Sleep(1000);
	}
	else
	{
		cout << "\nElement " << a[tos].c << " is removed from stack\n";
		tos--;
		show();
	}
}
void peek() {
	if (tos < 0)
	{
		drawBitmap("STACK IS EMPTY", -100, 220);
		glutSwapBuffers();
	}
	else {
		cout << "element at the top is " << a[tos].c << endl;
	}
}
void reshape(int w, int h) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h); 
	glOrtho(-250, 250, -250, 250, -100, 100); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i': push();
		break;
	case 'r': pop();
		render();
		break;
	case 'p': peek();
		break;
	case 'q': exit(0);
	}
}
int main(int argc, char* argv[])
{
	int m;
	cout<< "enter the size for the stack :" << endl;
	cin >>m;
	MAX = m - 1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("STACK");

	if (!init()) 
	{
		cout << "Error" << endl;
		return -1;
	}
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(render);  
	glutReshapeFunc(reshape);
	glutMainLoop();
return 0;
}