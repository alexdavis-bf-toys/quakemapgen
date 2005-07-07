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

#include "stairs.h"

Stairs::Stairs(const int stairsHeight, const int width, const int stairsDepth,
               const QString & name, int steps):Object(name)
{

    // 16 is the *magical* number the players can climb without jumping
    if (steps == 0)
        steps = stairsDepth / 16;

    //Stairs s(64, 512, 256, "test");
    int x = 0;
    int y = 0;
    int z = 0;
    QString skin = "GROUND1_6";

    int height = stairsHeight / steps;
    //int width = stairsWidth/steps;
    int depth = stairsDepth / steps;
    for (int i = 0; i < steps; i++) {
        y = i * (stairsHeight / steps);
        z = i * (stairsDepth / steps);

/*
		Plane frontLeft( Vertex(x,0,0),  Vertex(x,1,0), Vertex(x,0,1), skin);
		Plane frontRight( Vertex(0,y,0),  Vertex(0,y,1), Vertex(1,y,0), skin);
	
		Plane top( Vertex(0,0,z),  Vertex(1,0,z), Vertex(0,1,z), skin);
		Plane bottom( Vertex(0,0,z+depth),  Vertex(0,1,z+depth), Vertex(1,0,z+depth), skin);
	
		Plane backRight( Vertex(x+width,0,0),  Vertex(x+width,0,1), Vertex(x+width,1,0), skin);
		Plane backLeft( Vertex(0,y+height,0),  Vertex(1,y+height,0), Vertex(0,y+height,1), skin);

		Object box(QString("Stair %1, step %2").arg(name).arg(i));
		box.planes.append(frontLeft);
		box.planes.append(frontRight);
		box.planes.append(top);
		box.planes.append(bottom);
		box.planes.append(backRight);
		box.planes.append(backLeft);
*/
        Block box =
            makeBox(x, y, z, width, height, depth, skin,
                    QString("Stair %1, step %2").arg(name).arg(i));
        // testing
        //box.move(64,64);
        append(box);
    }
}

