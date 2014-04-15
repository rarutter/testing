

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/select.h>

#include <iostream>
#include <stdio.h>//still needed for fileno()

#include <readline/readline.h>
#include <readline/history.h>


void cb_linehandler(char*);

bool running;
char* prompt = "rltest$";


void cb_linehandler(char* line){

  if(line == NULL || strcmp(line, "exit")==0 ){

    if(line==0){
      std::cout<<"\n";
    }
    std::cout<<"exit\n";
    rl_callback_handler_remove();

    running = false;
  }
  else{

    if(*line){
      add_history(line);
    }
    std::cout<<"input line: "<<line<<std::endl;
    free(line);
  }

}


int main(){
  fd_set fds;
  int r;

  rl_callback_handler_install(prompt,cb_linehandler);

  running = true;
  while(running){

    FD_ZERO(&fds);
    FD_SET(fileno(rl_instream), &fds);

    r=select(FD_SETSIZE, &fds, NULL, NULL, NULL);
    if(r<0){
      std::cerr<"rltest:select";
      rl_callback_handler_remove();
      break;
    }

    if(FD_ISSET(fileno(rl_instream), &fds)){
      rl_callback_read_char();
    }

  }
  std::cout<<"event loop has exited\n";
  return 0;
}
