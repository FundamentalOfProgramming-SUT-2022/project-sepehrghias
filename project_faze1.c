#include <stdio.h>

#include <string.h>

#include <dirent.h>

#include <sys/stat.h>

#include <sys/types.h>

#include <stdlib.h>

#include <errno.h>

#include <unistd.h>


#define NUM 1000000

char output[NUM];
char clipboard[NUM];
char undo_name[300];
void createfile(char *a);
char * find_name(char *path);
int nameis_core(char *name);
void insertstr(char *a);
char* get_path(char* a);
void ReplaceAt(char *string , int at , char *str1 , char *str2);
void cat(char* a , int arman);
int check_file(char *a);
char *getstring(char *a);
char* tabdil(char *a);
void removes(char *a);
void copy(char *a);
void cut(char *a);
void paste(char *a);
int ch_enter(char *string);
void grep(char * a);
void replace(char *a);
void find(char *a);
int check_featf(int a , int b , int c , int d);
int FindSearch(FILE*file ,char * string , int word[] , int charc[]);
int SpecialFind(char *string , FILE *file);
int chand_space(char * string);
char * MakeUndoFile (char * path);
void DoUndo(char * path , char * token);
void AutoIndent(char * a);
void restore(char *a);
void compare(char *a);
void tree(char * a , int arman);
void ListFiles(char * dirname , int arman);
void arman(char *a);
int main(){
    char a[300];
    mkdir("root" , 0777);
    printf("hey lets start\n");
    while(1){
        gets(a);
        //barresi address dar qutation
        if(strstr(a , " =D ")!=NULL){
            arman(a);
        }
        else if(!strncmp(a , "createfile --file " , strlen("createfile --file "))){
            createfile(a);
        }
        else if(!strncmp(a , "insertstr --file " , strlen("insertstr --file "))){
            insertstr(a);
        }
        else if(!strncmp(a , "cat --file " , strlen("cat --file "))){
            cat(a , 1);
        }
        else if(!strncmp(a ,"removetstr --file " , strlen("removetstr --file ")) ){
            removes(a);
        }
        else if(!strncmp(a , "copystr --file " , strlen("copystr --file "))){
            copy(a);
        }
        else if(!strncmp(a , "pastestr --file " , strlen("pastestr --file "))){
            paste(a);
        }
        else if(!strncmp(a , "cutstr --file " , strlen("cutstr --file "))){
            cut(a);
        }
        else if(!strncmp(a , "find --str " , strlen("find --str "))){
            find(a);
        }
        else if(!strncmp(a , "replace --str1 "  , strlen("replace --str1"))){
            replace(a);
        }
        else if(!strncmp(a , "grep " , strlen("grep "))){
            grep(a);
        }
        else if(!strncmp(a , "undo --file" , strlen("undo --file"))){
            restore(a);
        }
        else if(!strncmp(a , "auto-indent " , strlen("auto-indent "))){
            AutoIndent(a);
        }
        else if(!strncmp(a , "tree " , 5)){
            tree(a  , 1);
        }
        else if(!strncmp(a , "compare " , 8)){
            compare(a);
        }
        else if(!strcmp(a ,"exit")){
            printf("have a good time!\n");
            break;
        }
        else{
            printf("not correct command\n");
        }
    }
    return 0;
}

char * find_name(char *path){
    char *token , *last;
    last = token = strtok(path, "/");
    for (;(token = strtok(NULL, "/")) != NULL; last = token);
    return last;
}

int nameis_core(char *name){
    int flag = 0;
    if(name[0]=='"'){
        while(flag!=strlen(name)){
            if(name[flag]==' '){

                return 1;
            }
            flag++;
        }
        printf("you add double qoutation wrongly\n");
        return 0;
    }
    else{

        while(flag!=strlen(name)){
            if(name[flag]==' '){
                printf("you forget double qoutation\n");
                return 0;
            }
            flag++;
        }
        return 1;
    }

}

int check_file(char*path){
    if(!access(path , F_OK))
    {
        printf("this file is exist\n");
        return 0;
    }
    return 1;
}

char* get_path(char* a){
    char*path;
    char *path1;
    path1 = (char*)malloc(300 * sizeof(char));
    // if("creatfile--file /root"!=)
    path = strstr(a , "root");
    if(path==NULL){
        printf("you dont,t use root in your path\n");
        return NULL;
    }
    int counter = 0;
    while(1){
        if((path[counter-4]=='.' && path[counter-3]=='t' && path[counter-1]=='t' && path[counter-2]=='x') || (path[counter-1]=='c' && path[counter-2]=='.')){
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

void createfile(char *a){
    int t;
    //check
    //kataha ra az ham joda kon
    char *token;
    char *path1;
    char path[300];
    char *name;
    path1=get_path(a);
    if(path1==NULL)
    return;
    strcpy(path , path1);
    name=find_name(path);
    t=nameis_core(name);
    if(t==1){
        if(name[0]=='"'){
            path1[strlen(path1)-1]='\0';
            for(int i ; i<strlen(path1)-2 ; i++){
                if(path1[i]=='"'){
                    for(int j = i ; j <= i+1 + strlen(name) - 2 ; j++){
                        path1[j]=path1[j+1];
                    }
                    break;
                }
            }
        }
        makedir(path1);
        if(check_file(path1)==1){

            FILE *sep = fopen(path1 , "w");

            fclose(sep);
            printf("success\n");

        }
    }
}

char *getstring(char*a) {
    int counter = 0;
    int count = 0;
    char string[400] = {'\0'};
    a = strstr(a, "--str");
    if(a==NULL) {
        char *t = "FALSE RESULT";
        return t;
    }
    while (1) {
        if ((a[counter + 6] == ' ' && a[counter + 7] == '-' && a[counter + 8] == '-' && a[counter + 9] == 'p' &&a[counter + 10] == 'o')
            || (a[counter + 6] == ' ' &&a[counter + 7] == '-' && a[counter + 8] == '-' && a[counter + 9] == 'f' &&a[counter + 10] == 'i' && a[counter + 11] == 'l')
            ||(a[counter + 6] == ' ' &&a[counter + 7] == '-' && a[counter + 8] == '-' && a[counter+9]=='s' && a[counter+10]=='t' && a[counter+11]=='r'
               && a[counter+12]=='2') || strlen(a)==counter + 6) {
            break;
        }
        if ((a[counter + 6] == '"' && a[counter + 7] == ' ' && a[counter + 8] == '-' && a[counter + 9] == '-' &&
             a[counter + 10] == 'p' && a[counter + 11] == 'o') || (a[counter + 6] == '"' && a[counter + 7] == ' ' &&
                                                                   a[counter + 8] == '-' && a[counter + 9] == '-' &&a[counter + 10] == 'f' &&
                                                                   a[counter + 11] == 'i' &&a[counter + 12] == 'l') ||( a[counter+6]=='"' && a[counter + 7] == ' ' &&a[counter + 8] == '-' && a[counter + 9] == '-' &&
                                                                                                                        a[counter+10]=='s' && a[counter+11]=='t' && a[counter+12]=='r'&& a[counter+13]=='2')) {
            break;
        }
        if (a[counter] == '\0') {
            char *b = "FALSE RESULT";
            return b;
        }
        if(a[counter+5]=='1' || a[counter+5]=='2')
            counter++;

        if (a[counter + 6] == '"') {
            counter++;
            string[count] = a[counter + 6];
            counter++;
            count++;
            continue;
        }
        if (a[counter + 6] == '\\' && a[counter + 7] == '"') {
            counter++;
            string[count] = a[counter + 6];
            counter++;
            count++;
            continue;
        }
        string[count] = a[counter + 6];
        counter++;
        count++;
    }
    return string;
}

void insertstr(char *a) {
    //back to insert to corect it
    // string age space dare joda kon
    //hale //n
    //talash bara hazf namad moshkel dar
    char path[100] ,stri[400];
    int count = 0;
    char * token;
    char *string;
    string = (char*)malloc(400 * sizeof(char));
    int from, to;
    strcpy(path , get_path(a));
    strcpy(string,getstring(a));
    if(!strcmp(string , "FALSE RESULT")){
        printf("not correct command\n");
        return ;
    }
    a = strstr(a , "--pos");
    if(a==NULL){
        printf("not correct command\n");
        return ;
    }
    int line = ch_enter(string);
    sscanf(a , "--pos %d:%d" ,& from ,&to);
    //int line = to - from;
    char *matn =(char*) calloc(NUM , sizeof(char));
    char *matn2 =(char*) calloc(NUM , sizeof(char));
    int lots = 1, counter = 0;
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("it's not correct address or file name\n");
        fclose(fp);
    } else {
        token=MakeUndoFile(path);
        DoUndo(path , token);
        while (1) {
            if (lots < from || count!=to) {

                matn[counter]=fgetc(fp);
                if (feof(fp)) {
                    break;
                }
                count++;
                if (matn[counter] == '\n') {
                    lots++;
                    count=0;
                }
                counter++;

            } else {

                if (fgets(stri, 40, fp) == NULL) {
                    break;
                }
                strcat(matn2 , stri);
            }

        }
        line = line + lots;
        line+= ch_enter(matn2);
        // printf("%s %d\n" ,string , strlen(string));
        fclose(fp);
        int ska =0 ;
        if(from>lots || count!=to){
            printf("you enter wrong position\n");
            return;
        }
        FILE * file = fopen(path , "w");
        fputs(matn , file);
        while(1) {
            if(string[ska]=='\0')
                break;
            else if(string[ska]=='\\' && string[ska+1]=='\\' && string[ska+2]=='n'){
                fputc('\\' , file);
                fputc('n' , file);
                ska += 2 ;
            }
            else if(string[ska]=='\\' && string[ska+1]=='n'){
                fputc('\n' , file);
                ska ++;
            }

            else
                fputc(string[ska] , file);
            ska++;
        }
        int g = ch_enter(string);
        fputs(matn2 , file);
        if(lots == line)
            fputc('\n' , file);
        printf("added succesfully\n");
        fclose(file);
    }
}

void cat(char* a , int arman) {
    //check
    //qutation
    char *path;
    path = get_path(a);
    if(!arman)
        memset(output , '\0' , NUM);
    char string[100];
    FILE *myfile = fopen(path, "r");
    while (1) {
        if (myfile == NULL) {
            printf("it's not correct address or file name");
            break;
        }
        if (fgets(string, 20, myfile) == NULL)
            break;
        if(arman)
        printf("%s", string);
        if(!arman)
            strcat(output , string);
    }
    fclose(myfile);
    if(arman)
    printf("\n");
}
void removes(char *a){
    //talash bara hazf on namade
    char u;
    char *path = get_path(a);
    char *string = (char*)calloc(NUM , sizeof(char));
    char * t;
    char *token;
    char flag='\0';
    int l = 0;
    int line=0 , word=-1 , chand;
    t= strstr(a , "--pos");
    if(t==NULL){
        printf("not correct command\n");
        return;
    }
    sscanf(t,"--pos %d:%d --size %d -%c" , &line , &word , &chand , &flag);
    if(line==0 || word==-1 || flag=='\0'){
        printf("not correct command\n");
        return;
    }
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("it's not correct address or file name\n");
        fclose(fp);
        return;
    }
    int counter = 0 , enter=1;
    int h = 0;
    token=MakeUndoFile(path);
    DoUndo(path , token);
    while(1){
        if(feof(fp))
            break;
        if(enter!=line) {
            string[counter] = fgetc(fp);
            if (string[counter]=='\n')
                enter++;
        }
        else{
            if(l<word+1){
                string[counter]=fgetc(fp);
                l++;
            }
            else{
                if(flag=='b'){
                    u=fgetc(fp);
                    if(u==EOF)
                        break;
                    string[counter-chand]=u;
                }
                else if(flag=='f'){
                    if(h==0) {
                        for (int k = 0; k < chand-1; k++)
                            fgetc(fp);
                    }
                    h++;
                    //barresi qutation
                    u=fgetc(fp);
                    if(u==EOF)
                        break;
                    string[counter-1] = u;
                }
                    //barresi word age \n dare ya na
                else{
                    printf("not correct command\n");
                    return;
                }
            }
        }

        counter++;
    }
    if(enter!=line){
        printf("you insert incorrect position\n");
        return;
    }
    printf("removed succesfully\n");
    fclose(fp);
    FILE *file = fopen(path , "w");
    fputs(string , file);
    fclose(file);
}

void copy(char *a){
    char *path = get_path(a);
    char * t = (char *)calloc(NUM , sizeof(char));
    char *string = (char*)calloc(NUM , sizeof(char));
    int l =0 ;
    int line = 0 , word = -1 , chand;
    char flag;
    t= strstr(a , "--pos");
    if(t==NULL){
        printf("not correct command\n");
        return;
    }
    sscanf(t,"--pos %d:%d --size %d -%c" , &line , &word , &chand , &flag);
    if(line==0 || word==-1 || flag=='\0'){
        printf("not correct command\n");
        return;
    }
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("it's not correct address or file name\n");
        fclose(fp);
        return;
    }
    int counter = 0 , enter = 1 ;
    while(1){
        if(feof(fp))
            break;
        if(enter!=line){
            string[counter]=fgetc(fp);
            if(string[counter]=='\n')
                enter++;
        }
        else{
            if(l<word) {
                string[counter] = fgetc(fp);
                l++;
            }
            else{
                if(flag=='b'){
                    //backward true
                    int i ,j;
                    string[counter]=fgetc(fp);
                    for(i = chand-1 ,j =0  ; i>=0 ; j++ ,  i--)
                        clipboard[j] = string[counter-i];
                    clipboard[j+1]='\0';
                    break;
                }
                else if(flag=='f'){
                    //forward true
                    for(int i = 0 ; i<chand ; i++)
                        clipboard[i]=fgetc(fp);
                    clipboard[chand] = '\0';
                    break;
                }

                else{
                    printf("not correct command\n");
                    return;
                }
            }

        }
        counter++;
    }
    if(enter!=line){
        printf("not correct command\n");
        return;
    }
    fclose(fp);
    printf("copy successfully\n");
}

void cut(char *a){
    copy(a);
    removes(a);
}
char * tabdil(char *a){
    char path[NUM];
    char *t;
    char string[NUM] = " --str ";
    strcpy(path , get_path(a));
    strcat(string , clipboard);
    t = strstr(a , " --pos");
    if(t==NULL){
        return NULL;
    }
    strcat(path , string);
    strcat(path , t);
    return path;
}

void paste(char *a){
    //its not okay yet
    //first handle it insert
    a = tabdil(a);
    if(a==NULL){
        printf("not correct command\n");
        return ;
    }
    insertstr(a);
}

int ch_enter(char *string){
    int counter = 0;
    for(int i = 0 ; i<strlen(string) ; i++){
        if(string[i]=='\n')
            counter++;
    }
    return counter;
}

int check_featf(int a , int b , int c , int d){
    if(a == 1 && b==0 && c==0 && d==0)
        return 1;
    else if(a == 0 && b==1 && c==0 && d==0)
        return 1;
    else if(a == 0 && b==0 && c==1 && d==0)
        return 1;
    else if(a == 0 && b==0 && c==0 && d==1)
        return 1;
    else if(a == 0 && b==0 && c==0 && d==0)
        return 2;
    else if(a == 0 && b==0 && c==1 && d==1)
        return 3;
    else{
        return 0;
    }
}

/*void find_evethi(int word[] , int l[] ,char * string , FILE * fp){
    char c;
    char * search = calloc(NUM , sizeof(char));
    int counter=0 , counterw = 0;
    while(1){
        if(feof(fp))
            break;
        c=fgetc(fp);

    }
}*/

int SpecialFind (char * string , FILE * file){
    char * search = calloc(NUM , sizeof(char));
    char c;
    int counter = 0 , max = -1 , flag = 1 , l=1;
    int t = strlen(string);
    while(1){
        if(feof(file)){
            break;
        }
        l=1;
        c = fgetc(file);
        if(c=='*'){
            search[counter]='\\';
            counter++;
        }
        search[counter] = c;
        flag =1;
        int i , j;
        for(i =1 , j = t-2 ; i<t ; i++ , j--) {
            if (search[counter - j] != string[i]) {
                flag = 0;
                break;
            }
        }
        if(flag==1){
            while ((search[counter-t+2 - l]!=' ') && ( counter-t+2-l!=-1))
                l++;
            max = counter - t + 3 -l;
        }
        counter++;
    }
    return max;
}

int chand_space(char * string){
    int space = 0;
    for(int i = 0 ; i<strlen(string) ; i++){
        if(string[i]==' ')
            space++;
    }
    return space;
}


int FindSearch(FILE*file ,char * string , int word[] , int l[]){
    char c;
    int space ,  star = 0 ;
    int counter = 0 , counterw = 0;
    int flag = 1 , max = -1 , h = 0;
    int t = strlen(string);
    char * search = calloc(NUM , sizeof(char));
    if(string[t-1]=='*'){
        string[t-1]='\0';
        t = t -1 ;
    }
    if(string[0]=='*'){
        counter = SpecialFind(string , file);
        return counter;
    }
    space = chand_space(string);
    while(1){
        if(feof(file)){
            break;
        }
        c=fgetc(file);
        if(c=='*'){
            search[counter]='\\';
            counter++;
            star = 1;
        }
        if(c==' '){
            counterw++;
        }
        search[counter] = c;
        flag = 1;
        int i , j;
        for(i=0 , j=t-1 ; i<t ; i++ , j--){
            if(search[counter-j] != string[i]) {
                flag =0;
                break;
            }
        }
        if(flag==1 ){
            if(star==0) {
                word[h] = counterw - space;
                l[h] = counter - t + 1;
            }
            if(star==1){
                word[h] = counterw - space - 1;
                l[h] = counter - t ;
            }
            h++;
            if(h==1) {
                max = counter - t + 1;
                if(star ==1)
                    max--;
            }
        }

        counter++;
    }
    word[h]=-10;
    l[h]=-10;
    return max;
}

void find(char *a){
    char *path = get_path(a);
    int count = 0 ,  at = 0 , all = 0 , byword = 0;
    char string[NUM];
    char * b;
    int  ate;
    int   word[100]  ={-10};
    int  charc[100]={-10};
    int check;
    int counter = 0;
    strcpy(string , getstring(a));
    char *token;
    b = strstr(a , "file");
    token = strtok(b , "-");
    while(token!=NULL){
        if((!strncmp(token , "at " , 3)) || (!strncmp(token , "at" , 2))) {
            at++;
            sscanf(token , "at %d" , &ate);
        }
        else if(!(strncmp(token , "all " , 4)) || (!strncmp ( token , "all" , 3)))
            all++;
        else if((!strncmp(token , "count " , 6)) || (!strncmp(token , "count" , 5)))
            count++;
        else if((!strncmp(token , "byword " , 7)) || (!strncmp(token , "byword" , 6)))
            byword++;
        token = strtok(NULL , "-");
    }
    printf("at : %d , all : %d , count : %d , byword : %d\n" ,at , all , count , byword);
    check = check_featf(count , at , byword , all);
    if(check==0) {
        printf("these features is not come with together");
        return;
    }
    if(check==2){  //simple find
        FILE * fp = fopen(path , "r");
        if(fp==NULL){
            printf("it's not correct address or file name\n");
            return;
        }
        counter = FindSearch(fp , string ,word ,charc);
        fclose(fp);
        printf("%d\n" ,counter);
    }
    if(check==1){
        FILE * fp = fopen(path , "r");
        if(fp==NULL){
            printf("it's not correct address or file name\n");
            return;
        }
        FindSearch(fp , string , word , charc);
        fclose(fp);
        if(count ==1){
            int i = 0;
            while(charc[i]!=-10)
                i++;
            printf("counted : %d\n" , i);
            return;
        }
        else if(at==1){
            int i =0 ;
            while(charc[i]!=-10){
                if(i+1==ate) {
                    printf("this word repeated %d times\n" , ate);
                    printf("%d\n",charc[i]);
                    return;
                }
                i++;
            }
            printf("this word not repeated %d times\n" , ate);
            return;
        }
        else if(byword){
            if(word[0]!=-10)
                printf("it starts at word : %d\n" , word[0]);
            else
                printf("not found this word in text\n");
            return;
        }
        else if(all){
            int i = 0;
            while(charc[i]!=-10){
                if(charc[i+1]!=-10)
                    printf("%d , ",charc[i]);
                else
                    printf("%d\n" , charc[i]);
                i++;
            }

            return;
        }
    }
    if(check==3){
        FILE * fp = fopen(path , "r");
        if(fp==NULL){
            printf("it's not correct address or file name\n");
            return;
        }
        FindSearch(fp , string , word , charc);
        fclose(fp);
        int i=0;
        while(word[i]!=-10){
            if(i==0){
                printf("word is find in :\n");
            }
            if(i!=0 && (word[i]==word[i-1])){
                i++;
                continue;
            }
            printf("%d\n",word[i]);
            i++;
        }
    }
    return;
}

/*void GetStringR(char *a , char * str1 , char * str2 ){
    char * c ;
    c= strstr(a , "--str");
    str1 = getstring(c);
    c = c+3;
    str2 = getstring(c);

}*/
/*void HazfStar(char * s){
    for(int i = 0 ; i<strlen(s)-1 ; i++){
        s[i]=s[i+1];
    }
    s[strlen(s)-1]='\0';
}*/
void ReplaceAt(char * string , int at , char *str1 ,char *str2){
    int a = 1;
    char *pos , temp[NUM];
    int d =0;
    int index = 0 ,  olen;
    int index1 = 0;
    if(str1[strlen(str1)-1]=='*') {
        str1[strlen(str1) - 1] = '\0';
        d=1;
    }
    olen = strlen(str1);
    strcpy(temp, string);
    while((pos=strstr(temp , str1))!=NULL){
        index = strlen(string)-strlen(pos);

        if(at==a || at==0) {
            string[index] = '\0';
            if(d==1){
                pos = strstr(pos , " ");
                index1 = strlen(temp) - strlen(pos) -1;
            }
            else
                index1 = strlen(temp) - strlen(pos);
            strcat(string, str2);

            strcat(string, temp + index1 + olen);
        }

        if(at==a)
            break;
        strcpy(temp , string + index + 1 );
        a++;
    }

}

void replace(char * a){
    char *path = get_path(a);
    int at=0 , all=0 , ate;
    char *token;
    char str1[100];
    char string[300];
    char str2[100];
    char *c;
    strcpy(str1 , getstring(a));
    c= strstr(a , "--str");
    c = c + 4;
    strcpy(str2 , getstring(c));
    if((!strcmp(str1 , "FALSE RESULT")) || (!strcmp(str2 , "FALSE RESULT"))){
        printf("not correct command\n");
        return;
    }
    FILE * ft = fopen(path , "r");
    if(ft==NULL){
        printf("it's not correct address or file name\n");
        return;
    }
    fclose(ft);
    printf("str 1 :%s , str 2 :%s\n" , str1 , str2);
    c = strtok(a ,"-");
    while(c!=NULL){
        if((!strncmp(c , "at " , 3)) || (!strncmp(c , "at" , 2))) {
            at++;
            sscanf(c , "at %d" , &ate);
        }
        else if(!(strncmp(c , "all " , 4)) || (!strncmp ( c , "all" , 3)))
            all++;
        c = strtok(NULL , "-");
    }
    printf("at : %d , all : %d\n" , at , all);
    token=MakeUndoFile(path);
    DoUndo(path , token);
    FILE *fp = fopen(path , "r");
    while(fgets(string , 300 , fp));
    fclose(fp);
    if(at==1)
        ReplaceAt(string , ate , str1 ,str2);
    else if(all)
        ReplaceAt(string , 0 ,str1 , str2);
    else
        ReplaceAt(string , 1 , str1 , str2);
    FILE *file = fopen(path , "w");
    fputs(string , file);
    fclose(file);
    return;
}

void grep_search(FILE*fp , int c , int i , char *path , int * fc , char * s){
    char string[NUM];
    while(fgets(string , 400 , fp ) != NULL){
        if((strstr(string , s)) != NULL){
            *(fc)+=1;
            if(i==1){
                printf("%s\n" ,path);
                return;
            }
            if(c==0){
                printf("%s" , string);
                if(string[strlen(string)-1]!='\n')
                printf("\n");
            }
        }
    }
    return;
}
void grep(char *a){
    char string[300];
    int fc = 0;
    char * path;
    int c=0 , i=0;
    a = strstr(a , "-");
    if(a[1]=='c')
        c++;
    else if(a[1]=='i')
        i++;
    strcpy(string , getstring(a));
    a = strstr(a , "--files ");
    printf("c is :%d , i is :%d\n" , c ,i);
    a=strstr(a , "root");
    while(a!=NULL){

        path = get_path(a);
        FILE * fp = fopen(path , "r");
        if(fp==NULL){
            printf("it's not correct address or file name\n");
            return;
        }
        grep_search(fp , c , i , path , &fc , string);
        fclose(fp);
        a = a + 2;
        a=strstr(a , "root");
    }
    if(c==1){
        printf("repeated in %d lines\n",fc);
    }

    return;
}

char * MakeUndoFile(char *path){
    char path1[200];
    char *NameOfFile;
    char path2[200];
    strcpy(path2 , path);
    strcpy(path1 , path);
    NameOfFile=find_name(path1);
    int index = strlen(path2)-strlen(NameOfFile);
    path2[index]='\0';
    strcat(path2 , "_undo");
    strcat(path2 , NameOfFile);
    return path2;
}

void DoUndo(char * path  , char * token){
    char string[NUM];
    FILE * fp = fopen(path , "r");
    if(fp==NULL)
        return;
    FILE * file = fopen(token , "w");
    while(fgets(string , 400 , fp)!=NULL){
        fputs(string , file);
    }
    fclose(fp);
    fclose(file);
}

void restore(char * a){
    char * path = get_path(a);
    char * path2 = MakeUndoFile(path);
    char string[100];
    FILE *file = fopen(path , "r");
    FILE *fp = fopen(path2 , "r");
    if(fp==NULL && (fgets(string , 100 , file))==NULL){
        remove(path);
        remove(path2);
        return;
    }
    if(fp==NULL)
        return;
    fclose(fp);
    if(file==NULL) {
        printf("it's not correct address or file name\n");
        return;
    }
    fclose(file);
    remove(path);
    rename(path2 , path);
    printf("undo successfully\n");
}

void AutoIndent(char *a){
    char string[NUM];
    int counter = 0;
    char * token;
    char c;
    char tab[] = "    ";
    int countacu = 0;
    char * path = get_path(a);
    FILE * fp = fopen(path , "r");
    if(fp==NULL)
    {
        printf("it's not correct address or file name\n");
        return;
    }
    token=MakeUndoFile(path);
    DoUndo(path , token);
    while((c=fgetc(fp))!=NULL){
        if(feof(fp)){
            break;
        }

        string[counter] = c;

        if(string[counter]=='{' && counter!=0){
            int l = 1;
            countacu++;
            string[counter] = '\0';
            while(string[counter-l]==' '){
                string[counter-l]='\0';
                l++;
            }
            if(string[counter-l]=='\n'){
                counter-=l-1;
                for(int i = 0 ; i<countacu-1 ; i++)
                    strcat(string , tab);
                counter+=4*(countacu-1);
                string[counter]='{';
                string[counter+1]='\n';
                counter+=2;
                continue;
            }
            counter -= l-1;
            string[counter]=' ';
            string[counter+1] ='{';
            string[counter+2]='\n';
            for(int i = 0 ; i<countacu ; i++)
                strcat(string , tab);
            counter = counter + 3 + countacu*4;

            continue;
        }

        if(string[counter]=='{' && counter==0){
            countacu++;
            counter++;
            string[counter]='\n';
            strcat(string , tab);
            counter +=4;
        }

        if(string[counter]=='}'){
            string[counter]='\0';
            int l = 1;
            countacu--;
            while(string[counter-l]==' '){
                string[counter-l]='\0';
                l++;
            }
            if(string[counter-l]=='\n' && string[counter-l-1]=='}'){
                counter -= l-1;
                for(int j=0 ; j<countacu ; j++)
                    strcat(string , tab);
                counter += 4*(countacu);
                string[counter]='}';
                    counter++;
                    string[counter]='\n';
                    continue;
            }
            counter -= l-1;
            string[counter]='\n';
            for(int j=0 ; j<countacu ; j++)
                strcat(string , tab);
            string[counter + 4 *countacu + 1]='}';
            counter = counter + 4 *countacu + 2;
            string[counter]='\n';
        }

        counter++;
    }
    fclose(fp);
    //printf("%s" , string);
    FILE * file = fopen(path , "w");
    fputs(string , file);
    printf("auto indent successfully\n");
    fclose(file);
}

int Chandline(FILE * a){
    int line =0 ;
    char string[NUM];
    while(fgets(string , 500 , a)){
        line++;
    }
    fseek(a , 0 , SEEK_SET);
    return line;
}

void compare(char *a){
    char * path;
    int t =1 , b =1;
    int s ,  f;
    char * path2;
    char string[500];
    int line = 0;
    char string2[500];
    a = strstr(a , "root/");
    if(a==NULL){
        printf("it's not correct address or file name\n");
        return;
    }
    path=get_path(a);
    a = a+2;
    a = strstr(a , "root/");
    if(a==NULL){
        printf("it's not correct address or file name\n");
        return;
    }
    path2 = get_path(a);
    FILE * fp = fopen(path , "r");
    FILE * file = fopen(path2 , "r");
    if(fp==NULL){
        printf("First file not found\n");
        return;
    }
    if(file==NULL){
        printf("Second file not found\n");
        return;
    }
    s = Chandline(fp);
    f = Chandline(file);
    while(1){
        if(fgets(string ,400 , fp )==NULL){
            t=0;
        }
        if(fgets(string2 , 400 ,file)==NULL){
            b = 0;
        }
        if(!(t || b))
            return;
        line++;
        if(t && b){
            if(strcmp(string , string2)!=0){
                printf("========== #%d  ==========\n" , line);
                printf("%s\n" , string);
                if(string[strlen(string)-1]!='\n')
                    printf("\n");
                    printf("%s\n", string2);
                if(string[strlen(string2)-1]!='\n')
                    printf("\n");
            }
        }
        if(t==0){
            printf(">>>>>>>>>> #%d - #%d >>>>>>>>>>\n",line , f);
            printf("%s\n",string2);
            for(int i = 0 ; i<f - line ; i++){
                fgets(string2 , 400 , file);
                printf("%s\n",string2);
            }
            break;
        }
        if(b==0){
            printf(">>>>>>>>>> #%d - #%d >>>>>>>>>>\n",line , s);
            printf("%s\n",string);
            for(int i = 0 ; i<s - line ; i++){
                fgets(string , 400 , fp);
                printf("%s\n",string);
            }
            break;
        }
    }
    fclose(file);
    fclose(fp);

    return;
}

void tree(char * a , int arman){
    int depth;
    int counter=0;
    if(arman)
        memset(output , '\0' , NUM);
    sscanf(a , "tree %d" , &depth);
    if(depth<=-1){
        printf("invalid depth\n");
        return;
    }
        DIR * directory;
        struct dirent *entry;
        directory = opendir("root");
        if(directory==NULL){
            printf("This is not a correct address\n");
            closedir(directory);
            return;
        }

        while((entry = readdir(directory))!=NULL){
            if(counter>2){
                if(arman)
            printf("%s\n",entry ->d_name);
                if(!arman){
                    strcat(output , entry ->d_name);
                    strcat(output , "\n");
                }
            if(depth==1 && entry ->d_type==DT_DIR){
                char dirname[300]={'\0'};
                strcat(dirname , "root");
                strcat(dirname , "/");
                strcat(dirname , entry ->d_name);
                ListFiles(dirname , arman);
                }
            }
            counter++;
        }
        closedir(directory);
        return;
}
void ListFiles(char * dirname , int arman){
    DIR * directory;
    int counter=0;
    struct dirent *entry;
    directory = opendir(dirname);
    if(directory==NULL){
        printf("This is not a correct address\n");
        closedir(directory);
        return;
    }

    while((entry = readdir(directory))!=NULL){
        if(counter>=2){
            if(entry ->d_name==".DS_Store")
            continue;
            if(arman) {
                printf("--");
                printf("%s\n", entry->d_name);
            }
            if(!arman){
                strcat(output , entry ->d_name);
                strcat(output , "\n");
            }
        }
        counter++;
    }
    closedir(directory);
    return;
}
char * CommandFirst(char *a){
    char string[400];
    int counter = 0;
    while(a[counter]!=' ' || a[counter+1]!='=' || a[counter+2]!='D' || a[counter+3]!=' ') {
        string[counter] = a[counter];
        counter++;
    }
    return string;
}

char * CommandSecond(char *a){
    a = strstr(a , "=D ");
    a=a+3;
    return a;
}

void arman(char * a){
//    printf("%s",a);
    char first_function[NUM];
    char second_function[NUM];
    strcpy(first_function , CommandFirst(a));
    strcpy(second_function , CommandSecond(a));
    //printf("%s\n",first_function);
    //printf("%s\n",second_function);
    if(!strncmp(first_function , "cat --file " , strlen("cat --file "))){
        cat(a , 0);
    }
    else if(!strncmp(first_function , "tree " , 5)){
        tree(a  , 0);
        output[strlen(output)-1]='\0';
    }
    //printf("%s\n",output);
    if(!strncmp(second_function , "insertstr --file " , strlen("insertstr --file "))){
        strcat(second_function , " --str ");
        strcat(second_function , output);
        insertstr(second_function);
    }
    else if(!strncmp(second_function , "find --file " , strlen("find --file "))){
        strcat(second_function , " --str ");
        strcat(second_function , output);
        find(second_function);
    }
    else if(!strncmp(second_function  , "grep " , 5)){
        strcat(second_function , " --str ");
        strcat(second_function , output);
        grep(second_function);
    }
    return;
}
//handle closing pairs