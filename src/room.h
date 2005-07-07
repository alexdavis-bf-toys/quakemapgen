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
#ifndef ROOM_H
#define ROOM_H

#include "object.h"

class Room:public Object {

  public:
    Room();
    Room(const int height, const int width, const int depth,
         const QString & name = QString(), int thickness = 32);

    //void addWall();
    void light();
    void addItems();
    void addSpawnPoint();
    void connectTo(Room & otherRoom);

  protected:
    int width;
    int height;
    int depth;

};

#endif // ROOM_H

