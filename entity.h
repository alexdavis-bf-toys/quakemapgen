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
#ifndef ENTITY_H
#define ENTITY_H

#include "block.h"
#include <qvaluelist.h>
#include <qmap.h>

/**
 * Basic Quake Entity
 *
 * Example: 
 * {
 *   "classname" "light"
 *	 "origin" "0 128 64"
 *	 "light" "255"
 * }
 *
 * Entities can have blocks attached to them (or the other way around
 * depending on how you look at it.
 */
class Entity {

public:
	Entity();
	Entity(const QString &className);
	virtual ~Entity();

	void setOrigin(const int x, const int y, const int z);
	void move(const int x, const int y, const int z);
	void addFlag(const QString &key, const QString &value=QString());
	virtual QString toString(bool close=true);

	Blocks blocks;

protected:
	Vertex origin;
	QMap<QString, QString> keys;
};

#endif // ENTITY_H

