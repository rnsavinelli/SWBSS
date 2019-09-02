/*
 * al_handler_priv.h
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

#ifndef ALLEGRO_HANDLER_PRIV_H_
#define ALLEGRO_HANDLER_PRIV_H_

#include "al_handler.h"

typedef struct handler_global_vars {
    bool key[ALLEGRO_KEY_MAX];

    ALLEGRO_DISPLAY * window_handler;
    ALLEGRO_TIMER * timer;
    ALLEGRO_EVENT_QUEUE * event_queue;
    
    char *string_src;
    int string_len;

    int window_width;
    int window_height;
    
    void (*start_callback)( int window_width, int window_height, void *arg);
    bool (*logic_callback)( int window_width, int window_height, void *arg);
    void (*draw_callback)(  int window_width, int window_height, void *arg);

    int num_sounds;
} handler_global_vars_t;

extern handler_global_vars_t global;

#endif // ALLEGRO_HANDLER_PRIV_H_
