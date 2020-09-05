#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void crawler(char *basePath, long int *max, long int *counter, long int *sizes, long int *mult);
void urner(long int *sizes, long int counter, long int max, long int urn);


int main()
{
    
    long int urn;
    long int mult = 100;
    long int counter = 0;
    long int max = 0;

    char* path;
    path = (char*)malloc(100 * sizeof(char)); 
    // char path[100] = "/mnt/d/Games/Emulators/ROMs";

    long int* sizes;
    sizes = (long int*)malloc(sizeof(long int) * mult);

    // Input path from user
    printf("Enter path to list files: \n");
    // scanf("%s", path);

    strcpy(path, "..");

    crawler(path, &max, &counter, sizes, &mult);

    free(path);

    // printf("Enter urn size: \n");
    // scanf("%ld", &urn);
    urn = 1024;

    urner(sizes, counter, max, urn);

    // for (int i = 0; i < counter; i++)
    // {
    //     printf("%ld\n", sizes[i]);
    // }

    return 0;
}


void crawler(char *basePath, long int *max, long int *counter, long int *sizes, long int *mult)
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
            

            strcpy(nextPath, basePath);
            strcat(nextPath, "/");
            strcat(nextPath, dirent->d_name);

            status = stat(nextPath, &buffer);

            //checks if entry is directory and sends crawler through it
            if (S_ISDIR(buffer.st_mode))
            {
                crawler(nextPath, max, counter, sizes, mult);
            }

            //checks if entry is file and gets its size
            if (S_ISREG(buffer.st_mode))
            {
                printf("Name: %s\nWeight: %ld\n\n", dirent->d_name, buffer.st_size);
                if (buffer.st_size > *max)
                {
                    *max = buffer.st_size;
                }
                sizes[*counter] = buffer.st_size;
                *counter += 1;
                printf("Counter = %ld\nMax: %ld\n\n\n", *counter, *max);

                // if (*counter >= *mult)
                // {   
                //     *mult = *mult * 2;
                //     printf("mult is %ld\n", *mult);
                //     sizes = (long int*)realloc(sizes, *mult);
                //     if (sizes == NULL)
                //     {
                //         printf("ERROR\n");
                //         return;
                //     }
                //     else
                //     {
                //         printf("REALLOC SUCCEEDED\n");
                //     }
                // }
            }

            
        }
    }

    closedir(dir);
}

void urner(long int *sizes, long int counter, long int max, long int urnSize)
{
    long int urnNum = max/urnSize + 1;
    printf("Number of urns: %ld\n", urnNum);
    int perc;

    int* urns;
    urns = (int*)malloc(sizeof(int) * urnNum);

    for (int i = 0; i < urnNum; i++)
    {
        urns[i] = 0;
    }

    for (int i = 0; i < counter; ++i)
    {
        urns[sizes[i]/urnSize] += 1;
    }

    for (int i = 0; i < urnNum; i++)
    {
        if (urns[i] > 0)
        {
            printf("%7ld   -%7ld    %5d   ", urnSize*(i), urnSize*(i+1)-1, urns[i]);
            perc = urns[i]*100/counter;
            for (int i = 0; i <= perc; ++i)
            {
                printf("*");
            }

            printf("\n");
        }
        else
        {
            printf("%7ld   -%7ld    %5d   \n", urnSize*(i), urnSize*(i+1)-1, urns[i]);
        }
        
    }
}