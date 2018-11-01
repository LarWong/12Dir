
#include <dirent.h>
#include <zconf.h>
#include <printf.h>

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
        }
    }
    printf("dirs:\n");
    for (int i = 0; i < diri; i++){
        printf("\t%s\n",buffer[0][i]);
    }
    printf("dirs:\n");
    for (int i = 0; i < fili; i++){
        printf("\t%s\n",buffer[1][i]);
    }
}