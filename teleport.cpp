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

#include "teleport.h"
#include "room.h"

Teleport::Teleport(const Vertex &start, const Vertex &end, const QString &name, int angle) : Object(name){
	// TODO this should really just be rotated rather then the if hack
				
	int teleportWidth = 64;
	int teleportHeight = 64;
	int teleportDepth = 112;

	if(angle == 0 || angle == 180)
		teleportWidth = 16;
	else
		teleportHeight = 16;
	
	int teleportBorder = 8;
	// The box users see
	Room room(teleportWidth+teleportBorder, teleportHeight+teleportBorder, teleportDepth+teleportBorder, QString("Teleport %1 walls ").arg(name), teleportBorder);
	room.move(start.x, start.y, start.z+8);
	
	QValueList<Block>::iterator it;
  for ( it = room.begin(); it != room.end(); ++it )
  	if((*it).name.contains("rightWall"))
			it = remove(it);
  for ( it = room.begin(); it != room.end(); ++it )
  	if((*it).name.contains("leftWall"))
			it = remove(it);
	
	for ( it = room.begin(); it != room.end(); ++it )
  	(*it).paint(Texture("LGMETAL2"));

	add(room);

	Block box = makeBox(x()-32, y()-32, z(), 96, 128, 4, "LGMETAL2", QString("Teleport Floor %1").arg(name));
	box.move(start.x, start.y, start.z);
	
	append(box);

	
	int boxWidth = teleportWidth;
	int boxHeight = teleportHeight;
	
	if(angle == 0 || angle == 180)
		boxWidth = 8;
	else
		boxHeight = 8;

	Vertex startJump = start;
	if(angle == 0 || angle == 180)
		startJump.move(teleportWidth/2, 0, teleportBorder);
	else
		startJump.move(0, teleportHeight/2, teleportBorder);
	startJump.z += 8;

	box = makeBox(startJump.x, startJump.y, startJump.z, boxWidth, boxHeight, teleportDepth, "*TELEPORT", QString("Teleport %1").arg(name));
	append(box);

	// The jump from entity
	Entity newEntity("trigger_teleport");
	newEntity.addFlag("target", QString("Teleport_%1").arg(name));
	Block boxOut = makeBox(startJump.x, startJump.y, startJump.z, boxWidth, boxHeight, teleportDepth, "*TELEPORT", QString("Teleport %1").arg(name));
	newEntity.blocks.append(boxOut);
	entities.append(newEntity);

	// The jump to entity
	Entity endEntity("info_teleport_destination");
	endEntity.setOrigin(end.x, end.y, end.z);
	endEntity.addFlag("targetname", QString("Teleport_%1").arg(name));
	endEntity.addFlag("angle", QString("%1").arg(angle));
	entities.append(endEntity);
}

