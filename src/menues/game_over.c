/*
 * game_over.c
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

#include <allegro5/allegro.h>
#include "struct.h"
#include "application.h"

bool logic_game_over(int window_width, int window_height, app_t *app_struct)
{
    assert(app_struct);

    unsigned char *menu;
    
    assert(app_struct);

    menu = &(app_struct->menu);

    assert(menu);

    al_stop_samples();
     
    if(handler_key(ALLEGRO_KEY_TAB)) {
        app_start(window_width, window_height, app_struct);
        (app_struct->gameplay).reset = true;
        (*menu) = MENU_GAME_START;
    }
    
    if(handler_key(ALLEGRO_KEY_ESCAPE)) {
        (*menu) = MENU_EXIT;
    }
    
    /* prints name */
    if (handler_key(ALLEGRO_KEY_S)) {
        strcpy((app_struct->player).name, "");
        set_string_source((app_struct->player).name, MAX_NAME_LEN);
        
        (*menu) = MENU_INSERT_NAME;
    }
    
    return true;
}

bool draw_game_over( int window_width, int window_height, app_t *app_struct)
{
    assert(app_struct);
    
    int *score = &(app_struct->player).points;

    ALLEGRO_FONT *font  = app_struct->fonts[FONT_START];
        
    assert(font);

    al_clear_to_color(al_map_rgb(12,12,12));

    al_draw_text(font, al_map_rgb(255, 0, 0), 
                 window_width/2, window_height/3 - al_get_font_line_height(font)*3,  
                 ALLEGRO_ALIGN_CENTER, "GAME OVER!");
                 
    al_draw_textf(font, al_map_rgb(255, 215, 0), 
                 window_width/2, window_height/3 - al_get_font_line_height(font),  
                 ALLEGRO_ALIGN_CENTER, "Your SCORE: %d", *score);
                 
    al_draw_text(font, al_map_rgb(255, 255, 255), 
                 window_width/2, window_height/2 + al_get_font_line_height(font), 
                 ALLEGRO_ALIGN_CENTER, "Press S to save your score");
                 
    al_draw_text(font, al_map_rgb(255, 255, 255), 
                 window_width/2, window_height/2 + al_get_font_line_height(font)*3,  
                 ALLEGRO_ALIGN_CENTER, "Press TAB to start a new game");

    al_draw_text(font, al_map_rgb(255, 255, 255), 
                 window_width/2, window_height/2 + al_get_font_line_height(font)*5, 
                 ALLEGRO_ALIGN_CENTER, "Press ESCAPE to exit");
    
    return true;
}
