/*
 * insert_name.c
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
#include <stdio.h>
#include "struct.h"
#include "application.h"
#include "save_score.h"

bool logic_insert_name(int window_width, int window_height, app_t *app_struct)
{
    unsigned char *menu;
    
    assert(app_struct);

    menu = &(app_struct->menu);

    assert(menu);

    /* flag variable avoids multiple score saving */
    if(handler_key(ALLEGRO_KEY_ENTER) && (app_struct->player).flag == false) {
        (app_struct->player).flag = true;
        (app_struct->gameplay).status = save_score(&(app_struct->player), app_struct);
    }     
    
    else if (handler_key(ALLEGRO_KEY_TAB)) {
        app_start(window_width, window_height, app_struct);
        (app_struct->gameplay).reset = true;
        (*menu) = MENU_GAME_START;
    }
    
    if(handler_key(ALLEGRO_KEY_ESCAPE)) {
        (*menu) = MENU_EXIT;
        return false;
    }
    
    return true;
}

bool draw_insert_name(int window_width, int window_height, app_t *app_struct)
{
    assert(app_struct);
    ALLEGRO_FONT *font  = app_struct->fonts[FONT_START];
    
    assert(font);

    al_clear_to_color(al_map_rgb(12,12,12));

    al_draw_text(font, al_map_rgb(255, 215, 0),
    window_width/2, window_height/2 - al_get_font_line_height(font) * 5,
    ALLEGRO_ALIGN_CENTER, "PLEASE ENTER YOUR NAME AND FINISH BY PRESSING ENTER:");
    
    al_draw_text(font, al_map_rgb(255, 255, 255),
    window_width/2, window_height/2 - al_get_font_line_height(font) * 3,
    ALLEGRO_ALIGN_CENTER, (app_struct->player).name);
    
    if ((app_struct->gameplay).status == -1) {
        al_clear_to_color(al_map_rgb(12,12,12));

        al_draw_text(font, al_map_rgb(255, 0, 0),
                    window_width/2, window_height/2 - al_get_font_line_height(font) * 5,
                    ALLEGRO_ALIGN_CENTER, "Failed to save the score!");
                
        al_draw_text(font, al_map_rgb(255, 255, 255),
                    window_width/2, window_height/2 - al_get_font_line_height(font) * 3,
                    ALLEGRO_ALIGN_CENTER, "Press TAB to start a new game");
                
        al_draw_text(font, al_map_rgb(255, 255, 255),
                    window_width/2, window_height/2 - al_get_font_line_height(font),
                    ALLEGRO_ALIGN_CENTER, "Press ESCAPE to exit");
    }
    
    else if ((app_struct->gameplay).status == 0) {        
        al_clear_to_color(al_map_rgb(12,12,12));

        al_draw_text(font, al_map_rgb(255, 215, 0), 
                    window_width/2, window_height/3 - al_get_font_line_height(font)*3,  
                    ALLEGRO_ALIGN_CENTER, "Your score has been saved!");
        
        al_draw_textf(font, al_map_rgb(255, 255, 255),
                    window_width/2, window_height/3 - al_get_font_line_height(font),
                    ALLEGRO_ALIGN_CENTER ,"Your score: %s -> %d", (app_struct->player).last_play.top_name,
                    (app_struct->player).last_play.top_points);
            
        /* top 5 */
        for (int i = 0; i < PODIO; i++) {
            al_draw_textf(font, al_map_rgb(6, 188, 249), 
                        window_width/2, (window_height/3) + al_get_font_line_height(font)*(i+2), 
                        ALLEGRO_ALIGN_CENTER, "Top %d: %s -> %d", (i+1), (app_struct->best[i]).top_name,
                        (app_struct->best[i]).top_points);
        }
        
        al_draw_text(font, al_map_rgb(255, 255, 255), 
                    window_width/2, window_height/2 + al_get_font_line_height(font)*3,  
                    ALLEGRO_ALIGN_CENTER, "Press TAB to start a new game");

        al_draw_text(font, al_map_rgb(255, 255, 255), 
                    window_width/2, window_height/2 + al_get_font_line_height(font)*5, 
                    ALLEGRO_ALIGN_CENTER, "Press ESCAPE to exit");
    }
    
    return true;
}
