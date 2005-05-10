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

#include "entity.h"

Entity::Entity(){

}

Entity::Entity(const QString &className) {
	keys["classname"] = className; 				
}

Entity::~Entity(){

}

void Entity::setOrigin(const int x, const int y, const int z){
	keys["origin"] = "";
	origin = Vertex( x,y,z );
}

void Entity::move(const int x, const int y, const int z){
	origin.move( x,y,z );
}

void Entity::addFlag(const QString &key, const QString &value){
	keys[key] = value;
}

QString Entity::toString(bool close){
	QString ret = "{";
	
	// Add all the properties
	QMap<QString,QString>::Iterator it;
  for ( it = keys.begin(); it != keys.end(); ++it ) {
		if( it.key() == "origin" )
			it.data() = QString("%1 %2 %3").arg(origin.x).arg(origin.y).arg(origin.z);
					
		ret += QString("\n \"%1\"").arg(it.key());
		if( !(it.data().isEmpty()) )
			ret += QString(" \"%1\"").arg( it.data() );
	}

	// Add all of the blocks
	QValueList<Block>::iterator bit;
	for ( bit = blocks.begin(); bit != blocks.end(); ++bit )
	  ret += QString("\n%1").arg((*bit).toString());
	
	if(close)
		ret += "\n}";
	
	return ret;
}

