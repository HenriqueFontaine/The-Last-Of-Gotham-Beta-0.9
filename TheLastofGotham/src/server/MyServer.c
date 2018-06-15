#include "alle.h"
#include "server.h"
#include <stdio.h>
#include <string.h>

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define MAX_CHAT_CLIENTS 6
#define VEL_TIRO 3

int main()
{
  char client_names[MAX_CHAT_CLIENTS][LOGIN_MAX_SIZE];
  char str_buffer[BUFFER_SIZE];
  serverInit(MAX_CHAT_CLIENTS);
  puts("Server is running!!");
  DADOS aux_buffer;
  DADOS serverun;

  aux_buffer.finaltiro=1;
  aux_buffer.inicialtiro=0;

  int tirofinal=aux_buffer.finaltiro;
  int inicialtiro=aux_buffer.inicialtiro;
  int loop=0;
  int timertiro;
  int lastid;
  int timerreal=0;

  while (1) 
  {

    int id = acceptConnection();
    if (id != NO_CONNECTION) {
      recvMsgFromClient(client_names[id], id, WAIT_FOR_IT);
      strcpy(str_buffer, client_names[id]);
      strcat(str_buffer, " connected to chat");
      broadcast(str_buffer, (int)strlen(str_buffer) + 1);
      printf("%s connected id = %d\n", client_names[id], id);
      lastid=id;
    }

    struct msg_ret_t msg_ret = recvMsg(&aux_buffer);
    timertiro++;
    if(aux_buffer.projetdir){

        serverun.direct[tirofinal] = aux_buffer.projetdir;
        aux_buffer.projetdir=0;
        if(serverun.direct[tirofinal]==1){
          serverun.prox[tirofinal] = aux_buffer.x_env+8;
          serverun.proy[tirofinal] = aux_buffer.y_env+36;
        }
        else  if(serverun.direct[tirofinal]==2){
          serverun.prox[tirofinal] = aux_buffer.x_env-24;
          serverun.proy[tirofinal] = aux_buffer.y_env+8;
        }
        else  if(serverun.direct[tirofinal]==3){
          serverun.prox[tirofinal] = aux_buffer.x_env+36;
          serverun.proy[tirofinal] = aux_buffer.y_env+8;
        }
        else if(serverun.direct[tirofinal]==4){
          serverun.prox[tirofinal] = aux_buffer.x_env+8;
          serverun.proy[tirofinal] = aux_buffer.y_env-24;
        }

        serverun.timert[tirofinal]=0;
        tirofinal++;
        if(tirofinal>=10){
          tirofinal=0;
        }
    }
    
timerreal++;
  if(timerreal>5){
      for(loop=0;loop<10 ;loop++){
      serverun.timert[loop]++;

      if(serverun.direct[loop]==4)      serverun.proy[loop]-=VEL_TIRO;
      else if(serverun.direct[loop]==1) serverun.proy[loop]+=VEL_TIRO;
      else if(serverun.direct[loop]==2) serverun.prox[loop]-=VEL_TIRO;
      else if(serverun.direct[loop]==3) serverun.prox[loop]+=VEL_TIRO;

      if(serverun.timert[loop]>=100){
         serverun.prox[loop]=-10000;
        serverun.proy[loop]=-10000;
       }

    }
    timerreal=0;
  }

    serverun.inicialtiro=inicialtiro;
    aux_buffer.lastid=lastid;
    for(loop=inicialtiro;loop<=TIRO;loop++){  
      aux_buffer.prox[loop] = serverun.prox[loop];
      aux_buffer.proy[loop] = serverun.proy[loop];
      aux_buffer.inicialtiro = serverun.inicialtiro;

    }

    if(aux_buffer.status == 0){
      aux_buffer.x_env = -10000;
      aux_buffer.y_env = -10000;
    }
    if (msg_ret.status == MESSAGE_OK)
      broadcast(&aux_buffer,sizeof(DADOS));
    else if (msg_ret.status == DISCONNECT_MSG){
      sprintf(str_buffer, "%s disconnected", client_names[msg_ret.client_id]);
      printf("%s disconnected, id = %d is free\n", client_names[msg_ret.client_id], msg_ret.client_id);
      broadcast(str_buffer, (int)strlen(str_buffer) + 1);
    }
  }
}
