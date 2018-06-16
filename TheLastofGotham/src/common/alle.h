#ifndef _ALLE_H_

#define _ALLE_H_

// BIBLIOTECAS
#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

// PARAMETROS DA TELA
#define COMPRIMENTO 720
#define ALTURA 480
#define FPS 30
#define TIRO 10
#define PLAYERSGO 2

// CORES
#define BLACK al_map_rgb(0, 0, 0)
#define WHITE al_map_rgb(255, 255, 255)
#define RED al_map_rgb(255, 0, 0)
#define BLUE al_map_rgb(0, 0, 255)
#define GREEN al_map_rgb(0, 255, 0)

#define MAGENTA al_map_rgb(255, 0, 255)
#define YELLOW al_map_rgb(255, 255, 0)
#define CYAN al_map_rgb(0, 255, 255)
#define ORANGE al_map_rgb(255, 153, 51)
#define DARK_BLUE al_map_rgb(0, 0, 102)
#define DARK_PURPLE al_map_rgb(51, 0, 51)
#define DPURPLE al_map_rgb(25, 0, 25)
#define DARK_GREY al_map_rgb(64, 64, 64)
#define GREY al_map_rgb(96, 96, 96)
#define LIGHT_GREY al_map_rgb(160, 160, 160)

double startingTime;

// PONTEIROS
// TELA
ALLEGRO_DISPLAY* janela;
// FONTES
ALLEGRO_FONT* mad_24;
ALLEGRO_FONT* mad_30;
ALLEGRO_FONT* mad_64;
ALLEGRO_FONT* mad_72;
ALLEGRO_FONT* knight_72;
// BACKGROUNDS
ALLEGRO_BITMAP* menu_bckg;
ALLEGRO_BITMAP* char_bckg;
ALLEGRO_BITMAP* credits_bckg;
ALLEGRO_BITMAP* adjusts_bckg;
ALLEGRO_BITMAP* ip_bckg;
ALLEGRO_BITMAP* wait_bckg;
ALLEGRO_BITMAP* over_bckg;
ALLEGRO_BITMAP* winner;
// SPRITES
ALLEGRO_BITMAP* spr[8];
// ICONS
ALLEGRO_BITMAP* arrow;
ALLEGRO_BITMAP* heart;
// MAPS
ALLEGRO_BITMAP* map;
ALLEGRO_BITMAP* corner;
ALLEGRO_BITMAP* walk_area;
ALLEGRO_LOCKED_REGION* walkable;
// MUSICA
ALLEGRO_AUDIO_STREAM* menu;
ALLEGRO_AUDIO_STREAM* credito;
ALLEGRO_AUDIO_STREAM* select_char;
//SOM
ALLEGRO_SAMPLE *sample;


#define _f0 0, 0, 32, 32  // 0
#define _f2 32, 0, 32, 32  // 1
#define _f1 64, 0, 32, 32  // 2
#define _l0 0, 32, 32, 32  // 3
#define _l2 32, 32, 32, 32  // 4
#define _l1 64, 32, 32, 32  // 5
#define _r0 0, 64, 32, 32  // 6 
#define _r2 32, 64, 32, 32  // 7
#define _r1 64, 64, 32, 32  // 8
#define _b0 0, 96, 32, 32  // 9
#define _b2 32, 96, 32, 32  // 10
#define _b1 64, 96, 32, 32  // 11

// INPUT TECLADO
ALLEGRO_EVENT_QUEUE* tick;
// MUSICA
ALLEGRO_SAMPLE* music;
// TIMER
ALLEGRO_TIMER* timer;

// Dados

typedef struct
{
	int x_env;
	int y_env;
	int posicao;
	int personagem;
	int projetdir;
	int direct[TIRO];
	int prox[TIRO];
	int proy[TIRO];
	int timert[TIRO];
	int finaltiro;
	int inicialtiro;
	int lastid;
	int inic;
	int allinic;
	int status;
}DADOS;

typedef struct 
{
	int x;
	int y;
	int tipo;
}PROJETEIS;

typedef struct 
{
	int x;
	int y;
	int posicao;
	
}DADOS_DISPLAY;



// OPCOES
int run;
int musica_de_fundo;

// FUNCOES
// INICIALIZACAO
void inicializacao_addons();
void inicializacao_fontes();
void inicializacao_imagens();
void inicializacao_sprites();
void inicializacao_musica();
void inicializacao();
// AUXILIAR
void trans_inicial();
void fade();
void text_fade();

#endif
