/*
 * draw_enemies.c
 * 
 * Copyright 2019 Roberto Nicolás Savinelli <rnsavinelli@est.frba.utn.edu.ar>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

#include <stdio.h>
#include <allegro5/allegro.h>
#include "draw.h"

void draw_enemy(app_t *app_struct)
{
    assert(app_struct);

    ALLEGRO_BITMAP *enemy = app_struct->images[IMG_ENEMY];

    assert(enemy);

    int enemy_x;
    int enemy_y;
    
    int enemy_w = al_get_bitmap_width(enemy);
    int enemy_h = al_get_bitmap_height(enemy);

	for(int j = 0; j < NUM_FILAS; j++) {
		for(int i = 0; i < NUM_ENEMIES; i++) {
			if((app_struct->enemigo[(NUM_ENEMIES * j) + i]).flag) {
				enemy_x = app_struct->enemigo[(NUM_ENEMIES * j) + i].x;
				enemy_y = app_struct->enemigo[(NUM_ENEMIES * j) + i].y;
			
				al_draw_bitmap_region(  enemy, 0, 0, enemy_w, enemy_h, enemy_x - enemy_w/2, enemy_y - enemy_h/2, 0);
			}
		}
	}
}
