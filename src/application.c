/*
 * application.c
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
#include <stdlib.h>
#include <time.h>

#include "al_handler.h"

#include "application.h"
#include "menues/main_menu.h"
#include "menues/game_start.h"
#include "menues/game_restart.h"
#include "menues/game_over.h"
#include "menues/insert_name.h"

void app_init(app_t *app_struct)
{
    ALLEGRO_FONT    * font          = NULL;
    ALLEGRO_BITMAP  * background    = NULL,
                    * spaceship     = NULL,
                    * asteroid      = NULL,
                    * enemy         = NULL;
    ALLEGRO_SAMPLE  * music         = NULL;

    assert(app_struct);
    
    struct_init(app_struct);

    // loads fonts
    font = al_load_ttf_font("./fonts/LiberationSans-Bold.ttf", 20, 0);
    
    assert(font);

    // loads images
    background  = load_img("./images/background.bmp");
    spaceship   = load_img("./images/spaceship.bmp");
    asteroid    = load_img("./images/asteroid.bmp");
    enemy       = load_img("./images/enemy.bmp");
    
    assert(background);
    assert(spaceship_img);
    assert(asteroid);
    assert(enemy);
    
    // loads music
    music = load_sound("./sounds/Visager_Battle_Loop.wav", 1);
    
    assert(music);
    
    // saves loaded data to app_srtuct
    app_struct->fonts[FONT_START]           = font;
    app_struct->images[IMG_BACKGROUND]      = background;
    app_struct->images[IMG_SPACESHIP]       = spaceship;
    app_struct->images[IMG_ASTEROID]        = asteroid;
    app_struct->images[IMG_ENEMY]           = enemy;
    
    app_struct->sounds[SND_MUSIC] = music;

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_flip_display();
}

void app_start(int window_width, int window_height, void * arg)
{
    app_t *app_struct = (app_t *) arg;

    assert(app_struct);
    assert(menu);

    /* Sets main variables to their respective default */
    (app_struct->gameplay).time = 0;
    (app_struct->player).flag = false;
    (app_struct->player).points = 0;
    (app_struct->player).life = 3;
    (app_struct->gameplay).velocidad = DEFAULT_SPEED;
    (app_struct->gameplay).reset = true;
    (app_struct->gameplay).status = 1;

    /* instantiates clean best scores vector */
    for(int i = 0; i <= PODIO; i ++) {
        strcpy((app_struct->best[i]).top_name, "");
        (app_struct->best[i]).top_points = 0;
    }

    set_gameplay_to_default(window_width, window_height, arg);
    app_struct->menu = MENU_MAIN_MENU;

    play_sound(app_struct->sounds[SND_MUSIC], ALLEGRO_PLAYMODE_LOOP);
}

void app_restart(int window_width, int window_height, void * arg)
{
    app_t *app_struct = (app_t *) arg;

    assert(app_struct);
    assert(menu);

    set_gameplay_to_default(window_width, window_height, arg);
    (app_struct->gameplay).time = 0;
    app_struct->menu = MENU_MAIN_MENU;

    play_sound(app_struct->sounds[SND_MUSIC], ALLEGRO_PLAYMODE_LOOP);
}

void set_gameplay_to_default(int window_width, int window_height, void * arg)
{
    app_t *app_struct = (app_t *) arg;

    assert(app_struct);

    srand(time(NULL));

    ALLEGRO_BITMAP *asteroid = app_struct->images[IMG_ASTEROID];

    assert(asteroid);
    
    int asteroid_w = al_get_bitmap_width(asteroid);

    int i, j;
    
    /* all enemies to false */
    for(j = 0; j < NUM_FILAS; j++) {
        for(i = 0; i < NUM_ENEMIES; i++) {
            (app_struct->enemigo[(NUM_ENEMIES * j) + i]).flag = false;
        }
    }
    
    for(i = 0; i < NUM_ASTEROIDS; i++) {
        (app_struct->asteroide[i]).x = rand()%(window_width/2 - asteroid_w) + (window_width/4) + asteroid_w/2;
        (app_struct->asteroide[i]).y = -(((i+1)*window_height)/NUM_ASTEROIDS);
    }
    
    /* all fire to false */
    for (i = 0; i < NUM_FIRE; i++) {
        (app_struct->disparo[i]).flag = false;
    }

    (app_struct->spaceship).x = window_width/2;
    (app_struct->spaceship).y = window_height;
}

bool app_logic(int window_width, int window_height, void * arg)
{
    app_t *app_struct = (app_t *) arg;
    bool keep_looping = true;

    assert(app_struct);

    (app_struct->gameplay).time += 1000.0/FPS;

    unsigned char *menu = &(app_struct->menu);

    assert(menu);

    switch(*menu) {
        case MENU_MAIN_MENU:
            keep_looping = logic_main_menu(window_width, window_height, app_struct);
            break;

        case MENU_GAME_START:
            keep_looping = logic_game_start(window_width, window_height, app_struct);
            break;
        
        case MENU_GAME_RESTART:
            keep_looping = logic_game_restart(window_width, window_height, app_struct);
            break;

        case MENU_GAME_OVER:
            keep_looping = logic_game_over(window_width, window_height, app_struct);
            break;
            
        case MENU_INSERT_NAME:
            keep_looping = logic_insert_name(window_width,window_height,app_struct);
            break;
        
        case MENU_EXIT:
            keep_looping = false;
            break;
    }

    return keep_looping;
}

void app_draw(int window_width, int window_height, void * arg)
{          
    app_t *app_struct = (app_t *) arg;

    assert(app_struct);

    unsigned char *menu = &(app_struct->menu);
    
    assert(menu);

    switch(*menu) {
        case MENU_MAIN_MENU:
            draw_main_menu(window_width, window_height, app_struct);
            break;
            
        case MENU_GAME_START:
            draw_game_start(window_width, window_height, app_struct);
            break;
            
        case MENU_GAME_RESTART:
            draw_game_restart(window_width, window_height, app_struct);
            break;
            
        case MENU_GAME_OVER:
            draw_game_over(window_width, window_height, app_struct);
            break;
            
        case MENU_INSERT_NAME:
            draw_insert_name(window_width, window_height, app_struct);
            break;
    }
}

void app_exit(app_t *app_struct)
{
    assert(app_struct);

    struct_delete(app_struct);
}

