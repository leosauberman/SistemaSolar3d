#ifdef _WIN32
#include <Windows.h>
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#define PI 3.14159265f
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL\GL.h> // Funções do OpenGL
#include <GL\GLU.h> // Funções adicionais do OpenGL
#include <GL\glut.h> //Gerenciador de Janelas

#include "texture.h"

Texture background;

float scale = 0.03;
float posX = 0;
float posY = 0;
float time_scale = 0.01;

void drawPlanet(double r)
{
	gluSphere(gluNewQuadric(), r, 150, 150);
}

void drawOrbit(float r)
{
	glDisable(GL_TEXTURE_2D);
	glLineStipple(1, 0x00FF);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINE_LOOP);
	for (float a = 0; a < 2 * PI; a += 0.01f)
	{
		double x = sin(a)*r;
		double y = cos(a)*r;
		glVertex2d(x, y);
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

void drawComet()
{
	static float x = 0;
	glPushMatrix();
	glTranslatef(100, 100, 0);
	glRotatef(180 + 45, 0, 0, 1);
	glTranslatef(x, 0, 0);
	drawPlanet(1);
	glPopMatrix();
	x += 0.1*time_scale;
}

void display() {
	//Dados tirados de : https://nssdc.gsfc.nasa.gov/planetary/factsheet/planetfact_ratio_notes.html#orbv

	glClear(GL_COLOR_BUFFER_BIT);

	float raio_da_terra = 0.1;
	float distancia_terra_sol = 1;

	glLoadIdentity();
	glTranslatef(posX, posY, 0);
	glScalef(scale, scale, 1);

	background.Use();
	background.SetRepeat();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 35);
	glVertex2f(-100, 100);
	glTexCoord2f(35, 35);
	glVertex2f(100, 100);
	glTexCoord2f(35, 0);
	glVertex2f(100, -100);
	glTexCoord2f(0, 0);
	glVertex2f(-100, -100);
	glEnd();

	//Sol-------------------------------------------------------------
	drawPlanet(0.25);

	//Mercurio----------------------------------------------------------
	static float mercurioAng = 0;
	glPushMatrix();
	drawOrbit(distancia_terra_sol*0.387);
	glRotatef(mercurioAng, 0, 0, 1);
	glTranslatef(distancia_terra_sol*0.387, 0, 0);
	drawPlanet(raio_da_terra*0.383);
	glPopMatrix();
	mercurioAng += time_scale* 4.092304194611799;

	//Vênus-------------------------------------------------------------
	static float venusAng = 0;
	glPushMatrix();
	drawOrbit(distancia_terra_sol*0.723);
	glRotatef(venusAng, 0, 0, 1);
	glTranslatef(distancia_terra_sol*0.723, 0, 0);
	drawPlanet(raio_da_terra*0.949);
	glPopMatrix();
	venusAng += time_scale* 1.602136181575434;

	//Terra-------------------------------------------------------------
	static float terraAng = 0;
	glPushMatrix();
	drawOrbit(distancia_terra_sol);
	glRotatef(terraAng, 0, 0, 1);
	glTranslatef(distancia_terra_sol, 0, 0);
	drawPlanet(raio_da_terra);
	//Lua
	static float luaAng = 0;
	glPushMatrix();
	drawOrbit(0.15f);
	glRotatef(luaAng, 0, 0, 1);
	glTranslatef(0.15, 0, 0);
	drawPlanet(raio_da_terra*0.2724);
	glPopMatrix();
	luaAng += time_scale * 131399.9999999981;
	glPopMatrix();
	terraAng += time_scale* 0.9863013698630137;

	//Marte-------------------------------------------------------------
	static float marteAng = 0;
	glPushMatrix();
	drawOrbit(distancia_terra_sol*1.52);
	glRotatef(marteAng, 0, 0, 1);
	glTranslatef(distancia_terra_sol*1.52, 0, 0);
	drawPlanet(raio_da_terra*0.532);
	glPopMatrix();
	marteAng += time_scale* 0.5240327229322542;

	//Júpter-------------------------------------------------------------
	static float jupterAng = 0;
	glPushMatrix();
	drawOrbit(distancia_terra_sol*5.20);
	glRotatef(jupterAng, 0, 0, 1);
	glTranslatef(distancia_terra_sol*5.20, 0, 0);
	drawPlanet(raio_da_terra*11.21);
	glPopMatrix();
	jupterAng += time_scale* 0.0830867656630093;

	//Saturno-------------------------------------------------------------
	static float saturnoAng = 0;
	glPushMatrix();
	drawOrbit(distancia_terra_sol*9.58);
	glRotatef(saturnoAng, 0, 0, 1);
	glTranslatef(distancia_terra_sol*9.58, 0, 0);
	drawPlanet(raio_da_terra*9.45);

	static float anelAng = 0;
	glRotatef(anelAng, 0, 0, 1);
	glBegin(GL_QUAD_STRIP);
	for (float ang = 0; ang <= (PI * 2) + 0.01; ang += 0.01)
	{
		float texX = sin(ang)*0.35 + 0.5;
		float texY = cos(ang)*0.35 + 0.5;
		glTexCoord2f(texX, texY);
		double x = sin(ang) * 1.;
		double y = cos(ang) * 1;
		glVertex2f(x, y);

		texX = sin(ang)*0.5 + 0.5;
		texY = cos(ang)*0.5 + 0.5;
		glTexCoord2f(texX, texY);

		x = sin(ang) * 1.5;
		y = cos(ang) * 1.5;
		glVertex2f(x, y);
	}
	glEnd();
	anelAng += time_scale * 10;

	glPopMatrix();
	saturnoAng += time_scale* 0.0334706248779717;

	//Urano-------------------------------------------------------------
	static float uranoAng = 0;
	glPushMatrix();
	drawOrbit(distancia_terra_sol*19.20);
	glRotatef(uranoAng, 0, 0, 1);
	glTranslatef(distancia_terra_sol*19.20, 0, 0);
	drawPlanet(raio_da_terra*4.01);
	glPopMatrix();
	uranoAng += time_scale* 0.0117312946950108;

	//Netuno-------------------------------------------------------------
	static float netunoAng = 0;
	glPushMatrix();
	drawOrbit(distancia_terra_sol*30.05);
	glRotatef(netunoAng, 0, 0, 1);
	glTranslatef(distancia_terra_sol*30.05, 0, 0);
	drawPlanet(raio_da_terra*3.88);
	glPopMatrix();
	netunoAng += time_scale* 0.0059810569956519;

	//Executa os comando e desenha na tela
	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void keypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i':
		scale += 0.05;
		break;
	case 'o':
		scale -= 0.05;
		if (scale < 0.03) {
			scale = 0.03;
		}
		break;
	case 'u':
		posY += 0.05;
		if (posY > 1.9099*scale / 0.03) {
			posY = 1.9099*scale / 0.03;
		}
		break;
	case 'd':
		posY -= 0.01;
		if (posY < -1.9099*scale / 0.03) {
			posY = -1.9099*scale / 0.03;
		}
		break;
	case 'r':
		posX += 0.01;
		if (posX > 1.9099*scale / 0.03) {
			posX = 1.9099*scale / 0.03;
		}
		break;
	case 'l':
		posX -= 0.01;
		if (posX < -1.9099*scale / 0.03) {
			posX = -1.9099*scale / 0.03;
		}
		break;
	case 'y':
		posX = 0;
		posY = 0;
		scale = 0.03;
		time_scale = 0.01;
	case 'm':
		time_scale += 0.1;
		break;
	case 'n':
		time_scale -= 0.1;
		if (time_scale <= 0) {
			time_scale = 0.01;
		}
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamanho da janela

	glutCreateWindow("Sistema Solar"); // Cria uma janela com o argumento como nome
	glutReshapeFunc(reshape); //Função que será chamada ao redimensionar a janela
	glutDisplayFunc(display);
	glutKeyboardFunc(keypress);

	glEnable(GL_TEXTURE_2D);

	/*comet.load("comet.bmp");
	background.load("background.bmp");
	sun.load("sun.bmp");
	mercury.load("mercury.bmp");
	venus.load("venus.bmp");
	earth.load("earth.bmp");
	moon.load("moon.bmp");
	mars.load("mars.bmp");
	jupiter.load("jupiter.bmp");
	saturno.load("saturn.bmp");
	anelsaturno.load("saturn_rings.bmp");
	uranus.load("uranus.bmp");
	neptune.load("neptune.bmp");*/
	glutMainLoop();
}

