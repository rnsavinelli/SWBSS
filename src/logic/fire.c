/*
 * fire.c
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
#include "logic.h"

void generate_fire (app_t *app_struct)
{
	assert(app_struct);

	for (int i = 0; i < NUM_FIRE; i++)
	{
		if(!(app_struct->disparo[i]).flag) {
			(app_struct->disparo[i]).x = (app_struct->spaceship).x;
			(app_struct->disparo[i]).y = (app_struct->spaceship).y;
			(app_struct->disparo[i]).flag = true;
			break;
		}
	}
}

void move_fire(app_t *app_struct)
{
	assert(app_struct);

	int desplazamiento = FIRE_SPEED;
	
	for (int i = 0; i < NUM_FIRE; i++) {
		if((app_struct->disparo[i]).flag) {
			(app_struct->disparo[i]).y += desplazamiento;

			if((app_struct->disparo[i]).y < 0) {
				(app_struct->disparo[i]).flag = false;
			}
		}
	}
}
