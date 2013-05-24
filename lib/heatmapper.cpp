/*====================================================================
 * Filename:      heatmapper.cpp
 * Version:       
 * Author:        Dianchun Huang <simpleotter23@gmail.com>
 * 
 * Copyright (c) 2013 Dianchun Huang (simpleotter23@gmail.com)
 * 
 * Created at:    Thu May 23 23:39:03 2013
 * Modified at:   Sat May 25 02:26:48 2013
 * Description:   
 *==================================================================*/
#include "heatmapper.h"
#include <QImage>
#include <QColor>
#include <QPainter>
#include <QRadialGradient>
#include <QDebug>
/*
 * 构造函数
 * @param image 用于显示输出的图像
 * @param radius 半径，决定了径向渐变的大小
 * @param opacity 不透明度，取值范围为[0, 100]
 */
HeatMapper::HeatMapper(QImage *image, int radius, int opacity)
	: radius_(radius), opacity_(opacity), max_(1)
{
	Q_ASSERT(image);
	mainCanvas_ = image;
	alphaCanvas_ = new QImage(image->size(), QImage::Format_ARGB32);
	Q_ASSERT(alphaCanvas_);
	alphaCanvas_->fill(QColor(0, 0, 0, 0));

	width_ = image->width();
	height_ = image->height();
	data_.resize(width_ * height_);
	data_.fill(0);
}

HeatMapper::~HeatMapper()
{}

/*
 * 增加指定坐标点的命中次数
 * @param x 横坐标
 * @param y 纵坐标
 * @param delta 增加的次数值
 */
int HeatMapper::increase(int x, int y, int delta)
{
	int index = (x - 1) * width_ + (y - 1);
	data_[index] = data_[index] + delta;
	return data_[index];
}

/*
 * 将图像保存到文件
 * @param fname 文件名
 */
void HeatMapper::save(const QString &fname)
{
	
}

/*
 * 添加一个数据点
 * @param x 横坐标
 * @param y 纵坐标
 */
void HeatMapper::addPoint(int x, int y)
{
	if (x <= 0 || y <= 0 || x > width_ || y > height_)
		return;

	int count = increase(x, y);

	if (max_ < count) {
		alphaCanvas_->fill(QColor(0, 0, 0, 0));
		max_ = count;
	}

	drawAlpha(x, y, count);
}

/*
 * 绘制透明径向渐变
 * @param x 横坐标
 * @param y 纵坐标
 * @param count 被命中次数
 */
void HeatMapper::drawAlpha(int x, int y, int count)
{
	int alpha = int(qreal(count * 1.0 / max_)*255);
	QRadialGradient gradient(x, y, radius_);
	gradient.setColorAt(0, QColor(0, 0, 0, alpha));
	gradient.setColorAt(1, QColor(0, 0, 0, 0));
	
	QPainter painter(alphaCanvas_);
	painter.setPen(Qt::NoPen);
	painter.setBrush(gradient);
	painter.drawEllipse(QPoint(x, y), radius_, radius_);

	colorize(x, y);
}

/*
 * 着色
 * @param subArea 透明径向渐变区域
 */
void HeatMapper::colorize(int x, int y)
{
	int alpha = 0;
	int offset = 0;
	int finalAlpha = 0;
	int left = x - radius_;
	int top = y - radius_;
	int right = x + radius_;
	int bottom = y + radius_;

	if (left < 0)
		left = 0;

	if (top < 0)
		top = 0;

	if (right > width_)
		right = width_;

	if (bottom > height_)
		bottom = height_;

	for (int i = left; i < right; ++i) {
		for (int j = top; j < bottom; ++j) {
			alpha = qAlpha(alphaCanvas_->pixel(i, j));
			offset = alpha * 4;
			if (!offset)
				continue;
			finalAlpha = (alpha < opacity_ ? alpha : opacity_);
			mainCanvas_->setPixel(i, j, qRgba(255, 0, 0, finalAlpha));
		}
	}
}



















