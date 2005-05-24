/*
 * Copyright (C) 2003 Benjamin C Meyer (ben at meyerhome dot net)
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
#ifndef WORLD_H
#define WORLD_H

#include "object.h"
#include <qvaluelist.h>

/**
 * Like most things in the Quake map structor the World is a entity
 */
class World {

public:
	World( const QString &file );
	void output();
	
private:
	void generateWorld();
	QValueList<Object> objects;
	Entity map;

};

#endif // QWORLD_H

