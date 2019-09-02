/*
 * game_restart.c
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

bool logic_game_restart(int window_width, int window_height, app_t *app_struct)
{
	assert(app_struct);
	
    unsigned char *menu;
    
    al_stop_samples();
    menu = &(app_struct->menu);
    
	assert(menu);
   
    if(handler_key(ALLEGRO_KEY_ENTER)) {
	    app_restart(window_width, window_height, app_struct);
	    (app_struct->gameplay).reset = true;
        (*menu) = MENU_GAME_START;
    }
    
    	return true;
}

bool draw_game_restart(int window_width, int window_height, app_t *app_struct)
{
    ALLEGRO_FONT *font;

	assert(app_struct);

    font = app_struct->fonts[FONT_START];

	assert(font);
	
	al_clear_to_color(al_map_rgb(12,12,12));

    al_draw_text(font, al_map_rgb(255, 0, 0), 
                 window_width/2, window_height/3 - al_get_font_line_height(font),  
                 ALLEGRO_ALIGN_CENTER, "YOU DIED!");
                 
    al_draw_textf(font, al_map_rgb(255, 255, 255), 
                 window_width/2, window_height/2 - al_get_font_line_height(font)*3,
                 ALLEGRO_ALIGN_CENTER, "SCORE: %d", (app_struct->player).points);
                 
    al_draw_textf(font, al_map_rgb(255, 255, 255), 
                 window_width/2, window_height/2 - al_get_font_line_height(font),
                 ALLEGRO_ALIGN_CENTER, "LIVES: %d", (app_struct->player).life);
        	         
    al_draw_text(font, al_map_rgb(215, 215, 215), 
                 window_width/2, (window_height/3)*2 - al_get_font_line_height(font), 
                 ALLEGRO_ALIGN_CENTER, "Press ENTER when you are ready");

    return true;
}
