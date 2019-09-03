/*
 * game_start.c
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

#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include "struct.h"
#include "application.h"
#include "draw.h"
#include "logic.h"

bool logic_game_start(int window_width, int window_height, app_t *app_struct)
{
    assert(app_struct);
    
    unsigned char *menu;

    menu = &(app_struct->menu);

    assert(menu);

    if(handler_key(ALLEGRO_KEY_ESCAPE)) {
        (*menu) = MENU_EXIT;
        return false;
    }
    
    /* if reset == true : fires, enemies and speed are reset */
    if ((app_struct->gameplay).reset) {
        reset_game(app_struct);
    }

    movimiento_spaceship(window_width, window_height, app_struct);
    generate_asteroid(window_width, window_height, app_struct);
    generate_enemy(window_width, window_height, app_struct);
    move_enemy(window_width, window_height, app_struct);
    
    if (handler_key(ALLEGRO_KEY_SPACE)) {
        generate_fire (app_struct);
    }
    
    move_fire(app_struct);
    
    /* checks if collisions or tolerance reached zero */
    if(collision_all (window_width, window_height, app_struct) || (app_struct->gameplay).tolerance <= 0) {
        (app_struct->player).life --;
        
        if((app_struct->player).life > 0) {
            (*menu) = MENU_GAME_RESTART;
        }
        
        else {
            (app_struct->player).flag = false;
            (*menu) = MENU_GAME_OVER;
        }
    }
    
    return true;
}

void reset_game    (app_t *app_struct)
{
    assert(app_struct);
    
    int i;
        
    for (i = 0; i < NUM_FIRE; i++) {
        (app_struct->disparo[i]).flag = false;
        (app_struct->disparo[i]).x = -1;
        (app_struct->disparo[i]).y = -1;
    }

    (app_struct->gameplay).tolerance = 100;
    
    /* if not above 3/4 default wave speed the set it to its default value */
    if ((app_struct->gameplay).velocidad < 1.2) {
        (app_struct->gameplay).velocidad =  0.80;
    }
    
    /* if above that value then: */
    else {
        (app_struct->gameplay).velocidad =  (3*((app_struct->gameplay).velocidad))/4;
    }
    
    (app_struct->gameplay).reset = false;
}

bool draw_game_start( int window_width, int window_height, app_t *app_struct)
{
    assert(app_struct);
    
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *background = app_struct->images[IMG_BACKGROUND];

    font = app_struct->fonts[FONT_START];

    assert(background);
    assert(font);
    
    int w = al_get_bitmap_width(background);
       int h = al_get_bitmap_height(background);
       int *score = &(app_struct->player).points; /* defaults to 0 */
       int *life = &(app_struct->player).life; /* defaults to 3 */
       int *tolerance = &(app_struct->gameplay).tolerance; /* defaults to 100 */
    
       al_draw_scaled_bitmap(background, 0, 0, w, h, 0, 0, window_width, window_height, 0);

    /* black bars on the sides */
    al_draw_filled_rectangle(0, 0, window_width/4, window_height, al_map_rgb(12,12,12));
    al_draw_filled_rectangle(window_width - window_width/4, 0, window_width, window_height, al_map_rgb(12,12,12));

    /* prints score and lives */
    al_draw_text(font, al_map_rgb(255, 215, 0), 
            (window_width/20)*16, al_get_font_line_height(font)*2, ALLEGRO_ALIGN_LEFT, "PLAYER INFO");
            
    al_draw_textf(font, al_map_rgb(255, 255, 255), 
            (window_width/20)*16, al_get_font_line_height(font)*6, ALLEGRO_ALIGN_LEFT, "SCORE: %d", *score);
            
    al_draw_textf(font, al_map_rgb(255, 255, 255),
            (window_width/20)*16, al_get_font_line_height(font)*8, ALLEGRO_ALIGN_LEFT, "LIVES: %d", *life);
            
    al_draw_textf(font, al_map_rgb(255, 255, 255),
            (window_width/20)*16, al_get_font_line_height(font)*10, ALLEGRO_ALIGN_LEFT, "TOLERANCE: %d", *tolerance);
            
    al_draw_text(font, al_map_rgb(255, 215, 0),
            (window_width/20)*4, al_get_font_line_height(font)*2, ALLEGRO_ALIGN_RIGHT, "INSTRUCTIONS    ");
            
    al_draw_text(font, al_map_rgb(255, 255, 255),
            (window_width/20)*4, al_get_font_line_height(font)*6, ALLEGRO_ALIGN_RIGHT, "Use the arrow keys");
            
    al_draw_text(font, al_map_rgb(255, 255, 255),
            (window_width/20)*4, al_get_font_line_height(font)*8, ALLEGRO_ALIGN_RIGHT, "to move and the   ");
            
    al_draw_text(font, al_map_rgb(255, 255, 255),
            (window_width/20)*4, al_get_font_line_height(font)*10, ALLEGRO_ALIGN_RIGHT, "SPACE BAR to shoot");
    
    /* spaceship */
    if(handler_key(ALLEGRO_KEY_LEFT)) {
        draw_spaceship(IMG_SPACESHIP_LEFT, app_struct);
    }

    else if(handler_key(ALLEGRO_KEY_RIGHT)) {
        draw_spaceship(IMG_SPACESHIP_RIGTH, app_struct);
    }

    else if(handler_key(ALLEGRO_KEY_UP)) {
        draw_spaceship(IMG_SPACESHIP_IDLE, app_struct);
    }    

    else if(handler_key(ALLEGRO_KEY_DOWN)) {
        draw_spaceship(IMG_SPACESHIP_IDLE, app_struct);
    }

    else {
        draw_spaceship(IMG_SPACESHIP_IDLE, app_struct);
    }

    draw_enemy(app_struct);
    draw_asteroids(app_struct);
    draw_fire(app_struct);
    
    return true;
}
