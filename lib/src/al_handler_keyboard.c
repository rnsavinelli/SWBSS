/*
 * al_handler_keyboard.c
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

#include "al_handler_keyboard.h"
#include "al_handler_priv.h"

bool handler_key(int keycode)
{
	assert(keycode < ALLEGRO_KEY_MAX);

	return global.key[keycode];
}

void set_string_source(char *string_source, int string_len)
{
	assert(string_source && string_len > 0);

    global.string_src = string_source;
	global.string_len = string_len;
}
