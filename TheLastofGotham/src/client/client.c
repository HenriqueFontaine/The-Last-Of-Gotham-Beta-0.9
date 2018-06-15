#include <stdio.h>
  #include <stdlib.h>
  #include "alle.h"
  #include "client.h"
  #include <math.h>

//---------MENUS---------//
bool connectScreen = true;
bool loginScreen = true;
void menu_principal();
void waiting_room();
void char_select();
void ajustes();
void credits();
// JOGO
void jogo(int personagem);
// ENCERRAMENTO
void encerrar();
int theend=0;


typedef struct {
  int val;
  int pos;
}
vetor;

//---------MAIN--------//
int main() {
  printf("Inicializando...\n");
  run = 1;
  musica_de_fundo = 1;
  inicializacao();
  printf("Carregado ! :)\n");

  if (run) system("clear");

  //trans_inicial();

  al_start_timer(timer);

  menu_principal();

}


void printConnectScreen(char str[]);
void printLoginScreen(char str[]);

void merge(vetor * vector, int left, int right, vetor * aux) {
  int i, j, k;
  int mid;

  for (i=left; i<=right; i++) {
    aux[i]=vector[i];
  }

  mid=floor((left+right)/2);

  i=left;
  j=mid+1;

  for (k=left; k<=right; k++) {
    if (j>right) {
      vector[k]=aux[i];
      i++;
    } else if (i>mid) {
      vector[k]=aux[j];
      j++;
    } else if (aux[i].val<aux[j].val) {
      vector[k]=aux[i];
      i++;
    } else {
      vector[k]=aux[j];
      j++;
    }
  }
}


void msort(vetor * vector, int left, int right, vetor *aux) {

  if (left!=right) {
    int mid;

    mid=floor((left+right)/2);

    msort(vector, left, mid, aux);
    msort(vector, mid+1, right, aux);
    merge(vector, left, right, aux);
  }
}

void merge_sort(vetor *vector, int left, int right) {
  vetor * aux=NULL;

  aux=(vetor * )malloc((right+1)*sizeof(vetor));

  msort(vector, left, right, aux);

  free(aux);
}

enum conn_ret_t tryConnect(char IP[]) {
  char server_ip[30];
  printf("Please enter the server IP: ");
  //scanf(" %s", server_ip);
  //getchar();
  return connectToServer(IP);
}

void assertConnection(char IP[], char login[]) {
  enum conn_ret_t ans = tryConnect(IP);

  while (ans != SERVER_UP) 
  {
    if (ans == SERVER_DOWN) {
      puts("Server is down!");
    } else if (ans == SERVER_FULL) {
      puts("Server is full!");
    } else if (ans == SERVER_CLOSED) {
      puts("Server is closed for new connections!");
    } else {
      puts("Server didn't respond to connection!");
    }
    waiting_room();
    int res;
    while (res = tolower(getchar()), res != 'n' && res != 'y' && res != '\n') {
      puts("anh???");
    }
    if (res == 'n') {
      exit(EXIT_SUCCESS);
    }
    ans = tryConnect(IP);
  }
  //char login[LOGIN_MAX_SIZE + 4];
  //printf("Please enter your login (limit = %d): ", LOGIN_MAX_SIZE);
  //scanf(" %[^\n]", login);
  //getchar();
  int len = (int)strlen(login);
  sendMsgToServer(login, len + 1);
}

void printConnectScreen(char str[])
{
  al_draw_bitmap(ip_bckg, 0, 0, 0);

  al_draw_text(mad_64, al_map_rgb(255, 255, 255), COMPRIMENTO / 2, 30, ALLEGRO_ALIGN_CENTRE, "Digite o IP do server:");

  if (strlen(str) > 0)
  {
    al_draw_text(mad_64, al_map_rgb(255, 255, 255), COMPRIMENTO / 2, 
      (480 - al_get_font_ascent(mad_64)) / 2, 
      ALLEGRO_ALIGN_CENTRE, str);
  } else
  {
    al_draw_text(mad_64, al_map_rgb(255, 255, 255), COMPRIMENTO / 2, 
      (480 - al_get_font_ascent(mad_64)) / 2, 
      ALLEGRO_ALIGN_CENTRE, "0.0.0.0");
  }
}

void printLoginScreen(char str[])
{
  al_draw_bitmap(ip_bckg, 0, 0, 0);

  al_draw_text(mad_64, al_map_rgb(255, 255, 255), COMPRIMENTO / 2, 30, ALLEGRO_ALIGN_CENTRE, "Digite o Login desejado: ");

  if (strlen(str) > 0)
  {
    al_draw_text(mad_64, al_map_rgb(255, 255, 255), COMPRIMENTO / 2, 
      (ALTURA - al_get_font_ascent(mad_64)) / 2, 
      ALLEGRO_ALIGN_CENTRE, str);
  } else
  {
    al_draw_text(mad_64, al_map_rgb(255, 255, 255), COMPRIMENTO / 2, 
      (ALTURA - al_get_font_ascent(mad_64)) / 2, 
      ALLEGRO_ALIGN_CENTRE, "<login>");
  }
}



//-----------MENU PRINCIPAL------------//

#define OP_MENU 4
  void menu_principal() {

  if(musica_de_fundo){
    al_attach_audio_stream_to_mixer(menu, al_get_default_mixer());
    al_set_audio_stream_playing(menu, true);
  }
  else{
  	al_set_audio_stream_playing(menu, false);
  }
    al_set_audio_stream_playing(credito, false);
    al_set_audio_stream_playing(select_char, false);


  int op = 0;
  while (1) {
    ALLEGRO_EVENT event;
    al_wait_for_event(tick, &event);

    //------TIPOS DE EVENTO------//

    if (event.type == ALLEGRO_EVENT_TIMER) {
      //------IMPRESSAO NO DISPLAY-------//

      al_draw_bitmap(menu_bckg, 0, 0, 0);

      if (op == 0)
        al_draw_text(mad_30, YELLOW, COMPRIMENTO / 2, 190, ALLEGRO_ALIGN_CENTER, 
          "INICIAR JOGO");
      else
        al_draw_text(mad_30, WHITE, COMPRIMENTO / 2, 190, ALLEGRO_ALIGN_CENTER, 
          "INICIAR JOGO");
      if (op == 1)
        al_draw_text(mad_30, YELLOW, COMPRIMENTO / 2, 215, ALLEGRO_ALIGN_CENTER, 
          "AJUSTES");
      else
        al_draw_text(mad_30, WHITE, COMPRIMENTO / 2, 215, ALLEGRO_ALIGN_CENTER, 
          "AJUSTES");
      if (op == 2)
        al_draw_text(mad_30, YELLOW, COMPRIMENTO / 2, 240, ALLEGRO_ALIGN_CENTER, 
          "CREDITOS");
      else
        al_draw_text(mad_30, WHITE, COMPRIMENTO / 2, 240, ALLEGRO_ALIGN_CENTER, 
          "CREDITOS");
      if (op == 3)
        al_draw_text(mad_30, YELLOW, COMPRIMENTO / 2, 265, ALLEGRO_ALIGN_CENTER, 
          "SAIR");
      else
        al_draw_text(mad_30, WHITE, COMPRIMENTO / 2, 265, ALLEGRO_ALIGN_CENTER, 
          "SAIR");

      al_flip_display();
    } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
      if (event.keyboard.keycode == ALLEGRO_KEY_UP)
        op = (op - 1 + OP_MENU) % OP_MENU;
      if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) op = (op + 1) % OP_MENU;
      if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
        if (op == 0)
          return waiting_room();
        else if (op == 1)
          return ajustes();
        else if (op == 2)
          return credits();
        else
          return encerrar();
      }
    } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      return encerrar();
  }
}


//------------SALA DE ESPERA--------------//


void waiting_room() {
  char loginMsg[450]={0};
  char buffer[40]={};
  int pos=0;
  char ServerIP[30]={"127.0.0.1"};
  al_draw_bitmap(ip_bckg, 0, 0, 0);
  al_draw_text(mad_64, YELLOW, COMPRIMENTO/2, 150, ALLEGRO_ALIGN_CENTER, "ENTRE COM O IP:");
  al_flip_display();

  if(musica_de_fundo){
    al_attach_audio_stream_to_mixer(menu, al_get_default_mixer());
    al_set_audio_stream_playing(menu, true);
  }
  else{
  	al_set_audio_stream_playing(menu, false);
  }
  	al_set_audio_stream_playing(credito, false);
    al_set_audio_stream_playing(select_char, false);

  while (1) {
    ALLEGRO_EVENT event;
    al_wait_for_event(tick, &event);

    //------TIPOS DE EVENTO------//

    while (connectScreen)
    {
      startTimer();

      while (!al_is_event_queue_empty(tick))
      {
        ALLEGRO_EVENT connectEvent;
        al_wait_for_event(tick, &connectEvent);

        readInput(connectEvent, ServerIP, 30);

        if (connectEvent.type == ALLEGRO_EVENT_KEY_DOWN)
        {
          switch(connectEvent.keyboard.keycode)
          {
          case ALLEGRO_KEY_ENTER:
            connectScreen = false;
            break;
          }
        }

        if (connectEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
          connectScreen = false;
          loginScreen = false;
          //quit = true;
        }
      }

      printConnectScreen(ServerIP);
      al_flip_display();
      al_clear_to_color(al_map_rgb(0, 0, 0));
      FPSLimit();
    }

    while (loginScreen)
    {
      startTimer();


      while (!al_is_event_queue_empty(tick))
      {
        ALLEGRO_EVENT loginEvent;
        al_wait_for_event(tick, &loginEvent);

        readInput(loginEvent, loginMsg, 13);

        if (loginEvent.type == ALLEGRO_EVENT_KEY_DOWN)
        {
          switch(loginEvent.keyboard.keycode)
          {
          case ALLEGRO_KEY_ENTER:
            loginScreen = false;
            break;
          }
        }

        if (loginEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
          loginScreen = false;
        }
      }
      printLoginScreen(loginMsg);
      al_flip_display();
      al_clear_to_color(al_map_rgb(0, 0, 0));
      FPSLimit();
    }
    assertConnection(ServerIP, loginMsg);
    char_select();
  }
}


//---------SELECAO DE PERSONAGEM---------//

#define OP_CHAR 9
  #define TIME_AUX 12
  void char_select() {
  int op = 0;
  int i;
  int time = 0;

  char nome_char[8][14];
  strcpy(nome_char[0], "BATMAN");
  strcpy(nome_char[1], "CATWOMAN");
  strcpy(nome_char[2], "ROBIN");
  strcpy(nome_char[3], "BATWOMAN");
  strcpy(nome_char[4], "JOKER");
  strcpy(nome_char[5], "HARLEY QUINN");
  strcpy(nome_char[6], "BANE");
  strcpy(nome_char[7], "PENGUIN");

  if(musica_de_fundo){
    al_attach_audio_stream_to_mixer(select_char, al_get_default_mixer());
    al_set_audio_stream_playing(select_char, true);
  }
  else{
  	al_set_audio_stream_playing(select_char, false);
  }
    al_set_audio_stream_playing(credito, false);
    al_set_audio_stream_playing(menu, false);
  while (1) {
    ALLEGRO_EVENT event;
    al_wait_for_event(tick, &event);

    //------TIPOS DE EVENTO------//

    if (event.type == ALLEGRO_EVENT_TIMER) {
      time = (time + 1) % TIME_AUX;

      //------IMPRESSAO NO DISPLAY-------//

      al_draw_bitmap(char_bckg, 0, 0, 0);
      al_draw_rectangle(40 + op * 73, 397, 97 + op * 73, 445, YELLOW, 5);
      al_draw_bitmap(arrow, 623, 397, 0);

      if (op < 8)
        al_draw_text(mad_64, YELLOW, COMPRIMENTO / 2, 100, ALLEGRO_ALIGN_CENTER, 
          nome_char[op]);
      else
        al_draw_text(mad_64, YELLOW, COMPRIMENTO / 2, 212, ALLEGRO_ALIGN_CENTER, 
          "RETORNAR");

      for (i = 0; i < 8; i++) {
        if (op == i) {
          if (time > 5) {
            al_draw_tinted_scaled_rotated_bitmap_region(
              spr[i], _f1, WHITE, 16, 16, COMPRIMENTO / 2, 280, 6, 6, 0, 
              ALLEGRO_ALIGN_CENTER);
            al_draw_bitmap_region(spr[i], _f1, 52 + i * 73, 404, 0);
          }
          else {
            al_draw_tinted_scaled_rotated_bitmap_region(
              spr[i], _f0, WHITE, 16, 16, COMPRIMENTO / 2, 280, 6, 6, 0, 
              ALLEGRO_ALIGN_CENTER);
            al_draw_bitmap_region(spr[i], _f0, 52 + i * 73, 404, 0);
          }
        }
        else al_draw_bitmap_region(spr[i], _f2, 52 + i * 73, 404, 0);
      }

      al_flip_display();
    } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      return encerrar();
    else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
      if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
        op = (op - 1 + OP_CHAR) % OP_CHAR;
      else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
        op = (op + 1) % OP_CHAR;
      else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
        if (op == 8) return menu_principal();
        else return lobby(op);
      }
    }
  }
}


//------------SALA DE ESPERA--------------//

void lobby(int op) {
  int i, go = 0;
  DADOS pacote;
  int foi=1;
  int timerl=0;

  if(musica_de_fundo){
    al_attach_audio_stream_to_mixer(select_char, al_get_default_mixer());
    al_set_audio_stream_playing(select_char, true);
  }
  else{
  	al_set_audio_stream_playing(select_char, false);
  }
    al_set_audio_stream_playing(credito, false);
    al_set_audio_stream_playing(menu, false);


  while(foi){
    al_flip_display();
    al_draw_bitmap(wait_bckg, 0, 0, 0);
    al_draw_text(mad_64, MAGENTA, COMPRIMENTO/2, ALTURA/2, ALLEGRO_ALIGN_CENTER, "Esperando mais jogadores");
    sendMsgToServer(&pacote,DONT_WAIT);
    int rec = recvMsgFromServer(&pacote, WAIT_FOR_IT);
    if(pacote.lastid<7)go = pacote.lastid;
    printf("%d\n",pacote.lastid );
    if(go>=PLAYERSGO-1){     
      foi=0;
    }
    timerl++;
  }
    gameloading(op);
  
}

void gameloading(int personagem){
  int x, y;

  if(musica_de_fundo){
    al_attach_audio_stream_to_mixer(select_char, al_get_default_mixer());
    al_set_audio_stream_playing(select_char, true);
  }
  else{
  	al_set_audio_stream_playing(select_char, false);
  }
    al_set_audio_stream_playing(credito, false);
    al_set_audio_stream_playing(menu, false);

  switch(personagem) {
    case 0 :  x = 50;   y = 90;   break;
    case 1 :  x = 980;  y = 1180; break;
    case 2 :  x = 1060; y = 330;  break;
    case 3 :  x = 60;   y = 1060; break;
    case 4 :  x = 1640; y = 60;   break;
    case 5 :  x = 1640; y = 670;  break;
    case 6 :  x = 470;  y = 700;  break;
    case 7 :  x = 1500; y = 1210; break;
    default : x = 200;  y = 200;
  }
  int timerjogo = 0;
  int movtype = 0, dir = 1;
  DADOS pacote;
  DADOS_DISPLAY conversor[8];
  PROJETEIS tiros[TIRO];
  int conversortiros;


  int receber;
  int characters;
  int x_adv, y_adv;

  int ult_tiro=0;
  int ini_tiro=0;
  int shoot=0, dirproj=0;
  int ready=0;
  int ready_all=0;
  int readypersonagem[4];
  int ready_allpersonagem[4];
    pacote.inic=0;
    pacote.inicialtiro=0;
    int timerz=0;

    int timerloading=0;
  while (1) {
    ALLEGRO_EVENT event;
    al_wait_for_event(tick, &event);

    //------TIPOS DE EVENTO------//

    if (event.type == ALLEGRO_EVENT_TIMER) {
      //------IMPRESSAO NO DISPLAY-------//

      //-------PROCESSA MOVIMENTO-------//
     
      al_clear_to_color(BLACK);
      

      pacote.x_env = x;
      pacote.y_env = y;
      pacote.personagem=personagem;

      if(shoot==1){
        shoot=-1;
        dirproj = dir;
      }

      pacote.projetdir = dirproj; // direção do projetil, 1=cima,2=baixo,3=esquerda,4=direita 
      dirproj=0;

      
      sendMsgToServer(&pacote, sizeof(DADOS));
      ready=0;
      ready_all=0;
      int a=0;
      for(a=0;a<4;a++){
        readypersonagem[a]=0;
        ready_allpersonagem[a]=0;
      }
      for (receber=0; receber<5; receber++) {
        pacote.x_env = 0;
        pacote.y_env = 0;
        pacote.posicao = 0;
        pacote.personagem = 0;
        int rec = recvMsgFromServer(&pacote, DONT_WAIT);
        for (conversortiros=0; conversortiros<TIRO; conversortiros++) {
          tiros[conversortiros].x=pacote.prox[conversortiros];
          tiros[conversortiros].y=pacote.proy[conversortiros];
        }
        al_draw_bitmap(wait_bckg, 0, 0, 0);
        al_draw_text(mad_64, MAGENTA, COMPRIMENTO/2, ALTURA/2, ALLEGRO_ALIGN_CENTER, "Esperando mais jogadores");
        ult_tiro=pacote.finaltiro;
        ini_tiro=pacote.inicialtiro;
         if (rec != NO_MESSAGE) {
          if (pacote.personagem<9 && pacote.personagem>=0) {
            conversor[pacote.personagem].x = pacote.x_env;
            conversor[pacote.personagem].y = pacote.y_env;
            conversor[pacote.personagem].posicao = pacote.posicao;
            if(pacote.inic==1 && readypersonagem[pacote.personagem]==0){
              ready++;
              readypersonagem[pacote.personagem]=1;
            }
            if(pacote.allinic==1 && ready_allpersonagem[pacote.personagem]==0){
              ready_all++;
              ready_allpersonagem[pacote.personagem]=1;
            }
          }
        }
      }
      printf("%d %d\n",ready,ready_all );
      if(ready>=PLAYERSGO-1){
        pacote.allinic=1;
      }
     if(ready_all>=PLAYERSGO-1){
        jogo(personagem);
     }
    }
    timerz++;
    if(timerz>500){
      pacote.inic=1;
    }
}
}




//----------JOGO------------//


int ableWalk(int x, int y) {
  unsigned char r, g, b;
  int i, j;
  for (i=x; i<=x+16; i++) {
    for (j=y; j<=y+16; j++) {
      al_unmap_rgb(al_get_pixel(walk_area, i, j), &r, &g, &b);
      if (r==242 && g==0 && b==255) return 0;
    }
  }
  return 1;
}

#define _BITMOV 3
  void jogo(int personagem) {
  int x, y;

  if(musica_de_fundo){
    al_attach_audio_stream_to_mixer(menu, al_get_default_mixer());
    al_set_audio_stream_playing(menu, true);
  }
  else{
  	al_set_audio_stream_playing(menu, false);
  }
    al_set_audio_stream_playing(credito, false);
    al_set_audio_stream_playing(select_char, false);
  
  switch(personagem) {
    case 0 :  x = 50;   y = 90;   break;
    case 1 :  x = 980;  y = 1180; break;
    case 2 :  x = 1060; y = 330;  break;
    case 3 :  x = 60;   y = 1060; break;
    case 4 :  x = 1640; y = 60;   break;
    case 5 :  x = 1640; y = 670;  break;
    case 6 :  x = 470;  y = 700;  break;
    case 7 :  x = 1500; y = 1210; break;
    default : x = 200;  y = 200;
  }
  int timerjogo = 0;
  int movtype = 0, dir = 1;
  DADOS pacote;
  DADOS_DISPLAY conversor[8];
  PROJETEIS tiros[TIRO];
  int conversortiros;

  int receber;
  int characters;
  int x_adv, y_adv;
  int vstatus=30;
  int ult_tiro=0;
  int ini_tiro=0;
  int shoot=0, dirproj=0;
    pacote.inicialtiro=0;



  while (1) {
    ALLEGRO_EVENT event;
    al_wait_for_event(tick, &event);

    //------TIPOS DE EVENTO------//

    if (event.type == ALLEGRO_EVENT_TIMER) {
      //------IMPRESSAO NO DISPLAY-------//

      //-------PROCESSA MOVIMENTO-------//
      if (movtype) {
        if (movtype == 1) {
          dir = 1;
          if (ableWalk(x+172, y+112+_BITMOV)) y += _BITMOV;
        } else if (movtype == 2) {
          dir = 2;
          if (ableWalk(x+172-_BITMOV, y+112)) x -= _BITMOV;
        } else if (movtype == 3) {
          dir = 3;
          if (ableWalk(x+172+_BITMOV, y+112)) x += _BITMOV;
        } else {
          dir = 4;
          if (ableWalk(x+172, y+112-_BITMOV)) y -= _BITMOV;
        }
      } 
      al_clear_to_color(BLACK);
      al_draw_scaled_bitmap(map, x, y, 360, 240, 0, 0, 720, 480, 0);

      pacote.x_env = x;
      pacote.y_env = y;
      pacote.personagem=personagem;
      pacote.status = vstatus;
      pacote.inic =1;
      pacote.allinic=1;

      if(shoot==1){
      	shoot=-1;
      	dirproj = dir;
      }

      pacote.projetdir = dirproj; // direção do projetil, 1=cima,2=baixo,3=esquerda,4=direita 
      dirproj=0;

      
      sendMsgToServer(&pacote, sizeof(DADOS));
      if(vstatus<=0){
        return encerrar();
      }

      for (receber=0; receber<5; receber++) {
        pacote.x_env = 0;
        pacote.y_env = 0;
        pacote.posicao = 0;
        pacote.personagem = 0;
        int rec = recvMsgFromServer(&pacote, DONT_WAIT);
        for (conversortiros=0; conversortiros<TIRO; conversortiros++) {
          tiros[conversortiros].x=pacote.prox[conversortiros];
          tiros[conversortiros].y=pacote.proy[conversortiros];
        }

        ult_tiro=pacote.finaltiro;
        ini_tiro=pacote.inicialtiro;
         if (rec != NO_MESSAGE) {
          if (pacote.personagem<9 && pacote.personagem>=0) {
            conversor[pacote.personagem].x = pacote.x_env;
            conversor[pacote.personagem].y = pacote.y_env;
            conversor[pacote.personagem].posicao = pacote.posicao;
          }
        }
      }

      int localizar[8];

      vetor loc[8];
      int i;

      for (i=0; i<8; i++) {
        loc[i].val=conversor[i].y;;
        loc[i].pos=i;
      }

      merge_sort(loc, 0, 7);

      for (i=0; i<8; i++) localizar[i]=loc[i].pos;

      for (i=0; i<8; i++) {
        characters=localizar[i];

        if (characters!=personagem) {
          if (conversor[characters].posicao == 0)      al_draw_bitmap_region(spr[characters], _f0, (2*conversor[characters].x)-(2*x)+344, (2*conversor[characters].y)-(2*y)+224, 0);
          else if (conversor[characters].posicao ==1)  al_draw_bitmap_region(spr[characters], _f1, (2*conversor[characters].x)-(2*x)+344, (2*conversor[characters].y)-(2*y)+224, 0);
          else if (conversor[characters].posicao ==2)  al_draw_bitmap_region(spr[characters], _f2, (2*conversor[characters].x)-(2*x)+344, (2*conversor[characters].y)-(2*y)+224, 0);
          else if (conversor[characters].posicao ==3)  al_draw_bitmap_region(spr[characters], _l0, (2*conversor[characters].x)-(2*x)+344, (2*conversor[characters].y)-(2*y)+224, 0);
          else if (conversor[characters].posicao ==4)  al_draw_bitmap_region(spr[characters], _l1, (2*conversor[characters].x)-(2*x)+344, (2*conversor[characters].y)-(2*y)+224, 0);
          else if (conversor[characters].posicao ==5)  al_draw_bitmap_region(spr[characters], _l2, (2*conversor[characters].x)-(2*x)+344, (2*conversor[characters].y)-(2*y)+224, 0);
          else if (conversor[characters].posicao ==6)  al_draw_bitmap_region(spr[characters], _r0, (2*conversor[characters].x)-(2*x)+344, (2*conversor[characters].y)-(2*y)+224, 0);
          else if (conversor[characters].posicao ==7)  al_draw_bitmap_region(spr[characters], _r1, (2*conversor[characters].x)-(2*x)+344, (2*conversor[characters].y)-(2*y)+224, 0);
          else if (conversor[characters].posicao ==8)  al_draw_bitmap_region(spr[characters], _r2, (2*conversor[characters].x)-(2*x)+344, (2*conversor[characters].y)-(2*y)+224, 0);
          else if (conversor[characters].posicao ==9)  al_draw_bitmap_region(spr[characters], _b0, (2*conversor[characters].x)-(2*x)+344, (2*conversor[characters].y)-(2*y)+224, 0);
          else if (conversor[characters].posicao ==10) al_draw_bitmap_region(spr[characters], _b1, (2*conversor[characters].x)-(2*x)+344, (2*conversor[characters].y)-(2*y)+224, 0);
          else                                         al_draw_bitmap_region(spr[characters], _b2, (2*conversor[characters].x)-(2*x)+344, (2*conversor[characters].y)-(2*y)+224, 0);
          
          x_adv = conversor[characters].x;
          y_adv = conversor[characters].y;

          if (movtype) {
            if (movtype == 1 && x_adv - 6 <= x && x_adv + 6 >= x && y_adv + 6 >= y && y_adv - 6 <= y) {
              y -= _BITMOV;
              dir = 1;
            } else if (movtype == 2 && x_adv - 6 <= x && x_adv + 6 >= x && y_adv + 6 >= y && y_adv - 6 <= y) {
              x += _BITMOV;
              dir = 2;
            } else if (movtype == 3 && x_adv - 6 <= x && x_adv + 6 >= x && y_adv + 6 >= y && y_adv - 6 <= y) {
              x -= _BITMOV;
              dir = 3;
            } else if (movtype == 4 && x_adv - 6 <= x && x_adv + 6 >= x && y_adv + 6 >= y && y_adv - 6 <= y) {
              y += _BITMOV;
              dir = 4;
            }
          }
        }
        else {
          if (dir == 1) {
            if (movtype) {
              if (timerjogo > 5) {
                al_draw_bitmap_region(spr[personagem], _f0, 344, 224, 0);
                pacote.posicao = 0;
              } else {
                al_draw_bitmap_region(spr[personagem], _f1, 344, 224, 0);
                pacote.posicao = 1;
              }
            } else {
              al_draw_bitmap_region(spr[personagem], _f2, 344, 224, 0);
              pacote.posicao = 2;
            }
          }
          else if (dir == 2) {
            if (movtype) {
              if (timerjogo > 5) {
                al_draw_bitmap_region(spr[personagem], _l0, 344, 224, 0);
                pacote.posicao = 3;
              } else {
                al_draw_bitmap_region(spr[personagem], _l1, 344, 224, 0);
                pacote.posicao = 4;
              }
            } else {
              al_draw_bitmap_region(spr[personagem], _l2, 344, 224, 0);
              pacote.posicao = 5;
            }
          }
          else if (dir == 3) {
            if (movtype) {
              if (timerjogo > 5) {
                al_draw_bitmap_region(spr[personagem], _r0, 344, 224, 0);
                pacote.posicao = 6;
              } else {
                al_draw_bitmap_region(spr[personagem], _r1, 344, 224, 0);
                pacote.posicao = 7;
              }
            }
            	else {
              al_draw_bitmap_region(spr[personagem], _r2, 344, 224, 0);
              pacote.posicao = 8;
            }
          }
          else {
            if (movtype) {
              if (timerjogo > 5) {
                al_draw_bitmap_region(spr[personagem], _b0, 344, 224, 0);
                pacote.posicao = 9;
              } else {
                al_draw_bitmap_region(spr[personagem], _b1, 344, 224, 0);
                pacote.posicao = 10;
              }
            } else {
              al_draw_bitmap_region(spr[personagem], _b2, 344, 224, 0);
              pacote.posicao = 11;
            }
          }
        }
      }
      

      timerjogo = (timerjogo+1)%12;

      al_draw_scaled_bitmap(corner, x, y, 360, 240, 0, 0, 720, 480, 0);
      for(i=0;i<vstatus;i++){
        al_draw_bitmap(heart,8*i,0,0);
      }
      for(i=0;i<TIRO;i++){
      	al_draw_filled_rectangle((2*tiros[i].x)-(2*x)+342, (2*tiros[i].y)-(2*y)+222, (2*tiros[i].x)-(2*x)+346, (2*tiros[i].y)-(2*y)+226, YELLOW);
        if(tiros[i].x >= x && tiros[i].x <= x+16 && tiros[i].y >= y && tiros[i].y <= y+16){
          vstatus--;
        }
      }

      al_flip_display();
    }
    else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
      if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) movtype = 1;
      else if (event.keyboard.keycode == ALLEGRO_KEY_UP) movtype = 4;
      else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) movtype = 2;
      else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) movtype = 3;
      else if (event.keyboard.keycode == ALLEGRO_KEY_LSHIFT) shoot=1;
    }
    else if (event.type == ALLEGRO_EVENT_KEY_UP) {
      if (event.keyboard.keycode == ALLEGRO_KEY_DOWN && movtype == 1) movtype = 0;
      else if (event.keyboard.keycode == ALLEGRO_KEY_UP && movtype == 4) movtype = 0;
      else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT && movtype == 2) movtype = 0;
      else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && movtype == 3) movtype = 0;
      else if (event.keyboard.keycode == ALLEGRO_KEY_LSHIFT) shoot=0;
    } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return encerrar();
  }

  return encerrar();
}

#define OP_AJ 3
  void ajustes() {
  int op = 2;
  while (1) {
    ALLEGRO_EVENT event;
    al_wait_for_event(tick, &event);

    //------TIPOS DE EVENTO------//

    if (event.type == ALLEGRO_EVENT_TIMER) {
      //------IMPRESSAO NO DISPLAY-------//

      al_draw_bitmap(adjusts_bckg, 0, 0, 0);

      if (musica_de_fundo) al_draw_filled_rectangle(60, 265, 94, 299, YELLOW);
      else al_draw_rectangle(60, 265, 94, 299, YELLOW, 5);

      al_draw_filled_rectangle(60, 325, 94, 359, YELLOW);

      if (op == 0) al_draw_text(mad_64, YELLOW, 100, 260, 0, "MUSICA");
      else al_draw_text(mad_64, WHITE, 100, 260, 0, "MUSICA");

      if (op == 1) al_draw_text(mad_64, YELLOW, 100, 320, 0, "SOM");
      else al_draw_text(mad_64, WHITE, 100, 320, 0, "SOM");

      if (op == 2) al_draw_text(mad_64, YELLOW, 60, 400, 0, "VOLTAR");
      else al_draw_text(mad_64, WHITE, 60, 400, 0, "VOLTAR");

      al_flip_display();
    }
    else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
      if (event.keyboard.keycode == ALLEGRO_KEY_UP)
        op = (op - 1 + OP_AJ) % OP_AJ;
      if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) op = (op + 1) % OP_AJ;
      if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
        if (op == 0) musica_de_fundo = !musica_de_fundo;
        else return menu_principal();
      }
    } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return encerrar();
  }
}

void credits() {

	if(musica_de_fundo){
	  al_attach_audio_stream_to_mixer(credito, al_get_default_mixer());
	  al_set_audio_stream_playing(credito, true);
	}
	 else{
  	al_set_audio_stream_playing(credito, false);
  	}
	al_set_audio_stream_playing(select_char, false);
  	al_set_audio_stream_playing(menu, false);

  
  al_draw_bitmap(credits_bckg, 0, 0, 0);
  al_draw_text(mad_64, WHITE, 180, 40, ALLEGRO_ALIGN_CENTER, "GRUPO 1");
  al_draw_text(mad_30, WHITE, 180, 110, ALLEGRO_ALIGN_CENTER, "CARLOS HENRIQUE");
  al_draw_text(mad_30, WHITE, 180, 160, ALLEGRO_ALIGN_CENTER, "GABRIEL NOBREGA");
  al_draw_text(mad_30, WHITE, 180, 210, ALLEGRO_ALIGN_CENTER, "JOAO GABRIEL");
  al_draw_text(mad_30, WHITE, 180, 260, ALLEGRO_ALIGN_CENTER, "LUCAS AMBROSIO");
  al_draw_text(mad_30, WHITE, 180, 310, ALLEGRO_ALIGN_CENTER, "MARIA EDUARDA SENNA");
  al_draw_text(mad_30, WHITE, 180, 360, ALLEGRO_ALIGN_CENTER, "MATHEUS VINICIUS");
  al_draw_text(mad_30, WHITE, 180, 410, ALLEGRO_ALIGN_CENTER, "PAULA LIRA");
  al_draw_text(mad_30, YELLOW, 635, 430, ALLEGRO_ALIGN_CENTER, "RETORNAR");
  al_flip_display();

  while (1) {
    ALLEGRO_EVENT event;
    al_wait_for_event(tick, &event);

    //------TIPOS DE EVENTO------//

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      return;
    else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
      if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) return menu_principal();
    }
  }
}

void encerrar() {
  al_clear_to_color(BLACK);
  al_flip_display();

  al_destroy_display(janela);
  al_destroy_bitmap(menu_bckg);
  al_destroy_bitmap(char_bckg);
  al_destroy_bitmap(credits_bckg);
  al_destroy_event_queue(tick);
  al_uninstall_keyboard();
  al_destroy_sample_instance(music);
  al_uninstall_audio();

  int i;
  for (i = 0; i < 8; i++) al_destroy_bitmap(spr[i]);
  exit(1);
}
