//#ifndef GEN_DUN
//#def GEN_DUN
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


struct room{
  int x, y, height, length;
  int hardness;
};
struct dungeon{
  int numRooms;//number of rooms currently placed in the dungeon
  int map[21][80][2];
  struct room rooms[12];
  int roomCount;
};

void printDungeon(struct dungeon tempDung);

struct dungeon generateDungeon(int rooms);
struct dungeon placeRoom(struct dungeon tempDung);//places a room in a dungeon
struct dungeon placeCooridors(struct dungeon tempDung);//after all rooms placed, connects rooms

int main(int argv, char *argc[]){
  int numRooms = 7;
  
  printDungeon(generateDungeon(numRooms));
  
  return 0;
}

struct dungeon generateDungeon(int rooms){
  struct dungeon tempDung;
  tempDung.numRooms = rooms;
  tempDung.roomCount = 0;
  int i, j;
  //int tempHardness = 0;
  //initialize empty dungeon
  for(i = 0; i<21; i++){
    for(j = 0; j<80; j++){
      //set dungeon character (0 = space, 1 = period, 2 = hash, 3 = outer side wall, 4 = outer top/ bottom wall)
      //and hardness from 0 to 100 with 0 being empty
      if((i==0)||(i==20)){
	tempDung.map[i][j][0] = 3;
	tempDung.map[i][j][1] = 100;
      }
      else if((j==0)||(j==79)){
	tempDung.map[i][j][0] = 4;
	tempDung.map[i][j][1] = 100;
      }
      else{
	tempDung.map[i][j][0] = 0;
	tempDung.map[i][j][1] = 0;
      }
    }
  }
  
  for(i = 0; i < rooms; i++){
    tempDung = placeRoom(tempDung);
  }
  
  tempDung = placeCooridors(tempDung);
  
  return tempDung;
}

void printDungeon(struct dungeon tempDung){
  char dungeonTiles[] = {' ', '.', '#', '-', '|'};
  int i, j;

  for(i = 0; i<21; i++){
    for(j = 0; j<80;j++){
      printf("%c",dungeonTiles[tempDung.map[i][j][0]]);
    }
    printf("\n");
  }
}

struct dungeon placeRoom(struct dungeon tempDung){
  int minX, minY, maxX, maxY, xpos, ypos, success, i, j, k;
  success = 1;
  minX = 3; minY = 2; maxX = 8; maxY = 5;
  struct room tempRoom;
  srand(time(NULL));
  //generate random room
  for(i = 0; (i<2000)&&(success==1); i++){
    
    tempRoom.length = rand() % maxX + minX;
    tempRoom.height = rand() % maxY + minY;
    
    //randomly attempt to place room
    xpos = rand()%75+1;
    ypos = rand()%18+1;

    //check for legal placement
    success = 0;
    for(j = 0; (j < tempRoom.height)&&(success == 0); j++){
      for(k = 0; (k < tempRoom.length)&&(success == 0); k++){
	if(tempDung.map[ypos+j][xpos+k][1]>0){
	  success = 1;
	}
      }
    }
  }
  if(success == 1){
    //unsuccessful placement in 2000 trys
  }
  else{
    //successful placement
    //mark room on dungeon
    tempRoom.x = xpos;
    tempRoom.y = ypos;

    for(j = 0; j<tempRoom.height; j++){
      //mark side edges of room
      if((tempRoom.x - 1) != 0){
	tempDung.map[tempRoom.y + j][tempRoom.x-1][1] = 7;
      }
      if((tempRoom.x + tempRoom.length) != 79){
	tempDung.map[tempRoom.y + j][tempRoom.x+tempRoom.length][1] = 7;
      }
      //place room
      for(k = 0; k<tempRoom.length; k++){
	tempDung.map[tempRoom.y + j][tempRoom.x + k][0] = 1;
	tempDung.map[tempRoom.y + j][tempRoom.x + k][1] = 10;
      }
    }
    //mark top/ bottom edges of room
    for(k = 0; k<tempRoom.length; k++){
      if((tempRoom.y - 1) != 0){
	tempDung.map[tempRoom.y - 1][tempRoom.x + k][1] = 7;
      }
      if((tempRoom.y + tempRoom.height) != 20){
	tempDung.map[tempRoom.y + tempRoom.height][tempRoom.x + k][1] = 7;
      }
    }
    //mark corners
    if((tempRoom.y - 1) != 0){
      if((tempRoom.x - 1) != 0){
	tempDung.map[tempRoom.y - 1][tempRoom.x - 1][1] = 7;
      }
      if((tempRoom.x + tempRoom.length) != 79){
	tempDung.map[tempRoom.y - 1][tempRoom.x + tempRoom.length][1] = 7;
      }
    }
    if((tempRoom.y + tempRoom.height) != 20){
      if((tempRoom.x - 1) != 0){
	tempDung.map[tempRoom.y + tempRoom.height][tempRoom.x - 1][1] = 7;
      }
      if((tempRoom.x + tempRoom.length) != 79){
	tempDung.map[tempRoom.y + tempRoom.height][tempRoom.x + tempRoom.length][1] = 7;
      }
    }
  }
  tempDung.rooms[tempDung.roomCount] = tempRoom;
  tempDung.roomCount++;
  
  return tempDung;
}

struct dungeon placeCooridors(struct dungeon tempDung){
  int minDistance = 81 * 22;
  int tempDist, x1, y1, x2, y2, xx, yy, minX, minY;
  int movedir;
  int i,j;
  int dy, dx;
  srand(time(NULL));
  
  for(i = 1; i < tempDung.roomCount; i++){
    minDistance = 81 * 22;
    //get centroid of next room to connect
    x1 = tempDung.rooms[i].x + (tempDung.rooms[i].length) / 2;
    y1 = tempDung.rooms[i].y + (tempDung.rooms[i].height) / 2;
    //get centroid of closest room 
    for(j = 0; j<i; j++){
      x2 = tempDung.rooms[j].x + (tempDung.rooms[j].length) / 2;
      y2 = tempDung.rooms[j].y + (tempDung.rooms[j].height) / 2;
      xx = (int)pow((double)(x1-x2),(double)(2.0));
      yy = (int)pow((double)(y1-y2),(double)(2.0));
      tempDist =(int)pow((double) ( xx + yy ),(double)(1/2));
      if(tempDist < minDistance){
	minX = x2;
	minY = y2;
	dx = x1-minX;
	dy = y1-minY;
	minDistance = tempDist;
      }
    }
    printf("x2: %d y2: %d\n",minX,minY);
    //place cooridor connecting rooms i and minRoomPos
    //determine which corner to begin placing cooridors
    while(minDistance>0){
      movedir = rand()%2;
      if((movedir==0) && ((dx)!=0)){
	if(dx>0){x1--;}
	else{x1++;}
	//place cooridor
	if(tempDung.map[y1][x1][0]==0){
	  tempDung.map[y1][x1][0] = 2;
	  tempDung.map[y1][x1][1] = 10;
	}
	
	
      }
      else if((movedir==1) && ((dy)!=0)){
	if(dy>0){y1--;}
	else{y1++;}
	//place cooridor
	if(tempDung.map[y1][x1][0]==0){
	  tempDung.map[y1][x1][0] = 2;
	  tempDung.map[y1][x1][1] = 10;
	}
	
      }
      //update distance
      dx = x1-minX;
      dy = y1-minY;
      xx = (int)pow((double)(dx),(double)(2.0));
      yy = (int)pow((double)(dy),(double)(2.0));
      minDistance =(xx+yy);
    }
  }
  return tempDung;
}

//#endif
