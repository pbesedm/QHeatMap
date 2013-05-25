/*====================================================================
 * Filename:      mainwindow.h
 * Version:       
 * Author:        Dianchun Huang <simpleotter23@gmail.com>
 * 
 * Copyright (c) 2013 Dianchun Huang (simpleotter23@gmail.com)
 * 
 * Created at:    Thu May 23 22:20:02 2013
 * Modified at:   Sat May 25 10:54:24 2013
 * Description:   
 *==================================================================*/
#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE
class QImage;
QT_END_NAMESPACE

class HeatMapper;
class GradientPalette;

class MainWindow : public QWidget
{
public:
	enum {
		CANVAS_WIDTH = 1000,
		CANVAS_HEIGHT = 700,
		DEFAULT_RADIUS = 60,
		DEFAULT_OPACITY = 128,
		DEFAULT_WIDTH = 255
	};
	
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

protected:
	void paintEvent(QPaintEvent *);
	void mouseReleaseEvent(QMouseEvent *e);

private:
	// 绘图对象指针
	HeatMapper *mapper_;
	// 用于显示输出的图像
	QImage *canvas_;
	// 调色板
	GradientPalette *palette_;
};

#endif /* _MAINWINDOW_H_ */

















