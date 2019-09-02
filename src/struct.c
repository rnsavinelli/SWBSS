/*
 * struct.c
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
#include "struct.h"

void struct_init(app_t *app_struct)
{
	unsigned int i;

	assert(app_struct);

	for(i = 0; i < MAX_FONTS; i++) {
		app_struct->fonts[i] = NULL;
	}

	for(i = 0; i < MAX_IMAGES; i++) {
		app_struct->images[i] = NULL;
	}

	for(i = 0; i < MAX_SOUNDS; i++) {
		app_struct->sounds[i] = NULL;
	}
}

void struct_delete(app_t *app_struct)
{
	unsigned int i;

	assert(app_struct);

	for(i = 0; i < MAX_FONTS; i++) {
		if(app_struct->fonts[i]) {     
			al_destroy_font(app_struct->fonts[i]);
		}
	}

	for(i = 0; i < MAX_IMAGES; i++) {
		if(app_struct->images[i]) {
			al_destroy_bitmap(app_struct->images[i]);
		}
	}

	for(i = 0; i < MAX_SOUNDS; i++) {
		if(app_struct->sounds[i]) {
			al_destroy_sample(app_struct->sounds[i]);
		}
	}
}
