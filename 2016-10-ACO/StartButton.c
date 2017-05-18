/*
VERSION:1
LAST UPDATE:2016/10/19

アップデート内容:

内容:
・GPIOから入力する関数を別プロセスに構築する。

例外処理:
・ERROR型で返す。

コメント:
・pipe.cを参照した

 */
#include"Raspi.h"
#include"pipe.h"

ERROR StartButton(RASPI raspi,...){
  int pipe_child_parent[2];//pipe;child to parent
  int pipe_parent_child[2];//pipe;parent to child
  
  //criate pipe and error check;
  if(pipe(pipe_child_parent)<0){
    return CANT_CREATE_PIPE_CHILD_TO_PARENT;
  }

  if(pipe(pipe_parent_child)<0){
    close(pipe_child_parent[READ]);
    close(pipe_child_parent[WRITE]);
    return CANT_CREATE_PIPE_PARENT_TO_CHILD;
  }
  
  //Create process id.
  if((raspi->pipe.pid=fork())<0){
    close(pipe_child_parent[READ]);
    close(pipe_child_parent[WRITE]);
    close(pipe_parent_child[READ]);
    close(pipe_parent_child[WRITE]);
    return CANT_GET_PROCESS_ID;
  }
  
  //chack data
  if(raspi->pipe.value<0) raspi->pipe.value=0;

  //chack this program is child process or parent process.
  if(raspi->pipe.pid==0){
    //child pattern. this is new process.

    char* datas[raspi->pipe.value];

    //close "parent to child write" and "child to parent" pipe.
    close(pipe_child_parent[READ]);
    close(pipe_parent_child[WRITE]);

    //overwrite stdin and stdout.
    dup2(pipe_parent_child[READ],0);//stdin
    dup2(pipe_child_parent[WRITE],1);//stdout

    //close fd
    close(pipe_parent_child[READ]);
    close(pipe_child_parent[WRITE]);

    //read va_list
    if(raspi->pipe.value!=0){
      va_list va;
      int i;

      va_start(va,raspi);

      for(i=0;i<raspi->pipe.value;i++) datas[i]=va_arg(va,char*);

      va_end(va);
    }

    //start parent process
    if(execl(raspi->pipe.new_process_name,raspi->pipe.new_process_name,datas,NULL)<0){
      close(pipe_parent_child[READ]);
      close(pipe_child_parent[WRITE]);
      return CANT_START_NEW_PROGRAM;
    }
    return CHILD_END;
    
  }
  else if(raspi->pipe.pid>0){
    //parent pattern
    
    //close "parent to child read" and "child to parent write" pipe
    close(pipe_parent_child[READ]);
    close(pipe_child_parent[WRITE]);

    //substitute pipe for fd
    raspi->pipe.fd_r=pipe_child_parent[READ];
    raspi->pipe.fd_w=pipe_parent_child[WRITE];
  }

  return NOTHING_ERROR;
}
