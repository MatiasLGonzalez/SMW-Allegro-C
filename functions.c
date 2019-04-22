#pragma once
#include"header.h"


void get_desktop_resolution(int adapter, int* w, int* h)//Gets width and Height of actual monitor
{
	ALLEGRO_MONITOR_INFO info;
	al_get_monitor_info(adapter, &info);

	*w = info.x2 - info.x1;
	*h = info.y2 - info.y1;
}

void start_mario(Mario* mario, int x, int y, int lives, int mode, ALLEGRO_BITMAP *mario_sprite, int w, int h)
{
	mario->pos_x = x;
	mario->pos_y = y;
	mario->lives = lives;
	mario->speed = 37/30;
	mario->width = al_get_bitmap_width(mario_sprite);
	mario->height = al_get_bitmap_width(mario_sprite);
	mario->sprite = mario_sprite;
	mario->vy = 0;
	mario->ay = 0;
}

void drawMario(Mario* mario)
{
	al_draw_bitmap(mario->sprite, mario->pos_x, mario->pos_y , ALLEGRO_FLIP_HORIZONTAL);
}

int minimo(int sx,int sy)
{
	if (sx > sy)
		return sy;
	else
		return sx;
}

void move_mario(Mario* mario, bool* keys, camera* Camera)
{
	bool jump = false;
	if (keys[LEFT])
	{
		if (mario->pos_x > 120 - 7)
			mario->pos_x -= mario->speed;
		else
		{
			if (Camera->x > 0)
			{
				Camera->x -= mario->speed;
				if (Camera->x < 0)
					Camera->x = 0;
			}
			else if (mario->pos_x > 10)
			{
				mario->pos_x -= mario->speed;
				if (mario->pos_x < 10)
					mario->pos_x = 10;
			}
		}
	}
	else if (keys[RIGHT])
	{
		if (mario->bound_x + mario->pos_x < 136 + 7)
			mario->pos_x += mario->speed;
		else
			if (Camera->x < 4864)
			{
				Camera->x += mario->speed;
				if (Camera->x > 4864)
					Camera->x = 4864;
			}
			else if (mario->pos_x < 256 -14 - 10)
			{
				mario->pos_x += mario->speed;
				if (mario->pos_x > 256 - 14 - 10)
					mario->pos_x = 256 - 14 - 10;
			}
	}
	//4864
	//else if (keys[UP])
	//{
	//	
	//}
	//else if (keys[DOWN] && mario->pos_y < 224)
	//{
	//	mario->pos_y += 10;
	//}

	//system("cls");
	//printf("%lf %lf\n",mario->vy, mario->ay);
	if (mario->vy != 0 || mario->pos_y != 191-20)
	{
		mario->pos_y = mario->pos_y - mario->vy;
		mario->vy = mario->vy - mario->ay;
		if (mario->pos_y > 191 - 20)
		{
			mario->pos_y = 191 - 20;
			mario->vy = 0;
		}
	}
}


void drawBackground(camera Camera, ALLEGRO_BITMAP* level, ALLEGRO_BITMAP* background)
{
	al_draw_bitmap(background, 0, 0, 0);
	al_draw_bitmap_region(level, Camera.x, Camera.y, 256, 224, 0, 0, 0);
}