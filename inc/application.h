/*
 * application.h
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

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <allegro5/allegro.h>
#include "struct.h"

void app_init(app_t *app_struct);

void app_start(int window_width, int window_height, void *arg);
void app_restart(int window_width, int window_height, void *arg);
bool app_logic(int window_width, int window_height, void *arg);
void app_draw(int window_width, int window_height, void *arg);

void set_gameplay_to_default(int window_width, int window_height, void *arg);

void app_exit(app_t *app_struct);

#endif // APPLICATION_H_
