#ifndef PIPE_HEADER_VER_1
#define PIPE_HEADER_VER_1

#include<stdio.h>
#include<string.h>
#include<stdarg.h>

#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

#ifndef READ
#define READ 0
#endif
#ifndef WRITE
#define WRITE 1
#endif

int popen2(int *fd_r,int * fd_w,const char *start_program_name,int value,...);

#endif//#ifndef PIPE_HEADER_VER_
