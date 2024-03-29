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
#include <qtextstream.h>
#include <stdlib.h>

World::World(const QString & file):map("worldspawn")
{
    srandom(time(0) * getpid());

    map.addFlag("wad", "quake101.wad");
    map.addFlag("message", "testWold");

    if (!file.isEmpty()) {
        ImageTemplateRoom room(file, "pngroom");
        objects.append(room);
    }
    else
        generateWorld();
}

void World::generateWorld()
{
// Build world
/*
	
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
	
	QList<Room>::iterator it;
  for ( it = objects.begin(); it != objects.end(); ++it ){
		(*it).addSpawnPoint();
		(*it).light();
		(*it).addItems();
	}
  */
}

void World::output()
{
    QTextStream cout(stdout, QIODevice::WriteOnly);
    cout << map.toString(false) << endl;

    QList < Object >::iterator it;
    for (it = objects.begin(); it != objects.end(); ++it)
        cout << (*it).toString() << endl;

    printf("}\n");

    // Output entities
    QList < Entity >::iterator eit;
    for (it = objects.begin(); it != objects.end(); ++it)
        for (eit = (*it).entities.begin(); eit != (*it).entities.end(); ++eit)
            cout << (*eit).toString() << endl;
}

