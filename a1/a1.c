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

typedef struct Sectionheader{
    char sect_name[14];
    int sect_type;
    int sect_offset;
    int sect_size;
}Sectionheader;

int check_sf(char *path,int *x){
    int fd = open(path,O_RDONLY);
    if(fd == -1){
        return 0;
    }
    char magic[2] ;
    read(fd,magic,2);
    int header ; read(fd,&header,2);
    int version ; read(fd,&version,2);
    char buf[1];
    int nr_sec ; read(fd,buf,1);
    nr_sec = buf[0];
    int max = 0;
    if(strcmp(magic,"h5") != 0){
        
        close(fd);
        return 0;
    }
    else{
        if(version > 128 || version < 107){
            
            close(fd);
            return 0;
        }
        else{
            if(nr_sec < 3 || nr_sec > 13){
                
                close(fd);
                return 0;
            }
            else{
                 Sectionheader *sheader = malloc(nr_sec*sizeof(Sectionheader));
                    for(int i = 0;i < nr_sec;i++){
                        read(fd,sheader[i].sect_name,14);
                        read(fd,&sheader[i].sect_type,1);
                        read(fd,&sheader[i].sect_offset,4);
                        read(fd,&sheader[i].sect_size,4);
                        if(sheader[i].sect_size > max){
                            max = sheader[i].sect_size;
                        }
                        if(sheader[i].sect_type != 79 && sheader[i].sect_type != 69 && sheader[i].sect_type != 46 && sheader[i].sect_type != 40 && sheader[i].sect_type != 72){
                            free(sheader);
                            close(fd);
                            return 0;
                        }
                    }
                    free(sheader);
                close(fd);
                *x = max;
                return 1;
            }
        }
    }
}
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

void parse(char *path){
    int fd = open(path,O_RDONLY);
    if(fd == -1){
        return;
    }
    char magic[3] ;
    read(fd,magic,2);
    magic[2] = '\0';
    int header ; read(fd,&header,2);
    int version ; read(fd,&version,2);
    char buf[1];
    int nr_sec ; read(fd,buf,1);
    nr_sec = buf[0];
    if(strcmp(magic,"h5") != 0){
        printf("ERROR\nwrong magic\n");
        close(fd);
        return;
    }
    else{
        if(version > 128 || version < 107){
            printf("ERROR\nwrong version\n");
            close(fd);
            return;
        }
        else{
            if(nr_sec < 3 || nr_sec > 13){
                printf("ERROR\nwrong sect_nr\n");
                close(fd);
                return;
            }
            else{
                 Sectionheader *sheader = malloc((nr_sec+1)*sizeof(Sectionheader));
                    for(int i = 0;i < nr_sec;i++){
                        read(fd,sheader[i].sect_name,14);
                        read(fd,&sheader[i].sect_type,1);
                        read(fd,&sheader[i].sect_offset,4);
                        read(fd,&sheader[i].sect_size,4);
                        if(sheader[i].sect_type != 79 && sheader[i].sect_type != 69 && sheader[i].sect_type != 46 && sheader[i].sect_type != 40 && sheader[i].sect_type != 72){
                            printf("ERROR\nwrong sect_types\n");
                            free(sheader);
                            close(fd);
                            return;
                        }
                    }
                    printf("SUCCESS\n");
                    printf("version=%d\n",version);
                    printf("nr_sections=%d\n",nr_sec);
                    for(int i = 0;i < nr_sec;i++)
                    {
                        printf("section%d: %s %d %d\n",i+1,sheader[i].sect_name,sheader[i].sect_type,sheader[i].sect_size);
                    }
                    free(sheader);
                close(fd);
            }
        }
    }
   
}

void extract(char *path,int nr_sector,int line){
    int fd = open(path,O_RDONLY);
    if(fd == -1){
        return;
    }
    char magic[2] ;
    read(fd,magic,2);
    int header ; read(fd,&header,2);
    int version ; read(fd,&version,2);
    char buf[1];
    int nr_sec ; read(fd,buf,1);
    nr_sec = buf[0];
    if(strcmp(magic,"h5") != 0){
        printf("ERROR\ninvalid file\n");
        close(fd);
        return;
    }
    else{
        if(version > 128 || version < 107){
            printf("ERROR\ninvalid file\n");
            close(fd);
            return;
        }
        else{
            if(nr_sec < 3 || nr_sec > 13){
                printf("ERROR\ninvalid file\n");
                close(fd);
                return;
            }
            else{
                 Sectionheader *sheader = malloc(nr_sec*sizeof(Sectionheader));
                    for(int i = 0;i < nr_sec;i++){
                        read(fd,sheader[i].sect_name,14);
                        read(fd,&sheader[i].sect_type,1);
                        read(fd,&sheader[i].sect_offset,4);
                        read(fd,&sheader[i].sect_size,4);
                        if(sheader[i].sect_type != 79 && sheader[i].sect_type != 69 && sheader[i].sect_type != 46 && sheader[i].sect_type != 40 && sheader[i].sect_type != 72){
                            printf("ERROR\nwrong sect_types\n");
                            close(fd);
                            return;
                        }
                    }
                        
                    
                    
                close(fd);
            }
        }
    }
}

void findall_rec(char *path){
     int x;
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[1512];
    struct stat statbuf={};
    dir = opendir(path);
    
   
    while((entry = readdir(dir)) != NULL) {x=-1;
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
        snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
        if(lstat(fullPath, &statbuf) == 0) {
            if(S_ISDIR(statbuf.st_mode)) {
                findall_rec(fullPath);
            } 
            else{
                
                if(check_sf(fullPath,&x) ==1){
                    if(x <= 1471)
                    printf("%s\n",fullPath);
                }
            }
            
        } 
        }
    }
    closedir(dir);
}

void findall(char *path){
    DIR *dir = NULL;
    dir = opendir(path);
    if(dir != NULL){
        printf("SUCCESS\n");
        findall_rec(path);
    }
    else{
        printf("ERROR\ninvalid directory path\n");
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
            parse(path);
        }
        else if(strcmp(argv[1],"findall") == 0){
            char* path = (char*)malloc(1600*sizeof(char));
            path = strtok(argv[2],"=");
            path=strtok(NULL," ");
            findall(path);
        }
    }
    
    }
    return 0;
}
