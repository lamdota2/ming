/*************************************************************************
	> File Name: mmap_txt.c
	> Author: Terry
	> Mail: terry.liao@nokia-sbell.com
	> Created Time: 2021年03月07日 星期日 21时51分36秒
 ************************************************************************/

#include<stdio.h>
#include <sys/mman.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <error.h>  
  
#define BUF_SIZE 100  
  
int main(int argc, char **argv)  
{  
    int fd, nread, i;  
    struct stat sb;  
    char *mapped, buf[BUF_SIZE];  
  /*
    for (i = 0; i < BUF_SIZE; i++) {  
        buf[i] = '#';  
    }*/  
  
    /* 打开文件 */  
    if ((fd = open("data.txt", O_RDWR)) < 0) {  
        perror("open");  
    }  
  
    /* 获取文件的属性 */  
    if ((fstat(fd, &sb)) == -1) {  
        perror("fstat");  
    }  
  
    /* 将文件映射至进程的地址空间 */  
    if ((mapped = (char *)mmap(NULL, sb.st_size, PROT_READ |   
                    PROT_WRITE, MAP_SHARED, fd, 0)) == (void *)-1) {  
        perror("mmap");  
    }  
  
    /* 映射完后, 关闭文件也可以操纵内存 */  
    close(fd);  
  
    printf("%s\n,mapped[0-1]=%c-%c,st_size=%ld\n",mapped,mapped[0],mapped[17],sb.st_size);  
  
    /* 修改一个字符,同步到磁盘文件 */  
    mapped[20] = '9';  
    if ((msync((void *)mapped, sb.st_size, MS_SYNC)) == -1) {  
        perror("msync");  
    }  
  
    /* 释放存储映射区 */  
    if ((munmap((void *)mapped, sb.st_size)) == -1) {  
        perror("munmap");  
    }  
  
    return 0;  
}  
