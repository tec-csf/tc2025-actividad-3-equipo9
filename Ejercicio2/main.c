#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void crawler(char *path);


int main()
{
    // Directory path
    char path[100] = "/mnt/d/Games/Emulators/ROMs";

    // Input path from user
    // printf("Enter path to list files: ");
    // scanf("%s", path);

    crawler(path);

    return 0;
}


void crawler(char *basePath)
{
    struct stat buffer;
    int status;
    
    char nextPath[1000];
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
            if (S_ISDIR(buffer.st_mode))
            {
                printf("%s\n\n", "isdir");
                crawler(nextPath);
            }

            if (S_ISREG(buffer.st_mode))
            {
                printf("%ld\n\n", buffer.st_size);
            }

            
        }
    }

    closedir(dir);
}