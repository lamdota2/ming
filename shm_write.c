/*************************************************************************
	> File Name: shm_get.c
	> Author: Terry
	> Mail: terry.liao@nokia-sbell.com
	> Created Time: 2021年03月07日 星期日 15时28分37秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
int main(int argc, char const *atgv[])
{
    //使用ftok函数获取键值
    key_t mykey;
    if((mykey = ftok(".",100))== -1)
    {
        printf("fail to ftok");
        return -1;
    }
    //通过shmget函数创建或者打开一个共享内存，返回一个共享内存的标识符
    int shmid;
    if((shmid = shmget(mykey,500,IPC_CREAT | 0666)) == -1)
    {
        printf("fail to shmget");
        return -1;
    }
    printf("shmid = %d\n",shmid);
    system("ipcs -m");
    //使用shmat函数映射共享内存的地址
    char *text;
    if((text = (char *)shmat(shmid,NULL,0)) == (void *)-1);
    strcpy(text,"hello world");
    printf("text = %s",text);
    return 0;
}
