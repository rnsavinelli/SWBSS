/*
 * struct.h
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

#ifndef STRUCT_H_
#define STRUCT_H_

#include "al_handler.h"

#define NUM_ASTEROIDS 4
#define NUM_FIRE 20
#define NUM_ENEMIES	14
#define NUM_FILAS 5
#define DEFAULT_SPEED 0.80
#define FIRE_SPEED -13

#define MAX_NAME_LEN 20
#define PODIO 5

enum APP_FONTS {
    FONT_START,
    MAX_FONTS
};

enum APP_IMAGES {
    IMG_BACKGROUND,
    IMG_SPACESHIP,
	IMG_ENEMY,
    IMG_ASTEROID,
    MAX_IMAGES
};

enum APP_SUBIMAGES_SPACESHIP {
    IMG_SPACESHIP_LEFT,
    IMG_SPACESHIP_RIGTH,
    IMG_SPACESHIP_IDLE,
    IMG_SPACESHIP_MAX
};

enum APP_SOUNDS {
    SND_MUSIC,
    MAX_SOUNDS
};

enum APP_MENU {
    MENU_INSERT_NAME,
    MENU_MAIN_MENU,
    MENU_GAME_START,
    MENU_GAME_RESTART,
    MENU_GAME_OVER,
    MENU_EXIT,
    MENU_MAX
};

typedef struct leaderboard {
    char top_name[MAX_NAME_LEN];
    int top_points;
} top_t;

typedef struct score {
    char name[MAX_NAME_LEN];
    int points;
    int life;
    bool flag;
    top_t last_play;
} score_t;

typedef struct fires {
    float x;
    float y;
	bool flag;
} fires_t;

typedef struct enemy {
	float x;
	float y;
	bool flag;
} enemy_t;

typedef struct asteroid {
	float x;
	float y;
} asteroid_t;

typedef struct spaceship_coordinates {
	float x;
	float y;
} coordinates_t;

typedef struct gameplay_variables {
    float time;
	int status;
	int tolerance;
    bool reset; /* if true enemies and fire get reseted */
    float velocidad;
} gameplay_t;

typedef struct app {
    ALLEGRO_FONT * fonts[MAX_FONTS];
    ALLEGRO_BITMAP * images[MAX_IMAGES];
    ALLEGRO_SAMPLE * sounds[MAX_SOUNDS];
	
    unsigned char menu;

    gameplay_t gameplay;
	coordinates_t spaceship;
	asteroid_t asteroide[NUM_ASTEROIDS];
    enemy_t enemigo[NUM_ENEMIES * NUM_FILAS];
    score_t player;
    top_t best[PODIO];
    fires_t disparo[NUM_FIRE];

} app_t;

void struct_init(app_t *app_struct);
void struct_delete(app_t *app_struct);

#endif // STRUCT_H_




