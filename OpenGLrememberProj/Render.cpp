

#include "Render.h"

#include <cmath>
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>

using namespace std;

double func_ermit(double p1, double p4, double r1, double r4, double t)
{
	return p1 * (2 * pow(t, 3) - 3 * pow(t, 2) + 1) + p4 * (-2 * pow(t, 3) + 3 * pow(t, 2)) + r1 * (pow(t, 3) - 2 * pow(t, 2) + t) + r4 * (pow(t, 3) - pow(t, 2));
}

inline double func_bez(double p0, double p1, double p2, double p3, double t)
{
	return (1 - t) * (1 - t) * (1 - t) * p0 + 3 * t * (1 - t) * (1 - t) * p1 + 3 * t * t * (1 - t) * p2 + t * t * t * p3;
}



double t_max = 0;
void Render(double delta_time)
{
	double quad1[] = { 1,1,0 };
	double quad2[] = { 1,-1,0 };
	double quad3[] = { -1,-1,0 };
	double quad4[] = { -1,1,0 };


	t_max += delta_time / 5; //t_max ���������� = 1 �� 5 ������
	if (t_max > 1) t_max = 0; //����� ����������

	double P0[] = { 0,0,0 };
	double P1[] = { -3,3,9 }; //���� �����
	double P2[] = { -4,7,7 };
	double P3[] = { -10,10,0 };
	double P[3];

	glBegin(GL_LINE_STRIP); //�������� ������� P1P2 � P2P3
	glVertex3dv(P0);
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glEnd();
	glLineWidth(3); //������ �����
	glColor3d(0, 1, 0);

	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= t_max; t += 0.01)
	{
		P[0] = func_bez(P0[0], P1[0], P2[0], P3[0], t);
		P[1] = func_bez(P0[1], P1[1], P2[1], P3[1], t);
		P[2] = func_bez(P0[2], P1[2], P2[2], P3[2], t);
		glVertex3dv(P); //������ ����� P


	}
	glEnd();
	glColor3d(1, 0, 1);
	glLineWidth(1); //���������� ������ ����� = 1
	//�������� ��� �����
	glPointSize(10);
	
	glBegin(GL_POINTS);
	glVertex3dv(P);
	glEnd();
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex3dv(P0);
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glEnd();


	double G0[] = { 0,0,0 };
	double G1[] = { -2,-3,9 }; //���� �����
	double G2[] = { -1,-7,7 };
	double G3[] = { -15,-10,0 };
	double G[3];

	glBegin(GL_LINE_STRIP); //�������� ������� P1P2 � P2P3
	glVertex3dv(G0);
	glVertex3dv(G1);
	glVertex3dv(G2);
	glVertex3dv(G3);
	glEnd();
	glLineWidth(3); //������ �����
	glColor3d(0, 1, 0);

	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= t_max; t += 0.01)
	{
		G[0] = func_bez(G0[0], G1[0], G2[0], G3[0], t);
		G[1] = func_bez(G0[1], G1[1], G2[1], G3[1], t);
		G[2] = func_bez(G0[2], G1[2], G2[2], G3[2], t);
		glVertex3dv(G); //������ ����� P
	}
	glEnd();
	glColor3d(1, 0, 1);
	glLineWidth(1); //���������� ������ ����� = 1
	//�������� ��� �����
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3dv(G);
	glEnd();
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex3dv(G0);
	glVertex3dv(G1);
	glVertex3dv(G2);
	glVertex3dv(G3);
	glEnd();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//ermit

	double O1[] = { 0,0,0 }; //Наши точки
	double O2[] = { 2,4,8 };
	double O3[] = { 6,10,4 };
	double O4[] = { 2, 4,-4 };
	double O6[] = { 8,14,0 };
	double O[4];
	glBegin(GL_LINE_STRIP);
	glVertex3dv(O1);
	glVertex3dv(O2);

	glEnd();
	glBegin(GL_LINE_STRIP);

	glVertex3dv(O3);
	glVertex3dv(O6);
	glEnd();
	glLineWidth(3); //ширина линии
	glColor3d(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= t_max; t += 0.01)
	{
		O[0] = func_ermit(O1[0], O2[0], O3[0], O4[0], t);
		O[1] = func_ermit(O1[1], O2[1], O3[1], O4[1], t);
		O[2] = func_ermit(O1[2], O2[2], O3[2], O4[2], t);
		O[3] = func_ermit(O1[3], O2[3], O3[3], O4[3], t);
		glVertex3dv(O); //Рисуем точку P
	}
	glEnd();
	glColor3d(1, 0, 1);
	glLineWidth(1); //возвращаем ширину линии = 1
	//нарисуем все точки
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3dv(O);
	glEnd();
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex3dv(O1);
	glVertex3dv(O2);
	glVertex3dv(O3);
	glVertex3dv(O6);
	glEnd();




	//кривая Эрмита (2)
	double O11[] = { 0,0,0 }; //Наши точки
	double O22[] = { 4,2,12 };
	double O33[] = { 10,4,2 };
	double O44[] = { 4, 2,-4 };
	double O66[] = { 14,6,0 };
	double O5[4];
	glBegin(GL_LINE_STRIP);
	glColor3d(0, 0, 0);
	glVertex3dv(O11);
	glVertex3dv(O22);

	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3d(0, 0, 0);
	glVertex3dv(O33);
	glVertex3dv(O66);
	glEnd();
	glLineWidth(3); //ширина линии
	glColor3d(0, 0, 1);
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= t_max; t += 0.01)
	{
		O5[0] = func_ermit(O11[0], O22[0], O33[0], O44[0], t);
		O5[1] = func_ermit(O11[1], O22[1], O33[1], O44[1], t);
		O5[2] = func_ermit(O11[2], O22[2], O33[2], O44[2], t);
		O5[3] = func_ermit(O11[3], O22[3], O33[3], O44[3], t);
		glVertex3dv(O5); //Рисуем точку P
	}
	glEnd();
	glColor3d(1, 0, 1);
	glLineWidth(1); //возвращаем ширину линии = 1
	//нарисуем все точки
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3dv(O5);
	glEnd();
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex3dv(O11);
	glVertex3dv(O22);
	glVertex3dv(O33);
	glVertex3dv(O66);
	glEnd();
}