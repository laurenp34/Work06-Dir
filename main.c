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

int printDirInfo(char * dirname);

char *  getpwd();

int main(int argc, char *argv[]) {

  // char * directory = "/";
  // printf("\nOpening directory %s\n", directory);

  fgets(argv,2, stdin);
  char * dir_input = argv[1];
  //do not work if user doesn't enter input
  if (dir_input == NULL) {
    printf("Please re-run and enter a directory input!\n");
    return 0;
  }
  printf("Opening directory: %s\n", dir_input);

  int bytes = printDirInfo(dir_input);
  if (bytes == -1) return 0; 
  printf("\nTotal diretory size: %d bytes\n", bytes);



  // //add pwd to front of absolute path
  // char pwd[1000], abs_dir[1000];
  // pwd = getpwd();
  //
  // //combine pwd and specified directory path
  // strcpy(abs_dir, directory);
  // strcat(pwd, abs_dir);

  //printf("Absolute path: %s\n", pwd);
  //int bytes = printDirInfo(pwd);
  //printf("\nTotal diretory size: %d bytes\n", bytes);

  return 0;
}

//returns total bytes of directory
  int printDirInfo(char * dirname){
    DIR * dir = malloc(sizeof(DIR));
    dir = opendir(dirname);
    if (printDirStatus(dir) == NULL) {
      printf("Please enter a valid directory!\n");
      return -1;
    }
    printf("\n");

    struct dirent * cur = readdir(dir);

    struct stat * info; //var to store status of each file
    char * filepath; //var to store path of each file
    //make names into arrays to use with strcpy
    char dpath[500], fpath[50];

    int totalmem = 0; //var to store total memory of files in dir

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

        strcat(dpath, fpath);
        // printf("good\n");
        // printf("fpath: %s\n", cwd);
        //printf("\tfilepath: %s\n", filepath);
        //char * pathname = filepath;

        printf("%s | ", fpath);
        //get file info
        int status = stat(dpath, info);
        //only print info if file works
        if (status != -1) {
          //printf("success!\n");
          totalmem += info->st_size;
          printf("%d B\n", info->st_size);
        } else printStatus(status);

        free(info);
      }
      cur = readdir(dir);
    }

    free(dir);
    return totalmem;

  }

  char* getpwd() {
    char pwd[1000];
    getcwd(pwd, sizeof(pwd));
    if (pwd==NULL) printf("Errno %d: %s\n", errno, strerror(errno));
    char * out = pwd;
    return out;
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
