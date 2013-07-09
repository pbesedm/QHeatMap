/*====================================================================
 * Filename:      heatmapper.cpp
 * Version:       
 * Author:        Dianchun Huang <simpleotter23@gmail.com>
 * 
 * Copyright (c) 2013 Dianchun Huang (simpleotter23@gmail.com)
 * 
 * Created at:    Thu May 23 23:39:03 2013
 * Modified at:   Tue Jul  9 23:45:21 2013
 * Description:   
 *==================================================================*/
#include "heatmapper.h"
#include <QImage>
#include <QColor>
#include <QPainter>
#include <QRadialGradient>
#include <QDebug>
#include "gradientpalette.h"

/*
 * 构造函数
 * @param image 用于显示输出的图像
 * @param radius 半径，决定了径向渐变的大小
 * @param opacity 不透明度，取值范围为[0, 100]
 */
HeatMapper::HeatMapper(QImage *image, GradientPalette *palette,
					   int radius, int opacity)
	: radius_(radius), opacity_(opacity), max_(1)
{
	Q_ASSERT(image);
	Q_ASSERT(palette);

	palette_ = palette;
	
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
 * @return 返回更新后的命中次数
 */
int HeatMapper::increase(int x, int y, int delta)
{
	int index = (y - 1) * width_ + (x - 1);
	data_[index] += delta;
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
		max_ = count;
		redraw();
		return;
	}

	drawAlpha(x, y, count);
}

/*
 * 根据最大命中次数重绘整个图像，此方法会产生余辉效果
 */
void HeatMapper::redraw()
{
	QColor color(0, 0, 0, 0);
	alphaCanvas_->fill(color);
	mainCanvas_->fill(color);

	int size = data_.size();
	for (int i = 0; i < size; ++i) {
		if (0 == data_[i])
			continue;
		drawAlpha(i % width_ + 1, i / width_ + 1, data_[i], false);
	}
	colorize();
}

/*
 * 设置调色板
 * @param palette 调色板对象指针
 */
void HeatMapper::setPalette(GradientPalette *palette)
{
	Q_ASSERT(palette);
	
	if (palette)
		palette_ = palette;
}

/*
 * 获得指定点的命中次数
 */
int HeatMapper::getCount(int x, int y)
{
	if (x < 0 || y < 0)
		return 0;
	return data_[(y - 1) * width_ + (x - 1)];
}

/*
 * 绘制透明径向渐变
 * @param x 横坐标
 * @param y 纵坐标
 * @param count 被命中次数
 * @param colorize_now 是否调用着色方法
 */
void HeatMapper::drawAlpha(int x, int y, int count, bool colorize_now)
{
	int alpha = int(qreal(count * 1.0 / max_)*255);
	QRadialGradient gradient(x, y, radius_);
	gradient.setColorAt(0, QColor(0, 0, 0, alpha));
	gradient.setColorAt(1, QColor(0, 0, 0, 0));
	
	QPainter painter(alphaCanvas_);
	painter.setPen(Qt::NoPen);
	painter.setBrush(gradient);
	painter.drawEllipse(QPoint(x, y), radius_, radius_);

	if (colorize_now)
		colorize(x, y);
}

/*
 * 重载方法，着色
 */
void HeatMapper::colorize()
{
	colorize(0, 0, width_, height_);
}

/*
 * 重载方法，着色
 * @param x 横坐标
 * @param y 纵坐标
 * @param subArea 透明径向渐变区域
 */
void HeatMapper::colorize(int x, int y)
{
	int left = x - radius_;
	int top = y - radius_;
	int right = x + radius_;
	int bottom = y + radius_;
	QColor color;

	if (left < 0)
		left = 0;

	if (top < 0)
		top = 0;

	if (right > width_)
		right = width_;

	if (bottom > height_)
		bottom = height_;

	colorize(left, top, right, bottom);
}

/*
 * 重载函数，实际的着色操作在本方法
 * @param left   左上角横坐标
 * @param top    左上角纵坐标
 * @param right  右下角横坐标
 * @param bottom 右下角纵坐标
 */
void HeatMapper::colorize(int left, int top, int right, int bottom)
{
	int alpha = 0;
	int finalAlpha = 0;
	QColor color;
	for (int i = left; i < right; ++i) {
		for (int j = top; j < bottom; ++j) {
			alpha = qAlpha(alphaCanvas_->pixel(i, j));
			if (!alpha)
				continue;
			finalAlpha = (alpha < opacity_ ? alpha : opacity_);
			color = palette_->getColorAt(alpha);
			mainCanvas_->setPixel(i, j, qRgba(color.red(),
											  color.green(),
											  color.blue(),
											  finalAlpha));
		}
	}
}



















