/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
void isTrue(void);
void isFalse(void);
char *upper(char *command);
char EXITFLAG = 0;
const long MAX_LINE_LEN = 80;
const long MAX_ROW = 20;
char **command;
//char *inputLine();
void inputLine();
char outPut(char *command);
//stack pointer
long sp = 0;
char PANIC = 0;
int VALUE[26];
char input_string[65554];
char VAL_FLAG = 0;
FILE *fp;
int retvalnum(char ch);
int main(int argc,char *argv[]){
  int i = 0;
  for(i = 0;i < 26;i++){
    VALUE[i] = 0;
  }
  srand((unsigned)time(NULL));
  command = malloc(MAX_LINE_LEN * sizeof(char *));
  for(i = 0;i < MAX_ROW;i++){
    command[i] = malloc(sizeof(char) * MAX_LINE_LEN);
  }
  if(argc==1){
  while(1){
    //command[sp] = inputLine();
    inputLine();
    outPut(command[sp]);
    if(EXITFLAG){
      break;
    }
    sp++;
  }

  }
  /***********
   *command mode
   ***********/
  if(argc!=1){
    fp = fopen(argv[1],"r");
    while(1){
      fgets(command[sp],MAX_LINE_LEN,fp);
      outPut(command[sp]);
      if(EXITFLAG){
        break;
      }
      sp++;
    }
  }
  for(i = 0;i < MAX_ROW;i++){
    free(command[i]);
  }
  
  
  free(command);
  return 0;
}
//input command
void inputLine(){
  fgets(command[sp],MAX_LINE_LEN,stdin);
//return command[sp];
}
char outPut(char *command){
  int i;
  int printval;
  int valnum;
  int digi;
  int cond;
  //char tmpstr[1024];
  command = upper(command);

  i = 0;
  //ASSIGN
  if(command[i] == '$'){
    i++;
    //valnum = command[i] - 'A';
    valnum = retvalnum(command[i]);
    VALUE[valnum] = 0;
    i++;
    if(command[i] == '='){
      i++;
      while(isdigit(command[i])){
	digi = command[i] - '0';
	VALUE[valnum] += digi;
	i++;
	if(isdigit(command[i])){
	  VALUE[valnum] *= 10;
	}
      }
    }
    i++;
  }
  i=0;
  //PRINT value
  if(command[i] == '!'){
    i++;
    printval = retvalnum(command[i]);
    printf("%d\n",VALUE[printval]);
  }
  //IF
  if(command[i] == '?'){
    i++;
    valnum = retvalnum(command[i]);
    cond = VALUE[valnum];
    if(cond){
      isTrue();
    }else{
      isFalse();
    }
  }
  //Random number
  if(command[i] == '@'){
    i++;
    valnum = retvalnum(command[i]);
    VALUE[valnum] = rand();
  }
  //INPUT only STRING!
  if(command[i] == '&'){
    fgets(input_string,MAX_LINE_LEN,stdin);
  }
  //PRINT string
  if(command[i] == '#'){
    printf("%s\n",input_string);
  }
  //debug mode
  /*
  int j;
  for(j = 0;j < 26;j++){
    printf("%c=",j+'A');
    printf("%d\n",VALUE[j]);
  }
  printf("%s",command);
  */
  if(!strcmp(command,"END\n") || !strcmp(command,"END")){
    EXITFLAG = 1;
  }
  return 0;
}
int retvalnum(char ch){
  int retnum = ch - 'A';
  if(retnum > 25 || retnum < 0){
    printf("value error\n");
    exit(1);
  }
  return retnum;
}

char *upper(char *command){
  int i;
  for(i = 0; i < MAX_LINE_LEN;i++){
    command[i] = toupper(command[i]);
  }
  return command;
}

void isTrue(){
  char tmpstr[1024];
  while(1){
    fgets(tmpstr,1024,fp);
    strcpy(tmpstr,upper(tmpstr));
    if(!strcmp("BEGINT\n",tmpstr)){
      break;
    }
  }
}
void isFalse(){
  char tmpstr[1024];
  while(1){
    fgets(tmpstr,1024,fp);
    strcpy(tmpstr,upper(tmpstr));
    if(!strcmp("ENDIF\n",tmpstr)){
      break;
    }
  }
}
