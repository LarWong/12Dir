#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <zconf.h>
#include <printf.h>
#include <sys/stat.h>
#include <math.h>

int main(void) {
    const char * buffer[2][99];
    int diri = 0;
    int fili = 0;
    unsigned int tot_bytes = 0;
    struct dirent * line;
    DIR *dir = opendir(".");
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
    char pref = 0;
    long mult = 1;
    char pref_ary[3] = "KMG";
    for (int i = 1; i <= 3; i++){
        if (tot_bytes >= pow(1000,i)){
            pref = pref_ary[i-1];
            mult = pow(1000,i);
        }
    }
    char * men = calloc(6,sizeof(char));
    pref!=0 ? sprintf(men, "%lld%cB",tot_bytes/mult,pref) : sprintf(men, "%lldB",tot_bytes/mult);
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

void do_recursion(){
    struct dirent * line;
    DIR *dir = opendir(".");
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
}
