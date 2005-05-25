/*
 * Copyright (C) 2005 Benjamin C Meyer (ben at meyerhome dot net)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#ifndef IMAGETEMPLATEROOM_H
#define IMAGETEMPLATEROOM_H

#include "object.h"
#include <qimage.h>

class ImageTemplateRoom : public Object {

public:
	ImageTemplateRoom(const QString &filename, const QString &name=QString());
	
  /**
   * Creates the box/enties at point p in the image
   */
  void draw(QRgb p, int w, int h);

	/**
	 * @return the height that the room should be at w,h
	 */
	int getHeight( const int w, const int h ) const;
	
	/**
   * Creates a triangle
   */ 
	void drawTriangle(int x, int y, int z, int width, int height, int depth, const QString &skin, bool hor, bool top);
	
	QImage imageFile;

private:
	QMap<QString,int> itemLimit;
	QMap<QString,int> itemCount;

};

#endif // IMAGETEMPLATEROOM_H

