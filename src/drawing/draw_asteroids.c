/*
 * draw_asteroids.c
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

void draw_asteroids(app_t *app_struct)
{
    assert(app_struct);

    ALLEGRO_BITMAP *asteroid = app_struct->images[IMG_ASTEROID];

    assert(asteroid);

    int asteroid_x;
    int asteroid_y;

    int asteroid_w = al_get_bitmap_width(asteroid);
    int asteroid_h = al_get_bitmap_height(asteroid);


    for(int i = 0; i < NUM_ASTEROIDS; i++) {
        asteroid_x = (app_struct->asteroide[i]).x;
        asteroid_y = (app_struct->asteroide[i]).y;
        
        al_draw_bitmap_region(  asteroid, 0, 0, asteroid_w, asteroid_h, asteroid_x - asteroid_w/2, asteroid_y - asteroid_h/2, 0);
    }
}
