/*====================================================================
 * Filename:      global.h
 * Version:       
 * Author:        Dianchun Huang <simpleotter23@gmail.com>
 * 
 * Copyright (c) 2013 Dianchun Huang (simpleotter23@gmail.com)
 * 
 * Created at:    Tue Jul  9 22:00:51 2013
 * Modified at:   Tue Jul  9 22:02:15 2013
 * Description:   
 *==================================================================*/
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <QtCore/qglobal.h>

#if defined(QHEATMAP_DLL_LIBRARY)
#  define QHEATMAP_DLL_EXPORT Q_DECL_EXPORT
#else
#  define QHEATMAP_DLL_EXPORT
#endif

#endif /* _GLOBAL_H_ */
