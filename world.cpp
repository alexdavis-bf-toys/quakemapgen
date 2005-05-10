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

#include "world.h"
#include "block.h"
#include "imagetemplateroom.h"
#include "stairs.h"
#include "room.h"
#include "entity.h"
#include <stdlib.h>

World::World( const QString &file ) : map("worldspawn") {
	srandom(time(0) * getpid());
	
	map.addFlag("wad", "quake101.wad");
	map.addFlag("message", "testWold");

	printf("%s\n", map.toString(false).latin1());
	
	ImageTemplateRoom room(file, "pngroom");
	printf("%s\n", room.toString().latin1());
	
	printf("}\n");
	
	QValueList<Entity>::iterator eit;
  for ( eit = room.entities.begin(); eit != room.entities.end(); ++eit )
			printf("%s\n", (*eit).toString().latin1());

}

void World::output(){
	// Build world
/*	QValueList<Room> objects;
	
	for(int i=0;i<5;i++ ){
		Object j;
		int width  = (j.random(40)+20)*16;
		int height = (j.random(50)+20)*16;
		int depth = (j.random(50)+10)*16;
			
		Room room(width, height, depth, QString("test_room_%1").arg(i));
		if(objects.count() > 0){
			objects.last().connectTo(room);
		}
		objects.append(room);
	}
	
	QValueList<Room>::iterator it;
  for ( it = objects.begin(); it != objects.end(); ++it ){
		(*it).addSpawnPoint();
		(*it).light();
		(*it).addItems();
	}

	// Output World
	printf("%s\n", map.toString(false).latin1());
	
  for ( it = objects.begin(); it != objects.end(); ++it )
		printf("%s\n", (*it).toString().latin1());

	printf("}\n");
	
	// Output entities
	QValueList<Entity>::iterator eit;
  for ( it = objects.begin(); it != objects.end(); ++it )
		for ( eit = (*it).entities.begin(); eit != (*it).entities.end(); ++eit )
			printf("%s\n", (*eit).toString().latin1());
*/
}

