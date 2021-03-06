#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <zconf.h>
#include <printf.h>
#include <sys/stat.h>
#include <math.h>
#include <errno.h>
#include <string.h>

char * readify(unsigned int size){
    char pref = 0;
    long mult = 1;
    char pref_ary[3] = "KMG";
    for (int i = 1; i <= 3; i++){
        if (size >= pow(1000,i)){
            pref = pref_ary[i-1];
            mult = pow(1000,i);
        }
    }
    char * men = calloc(6,sizeof(char));
    pref!=0 ? sprintf(men, "%ld%cB",size/mult,pref) : sprintf(men, "%ldB",size/mult);
    return men;
}

char * makeindent(int x){
    char * store = malloc(99);
    for (int i = 0; i < x; i++){
        strcat(store,"\t");
    }
    return store;
}

unsigned int helper(int dir_level, char * dir_name){
    const char * buffer[99];
    int fili = 0;
    unsigned int size = 0;
    struct dirent * line;
    DIR *dir = opendir(dir_name);
    //printf("%s",strerror(errno));
    while ((line = readdir(dir))){
        if (line->d_type == DT_DIR && strcmp(".", line->d_name) != 0 && strcmp("..", line->d_name) != 0 && strcmp("cmake-build-debug", line->d_name) != 0){
            size += helper(dir_level+1 , line->d_name);
        }
        else if (line->d_type == DT_REG){
            buffer[fili] = line->d_name;
            fili++;
            struct stat fileinfo;
            stat(line->d_name, &fileinfo);
            size += fileinfo.st_size;
        }
    }
    printf("%sdir %s :\n",makeindent(dir_level-1),dir_name);
    for (int i = 0; i < fili; i++){
        printf("%s%s\n",makeindent(dir_level), buffer[i]);
    }
    return size;
}

void do_recursion(){
    unsigned int size = 0;
    size = helper(1, ".");
    printf("TOTAL SIZE: %s", readify(size));
}

void basic(DIR * dir){
    const char * buffer[2][99];
    int diri = 0;
    int fili = 0;
    unsigned int tot_bytes = 0;
    struct dirent * line;
    while ((line = readdir(dir))){
        if (line->d_type == DT_DIR){
            buffer[0][diri] = line->d_name;
            diri++;
        }
        else{
            buffer[1][fili] = line->d_name;
            fili++;
            struct stat fileinfo;
            stat(line->d_name, &fileinfo);
            tot_bytes += fileinfo.st_size;
        }

    }
    char * men = readify(tot_bytes);
    printf("size: %s\n", men);
    printf("dirs:\n");
    for (int i = 0; i < diri; i++){
        printf("\t%s\n",buffer[0][i]);
    }
    printf("files:\n");
    for (int i = 0; i < fili; i++){
        printf("\t%s\n",buffer[1][i]);
    }
}

int main(int argc,char * argv[]) {
    int boo = 10;
    if (boo) {
        if (argc < 2) {
            printf("\nPlease enter a dir, will print out current instead.\n");
            printf("Statistics for directory: %s\n", ".");
            basic(opendir("."));
        } else if (argc > 2) {
            printf("\n\tYou have entered too many things. Will terminate Program.\n");
        } else {
            printf("\nOpening Dir...\n");
            DIR *target = opendir(argv[1]);
            if (target == NULL) {
                printf("\nNo such Dir\n");
            } else {
                printf("Statistics for directory: %s\n", argv[1]);
                basic(target);
            }
        }
    }
    else {
        do_recursion();
    }
    return 0;
}
