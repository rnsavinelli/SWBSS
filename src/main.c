/*
 * main.c
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

#include "al_handler.h"
#include "application.h"
#include "struct.h"

int main(void)
{
	app_t data;

   	/* back-end initialization (allegro, keyboard, mouse, timer and creates the window) */
	init_fullscreen_desktop();

    /* game data initialization */
	app_init(&data);

	loop_set_start_callback(app_start);
	loop_set_logic_callback(app_logic);
	loop_set_draw_callback(app_draw);
    
	loop_handler(&data);
    
    /* frees used resources */
	app_exit(&data);

	return 0;
}

