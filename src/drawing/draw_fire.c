/*
 * draw_fire.c
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

void draw_fire(app_t *app_struct)
{	
	assert(app_struct);
	
	ALLEGRO_BITMAP *spaceship_img = app_struct->images[IMG_SPACESHIP];

	assert(spaceship_img);

	int spaceship_h = al_get_bitmap_height(spaceship_img);

	for(int i = 0; i < NUM_FIRE; i++) {
		if ((app_struct->disparo[i]).flag) {
			al_draw_filled_circle( (app_struct->disparo[i]).x + 1, (app_struct->disparo[i]).y - spaceship_h/2, 3, al_map_rgb(6, 188, 249));
		}
	}
}

