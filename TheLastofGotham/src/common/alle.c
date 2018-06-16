#include "alle.h"
#include <stdio.h>
#include <stdlib.h>

//-------INICIALIZACAO--------//

void inicializacao_addons() {
  if (!al_init()) {
    printf("Falha na inicializacao da Allegro! :(\n");
    exit(1);
  }

  al_init_font_addon();
  al_init_ttf_addon();
  al_init_image_addon();
  al_init_primitives_addon();
  al_install_keyboard();
  al_install_audio();
  al_init_acodec_addon();
  al_reserve_samples(5);
}
double getTimer()
{
    return al_get_time() - startingTime;
}

void FPSLimit()
{
    if (getTimer() < 1.0/FPS)
    {
        al_rest((1.0 / FPS) - getTimer());
    }
}


void readInput(ALLEGRO_EVENT event, char str[], int limit)
{
    if (event.type == ALLEGRO_EVENT_KEY_CHAR)
    {
        if (strlen(str) <= limit)
        {
            char temp[] = {event.keyboard.unichar, '\0'};
            if (event.keyboard.unichar == ' ')
            {
                strcat(str, temp);
            }
            else if (event.keyboard.unichar >= '!' &&
                     event.keyboard.unichar <= '?')
            {
                strcat(str, temp);
            }
            else if (event.keyboard.unichar >= 'A' &&
                     event.keyboard.unichar <= 'Z')
            {
                strcat(str, temp);
            }
            else if (event.keyboard.unichar >= 'a' &&
                     event.keyboard.unichar <= 'z')
            {
                strcat(str, temp);
            }
        }

        if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(str) != 0)
        {
            str[strlen(str) - 1] = '\0';
        }
    }
}

void inicializacao_fontes() {
  mad_24 = al_load_font("ext_files/fonts/8BitMadness.ttf", 24, 0);
  if (mad_24 == NULL) {
    printf("Falha na inicializacao da fonte 8BitMadness! :(\n");
    run = 0;
  }

  mad_30 = al_load_font("ext_files/fonts/8BitMadness.ttf", 30, 0);
  if (mad_30 == NULL) {
    printf("Falha na inicializacao da fonte 8BitMadness! :(\n");
    run = 0;
  }

  mad_64 = al_load_font("ext_files/fonts/8BitMadness.ttf", 64, 0);
  if (mad_64 == NULL) {
    printf("Falha na inicializacao da fonte 8BitMadness! :(\n");
    run = 0;
  }

  knight_72 = al_load_font("ext_files/fonts/darkknight.TTF", 72, 0);
  if (knight_72 == NULL) {
    printf("Falha na inicializacao da fonte Dark Knight! :(\n");
    run = 0;
  }
}

void inicializacao_imagens() {
  menu_bckg = al_load_bitmap("ext_files/imgs/menubckg.jpg");
  if (menu_bckg == NULL) {
    printf("Falha na inicializacao da imagem de Background do menu! :(\n");
    run = 0;
  }

  credits_bckg = al_load_bitmap("ext_files/imgs/creditsbckg.jpg");
  if (credits_bckg == NULL) {
    printf("Falha na inicializacao da imagem de Background dos creditos! :(\n");
    run = 0;
  }

  char_bckg = al_load_bitmap("ext_files/imgs/charselbckg.jpg");
  if (char_bckg == NULL) {
    printf("Falha na inicializacao da imagem de Background da selecao de personagem! :(\n");
    run = 0;
  }

  adjusts_bckg = al_load_bitmap("ext_files/imgs/adjustsbckg.jpg");
  if (adjusts_bckg == NULL) {
    printf("Falha na inicializacao da imagem de Background dos ajustes! :(\n");
    run = 0;
  }

  ip_bckg = al_load_bitmap("ext_files/imgs/ipbckg.jpg");
  if(ip_bckg == NULL){
    printf("Falha na inicializacao da imagem de Background da Conexao com o server! :(\n");
  }

  wait_bckg = al_load_bitmap("ext_files/imgs/late2.jpg");
  if (wait_bckg == NULL) {
    printf("Falha na inicializacao do icone da seta! :(\n");
    run = 0;
  }

  over_bckg = al_load_bitmap("ext_files/imgs/gameover.png");
  if(over_bckg == NULL){
    printf("Falha na inicializacao da imagem de Background do Game Over! :(\n");
    run = 0;
  }

  winner = al_load_bitmap("ext_files/imgs/waitbckg.jpg");
  if(winner == NULL){
    printf("Falha na inicializacao da imagem de Background do Vencedor! :(\n");
    run = 0;
  }

  heart = al_load_bitmap("ext_files/imgs/heart.png");
  if (heart == NULL) {
    printf("Falha na inicializacao do icone do corazon! :(\n");
    run = 0;
  }
  arrow = al_load_bitmap("ext_files/imgs/arrow.png");
  if (arrow == NULL) {
    printf("Falha na inicializacao do icone da seta! :(\n");
    run = 0;
  }
}

void inicializacao_sprites() {
  spr[0] = al_load_bitmap("ext_files/sprites/batm.png");
  if (spr[0] == NULL) {
    printf("Erro ao abrir o sprite do Batman :(\n");
    run = 0;
  }

  spr[1] = al_load_bitmap("ext_files/sprites/catw.png");
  if (spr[1] == NULL) {
    printf("Erro ao abrir o sprite da Mulher Gato :(\n");
    run = 0;
  }

  spr[2] = al_load_bitmap("ext_files/sprites/robi.png");
  if (spr[2] == NULL) {
    printf("Erro ao abrir o sprite do Robin :(\n");
    run = 0;
  }

  spr[3] = al_load_bitmap("ext_files/sprites/batw.png");
  if (spr[3] == NULL) {
    printf("Erro ao abrir o sprite da Batwoman :(\n");
    run = 0;
  }

  spr[4] = al_load_bitmap("ext_files/sprites/joke.png");
  if (spr[4] == NULL) {
    printf("Erro ao abrir o sprite do Coringa :(\n");
    run = 0;
  }

  spr[5] = al_load_bitmap("ext_files/sprites/harl.png");
  if (spr[5] == NULL) {
    printf("Erro ao abrir o sprite da Harlequina :(\n");
    run = 0;
  }

  spr[6] = al_load_bitmap("ext_files/sprites/bane.png");
  if (spr[6] == NULL) {
    printf("Erro ao abrir o sprite do Bane :(\n");
    run = 0;
  }

  spr[7] = al_load_bitmap("ext_files/sprites/peng.png");
  if (spr[7] == NULL) {
    printf("Erro ao abrir o sprite do Pinguim :(\n");
    run = 0;
  }
}

void inicializacao_map() {
  map = al_load_bitmap("ext_files/map/mapa.png");
  if (map == NULL) {
    printf("Erro ao abrir a imagem do Mapa! :(\n");
    run = 0;
  }

  corner = al_load_bitmap("ext_files/map/corners.png");
  if (corner == NULL) {
    printf("Erro ao abrir a imagem dos objetos! :(\n");
    run = 0;
  }

  walk_area = al_load_bitmap("ext_files/map/abletowalk.png");
  if (walk_area == NULL) {
    printf("Erro ao abrir a imagem de area caminhavel! :(\n");
    run = 0;
  }

  walkable = al_lock_bitmap(walk_area,al_get_bitmap_format(walk_area), ALLEGRO_LOCK_READONLY);
  if(walkable==NULL){
    printf("Erro ao declarar o bitmap de walkAble! :(\n");
    run = 0;
  }

}

void inicializacao_musica(){

  select_char = al_load_audio_stream("ext_files/musica/select_char.ogg", 4, 1024);
  if(select_char == NULL){
    printf("Erro ao encontrar o arquivo de musica da escolha de caracteres! :(\n");
    run = 0;
  }


  credito = al_load_audio_stream("ext_files/musica/creditos.ogg", 4, 1024);
  if(credito == NULL){
    printf("Erro ao encontrar o arquivo de musica dos creditos! :(\n");
    run = 0;
  }

  menu = al_load_audio_stream("ext_files/musica/menu.ogg", 4, 1024);
  if(menu == NULL){
    printf("Erro ao encontrar o arquivo de musica do menu! :(\n");
    run =0;
  }
}
void startTimer()
{
    startingTime = al_get_time();
}

void inicializacao() {
  inicializacao_addons();
  inicializacao_fontes();
  inicializacao_imagens();
  inicializacao_sprites();
  inicializacao_musica();
  inicializacao_map();

  janela = al_create_display(COMPRIMENTO, ALTURA);
  if (janela == NULL) {
    printf("Falha na inicializacao do display! :(\n");
    run = 0;
  }

  timer = al_create_timer(1.0 / FPS);
  if (timer == NULL) {
    printf("Falha na inicializacao do timer! :(\n");
    run = 0;
  }

  tick = al_create_event_queue();
  al_register_event_source(tick, al_get_timer_event_source(timer));
  al_register_event_source(tick, al_get_keyboard_event_source());
  al_register_event_source(tick, al_get_display_event_source(janela));

  if (tick == NULL) {
    printf("Falha na inicializacao do tick! :(\n");
    run = 0;
  }
}

//--------AUXILIARES---------//

void fade(int r, int g, int b, int rf, int gf, int bf, double delay,
          int passos) {
  int tr = (rf - r) / passos;
  int tg = (gf - g) / passos;
  int tb = (bf - b) / passos;

  int i;
  for (i = 0; i < passos; i++) {
    al_clear_to_color(al_map_rgb(r + tr * i, g + tg * i, b + tb * i));
    al_flip_display();
    al_rest(delay);
  }

  al_clear_to_color(al_map_rgb(rf, gf, bf));
  al_flip_display();
  al_rest(delay);
}

void text_fade(int r, int g, int b, int rf, int gf, int bf, double delay,
               int passos, ALLEGRO_FONT* fonte, char* texto, int distx,
               int disty) {
  int tr = (rf - r) / passos;
  int tg = (gf - g) / passos;
  int tb = (bf - b) / passos;

  int i;
  for (i = 0; i < passos; i++) {
    al_draw_text(fonte, al_map_rgb(r + tr * i, g + tg * i, b + tb * i), distx,
                 disty, ALLEGRO_ALIGN_CENTER, texto);
    al_flip_display();
    al_rest(delay);
  }

  al_draw_text(fonte, al_map_rgb(rf, gf, bf), distx, disty,
               ALLEGRO_ALIGN_CENTER, texto);
  al_flip_display();
  al_rest(delay);
}

void trans_inicial() {
  al_init_primitives_addon();
  al_install_keyboard();
  al_install_audio();
  al_init_acodec_addon();

  sample = al_load_sample("ext_files/sounds/thunder.ogg");
  al_reserve_samples(2);
  al_clear_to_color(WHITE);
  al_draw_text(knight_72, BLACK, COMPRIMENTO / 2, -36 + ALTURA / 2,
               ALLEGRO_ALIGN_CENTER, "1");
  al_flip_display();
  al_rest(3.0);
  int i;
  for (i = 0; i <= 85; i++) {
    al_clear_to_color(al_map_rgb(255 - 3 * i, 255 - 3 * i, 255 - 3 * i));
    al_draw_text(knight_72, BLACK, COMPRIMENTO / 2, -36 + ALTURA / 2,
                 ALLEGRO_ALIGN_CENTER, "1");
    al_flip_display();
    
    al_rest(0.03);
  }
  al_play_sample(sample, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
  al_rest(3);
  
  text_fade(0, 0, 0, 110, 110, 110, 0.03, 55, mad_24, "Ambrozitos apresenta",
            COMPRIMENTO / 2, 90);
  al_rest(1.0);
  al_play_sample(sample, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

  text_fade(0, 0, 0, 110, 110, 110, 0.05, 110, mad_64, "The Last of Gotham",
            COMPRIMENTO / 2, ALTURA / 2);
  al_rest(3.0);
  text_fade(110, 110, 110, 0, 0, 0, 0.03, 55, mad_24, "Ambrozitos apresenta",
            COMPRIMENTO / 2, 90);
  al_rest(1.0);
  text_fade(110, 110, 110, 0, 0, 0, 0.015, 110, mad_64, "The Last of Gotham",
            COMPRIMENTO / 2, ALTURA / 2);
  al_rest(2.5);
  al_destroy_sample(sample);
}
