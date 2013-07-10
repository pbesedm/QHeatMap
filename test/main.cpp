/*====================================================================
 * Filename:      main.cpp
 * Version:       
 * Author:        Dianchun Huang <simpleotter23@gmail.com>
 * 
 * Copyright (c) 2013 Dianchun Huang (simpleotter23@gmail.com)
 * 
 * Created at:    Thu May 23 22:42:59 2013
 * Modified at:   Wed Jul 10 19:11:47 2013
 * Description:   
 *==================================================================*/
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	MainWindow w;
	w.show();
	
    return app.exec();
}


















