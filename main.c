#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>

int printStatus(int status);

DIR * printDirStatus(DIR * status);

void printDirInfo(char * dirname);

int main() {

  char * directory = "../";
  printf("\nOpening directory %s\n", directory);
  printDirInfo("../");

  return 0;
}

  void printDirInfo(char * dirname){
    DIR *dir = opendir(dirname);
    printDirStatus(dir);
    printf("\n");

    struct dirent * cur = readdir(dir);

    struct stat * info; //var to store status of each file
    char * filepath; //var to store path of each file
    //make names into arrays to use with strcpy
    char dpath[50], fpath[50];

    while (cur != NULL) {
      //if entry is directory:
      if (cur->d_type == DT_DIR) {
        printf("DIR: %s\n", cur->d_name);
      } else {
        //malloc memory for stat info
        info = malloc(sizeof(struct stat));
        //need to append directory path to filename to get path
        //first need to change filename into char array to work with strcat
        strcpy(dpath, dirname); //re-declare dpath each time because it has been altered
        strcpy(fpath, cur->d_name);

        //filepath = strcat(dirname, cur->d_name);
        //printf("\tdirname: %s\n", dpath);
        //printf("\tfilename: %s\n", fpath);
        strcat(dpath, fpath);
        //printf("\tfilepath: %s\n", filepath);
        //char * pathname = filepath;

        printf("%s | ", dpath);
        //get file info
        int status = stat(dpath, info);
        //only print info if file works
        if (status != -1) {
          //printf("success!\n");
          printf("%d KB\n", info->st_size);
        } else printStatus(status);

        free(info);
      }
      cur = readdir(dir);
    }

  }

  int printStatus(int status) {
    if (status==-1) printf("Errno %d: %s\n", errno, strerror(errno));
    else printf("Success!\n");
    return status;
  }

  DIR * printDirStatus(DIR * status) {
    if (status==NULL) printf("Errno %d: %s\n", errno, strerror(errno));
    else printf("Success!\n");
    return status;
  }
