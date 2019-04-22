#pragma once
#include"objects.h"
#include<stdio.h>
#include<stdlib.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_primitives.h>

void get_desktop_resolution(int adapter, int* w, int* h);//Gets width and Height of actual monitor

void start_mario(Mario *mario, int x, int y, int lives, int mode, ALLEGRO_BITMAP* mario_sprite, int w, int h);
void drawMario(Mario *mario);
void move_mario(Mario* mario, bool* keys, camera* Camera);
void drawBackground(camera Camera, ALLEGRO_BITMAP* level, ALLEGRO_BITMAP* background);



//Credits to Matthew Leverton for "get_desktop_resolution()" at https://www.allegro.cc/forums/thread/605953/897067#target
//Credits to "David" from https://www.dafont.com/david-fens.d5063 for fonts https://www.dafont.com/super-mario-world.font