/*
 * draw_spaceship.c
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

void draw_spaceship(unsigned char sector, app_t *app_struct)
{
    assert(app_struct);

    ALLEGRO_BITMAP *spaceship_img = app_struct->images[IMG_SPACESHIP];

    assert(spaceship_img);

    float x = (app_struct->spaceship).x;
    float y = (app_struct->spaceship).y;

    int spaceship_w = al_get_bitmap_width(spaceship_img)/3;
    int spaceship_h = al_get_bitmap_height(spaceship_img);

    switch(sector)
    {
        case IMG_SPACESHIP_IDLE:
	    al_draw_bitmap_region(spaceship_img, 0, 0, spaceship_w, spaceship_h, x - spaceship_w/2, y - spaceship_h/2, 0);
            break;

        case IMG_SPACESHIP_LEFT:
            al_draw_bitmap_region(spaceship_img, spaceship_w, 0, spaceship_w, spaceship_h, x - spaceship_w/2, y - spaceship_h/2, 0);
            break;

        case IMG_SPACESHIP_RIGTH:
            al_draw_bitmap_region(spaceship_img, spaceship_w*2, 0, spaceship_w, spaceship_h, x - spaceship_w/2, y - spaceship_h/2, 0);
            break;
    }
}
