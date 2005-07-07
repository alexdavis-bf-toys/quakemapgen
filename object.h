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

#ifndef OBJECT_H
#define OBJECT_H

#include "block.h"
#include "entity.h"
#include <qstringlist.h>
#include <stdlib.h>
class Entity;

class Object:public Blocks {

  public:
    Object(const QString & name = QString());
      virtual ~ Object();

    virtual QString toString();
    void move(const int x, const int y, const int z);

    int x();
    int y();
    int z();
    inline Vertex loc() {
        return location;
    };

    Block makeBox(int x, int y, int z,
                  int width, int height, int depth,
                  const QString & skin, const QString & name);

        /**
	 * @returns a number from 1 - max
	 */
    inline int random(const float max) {
        return 1 + (int) (max * rand() / (RAND_MAX + 1.0));
    };

    void add(Object & object);
    // List of entities in this level
    QList < Entity > entities;
    // The name of this object, used in map generation
    QString objectName;

  private:
    Vertex location;

};

#endif // OBJECT_H

