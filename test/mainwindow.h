/*====================================================================
 * Filename:      mainwindow.h
 * Version:       
 * Author:        Dianchun Huang <simpleotter23@gmail.com>
 * 
 * Copyright (c) 2013 Dianchun Huang (simpleotter23@gmail.com)
 * 
 * Created at:    Thu May 23 22:20:02 2013
 * Modified at:   Fri May 24 20:51:11 2013
 * Description:   
 *==================================================================*/
#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE
class QImage;
QT_END_NAMESPACE

class HeatMapper;

class MainWindow : public QWidget
{
public:
	enum {
		CANVAS_WIDTH = 1024,
		CANVAS_HEIGHT = 768,
		DEFAULT_RADIUS = 60,
		DEFAULT_OPACITY = 128
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
};

#endif /* _MAINWINDOW_H_ */

















