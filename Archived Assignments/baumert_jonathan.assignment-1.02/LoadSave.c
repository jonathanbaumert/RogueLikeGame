#include <endian.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "GenerateDungeon.c"

struct dungeon loadMap(FILE *f);
int saveMap(struct dungeon tempDung);
int main(int argc, char *argv[]){
  //printDungeon(generateDungeon(5));
  char *path;
  //printf("%s\n", getenv("HOME"));
  path = malloc(strlen(getenv("HOME")) + strlen("/.rlg327/dungeon") + 1);
  strcpy(path, getenv("HOME"));
  strcat(path, "/.rlg327/dungeon");
  FILE *f;
  struct dungeon tempDung;
  //char name[12];
  int initialized = 1;
  //check if switch is set
  if(argc == 1){
    tempDung = generateDungeon(7);
    initialized = 0;
     printDungeon(tempDung);
  }  
  else{
    //if switch equals load
    //    load
    
    for(int i = 1; i < argc; i++){
      if(argv[i][2] == 'l'){
	//attempt to open file
	
	f = fopen(path, "r");
	if( f == NULL){
	  printf("ERROR: DUNGEON COULD NOT BE LOADED\n");
	  return 1;
	}
	else{
	  //printf("LOADING\n");
	  tempDung = loadMap(f);
	  initialized = 0;
	  printDungeon(tempDung);
	  fclose(f);
	}	
      }
    }   
    //printDungeon(tempDung);
    
    for(int i = 1; i<argc; i++){
      if(argv[i][2] == 's'){
	if(initialized == 1){tempDung = generateDungeon(7);printDungeon(tempDung);}
	saveMap(tempDung);
      }
    }
        
  }
  
  
  free(path);
  return 0;
}

int saveMap(struct dungeon tempDung){
  char *path;
  //printf("%s\n", getenv("HOME"));
  path = malloc(strlen(getenv("HOME")) + strlen("/.rlg327/dungeon") + 1);
  strcpy(path, getenv("HOME"));
  strcat(path, "/.rlg327/dungeon");
  FILE *f;
  f = fopen(path, "w");
  if(f!=NULL){
    char mark[] = "RLG327-F2018";
    fwrite(mark, 12, 1, f);
    uint32_t temp32[1];
    uint8_t temp8[2];
    temp32[0] = tempDung.version;
    fwrite(temp32, 4, 1, f);
    temp32[0] = tempDung.size;
    fwrite(temp32, 4, 1, f);
    temp8[0] = tempDung.pc_pos[0];
    fwrite(temp8, 1, 1, f);
    temp8[0] = tempDung.pc_pos[1];
    fwrite(temp8, 1, 1, f);
    for(int i = 0; i < 21; i++){
      for( int j = 0; j<80; j++){
	temp8[0] = tempDung.hardness[i][j];
	fwrite(temp8, 1, 1, f);
      }
    }
    for(int i = 0; i<tempDung.roomCount; i++){
      //printf("%d %d %d %d\n", tempDung.rooms[i].x, tempDung.rooms[i].y,  tempDung.rooms[i].length,  tempDung.rooms[i].height);
      temp8[0] = tempDung.rooms[i].x;
      fwrite(temp8, 1, 1, f);
      temp8[0] = tempDung.rooms[i].y;
      fwrite(temp8, 1, 1, f);
      temp8[0] = tempDung.rooms[i].length;
      fwrite(temp8, 1, 1, f);
      temp8[0] = tempDung.rooms[i].height;
      fwrite(temp8, 1, 1, f);
    }
    
    fclose(f);
  }
  free(path);
  return 0;
}

struct dungeon loadMap(FILE *f){
  struct dungeon tempDung= {};
  struct room tempRoom;
  uint32_t temp32[1];
  uint8_t temp8[1];
  long tempL;
  //fpos_t temppos[1];
  fseek(f,0L, SEEK_END);
  //fgetpos(f, temppos);
  //printf("%d\n", temppos[0]);
  tempL = ftell(f);
  tempDung.size = (uint32_t) tempL;
 
  rewind(f);
  fread(tempDung.marker, 12, 1, f);
  //printf("%s\n", tempDung.marker);
  
  fread(temp32, 4, 1, f);
  tempDung.version = temp32[0];
  //printf("%d\n", tempDung.version);
  
  fread(temp32, 4, 1, f);
  //tempDung.size = temp32[0];
  be32toh(tempDung.size);
  //printf("%d\n", tempDung.size);
  
  fread(temp8, 1, 1, f);
  tempDung.pc_pos[0] = temp8[0];
  fread(temp8, 1, 1, f);
  tempDung.pc_pos[0] = temp8[1];
  //fread(temp8, 1, 1, f);
  
  
  uint8_t tempHardness[1];
  for(int i = 0; i < 21; i++){
    for(int j = 0; j < 80; j++){
      fread(tempHardness, 1, 1, f);
      tempDung.hardness[i][j] = tempHardness[0];
      if((i==0)||(i==20)){
	tempDung.map[i][j] = 3; //side wall
      }
      else if((j==0)||(j==79)){
	tempDung.map[i][j] = 4; //top wall
      }
      else{
	tempDung.map[i][j] = 0;
      }
      //printf("%4d", tempDung.hardness[i][j]);
    }
    //printf("\n");
  }
  
  uint8_t roomInfo[4];
  int i = 1702;
  tempDung.roomCount=0;
  while(i < tempDung.size){
    fread(roomInfo, 1, 4, f);
    i = i+4;;
    //printf("%d %d %d %d\n", roomInfo[0], roomInfo[1], roomInfo[2], roomInfo[3]);
    tempRoom.x = roomInfo[0];
    tempRoom.y = roomInfo[1];
    tempRoom.length = roomInfo[2];
    tempRoom.height = roomInfo[3];
    tempDung = placeRoom(tempDung, tempRoom);
  }
  for(i = 0; i < 21; i++){
    for(int j = 0; j < 80; j++){
      
      if((tempDung.map[i][j] == 0)&&(tempDung.hardness[i][j]<1)){
	tempDung.hardness[i][j] = 0;
	tempDung.map[i][j] = 2;
      }
      //printf("%2d", tempDung.map[i][j]);
    }
    //printf("\n");
  }
  //printDungeon(tempDung);
  return tempDung;

}
