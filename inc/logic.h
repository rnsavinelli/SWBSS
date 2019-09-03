/*
 * logic.h
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

#ifndef LOGIC_H_
#define LOGIC_H_

#include <allegro5/allegro.h>
#include "struct.h"

bool collision (float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
bool collision_all (int window_width, int window_height, app_t *app_struct);

void movimiento_spaceship (int window_width, int window_height, app_t *app_struct);
void generate_asteroid (int window_width, int window_height, app_t *app_struct);
void generate_enemy    (int window_width, int window_height, app_t *app_struct);
void move_enemy    (int window_width, int window_height, app_t *app_struct);
void generate_fire (app_t *app_struct);
void move_fire (app_t *app_struct);
void reset_game (app_t *app_struct);

#endif // LOGIC_H_
