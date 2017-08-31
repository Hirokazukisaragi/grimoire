/*
one line to give the program's name and an idea of what it does.
Copyright (C) 2017  name of hirokazu

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char EXITFLAG = 0;
const long MAX_LINE_LEN = 80;
const long MAX_RAW = 20;
char **command;
//char *inputLine();
void inputLine();
char outPut(char *command);
//stack pointer
long sp = 0;
int main(int argc,char *argv[]){
  int i = 0;
  command = malloc(MAX_LINE_LEN * sizeof(char *));
  for(i = 0;i < MAX_RAW;i++){
    command[i] = malloc(sizeof(char) * MAX_LINE_LEN);
  }
      
  while(1){
    //command[sp] = inputLine();
    inputLine();
    outPut(command[sp]);
    if(EXITFLAG){
      break;
    }
    sp++;
  }
  
  for(i = 0;i < MAX_RAW;i++){
    free(command[i]);
  }
  
  
  free(command);
  return 0;
}
	
void inputLine(){
  fgets(command[sp],MAX_LINE_LEN,stdin);
//return command[sp];
}
char outPut(char *command){
  int i;
  for(i = 0; i < MAX_LINE_LEN;i++){
    command[i] = toupper(command[i]);
  }
  printf("%s",command);
  if(!strcmp(command,"END\n")){
    EXITFLAG = 1;
  }
  return 0;
}
