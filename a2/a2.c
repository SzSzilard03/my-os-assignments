#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include "a2_helper.h"
#include <fcntl.h>
sem_t semafork;
sem_t thr;
sem_t incr;
sem_t decr;
int x = 0;
int ended = 0;
int counter;
int t11 = 0;
int unended;


void* thread6(void* arg)
{
    sem_t *st1 = sem_open("st1",O_CREAT,0644,0);
    sem_t *st2 = sem_open("st2",O_CREAT,0644,0);
    int ID = *((int*)arg);
    
    
    if(ID == 1){
        info(BEGIN,6,ID);
        info(END,6,ID);
        sem_post(st1);
    }
    else{
        if(ID == 3){
            sem_wait(st2);
            info(BEGIN,6,ID);
            info(END,6,ID);
        }
        else
            {
                info(BEGIN,6,ID);
                info(END,6,ID);
            }
    }
    pthread_exit(NULL);
}



void* thread2(void* arg){
    int ID = *((int*)arg);

   
sem_wait(&semafork);
    sem_wait(&incr);
    counter++;
    sem_post(&incr);
    
    if(ID == 11){
        
        info(BEGIN,2,ID);
        unended = 1;
    }
    else{
        info(BEGIN,2,ID);
    }
    sem_wait(&thr);
    if(unended == 1 && (counter == 5 )){
        info(END,2,11);
        sem_wait(&decr);
        counter--;
        unended = 0;
        sem_post(&decr);
        
    }
    sem_post(&thr);
    if(ID != 11 && unended == 0){          
            info(END,2,ID);
            sem_wait(&decr);
            counter--;
            sem_post(&decr);
    }
    
sem_post(&semafork);
    pthread_exit(NULL);
}




void* thread_function(void* arg)
{
    int ID;
    sem_t *st1 = sem_open("st1",O_CREAT,0644,0);
    sem_t *st2 = sem_open("st2",O_CREAT,0644,0);
    ID = *((int*)arg);
    if(ID == 1){
        while(x == 0){
            //astept
        }
        info(BEGIN,4,ID);
        info(END,4,ID);
        ended = 1;

    }
    else if(ID == 3){
        info(BEGIN,4,ID);
        x = 1;
        while(ended == 0){}
        info(END,4,ID);
    }
    else{
        if(ID == 4){
            sem_wait(st1);
            info(BEGIN,4,ID);
            info(END,4,ID);
            sem_post(st2);
        }
        else{
            info(BEGIN,4,ID);
            info(END,4,ID);
        }
        
    }
    pthread_exit(NULL);

}


int main(int argc, char **argv)
{

;
// tester initialization
// only one time in the main process
init();
// inform the tester about (main) process’ start
info(BEGIN, 1, 0);
// other process’ actions

// create a new process
int pid = fork();

if (pid == 0) {
// inform the tester about process’ start
info(BEGIN, 2, 0);
sem_init(&semafork,0,5);
sem_init(&thr,0,1);
sem_init(&incr,0,1);
sem_init(&decr,0,1);


    pthread_t tid2_1;
    pthread_t tid2_2;
    pthread_t tid2_3;
    pthread_t tid2_4;
    pthread_t tid2_5;
    pthread_t tid2_6;
    pthread_t tid2_7;
    pthread_t tid2_8;
    pthread_t tid2_9;
    pthread_t tid2_10;
    pthread_t tid2_11;
    pthread_t tid2_12;
    pthread_t tid2_13;
    pthread_t tid2_14;
    pthread_t tid2_15;
    pthread_t tid2_16;
    pthread_t tid2_17;
    pthread_t tid2_18;
    pthread_t tid2_19;
    pthread_t tid2_20;
    pthread_t tid2_21;
    pthread_t tid2_22;
    pthread_t tid2_23;
    pthread_t tid2_24;
    pthread_t tid2_25;
    pthread_t tid2_26;
    pthread_t tid2_27;
    pthread_t tid2_28;
    pthread_t tid2_29;
    pthread_t tid2_30;
    pthread_t tid2_31;
    pthread_t tid2_32;
    pthread_t tid2_33;
    pthread_t tid2_34;
    pthread_t tid2_35;
    pthread_t tid2_36;
    pthread_t tid2_37;
int id2_1 = 1,id2_2 = 2,id2_3 =3,id2_4 =4,id2_5=5,id2_6=6,id2_7=7,id2_8=8,id2_9=9,id2_10=10,
id2_11=11,id2_12=12,id2_13=13,id2_14=14,id2_15=15,id2_16=16,id2_17=17,id2_18=18,id2_19=19,id2_20=20,id2_21=21,id2_22=22,id2_23=23,id2_24=24,id2_25=25,id2_26=26,id2_27=27,id2_28=28,id2_29=29,
id2_30=30,id2_31=31,id2_32=32,id2_33=33,id2_34=34,id2_35=35,id2_36=36,id2_37=37;
    
    pthread_create(&tid2_11,NULL,thread2,&id2_11);
    pthread_create(&tid2_1,NULL,thread2,&id2_1);
    pthread_create(&tid2_2,NULL,thread2,&id2_2);
    pthread_create(&tid2_3,NULL,thread2,&id2_3);
    pthread_create(&tid2_4,NULL,thread2,&id2_4);
    pthread_create(&tid2_5,NULL,thread2,&id2_5);
    pthread_create(&tid2_6,NULL,thread2,&id2_6);
    pthread_create(&tid2_7,NULL,thread2,&id2_7);
    pthread_create(&tid2_8,NULL,thread2,&id2_8);
    pthread_create(&tid2_9,NULL,thread2,&id2_9);
    pthread_create(&tid2_10,NULL,thread2,&id2_10);
    pthread_create(&tid2_12,NULL,thread2,&id2_12);
    pthread_create(&tid2_13,NULL,thread2,&id2_13);
    pthread_create(&tid2_14,NULL,thread2,&id2_14);
    pthread_create(&tid2_15,NULL,thread2,&id2_15);
    pthread_create(&tid2_16,NULL,thread2,&id2_16);
    pthread_create(&tid2_17,NULL,thread2,&id2_17);
    pthread_create(&tid2_18,NULL,thread2,&id2_18);
    pthread_create(&tid2_19,NULL,thread2,&id2_19);
    pthread_create(&tid2_20,NULL,thread2,&id2_20);
    pthread_create(&tid2_21,NULL,thread2,&id2_21);
    pthread_create(&tid2_22,NULL,thread2,&id2_22);
    pthread_create(&tid2_23,NULL,thread2,&id2_23);
    pthread_create(&tid2_24,NULL,thread2,&id2_24);
    pthread_create(&tid2_25,NULL,thread2,&id2_25);
    pthread_create(&tid2_26,NULL,thread2,&id2_26);
    pthread_create(&tid2_27,NULL,thread2,&id2_27);
    pthread_create(&tid2_28,NULL,thread2,&id2_28);
    pthread_create(&tid2_29,NULL,thread2,&id2_29);
    pthread_create(&tid2_30,NULL,thread2,&id2_30);
    pthread_create(&tid2_31,NULL,thread2,&id2_31);
    pthread_create(&tid2_32,NULL,thread2,&id2_32);
    pthread_create(&tid2_33,NULL,thread2,&id2_33);
    pthread_create(&tid2_34,NULL,thread2,&id2_34);
    pthread_create(&tid2_35,NULL,thread2,&id2_35);
    pthread_create(&tid2_36,NULL,thread2,&id2_36);
    pthread_create(&tid2_37,NULL,thread2,&id2_37);

    pthread_join(tid2_1,NULL);
    pthread_join(tid2_2,NULL);
    pthread_join(tid2_3,NULL);
    pthread_join(tid2_4,NULL);
    pthread_join(tid2_5,NULL);
    pthread_join(tid2_6,NULL);
    pthread_join(tid2_7,NULL);
    pthread_join(tid2_8,NULL);
    pthread_join(tid2_9,NULL);
    pthread_join(tid2_10,NULL);
    pthread_join(tid2_11,NULL);
    pthread_join(tid2_12,NULL);
    pthread_join(tid2_13,NULL);
    pthread_join(tid2_14,NULL);
    pthread_join(tid2_15,NULL);
    pthread_join(tid2_16,NULL);
    pthread_join(tid2_17,NULL);
    pthread_join(tid2_18,NULL);
    pthread_join(tid2_19,NULL);
    pthread_join(tid2_20,NULL);
    pthread_join(tid2_21,NULL);
    pthread_join(tid2_22,NULL);
    pthread_join(tid2_23,NULL);
    pthread_join(tid2_24,NULL);
    pthread_join(tid2_25,NULL);
    pthread_join(tid2_26,NULL);
    pthread_join(tid2_27,NULL);
    pthread_join(tid2_28,NULL);
    pthread_join(tid2_29,NULL);
    pthread_join(tid2_30,NULL);
    pthread_join(tid2_31,NULL);
    pthread_join(tid2_32,NULL);
    pthread_join(tid2_33,NULL);
    pthread_join(tid2_34,NULL);
    pthread_join(tid2_35,NULL);
    pthread_join(tid2_36,NULL);
    pthread_join(tid2_37,NULL);

sem_destroy(&semafork);
sem_destroy(&thr);
sem_destroy(&incr);
sem_destroy(&decr);



int pid3 = fork();
if(pid3 == 0){
    //copii lui 3

    info(BEGIN,3,0);

    int pid7 =fork();
    if(pid7 == 0){
        //coppi lui 7 
        info(BEGIN,7,0);

        int pid8 = fork();
        if(pid8 == 0){
            info(BEGIN,8,0);


            info(END,8,0);
        }
        else{
            waitpid(pid8, NULL, 0);
            info(END,7,0);
        }

    }
    else{
        int pid9 = fork();
        if(pid9 == 0){
            info(BEGIN,9,0);

            info(END,9,0);
        }
        else{
            waitpid(pid7, NULL, 0);
            waitpid(pid9, NULL, 0);
              info(END,3,0);
        }

    }
   
}
else{
    waitpid(pid3,NULL,0);
    info(END, 2, 0);
}
}
else{
    int pid4 = fork();
if(pid4 == 0){
    info(BEGIN,4,0);
    int id1 = 1,id2= 2 ,id3 = 3,id4 = 4;
    pthread_t tid1 ;
    pthread_t tid2 ;
    pthread_t tid3 ;
    pthread_t tid4 ;
    pthread_create(&tid1,NULL,thread_function,&id1);
    pthread_create(&tid2,NULL,thread_function,&id2);
    pthread_create(&tid3,NULL,thread_function,&id3);
    pthread_create(&tid4,NULL,thread_function,&id4);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    pthread_join(tid4,NULL);
    info(END,4,0);
}
else{
        int pid5 = fork();
    if(pid5 == 0){
        info(BEGIN,5,0);
        int pid6 = fork();
        if(pid6 == 0){
            info(BEGIN,6,0);
            pthread_t tid6[6];
            int id6[6]={1,2,3,4,5,6};
            for(int i=0;i<6;i++){
                pthread_create(&tid6[i],NULL,thread6,&id6[i]);
            }
            for(int i=0;i<6;i++){
                pthread_join(tid6[i],NULL);
            }
            info(END,6,0);
        }
        else{
            waitpid(pid6, NULL, 0);
            info(END,5,0);
        }
    }
    else{
        waitpid(pid5, NULL, 0);
        waitpid(pid4, NULL, 0);
        waitpid(pid, NULL, 0);
        info(END, 1, 0);
    }
}

}




return 0;
}

