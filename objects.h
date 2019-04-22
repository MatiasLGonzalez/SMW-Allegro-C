#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_image.h>

enum KEYS { UP, DOWN, LEFT, RIGHT };

typedef struct {
	ALLEGRO_BITMAP *sprite;
	int lives;
	int speed;
	int width;//Width of Mario in pixels
	int height;//Height of Mario in pixels
	float pos_x;
	float pos_y;
	int bound_x;
	int bound_y;
	float vy;
	float ay;


	int mode;
}Mario;

typedef struct {
	int x;
	int y;
}camera;
