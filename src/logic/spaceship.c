/*
 * spaceship.c
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

void movimiento_spaceship(int window_width, int window_height, app_t *app_struct)
{
    assert(app_struct);
    assert(spaceship);
    
    float desplazamiento = 5;
    float *x = &(app_struct->spaceship).x;
    float *y = &(app_struct->spaceship).y;

    ALLEGRO_BITMAP *spaceship_img = app_struct->images[IMG_SPACESHIP];
    
    assert(spaceship_img);

    int spaceship_w = al_get_bitmap_width(spaceship_img)/IMG_SPACESHIP_MAX;
    int spaceship_h = al_get_bitmap_height(spaceship_img);

    /* Spaceship movements */
    if(handler_key(ALLEGRO_KEY_LEFT)) {
        (*x) -= desplazamiento;
    }
    
    if(handler_key(ALLEGRO_KEY_RIGHT)) {
        (*x) += desplazamiento;
    }
    
    if(handler_key(ALLEGRO_KEY_UP)) {
        (*y) -= desplazamiento;
    }

    if(handler_key(ALLEGRO_KEY_DOWN)) {
        (*y) += desplazamiento/2;
    }

    /* Limits */
    if( (*x) > window_width - spaceship_w/2 - window_width/4) {
        (*x) = window_width - spaceship_w/2 - window_width/4;
    }
    
    else if( (*x) < spaceship_w/2 + window_width/4) {
        (*x) = spaceship_w/2 + window_width/4;
    }
    
    if( (*y) > window_height - spaceship_h/2) {
        (*y) = window_height - spaceship_h/2;
    }
    
    else if( (*y) < spaceship_h/2) {
        (*y) = spaceship_h/2;
    }
}
