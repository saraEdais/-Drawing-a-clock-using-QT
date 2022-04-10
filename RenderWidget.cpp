//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 24.02.2021
//


#include "RenderWidget.h"
#include <QPainter>
#include<cmath>
#include<iostream>
#include <math.h>
#include <windows.h>
#include <wingdi.h>

using namespace std;
RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent)
{
	// to be implemeted later
}

QSize RenderWidget::minimumSizeHint() const
{
	return QSize(100, 100);
}

QSize RenderWidget::sizeHint() const
{
	return QSize(800, 800);
}

void RenderWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	//    painter.setRenderHint(QPainter::Antialiasing, false);
	QColor color(0, 0, 0);
	painter.setPen(color);
	int startx = 390, starty = 408;
	for (int x = 0; x <= 95; ++x)
	{
		for(int i= 0 ; i<=5 ; i++)
			painter.drawPoint(startx, starty+i);
		startx++; starty--;
	}
	painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 80; j++)
			painter.drawPoint(398 + i, 390 + j);
	for (int i = 0; i < 5; i++)
	{
		DrawCircle2(400, 400, 198 + i);
	}
	for (int i = 0; i < 5; i++)
	{
		drawArc(400, 400, 228 + i, 30, 150);
	}

	DrawMinute(400, 400, 180);
	DrawMinute(400, 400, 179);
	for (int j = 0; j <= 6; j++)
		DrawCircle2(400, 400, j);

	
	//myDrawLine(400, 390, 398+i, 470, false);


  /*for (int x = 0; x <= 600; ++x)
  {
	painter.drawPoint(x, x);
  }*/

  //myDrawLine(10, 70, 50, 370);
}


void RenderWidget::myDrawLine(float x1, float y1, float x2, float y2, bool b)
{
	QPainter painter(this);

	//    painter.setRenderHint(QPainter::Antialiasing, false);
	QColor color(0, 0, 0);
	painter.setPen(color);

	float m = (y2 - y1) / (x2 - x1);
	//  SetPixel(x1, y1, color);   // first point
	painter.drawPoint(x1, y1);

	if (m < 1)
	{
		float y = y1;
		for (int i = x1 + 1; i < x2; ++i)
		{
			y = y + m;
			//      SetPixel(i, round(y), color);
			if (!b)
				painter.drawPoint(i, round(y));
			else
				draw7PixelsCircle(400, 400, i - 400, round(y) - 400);
		}
	}
	else     // i.e., m > 1
	{
		float mm = 1 / m;
		float x = x1;
		for (int i = y1 + 1; i < y2; ++i)
		{
			x = x + mm;
			//      SetPixel(round(x), i, color);
			//
			if (b)
				draw7PixelsCircle(400, 400, round(x), i);
			else
				painter.drawPoint(round(x), i);
		}
	}

	//  SetPixel(x2, y2, color);   // last point
   // painter.drawPoint(x2, y2);
}

void RenderWidget::DrawCircle(int xc, int yc, int r)
{
	QPainter painter(this);

	//    painter.setRenderHint(QPainter::Antialiasing, false);
	QColor color(255, 0, 0);
	painter.setPen(color);
	int x = 0, y = r, d = 3 - (2 * r);
	while (x <= y)
	{
		float eA = pow(x + 1, 2) + pow(y, 2) - pow(r, 2);
		float eB = pow(x + 1, 2) + pow(y - 1, 2) - pow(r, 2);
		int d = eA + eB;

		if (d <= 0) // choose A point 
		{
			d = d + (4 * x) + 6;
		}
		else //choose B point 
		{
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
		draw7PixelsCircle(xc, yc, x, y);
	}
}
void RenderWidget::draw7PixelsCircle(int xc, int yc, int x, int y)
{
	QPainter painter(this);
	painter.drawPoint(xc + x, yc + y);
	painter.drawPoint(xc - x, yc + y);
	painter.drawPoint(xc + x, yc - y);
	painter.drawPoint(xc - x, yc - y);
	painter.drawPoint(xc + y, yc + x);
	painter.drawPoint(xc - y, yc + x);
	painter.drawPoint(xc + y, yc - x);
	painter.drawPoint(xc - y, yc - x);
}

void RenderWidget::drawArc(int xc, int yc, int r, int startTheta, int endTheta)
{
	QPainter painter(this);
	int x, y;
	float pi = 3.141592653, DTheta = 1 / (r*1.0000);
	float angleFactor = pi / 180;

	pair<int, int> rightStart = { xc + round(r*cos(startTheta*angleFactor)), yc + round(r*sin(startTheta*angleFactor)) };
	for (float i = startTheta; i <= endTheta; i += DTheta)
	{
		x = xc + round(r*cos(i*angleFactor));
		y = yc + round(r*sin(i*angleFactor));
		painter.drawPoint(x, y);
	}
	pair<int, int> leftStart = { x,y };
	for (int i = 0; i < 140; ++i)
	{
		painter.drawPoint(leftStart.first - 1, leftStart.second - 1);
		painter.drawPoint(leftStart.first, leftStart.second);
		painter.drawPoint(leftStart.first + 1, leftStart.second + 1);
		leftStart.first -= 1;  leftStart.second += 1;
	}
	myDrawLine(rightStart.first - 1, rightStart.second, rightStart.first + 139, rightStart.second + 140, false);
	myDrawLine(rightStart.first, rightStart.second, rightStart.first + 140, rightStart.second + 140, false);
	myDrawLine(rightStart.first + 1, rightStart.second, rightStart.first + 141, rightStart.second + 140, false);
	myDrawLine(rightStart.first + 2, rightStart.second, rightStart.first + 142, rightStart.second + 140, false);
	myDrawLine(leftStart.first, leftStart.second, rightStart.first + 140, rightStart.second + 140, false);
	myDrawLine(leftStart.first, leftStart.second + 1, rightStart.first + 140, rightStart.second + 141, false);

}

void RenderWidget::DrawMinute(int xc, int yc, int r)
{
	QPainter painter(this);
	int cnt = 0;
	int x, y;
	float pi = 3.141592653;
	float angleFactor = pi / 180;

	for (float i = 0; i < 360; i += 6)
	{
		if (cnt % 5)
		{
			x = xc + round(r*cos(i*angleFactor));
			y = yc + round(r*sin(i*angleFactor));
			for (int j = 0; j <= 6; j++)
				DrawCircle2(x, y, j);
		}
		cnt++;
	}
	cnt = 0;
	for (int j = 0; j < 50; j++)
	{
		for (int k = 0; k < 5; k++)
			draw7PixelsCircle(xc, yc, 180 - j, -2 + k);
	}

	x = xc + round(r*cos(330 * angleFactor));
	y = yc + round(r*sin(330 * angleFactor));

	float rrr = sqrt(pow(x - xc, 2) + pow(y - yc, 2));
	float r2 = rrr / 4;
	int leny = r2 * sin(30 * angleFactor),
		lenx = r2 * cos(30 * angleFactor);
	int xprime = x - lenx, yprime = y + leny;

	for (int i = -2; i < 2; i++)
	{
		myDrawLine(xprime + i, yprime + i, x + i, y + i, true);
	}
}

void RenderWidget::DrawCircle2(int xc, int yc, int r)
{
	QPainter painter(this);
	int x, y;
	float pi = 3.141592653, DTheta = 1 / (r*1.0000);
	float angleFactor = pi / 180;

	for (float i = 0; i <= 360; i += DTheta)
	{
		x = xc + round(r*cos(i*angleFactor));
		y = yc + round(r*sin(i*angleFactor));
		painter.drawPoint(x, y);
	}
}