/*====================================================================
 * Filename:      mainwindow.cpp
 * Version:       
 * Author:        Dianchun Huang <simpleotter23@gmail.com>
 * 
 * Copyright (c) 2013 Dianchun Huang (simpleotter23@gmail.com)
 * 
 * Created at:    Thu May 23 22:42:06 2013
 * Modified at:   Sat May 25 02:28:53 2013
 * Description:   
 *==================================================================*/
#include "mainwindow.h"
#include <QPainter>
#include <QRadialGradient>
#include <QImage>
#include <QMouseEvent>
#include <QDebug>
#include "heatmapper.h"

/*
 * 构造函数
 */
MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	canvas_ = new QImage(CANVAS_WIDTH, CANVAS_HEIGHT, QImage::Format_ARGB32);
	mapper_ = new HeatMapper(canvas_, DEFAULT_RADIUS, DEFAULT_OPACITY);
	this->setFixedSize(CANVAS_WIDTH, CANVAS_HEIGHT);
}

MainWindow::~MainWindow()
{
	delete mapper_;
	mapper_ = NULL;
}

/*
 * 绘图方法，当窗口刷新时该方法会被调用
 */
void MainWindow::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawImage(0, 0, *canvas_);
}

/*
 * 该方法用于向绘图对象添加一个数据点
 */
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
	if (NULL == mapper_)
		return;

	mapper_->addPoint(e->x(), e->y());
	this->update();
}


















