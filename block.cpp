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

#include "block.h"

QString Vertex::toString(){
	return QString("( %1 %2 %3 )").arg(x).arg(y).arg(z);
}

void Vertex::move(const int x, const int y, const int z){
	this->x += x;
	this->y += y;
	this->z += z;
}

Texture::Texture() : name("GROUND1_6") {
	x_offset = 0;
	y_offset = 0;
	rotation = 0;
	x_scale = 1.0;
	y_scale = 1.0;
}

Texture::Texture(const QString name) : name(name){
	x_offset = 0;
	y_offset = 0;
	rotation = 0;
	x_scale = 1.0;
	y_scale = 1.0;
}

QString Texture::toString(){
	return QString("%1 %2 %3 %4 %5 %6").arg(name).arg(x_offset).arg(y_offset).arg(rotation).arg(x_scale).arg(y_scale);
}

Plane::Plane(const Vertex &corner, const Vertex &left, const Vertex &right, const QString &textureName)
				:corner(corner), left(left), right(right), texture(textureName){
}

QString Plane::toString(){
  //( 128 0 0 ) ( 128 1 0 ) ( 128 0 1 ) GROUND1_6 0 0 0 1.0 1.0
  // 1st Point   2nd Point   3rd Point   Texture  
	return QString("%1 %2 %3 %4").arg(corner.toString()).arg(left.toString()).arg(right.toString()).arg(texture.toString());
}

void Plane::move(const int x, const int y, const int z){
	corner.move(x,y,z);
	left.move(x,y,z);
	right.move(x,y,z);
}

Block::Block(const QString &name) : name(name) {

}

QString Block::toString(){
	if(planes.count() < 4)
		qWarning(QString("Error!  object: %1 has less then four planes!").arg(name).latin1());
/*
Example:
{
  ( 128 0 0 ) ( 128 1 0 ) ( 128 0 1 ) GROUND1_6 0 0 0 1.0 1.0
  ( 256 0 0 ) ( 256 0 1 ) ( 256 1 0 ) GROUND1_6 0 0 0 1.0 1.0
  ( 0 128 0 ) ( 0 128 1 ) ( 1 128 0 ) GROUND1_6 0 0 0 1.0 1.0
  ( 0 384 0 ) ( 1 384 0 ) ( 0 384 1 ) GROUND1_6 0 0 0 1.0 1.0
  ( 0 0 64 ) ( 1 0 64 ) ( 0 1 64 ) GROUND1_6 0 0 0 1.0 1.0
  ( 0 0 128 ) ( 0 1 128 ) ( 1 0 128 ) GROUND1_6 0 0 0 1.0 1.0
 }
*/
	QString ret = "{";
	if( !name.isEmpty() )
		ret += QString("\n // %1").arg(name);
	QValueList<Plane>::iterator it;
  for ( it = planes.begin(); it != planes.end(); ++it )
  	ret += QString("\n %1").arg((*it).toString());
	ret += "\n}";
	return ret;
}

void Block::move(const int x, const int y, const int z){
	QValueList<Plane>::iterator it;
  for ( it = planes.begin(); it != planes.end(); ++it )
  	((*it).move(x,y,z));
}

void Block::paint(const Texture &texture){
	QValueList<Plane>::iterator it;
  for ( it = planes.begin(); it != planes.end(); ++it )
  	(*it).texture = texture;
}

QValueList<Block> Block::subtract(Block &block){
	/*QValueList<Block> newBlocks;
	for(int i=0; i < block.count();i++){

	}*/
}

