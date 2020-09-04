#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void crawler(char *path);


int main()
{
    // Directory path
    char* path;

    path = (char*)malloc(100 * sizeof(char)); 
    // char path[100] = "/mnt/d/Games/Emulators/ROMs";

    // Input path from user
    printf("Enter path to list files: ");
    // scanf("%s", path);

    strcpy(path, "/mnt/d/Games/Emulators/ROMs");

    crawler(path);

    free(path);

    return 0;
}


void crawler(char *basePath)
{
    struct stat buffer;
    int status;
    
    char* nextPath;
    nextPath = (char*)malloc(100 * sizeof(char)); 
    struct dirent *dirent;
    DIR *dir = opendir(basePath);

    // if not directory or unable to open, exit
    if (!dir)
        return;

    while ((dirent = readdir(dir)) != NULL)
    {
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0)
        {
            printf("%s\n", dirent->d_name);

            strcpy(nextPath, basePath);
            strcat(nextPath, "/");
            strcat(nextPath, dirent->d_name);

            status = stat(nextPath, &buffer);

            //checks if entry is directory and sends crawler through it
            if (S_ISDIR(buffer.st_mode))
            {
                printf("%s\n\n", "isdir");
                crawler(nextPath);
            }

            //checks if entry is file and gets its size
            if (S_ISREG(buffer.st_mode))
            {
                printf("%ld\n\n", buffer.st_size);
            }

            
        }
    }

    closedir(dir);
}