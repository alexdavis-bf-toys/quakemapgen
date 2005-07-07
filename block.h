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
#ifndef BLOCK_H
#define BLOCK_H

#include <qlist.h>
#include <qstring.h>

class Vertex {
  public:
    Vertex() {
    };
    Vertex(const int x, const int y, const int z):x(x), y(y), z(z) {
    };
    int x;
    int y;
    int z;
    QString toString();
    void move(const int x, const int y, const int z = 0);
};

/**
 * x_off     - Texture x-offset
 * y_off     - Texture y-offset
 * rot_angle - floating point value indicating texture rotation
 * x_scale   - scales x-dimension of texture (negative value to flip)
 * y_scale   - scales y-dimension of texture (negative value to flip)
 */
class Texture {
  public:
    Texture();
    Texture(const QString name);
    QString toString();

    QString name;
    int x_offset;
    int y_offset;
    float rotation;
    float x_scale;
    float y_scale;
};

class Plane {
  public:
    Plane() {
    };
    Plane(const Vertex & corner, const Vertex & left, const Vertex & right,
          const QString & textureName = "GROUND1_6");
    Vertex corner;
    Vertex left;
    Vertex right;

    Texture texture;

    QString toString();
    void move(const int x, const int y, const int z = 0);
};

class Block {

  public:
    Block(const QString & name = QString());
      QList < Plane > planes;
    QString toString();
    void move(const int x, const int y, const int z = 0);
    void paint(const Texture & texture);
      QList < Block > subtract(Block & block);

    QString name;
};

class Blocks:public QList < Block > {
  public:
    Blocks() {
    };
};

#endif // BLOCK_H

