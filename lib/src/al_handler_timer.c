/*
 * al_handler_timer.c
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
#include <allegro5/allegro_audio.h>

#include "al_handler_timer.h"
#include "al_handler_priv.h"

void loop_set_start_callback(void (*start_callback) (int window_width, int window_height, void *arg))
{
	global.start_callback = start_callback;
}

void loop_set_logic_callback(bool (*logic_callback) (int window_width, int window_height, void *arg))
{
	global.logic_callback = logic_callback;
}

void loop_set_draw_callback(void (*draw_callback) (int window_width, int window_height, void *arg))
{
	global.draw_callback = draw_callback;
}

void loop_handler(void *arg)
{
	bool loop = true;
	bool redraw = true;
	bool resize = false;
	
	ALLEGRO_EVENT event;

	al_reserve_samples(global.num_sounds);

	global.start_callback(global.window_width, global.window_height, arg);

	al_flip_display();
    
	al_start_timer(global.timer);

	while(loop) {
	    /* display */
		al_wait_for_event(global.event_queue, &event);

		if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			loop = false;
		}
		
		else {
			if(event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
				resize = true;
				global.window_width  = event.display.width;
				global.window_height = event.display.height;
			}

			else  {
				if(resize) {
					resize = false;
					al_acknowledge_resize(global.window_handler);
				}

				switch(event.type) {
					/* keyboard */
					case ALLEGRO_EVENT_KEY_DOWN:
					{
						global.key[event.keyboard.keycode] = true;
						break;
					}

					case ALLEGRO_EVENT_KEY_UP:
					{
						global.key[event.keyboard.keycode] = false;
						break;
					}

					case ALLEGRO_EVENT_KEY_CHAR:
					{
						if(global.string_src) {
							int length = strlen(global.string_src);
							
							if(length < global.string_len - 1) {
								char character = (char) event.keyboard.unichar;

								if (character >= 32 && character <= 127) {
									global.string_src[length] = (char) event.keyboard.unichar;
									global.string_src[length + 1] = '\0';
								}
								
                                else if (character == 8 && length > 0) {
									global.string_src[length - 1] = '\0';
								}
							}
						}

						break;
					}

					/* timer */
					case ALLEGRO_EVENT_TIMER:
					{
						redraw = true;

						loop = global.logic_callback(global.window_width, global.window_height, arg);
						break;
					}
				}

				/* empty event queue */
				if(redraw && al_is_event_queue_empty(global.event_queue)) {
					global.draw_callback(global.window_width, global.window_height, arg);
					al_flip_display();

					redraw = false;
				}
			}
		}
	}
}
