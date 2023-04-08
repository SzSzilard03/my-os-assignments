#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/mman.h>
#include <errno.h>


int stringStarts(char *str , char *x){
    char *zx = malloc(1700 * sizeof(char));
    zx = strcpy(zx,str);
    char *token=strtok(zx,"/");
    char *auxtok=strtok(NULL,"/");

    while(auxtok != NULL){
        token =auxtok;
        
        auxtok =strtok(NULL,"/");
    }
    
   
    for(int i = 0;i < sizeof(x)/8;i++){
        if(token[i] != x[i])
        {
            return 0;
        }
    }
    return 1;
}



void list_rec(char* path,int size, char* nams){
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[1512];
    struct stat statbuf={};
    dir = opendir(path);
    
    
    

   
    while((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
        snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
        if(lstat(fullPath, &statbuf) == 0) {
            if(S_ISDIR(statbuf.st_mode)) {
                if(size == -1 && (strcmp(nams,"x-1") == 0)){
                    printf("%s\n", fullPath);
                list_rec(fullPath,size,nams);
                }
                else{
                        if(size == -1){
                            if(stringStarts(fullPath,nams) == 1){
                               
                                printf("%s\n", fullPath);
                                list_rec(fullPath,size,nams);
                            }
                        }
                    
                    else{
                        list_rec(fullPath,size,nams);
                    }
                
                }
                
            } 
            else{
                if(size != -1){
                    if(statbuf.st_size > size){
                        if(strcmp(nams,"x-1") == 0){
                                            printf("%s\n", fullPath);
                        }   
                        else if(stringStarts(fullPath,nams) == 1){
                                                
                                                printf("%s\n", fullPath);
                            }
                    }
                    
                }
                else{
                    if(strcmp(nams,"x-1") == 0){
                    printf("%s\n", fullPath);
                }
                else if(stringStarts(fullPath,nams) == 1){
                        
                        printf("%s\n", fullPath);
                }
                }
            }
            
        } 
        }
    }
    closedir(dir);
}

void list(char* path,int r,int size,char* nams){
    
    
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[1512];
    struct stat statbuf={};
        dir = opendir(path);
        if(dir == NULL){
            printf("ERROR\n");
            printf("invalid directory path\n");
        }
        else{
            printf("SUCCESS\n");
            if(r!=0)
            list_rec(path,size,nams);
            else{
                while((entry = readdir(dir)) != NULL) {
                if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
                    snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
                    if(lstat(fullPath, &statbuf) == 0) {
            if(S_ISDIR(statbuf.st_mode)) {
                if(size == -1 && (strcmp(nams,"x-1") == 0)){
                    printf("%s\n", fullPath);
                
                }
                else{
                        if(size == -1){
                            if(stringStarts(fullPath,nams) == 1){
                                printf("%s\n", fullPath);
                                
                            }
                        }
                    
                    
                }
                
            } 
            else{
                if(size != -1){
                    if(statbuf.st_size > size){
                        if(strcmp(nams,"x-1") == 0){
                                            printf("%s\n", fullPath);
                        }   
                        else if(stringStarts(fullPath,nams) == 1){
                                                
                                                printf("%s\n", fullPath);
                            }
                    }
                    
                }
                else{
                    if(strcmp(nams,"x-1") == 0){
                    printf("%s\n", fullPath);
                }
                else if(stringStarts(fullPath,nams) == 1){
                    
                        printf("%s\n", fullPath);
                }
                }
            }
            
        }      
                }
            }
            closedir(dir);
        }
        
        
        }
        
    
}


int main(int argc, char **argv){
    if(argc >= 2){
        if(strcmp(argv[1], "variant") == 0){
            printf("10230\n");
        }
        else {if(strcmp(argv[1],"list") == 0){
            char* path = (char*)malloc(1600*sizeof(char));
            char* nams1 = (char*)malloc(1600*sizeof(char));
            nams1 = "x-1";
            int rec = 0;
            int size=-1;
            int cnt = 0;
            
            if(argc >= 3 ){

                if(strcmp(argv[2] , "recursive") != 0){
                    
                    char* token = strtok(argv[2],"=");
                    if(strcmp(token,"path")==0){
                             path=strtok(NULL," ");
                             cnt++;
                        
                    }
                    else{
                        if(strcmp(token,"size_greater") == 0){
                            size = atoi(strtok(NULL," "));
                            
                        }
                        else{
                            if(strcmp(token,"name_starts_with")==0)
                            nams1 = strtok(NULL," ");
                            else
                            cnt++;
                        }
                    }
                    
                }
                else{
                    rec = 1;
                }
                if(argc >= 4){
                    if(strcmp(argv[3] , "recursive") != 0){
                    
                    char* token = strtok(argv[3],"=");
                    if(strcmp(token,"path")==0){
                             path=strtok(NULL," ");
                             cnt++;
                        
                    }
                    else{
                        if(strcmp(token,"size_greater") == 0){
                            size = atoi(strtok(NULL," "));
                            
                        }
                        else{
                            if(strcmp(token,"name_starts_with")==0)
                            nams1 = strtok(NULL," ");
                            else
                            cnt++;
                        }
                    }
                    
                }
                else{
                    rec = 1;
                }
                }
                if(argc >= 5){
                    if(strcmp(argv[4] , "recursive") != 0){
                    
                    char* token = strtok(argv[4],"=");
                    if(strcmp(token,"path")==0){
                        cnt++;
                             path=strtok(NULL," ");
                       
                    }
                    else{
                        if(strcmp(token,"size_greater") == 0){
                            size = atoi(strtok(NULL," "));
                            
                        }
                        else{if(strcmp(token,"name_starts_with")==0)
                            nams1 = strtok(NULL," ");
                            else
                            cnt++;
                        }
                    }
                    
                }
                    else{
                    rec = 1;
                    }
                }
                    
            }
            
            if(cnt!=1)
            printf("ERROR\ninvalid directory path\n");
            else
            list(path,rec,size,nams1);
            
        
        }
        if(strcmp(argv[1],"parse")==0){
            char* path = (char*)malloc(1600*sizeof(char));
            path = strtok(argv[2],"=");
            path=strtok(NULL," ");
            printf("path: %s\n",path);
        }
    }
    
    }
    return 0;
}
