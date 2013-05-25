/*====================================================================
 * Filename:      gradientpalette.h
 * Version:       
 * Author:        Dianchun Huang <simpleotter23@gmail.com>
 * 
 * Copyright (c) 2013 Dianchun Huang (simpleotter23@gmail.com)
 * 
 * Created at:    Sat May 25 08:38:15 2013
 * Modified at:   Sat May 25 08:53:39 2013
 * Description:   
 *==================================================================*/
#ifndef _GRADIENTPALETTE_H_
#define _GRADIENTPALETTE_H_

#include <QLinearGradient>

QT_BEGIN_NAMESPACE
class QImage;
QT_END_NAMESPACE

class GradientPalette
{
public:
	GradientPalette(int width);
	~GradientPalette();

	void setColorAt(qreal index, const QColor &color);
	QColor getColorAt(qreal index);
	
private:
	// 作为调色板的画布
	QImage *canvas_;
	// 线性渐变
	QLinearGradient gradient_;
	// 宽度
	int width_;
};

#endif /* _GRADIENTPALETTE_H_ */
