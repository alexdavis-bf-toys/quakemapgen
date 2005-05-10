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

#include "imagetemplateroom.h"
#include "teleport.h"
#include "entity.h"
#include <qvaluelist.h>

#define WALL -16777216
#define SPAWN -16776961
#define ZONE1 -256
#define ZONE2 -16711681
#define ZONE3 -16711936
#define ZONE4 -8388480

ImageTemplateRoom::ImageTemplateRoom(const QString &fileName, const QString &name) : Object(name) {

	imageFile.load(fileName);

	for(int i=imageFile.width()-1; i >= 0; i--) {
		for(int j=0; j< imageFile.height(); j++) {
			draw(imageFile.pixel(i,j), i, j);
		}
		printf("\n");
	}
	
	// One big floor, optimizer? who knows?
	Block box = makeBox(0, 0, 0, 64*imageFile.width(), 64*imageFile.height(), 6, "AFLOOR1_4", QString("Floor %1").arg(objectName));
	append(box);
}

int ImageTemplateRoom::getHeight( const int w, const int h ) const {
	// Try hor
	uint hor=0;
	for(int i=w;i<imageFile.width();i++)
		if(imageFile.pixel(i,h) == WALL ) break; else hor++;
	for(int i=w;i>0;i--)
		if(imageFile.pixel(i,h)==WALL) break; else hor++;
	
	uint v=0;
	for(int i=h;i<imageFile.height();i++)
		if(imageFile.pixel(w,i)==WALL) break; else v++;
	for(int i=h;i>0;i--)
		if(imageFile.pixel(w,i)==WALL) break; else v++;

	//qDebug("%d %d", v, hor);
	uint small = hor;
	if(v < small) small = v;
	return small;
}

void ImageTemplateRoom::draw(QRgb p, int w, int h){
	if(p == -1)
		return;
	
	// Floor
 	QString floorChoice = "AFLOOR3_1";
	if(p == ZONE1) floorChoice="AFLOOR3_1";
	if(p == ZONE2) floorChoice="AFLOOR1_4";
	if(p == ZONE3) floorChoice="AFLOOR1_8";
	if(p == ZONE4) floorChoice="AFLOOR1_3";
	//Block box = makeBox(w*64, h*64, -6, 64, 64, 6, floorChoice, QString("Floor %1").arg(objectName));
	//append(box);
	
	//drawBox(w*64,h*64, -6, 64, 64, 6, floorChoice.latin1());

	// Celine
	QString celingTexture = "CEILING1_3";
	int pull = getHeight(w,h);
	if(pull > 12){
			celingTexture = "SKY4";
			pull = 12;
		}
	Block box = makeBox(w*64, h*64, 128+pull*20, 64, 64, 256, celingTexture, QString("Celine %1").arg(objectName));
	append(box);
	
	//drawBox(w*64,h*64, 128+pull*20, 64, 64, 256, celingTexture.latin1());

	
	// wall
	QString wallChoice = "CITY2_6";
 	static int wallChoiceNum = 0;
	if( random(50) == 1)
		wallChoiceNum = random(6);
	
	switch(wallChoiceNum){
		case 1: wallChoice = "CITY2_6"; break;
		case 2: wallChoice = "CITY2_3"; break;
		case 3: wallChoice = "CITY2_5"; break;
		case 4: wallChoice = "CITY2_6"; break;
		case 5: wallChoice = "CITY2_7"; break;
		case 6: wallChoice = "COLUMN1_2"; break;
	}
	
	
		//qDebug("w: %d h: %d, %d", w, h, imageFile.pixel(w+1,h));
	if(h > 0 && h < imageFile.height()-1 &&
			 w > 0 && w < imageFile.width()-1){
		if(imageFile.pixel(w,h-1) == WALL && imageFile.pixel(w-1,h) == WALL){
			drawTriangle(w*64,h*64, 0, 64, 64, 512, wallChoice, true, false);
			return;
		}
		if(imageFile.pixel(w,h+1) == WALL && imageFile.pixel(w+1,h) == WALL){
			drawTriangle(w*64,h*64, 0, 64, 64, 512, wallChoice, true, true);
			return;
		}
		if(imageFile.pixel(w,h-1) == WALL && imageFile.pixel(w+1,h) == WALL){
			drawTriangle(w*64,h*64, 0, 64, 64, 512, wallChoice, false, false);
			return;
		}	
		if(imageFile.pixel(w,h+1) == WALL && imageFile.pixel(w-1,h) == WALL){
			drawTriangle(w*64,h*64, 0, 64, 64, 512, wallChoice, false, true);
			return;
		}
	}
	
	if(p == WALL ){
		box = makeBox(w*64, h*64, 0, 64, 64, 512, wallChoice, QString("Wall %1").arg(objectName));
		append(box);
		//drawBox(w*64,h*64, 0, 64, 64, 512, wallChoice);
		return;
	}

	if( p == SPAWN ){
		Entity newEntity("info_player_deathmatch");
    newEntity.setOrigin(w*64, h*64, 65);
    entities.append(newEntity);
		//makeEntity("info_player_deathmatch", w*64, h*64, 65);
	}	

	int j=1+(int) (5.0*rand()/(RAND_MAX+1.0));
	
	if(j<=2){
    Entity light("light");
    light.setOrigin(w*64+32, h*64+32, 32+pull*10);
    light.addFlag("light", "200");
    entities.append(light);
	}
	
	// Add some random weapons
	int g=1+(int) (40.0*rand()/(RAND_MAX+1.0));

  if( random(10) == 1 ){
	  static int teleportCount = 1;
		static QValueList<Vertex> startPoints;
		if(p != WALL &&
			imageFile.pixel(w,h+1) != WALL && imageFile.pixel(w,h-1) != WALL &&
			imageFile.pixel(w+1,h) != WALL && imageFile.pixel(w-1,h) != WALL &&
			imageFile.pixel(w+1,h+1) != WALL && imageFile.pixel(w-1,h+1) != WALL &&
			imageFile.pixel(w+1,h-1) != WALL && imageFile.pixel(w-1,h-1) != WALL
			){
			Vertex start( w*64+32, h*64, 8 );
			startPoints.append(start);
		}
		
		if(startPoints.count() > 10){
			qDebug("teleport");
			//Vertex end( w*64+32, h*64+32, 8 );
			//qDebug("teleport making! %d %d %d %d %d %d", end.x, end.y, end.z, start.x, start.y, start.z);
			Vertex end = startPoints.front();
			end.move(-16,32,16);
	  	Teleport teleport(startPoints.back(), end, QString("%1_%1").arg(objectName).arg(teleportCount), 180);
			teleportCount++;
			add(teleport);
			end = startPoints.back();
			end.move(-16,32,16);
			Teleport teleport2(startPoints.front(), end, QString("%1_%1").arg(objectName).arg(teleportCount), 180);
			add(teleport2);
			startPoints.pop_back();
			startPoints.pop_front();
			// get rid of the next ones just in case.
			startPoints.pop_back();
			startPoints.pop_front();
			teleportCount++;
			// nothing else spawning here
			return;	
		}
	}
	
	if( g == 2 && w > 0){
		Entity newEntity("info_player_deathmatch");
    newEntity.setOrigin(w*64+32, h*64+32, 64);
    entities.append(newEntity);
		//makeEntity("info_player_deathmatch", w*64+32, h*64+32, 64);
	}	
	
	if( g < 5 ) {
		QString weapon;
		switch(random(10)){
			case 1: weapon = "item_armor1"; break;
			case 2: weapon = "item_armor2"; break;
			case 3: weapon = "item_armorInv"; break;
			case 4: weapon = "item_cells"; break;
			case 5: weapon = "item_rockets"; break;
			case 6: weapon = "item_shells"; break;
			//case 7: weapon = "item_sigil"; break;
			case 8: weapon = "item_spikes"; break;
			default:
					weapon = "item_health"; break;
		}
		Entity newEntity(weapon);
    newEntity.setOrigin(w*64+16, h*64+16, 64);
    entities.append(newEntity);
		//makeEntity(weapon.latin1(), w*64+32, h*64+32, 32);
	}

	if( g == 2 ) {
		static int gods = 0;
		if(gods < 2){
			gods++;
		QString weapon = "info_armor1";
		switch(random(2)){
			case 1: weapon = "item_artifact_invisibility"; break;
			case 2: weapon = "item_artifact_super_damage"; break;
			//case 3: weapon = "item_artifact_invulnerability"; break;
		}
		Entity newEntity(weapon);
    newEntity.setOrigin(w*64+32, h*64+32, 64);
    entities.append(newEntity);
		//makeEntity(weapon.latin1(), w*64+32, h*64+32, 32);
		}
	}

	if(g==1) {
		QString weapon = "supershotgun";
		switch(random(5)){
			case 1: weapon = "nailgun"; break;
			case 2: weapon = "supernailgun"; break;
			case 3: weapon = "grenadelauncher"; break;
			case 4: weapon = "rocketlauncher"; break;
			case 5: weapon = "lightning"; break;
		}
		weapon = QString("weapon_")+weapon;
		Entity newEntity(weapon);
    newEntity.setOrigin(w*64+32, h*64+32, 64);
    entities.append(newEntity);
		//makeEntity(weapon.latin1(), w*64+32, h*64+32, 32);
	}
}

void ImageTemplateRoom::drawTriangle(int x, int y, int z, int width, int height, int depth, const QString &skin, bool hor, bool top){

	Block box;
				
	//printf("{\n");
	//printf("// Triangle %d, %d\n", hor, top);
	//      ( 128 0 0 ) ( 128 1 0 ) ( 128 0 1 ) GROUND1_6 0 0 0 1.0 1.0
	if(hor && !top || !hor && top){ 
		//printf("// front left\n");
		Plane frontLeft( Vertex(x,0,0),  Vertex(x,1,0), Vertex(x,0,1), skin);
		box.planes.append(frontLeft);
		//printf("( %d 0 0 ) ( %d 1 0 ) ( %d 0 1 ) %s 0 0 0 1.0 1.0\n", x, x, x, skin.latin1());
	}

	//      ( 0 128 0 ) ( 0 128 1 ) ( 1 128 0 ) GROUND1_6 0 0 0 1.0 1.0
	if(hor && !top || !hor && !top){
		//printf("// front right\n");
		Plane frontRight( Vertex(0,y,0),  Vertex(0,y,1), Vertex(1,y,0), skin);
		box.planes.append(frontRight);
		//printf("( 0 %d 0 ) ( 0 %d 1 ) ( 1 %d 0 ) %s 0 0 0 1.0 1.0\n", y, y, y, skin.latin1());
	}

	if(hor && top || !hor && !top){
		//printf("// Back right\n");
		Plane backRight( Vertex(x+width,0,0),  Vertex(x+width,0,1), Vertex(x+width,1,0), skin);
		box.planes.append(backRight);
		//printf("( %d 0 0 ) ( %d 0 1 ) ( %d 1 0 ) %s 0 0 0 1.0 1.0\n", x+width, x+width, x+width, skin.latin1());
	}
	
	if(hor && top || !hor && top ){
		//printf("// Back left\n");
		Plane backLeft( Vertex(0,y+height,0),  Vertex(1,y+height,0), Vertex(0,y+height,1), skin);
		box.planes.append(backLeft);
		//printf("( 0 %d 0 ) ( 1 %d 0 ) ( 0 %d 1 ) %s 0 0 0 1.0 1.0\n", y+height, y+height, y+height, skin.latin1());
	}

	// Cross
	if(hor){
		if(top){
			//printf("( %d %d 0 ) ( %d %d 1 ) ( %d %d 0 ) %s 0 0 0 1.0 1.0\n", x, y+height,   x, y+height,    x+width, y,  skin.latin1());
			Plane diag( Vertex(x,y+height,0),  Vertex(x,y+height,1), Vertex(x+width,y,0), skin);
			box.planes.append(diag);
		}
		else{
			//printf("( %d %d 0 ) ( %d %d 0 ) ( %d %d 1 ) %s 0 0 0 1.0 1.0\n", x, y+height,   x+width, y, x, y+height,  skin.latin1());
			Plane diag( Vertex(x,y+height,0),  Vertex(x+width,y,0), Vertex(x,y+height,1), skin);
			box.planes.append(diag);
		}
	}
	else{
		if(top){
			//printf("( %d %d 0 ) ( %d %d 1 ) ( %d %d 0 ) %s 0 0 0 1.0 1.0\n",
			//           x, y,    x,y, x+width, y+height, skin.latin1());
			Plane diag( Vertex(x,y,0),  Vertex(x,y,1), Vertex(x+width,y+height,0), skin);
			box.planes.append(diag);
		}
		else {
			//printf("( %d %d 0 ) ( %d %d 0 ) ( %d %d 1 ) %s 0 0 0 1.0 1.0\n",
	    //      x, y,    x+width, y+height, x, y, skin.latin1());
			Plane diag( Vertex(x,y,0),  Vertex(x+width, y+height, 0), Vertex(x,y,1), skin);
			box.planes.append(diag);
		}
	}
	// bottom
	// ( 0 0 64 ) ( 1 0 64 ) ( 0 1 64 ) GROUND1_6 0 0 0 1.0 1.0
	Plane topPlane( Vertex(0,0,z),  Vertex(1,0,z), Vertex(0,1,z), skin);
	box.planes.append(topPlane);
	//printf("( 0 0 %d ) ( 1 0 %d ) ( 0 1 %d ) %s 0 0 0 1.0 1.0\n", z, z, z, skin.latin1());
		
	// top
	// ( 0 0 128 ) ( 0 1 128 ) ( 1 0 128 ) GROUND1_6 0 0 0 1.0 1.0
	//printf("( 0 0 %d ) ( 0 1 %d ) ( 1 0 %d ) %s 0 0 0 1.0 1.0\n", z+depth, z+depth, z+depth, skin.latin1());
	Plane bottom( Vertex(0,0,z+depth),  Vertex(0,1,z+depth), Vertex(1,0,z+depth), skin);
	box.planes.append(bottom);
	
	//printf("}\n");

	append(box);
}

