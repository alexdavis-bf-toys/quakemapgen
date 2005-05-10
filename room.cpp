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

#include "room.h"
#include "teleport.h"
#include "stairs.h"

Room::Room(){
};

Room::Room(const int width, const int height, const int depth,
					 const QString &name, int thickness ) : Object(name),
				width(width), height(height), depth(depth) {

	QString skin("GROUND1_6");
	int x = 0;
	int y = 0;
	int z = 0;

	skin = "CITY2_6";
	Block leftWall = makeBox(x, y, z, /*width*/ thickness, height, depth, skin, QString("Room %1, block leftWall").arg(name));
	append(leftWall);


	Block rightWall = makeBox(x+width, y, z, /*width*/thickness, height, depth, skin, QString("Room %1, block rightWall").arg(name));
	append(rightWall);


	Block frontWall = makeBox(x, y, z, width, /*height*/thickness, depth, skin, QString("Room %1, block frontWall").arg(name));
	append(frontWall);

	Block backWall = makeBox(x, y+height-thickness, z, width, /*height*/thickness, depth, skin, QString("Room %1, block backWall").arg(name));
	append(backWall);

	skin = "CEILING1_3";
	Block celeine = makeBox(x, y, z+depth, width, height, /*depth*/thickness, skin, QString("Room %1, block celing").arg(name));
	append(celeine);

	skin = "AFLOOR1_8";
	Block floor = makeBox(x, y, z, width, height, /*depth*/thickness, skin, QString("Room %1, block floor").arg(name));
	append(floor);
}

void Room::light(){
	int pull = 10;
	for(int w=1; w < (width/64)-1; w++){
		for(int h=1; h < (height/64)-1; h++){
			int r = random(3);
			if( r == 1 ){
				Entity light("light");
				light.setOrigin(x()+w*64+32, y()+h*64+32, z()+32+pull*10);
				light.addFlag("light", "200");
				entities.append(light);
			}
		}
	}
}

void Room::addItems(){
	for(int w=1; w < (width/64)-1; w++){
		for(int h=1; h < (height/64)-1; h++){
			int r = random(5);
			if( r == 1 ){
				QString item = "info_armor1";
				switch(random(18)){
					case 1: item = "item_armor1"; break;
					case 2: item = "item_armor2"; break;
					case 3: item = "item_armorInv"; break;
					case 4: item = "item_cells"; break;
					case 5: item = "item_health"; break;
					case 6: item = "item_rockets"; break;
					case 7: item = "item_shells"; break;
					//case 8: item = "item_sigil"; break;
					case 9: item = "item_spikes"; break;
					case 10: item = "item_artifact_invisibility"; break;
					case 11: item = "item_artifact_invulnerability"; break;
					case 12: item = "item_artifact_super_damage"; break;
					case 13: item = "weapon_supershotgun"; break;
					case 14: item = "weapon_nailgun"; break;
					case 15: item = "weapon_supernailgun"; break;
					case 16: item = "weapon_grenadelauncher"; break;
					case 17: item = "weapon_rocketlauncher"; break;
					case 18: item = "weapon_lightning"; break;
				}
				Entity itemEntity(item);
				itemEntity.setOrigin(x()+w*64+32, y()+h*64+32, z()+64);
				entities.append(itemEntity);
			}
		}
	}
}

//void Room::addWall(int x, int y, int z, int width, int height, int depth, const QString skin, const QString &name){
//  skin = "AFLOOR1_8";
//  Block floor = makeBox(x, y, z, width, height, /*depth*/32, skin, QString("Room %1, block backWall").arg(name));
//  append(floor);
//}

void Room::addSpawnPoint(){
	int w = 1;
	int h = 1;
	Entity newEntity("info_player_deathmatch");
	newEntity.setOrigin(x()+w*64+32, y()+h*64+32, z()+64);
	entities.append(newEntity);
}


void Room::connectTo( Room &otherRoom ){
	//int choice = random(6);
	int choice = 1;
	
	switch(choice){
		case 1:{
			otherRoom.move(x()+width, y(), z());
		
			{
				// go
				Vertex start = loc();
				start.move(width-64,128, 40);
				Vertex end = otherRoom.loc();
				end.move(64,128, 40);
				Teleport teleport(start, end, objectName+"1", 0);
				add(teleport);
			
				//Stairs stairs(128, 64, 48, objectName+"trigger_stairs_1");
				//stairs.move( x()+width-64, y()+64, z() );
				//add(stairs);
			}
			
			//return
			Vertex start = otherRoom.loc();
			start.move(48,otherRoom.height-128, 40);
			Vertex end = loc();
			end.move(width-64,height-96, 40);
			Teleport teleport(start, end, objectName+"2", 180);
			add(teleport);

			break;
		}

		default:
				qDebug("crap!");
	}
				
	/*int xMove = random(((width-32)/16)*2)*16-(width-32);
	int yMove = random(((height-32)/16)*2)*16-(height-32);
	int zMove = random(((depth-48)/16)*2)*16-(depth-48);

	qDebug("%d %d %d", xMove, yMove, zMove);
	otherRoom.move(x()+xMove, y()+yMove, z()+zMove);
*/
	/*QValueList<Block>::iterator it;
  for ( it = begin(); it != end(); ++it )
  	if((*it).name.contains("rightWall"))
			(*it).move(0,128);
		//				it = remove(it);

	//QValueList<Block>::iterator it;
  for ( it = otherRoom.begin(); it != otherRoom.end(); ++it )
  	if((*it).name.contains("leftWall"))
			it = otherRoom.remove(it);
	*/
}

