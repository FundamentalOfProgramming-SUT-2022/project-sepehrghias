#include<stdio.h>

#include<string.h>

#include<ncurses.h>

#include<stdlib.h>

#include <curses.h>

#include <dirent.h>

#include <sys/stat.h>

#include <sys/types.h>


#define NUM 10000


char output[NUM];
char commandstr[NUM];
int status = 0;
void command_mode(WINDOW * command);
void inputcommand(WINDOW * mode , WINDOW * file , WINDOW * command , WINDOW * num , WINDOW* input);
void open ( WINDOW * mode , WINDOW * file , WINDOW * command , WINDOW * num , WINDOW* input);
void createfile(WINDOW * mode , WINDOW * file , WINDOW * command , WINDOW * num , WINDOW* input);
int main(){
    mkdir("root" , 0777);
    while(1){
   initscr();
   noecho();
   int b;
   cbreak();
   int maxx , maxy;
   getmaxyx(stdscr , maxy , maxx);
   WINDOW * mode = newwin(4 , 26 , maxy -10 , 1);
   refresh();
   box(mode , 0 , 0);
   if(status==0)
   mvwprintw(mode , 1 , 12 , "normal");
   else if(status==1)
    mvwprintw(mode , 1 , 12 , "visual");
    else if(status==2)
    mvwprintw(mode , 1 , 12 , "insert");

   wrefresh(mode);
   move(maxy - 4 , 2);
    WINDOW * mode1 = newwin(4 , 38 , maxy -10 , 26);
   refresh();
   box(mode1 , 0 , 0);
   mvwprintw(mode1 , 1 , 3 , "NOfile");
   wrefresh(mode1);

   WINDOW * win = newwin(maxy - 10 , 8 , 1 ,1);
   refresh();
   box(win , 0 , 0);
   for(int i =0 ; i<maxy-12 ; i++){
      mvwprintw(win , i+1 , 3 , "%d" , i+1);
   }
   wrefresh(win);

   WINDOW * input = newwin(maxy - 10 , maxx - 8 , 1 ,8);
   refresh();
   box(input , 0 , 0);
   wrefresh(input);

   WINDOW * command = newwin(5 , 130 , maxy -7 , 1);
   refresh();
   box(command , 0 , 0);
   wrefresh(command);
        while(1){
        b = wgetch(mode);
        if(b=='/' || b==':'){
        command_mode(command);
        inputcommand(mode , mode1 , command , win , input);
        break;
        }
    }

   getch();
   endwin();


    }

    return 0;
   
}

void command_mode(WINDOW * command){
    int b;
    int i = 2;
    memset(commandstr , '\0' , NUM);
    while (1)
    {
        b=wgetch(command);
        if(b=='\n')
        return;
        commandstr[i-2]=(char)b;
        mvwprintw(command , 2 ,i ,"%c" , b);
        i++;
    }
    
}

void inputcommand(WINDOW * mode , WINDOW * file , WINDOW * command 
, WINDOW * num , WINDOW* input){
    if(!strncmp(commandstr , ":open " , 5)){
        open( mode ,  file , command ,  num , input);
    }
    else if(!strncmp(commandstr , "createfile --file " , strlen("createfile --file "))){
        createfile(mode ,  file , command ,  num , input);
    }
    else{
        mvwprintw(command , 2 , 2 , "valid command");
        wrefresh(command);
    }
}


char * getpath(){
    char*path;
    char *path1;
    path1 = (char*)malloc(300 * sizeof(char));
    // if("creatfile--file /root"!=)
    path = strstr(commandstr , "root");
    if(path==NULL){
        printf("you dont,t use root in your path\n");
        return NULL;
    }
    int counter = 0;
    while(1){
        if((path[counter-4]=='.' && path[counter-3]=='t' && 
        path[counter-1]=='t' && path[counter-2]=='x') || (path[counter-1]=='c'
         && path[counter-2]=='.')){
            break;
        }
        path1[counter]=path[counter];
        counter++;
    }
    return path1;
}

void makedir(char *path){
    char *string ;
    string = (char *) calloc(100 , sizeof(char));
    int i = 0;
    string[0]='\0';
    while(1){
        if(i==strlen(path))
            break;
        if(path[i]=='/'){
            mkdir(string , 0777);
        }
        string[i]=path[i];

        i++;
    }

}
void open(WINDOW * mode , WINDOW * file , WINDOW * command , WINDOW * num , WINDOW* input){
char * path = getpath();

}

void createfile(WINDOW * mode , WINDOW * file , WINDOW * command , WINDOW * num , WINDOW* input){
    char * path = getpath();
    makedir(path);
    FILE*fp = fopen(path , "w");
    fclose(fp);
     mvwprintw(command , 2 , 2 , "succesfull");
    wrefresh(command);
}