/*
 * al_handler.h
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

#ifndef AL_HANDLER_H_
#define AL_HANDLER_H_

#define FPS 60.0

#include <allegro5/allegro.h> 
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "al_handler_debug.h"
#include "al_handler_bitmap.h"
#include "al_handler_timer.h"
#include "al_handler_keyboard.h"
#include "al_handler_sound.h"

enum RET_MY_AL_INIT {
    AL_OK,
    AL_ERROR_ALLEGRO_INIT,
    AL_ERROR_VIDEO_ADAPTER,
    AL_ERROR_WINDOW,
};

int init_fullscreen_desktop(void);
int init_log(void);
const char * browse_file(char const * initial_path, char const * title, char const * patterns);

#endif // AL_HANDLER_H_
