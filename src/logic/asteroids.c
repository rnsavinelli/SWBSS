/*
 * asteroids.c
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

void generate_asteroid(int window_width, int window_height, app_t *app_struct)
{
    assert(app_struct);

    ALLEGRO_BITMAP *asteroid = app_struct->images[IMG_ASTEROID];

    assert(asteroid);
    
    float desplazamiento = 2;
    int i;

    int asteroid_w = al_get_bitmap_width(asteroid);
    int asteroid_h = al_get_bitmap_height(asteroid);

    for(i = 0; i < NUM_ASTEROIDS; i++) {
        (app_struct->asteroide[i]).y += desplazamiento;

        if( (app_struct->asteroide[i]).y > window_height + asteroid_w) {
            (app_struct->asteroide[i]).x = rand() % (window_width/2 - asteroid_w) + (window_width/4) + asteroid_w/2;
            (app_struct->asteroide[i]).y = - asteroid_h;
        }
    }
}
