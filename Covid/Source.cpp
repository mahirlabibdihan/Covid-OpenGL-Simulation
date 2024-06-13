#include <GL/glut.h>
#include <math.h>

#define HEIGHT 750
#define WIDTH 1200
#define PI (acos(-1.0))
GLfloat r = 0;
GLfloat sz = 10,ds=.2;
GLfloat zoom = 0.8;

void line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void rectangle(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h)
{
	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x+w, y, z);
	glVertex3f(x+w, y+h, z);
	glVertex3f(x, y+h, z);
	glEnd();
}
void circle(GLfloat x, GLfloat y, GLfloat z, GLfloat r)
{
	glBegin(GL_POLYGON);
	for (GLfloat t = 0; t <= 2 * PI ; t += 0.01)
	{
		glVertex3f(x + r * cos(t), y + r * sin(t), z);
	}
	glEnd();
}
void text(GLfloat x, GLfloat y, const char* str, GLfloat sz)
{
	glLineWidth(2.0);
	glPushMatrix();
	glTranslatef(x, y, 1);
	glScalef(sz, 1.3 * sz, 1.0);
	for (GLint i = 0; str[i]; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	glPopMatrix();
	glLineWidth(1.0);
}

void spikes()
{
	for (GLfloat t = 0; t < 2 * PI; t += 0.5)
	{
		GLfloat x = 218 * cos(t), y = 218 * sin(t);
		glPushMatrix();
		glTranslatef(y, 0, x);
		glRotatef(t * 180 / PI, 0, 1, 0);
		glRotatef(180, 1, 0, 0);
		glutSolidCone(sz,2*sz, 20, 20);
		glPopMatrix();
	}
}
void virus()
{
	glPushMatrix();

	glRotatef(r, 1, 0, 0);
	glRotatef(r, 0, 1, 0);
	glRotatef(r, 0, 0, 1);

	glPushMatrix();
	glColor3f(177 / 255.0, 103 / 255.0, 130 / 255.0);
	glutSolidSphere(200, 20, 20);
	glPopMatrix();


	for (GLfloat i = 0; i < 2 * PI; i += .5)
	{
		glPushMatrix();
		glRotatef(i * 180 / PI, 0, 1, 0);
		glRotatef(i * 180 / PI, 1, 0, 0);
		glColor3f(124 / 255.0, 27 / 255.0, 58 / 255.0);
		spikes();
		glPopMatrix();
	}

	glPopMatrix();

	glFlush();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor4f(0, 0, 0,0.5);
	circle(0, 500, -1, 300);

	glColor3f(1, 0, 0);
	text(-190, 300, "CORONA VIRUS" ,.4);
	line(-150, 280, 150, 280);

	glPushMatrix();
	glColor4f(0, 0, 0, .3);
	glTranslatef(-900, -400, 0);
	glRotatef(-45, 0, 0, 1);
	rectangle(0, 0, 0, 1000, 400);
	glPopMatrix();


	glPushMatrix();
	glColor4f(0, 0, 0, .3);
	glTranslatef(180, -1110, 0);
	glRotatef(45, 0, 0, 1);
	rectangle(0, 0, 0, 1000, 400);
	glPopMatrix();

	glPushMatrix();
	glScalef(zoom, zoom, zoom);
	glPushMatrix();
	glTranslatef(0,100,0);
	glScalef(1,1,1);
	virus();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-200,-500,0);
	glScalef(0.8,0.8,0.8);
	virus();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-600,-200,0);
	glScalef(0.8,0.8,0.8);
	virus();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-400,400,0);
	glScalef(0.7,0.7,0.7);
	virus();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(500,500,0);
	glScalef(0.7,0.7,0.7);
	virus();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(500,-200,0);
	glScalef(0.6,0.6,0.6);
	virus();
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -w / 2, h / 2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void init()
{
	const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

	const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat high_shininess[] = { 100.0f };
	glClearColor(28/255.0, 34/255.0, 46/255.0, 1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glEnable(GL_LINE_SMOOTH);
	glLineWidth(3.0);
}

void update(int n)
{
	if (sz >= 20)
	{
		ds *= -1;
		sz = 20;
	}
	else if (sz <= 10)
	{
		ds *= -1;
		sz = 10;
	}
	sz += ds;
	r+=0.1;

	glutPostRedisplay();
	glutTimerFunc(n, update, n);
}

void keyboard(unsigned char key,int,int)
{
	switch (key)
	{
	case '+':
		zoom *= 1.01;
		break;
	case '-':
		zoom /= 1.01;
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Corona");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(10, update, 10);
	glutMainLoop();
	return 0;
}
