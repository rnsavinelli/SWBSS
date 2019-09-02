/*
 * collision.c
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
#include "logic.h"

bool collision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	/* no collision */
	if ( (x1 > x2 + w2 - 1) || (y1 > y2 + h2 - 1) || (x2 > x1 + w1 - 1) || (y2 > y1 + h1 - 1) ) {
        return false;
    }
    
    /* collision */
	return true;
}

bool collision_all(int window_width, int window_height, app_t *app_struct)
{
	assert(spaceship);
	
 	bool ret_value = false;

    float x, y;
    int asteroid_x, asteroid_y;
    int enemy_x, enemy_y;
    int fire_x, fire_y;
    int i, j, k;

	assert(app_struct);

    x = (app_struct->spaceship).x;
    y = (app_struct->spaceship).y;

    ALLEGRO_BITMAP *spaceship_img = app_struct->images[IMG_SPACESHIP];
	ALLEGRO_BITMAP *asteroid = app_struct->images[IMG_ASTEROID];
    ALLEGRO_BITMAP *enemy = app_struct->images[IMG_ENEMY];

	assert(spaceship_img);
	assert(asteroid);
	assert(enemy);

    int spaceship_w = al_get_bitmap_width(spaceship_img)/IMG_SPACESHIP_MAX;
    int spaceship_h = al_get_bitmap_height(spaceship_img);

    int asteroid_w = al_get_bitmap_width(asteroid);
    int asteroid_h = al_get_bitmap_height(asteroid);
    
    int enemy_w = al_get_bitmap_width(enemy);
    int enemy_h = al_get_bitmap_height(enemy);

    for(i = 0; i < NUM_ASTEROIDS; i++) {
        asteroid_x = (app_struct->asteroide[i]).x;
        asteroid_y = (app_struct->asteroide[i]).y;

        if( collision(x - spaceship_w/2, y - spaceship_h/2, spaceship_w, 
       	    spaceship_h, asteroid_x - asteroid_w/2, asteroid_y - asteroid_h/2, 
       	    asteroid_w,  asteroid_h) ) {
			for(int i = 0; i < NUM_FIRE; i++) {
			    (app_struct->disparo[i]).flag = false;
			}
			
            ret_value = true;
        }        
    }

    for(j = 0; j < NUM_FILAS; j++) {
		for(i = 0; i < NUM_ENEMIES; i++) {
			enemy_x = (app_struct->enemigo[(NUM_ENEMIES * j) + i]).x;
			enemy_y = (app_struct->enemigo[(NUM_ENEMIES * j) + i]).y;

			if(collision(x - spaceship_w/2, y - spaceship_h/2, spaceship_w, spaceship_h, enemy_x - enemy_w/2, enemy_y - enemy_h/2, enemy_w, enemy_h) ) {
				for(int i = 0; i < NUM_FIRE; i++) {
					(app_struct->disparo[i]).flag = false;
				}
				
				ret_value = true;
			}
			
			for(k = 0; k < NUM_FIRE; k++) {
				fire_y = (app_struct->disparo[k]).y;
				fire_x = (app_struct->disparo[k]).x;
				
				if(collision(enemy_x - enemy_w/2, enemy_y - enemy_h/2, enemy_w, enemy_h, fire_x - 1, fire_y - 1, 2, 2) ) {
					(app_struct->disparo[k]).flag = false;
					(app_struct->disparo[k]).x = window_width;
					(app_struct->disparo[k]).y = 0;
					(app_struct->enemigo[(NUM_ENEMIES * j) + i]).flag = false;
					(app_struct->enemigo[(NUM_ENEMIES * j) + i]).x = window_width + (2 * enemy_w);
					(app_struct->player).points += 5;
				}				
			}
		}
	}
    
    return ret_value;
}
