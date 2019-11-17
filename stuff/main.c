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

  printDirInfo("../");

  return 0;
}

  void printDirInfo(char * dirname){
    DIR *dir = opendir(dirname);
    printDirStatus(dir);

    int * fd curfile; //used to get file info in loop

    struct dirent * cur = readdir(dir);
    while (cur != NULL) {
      //if entry is directory:
      if (cur->d_type == DT_DIR) {
        printf("DIR: %s\n", cur->d_name);
      } else {
        printf("%s | ", cur->d_name);
        //get file info
        curfile = stat(cur->d_name);
        //only print info if file works
        if (printStatus(curfile) != 0) {
          printf("%d KB\n", curfile->)
        }
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
