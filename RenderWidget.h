//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as 
// this commented part is listed
//
// Last modified by: Zein Salah, on 24.04.2018
//


#pragma once

#include <QWidget>

class RenderWidget : public QWidget
{
    Q_OBJECT

  public:
    RenderWidget(QWidget *parent = 0);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

	void myDrawLine(float x1, float y1, float x2, float y2, bool b);
	void DrawCircle(int xc, int yc, int r);
	void draw7PixelsCircle(int xc, int yc, int x, int y);
	void drawArc(int xc, int yc, int r, int startTheta, int endTheta);
	void DrawMinute(int xc, int yc, int r);
	void DrawCircle2(int xc, int yc, int r);
  protected:
    void paintEvent(QPaintEvent *event) override;

};
