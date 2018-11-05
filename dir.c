#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <zconf.h>
#include <printf.h>
#include <sys/stat.h>
#include <math.h>

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



unsigned int helper(int dir_level, char * dir_name){
    unsigned int size = 0;
    struct dirent * line;
    DIR *dir = opendir(dir_name);
    while ((line = readdir(dir))){
        if (line->d_type == DT_DIR){
            size += helper(dir_level++ , line->d_name);
        }
        else{
            struct stat fileinfo;
            stat(line->d_name, &fileinfo);
            size += fileinfo.st_size;
        }
    }
    return size;
}

void do_recursion(){
    unsigned int size = 0;
    printf("files:\n");
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
    if (argc < 2){
        printf("\nPlease enter a dir, will print out current instead.\n");
        printf("Statistics for directory: %s\n",".");
        basic( opendir(".") );
    }else if (argc > 2){
        printf("\n\tYou have entered too many things. Will termanate Program.\n");
    }else{
        printf("\nOpening Dir...\n");
        DIR * target = opendir(argv[1]);
        if (target == NULL){
            printf("\nNo such Dir\n");
        } else {
            printf("Statistics for directory: %s\n",argv[1]);
            basic(target);
        }
    }
    return 0;
}
