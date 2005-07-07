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

#include "object.h"

Object::Object(const QString & name):Blocks(), objectName(name), location(0,
                                                                          0,
                                                                          0)
{

}

Object::~Object()
{

}

int Object::x()
{
    return location.x;

    //qDebug("%s", (*at(2)).name.latin1());
    //return (*at(2)).planes[1].corner.x;
}

int Object::y()
{
    return location.y;
    //return (*at(2)).planes[1].corner.y;
}

int Object::z()
{
    return location.z;
    //return (*at(2)).planes[1].corner.z;
}

Block Object::makeBox(int x, int y, int z,
                      int width, int height, int depth,
                      const QString & skin, const QString & name)
{
    Plane frontLeft(Vertex(x, 0, 0), Vertex(x, 1, 0), Vertex(x, 0, 1), skin);
    Plane frontRight(Vertex(0, y, 0), Vertex(0, y, 1), Vertex(1, y, 0), skin);

    Plane bottom(Vertex(0, 0, z), Vertex(1, 0, z), Vertex(0, 1, z), skin);
    Plane top(Vertex(0, 0, z + depth), Vertex(0, 1, z + depth),
              Vertex(1, 0, z + depth), skin);

    Plane backRight(Vertex(x + width, 0, 0), Vertex(x + width, 0, 1),
                    Vertex(x + width, 1, 0), skin);
    Plane backLeft(Vertex(0, y + height, 0), Vertex(1, y + height, 0),
                   Vertex(0, y + height, 1), skin);

    Block box(name);
    box.planes.append(frontLeft);
    box.planes.append(frontRight);
    box.planes.append(top);
    box.planes.append(bottom);
    box.planes.append(backRight);
    box.planes.append(backLeft);
    return box;
}

QString Object::toString()
{
    QString ret = QString(" // %1").arg(objectName);
    QList < Block >::iterator it;
    for (it = begin(); it != end(); ++it)
        ret += QString("\n%1").arg((*it).toString());
    return ret;
}

void Object::move(const int x, const int y, const int z)
{
    location.move(x, y, z);

    QList < Block >::iterator it;
    for (it = begin(); it != end(); ++it)
        (*it).move(x, y, z);

    QList < Entity >::iterator eit;
    for (eit = entities.begin(); eit != entities.end(); ++eit)
        (*eit).move(x, y, z);
}

void Object::add(Object & object)
{
    QList < Block >::iterator it;
    for (it = (object.begin()); it != (object.end()); ++it)
        append((*it));

    QList < Entity >::iterator eit;
    for (eit = object.entities.begin(); eit != object.entities.end(); ++eit)
        entities.append((*eit));
}

