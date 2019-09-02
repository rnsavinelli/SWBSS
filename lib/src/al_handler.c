/*
 * al_handler.c
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
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "al_handler.h"
#include "al_handler_priv.h"

static int handler_exit(void (* func_ptr) (void));

static void handler_print_pixel_format(ALLEGRO_TEXTLOG *log, int format);

int init_fullscreen_desktop()
{
    char return_value = AL_OK;

	al_set_new_display_option(ALLEGRO_SINGLE_BUFFER, 0, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SWAP_METHOD, 2, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SUPPORT_SEPARATE_ALPHA, 1, ALLEGRO_REQUIRE);

    /* failed to initialize allegro */
	if(!al_install_system(ALLEGRO_VERSION_INT, handler_exit)) {

	    al_init_native_dialog_addon();
	    
	    /* error message box */
	    al_show_native_message_box( NULL, "[ERROR]", "al_install_system() failed", 
                                    "Failed to initialize allegro. Is it properly installed?\n", 
                                    NULL, ALLEGRO_MESSAGEBOX_ERROR);

		return_value = AL_ERROR_ALLEGRO_INIT;
	}
    
	else {
		al_install_keyboard();     	// Keyboard routines
		al_init_font_addon();		// Font routines
		al_init_ttf_addon();		// ttf fonts
		al_init_image_addon();		// Bitmap routines
		al_init_primitives_addon(); // Primitive drawing routines
		al_install_audio();			// Audio routines
		al_init_acodec_addon();		// Audio format

		global.num_sounds = 0;

		int nva = al_get_num_video_adapters();

		global.string_src = NULL;
		global.string_len = 0;

		if(nva < 1) {
			return_value = AL_ERROR_VIDEO_ADAPTER;
		}
		
		else {
    		/* creates window */
			al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_RESIZABLE);
			global.window_handler = al_create_display(1, 1);
			global.window_width = al_get_display_width(global.window_handler);
			global.window_height = al_get_display_height(global.window_handler);

			if(!global.window_handler) {
				return_value = AL_ERROR_WINDOW;
			}
			
			else {
				global.timer = al_create_timer(1.0/FPS);
				
				global.event_queue = al_create_event_queue();

				al_register_event_source(global.event_queue, al_get_keyboard_event_source());

				al_register_event_source(global.event_queue, al_get_timer_event_source(global.timer));
				
				al_register_event_source(global.event_queue, al_get_display_event_source(global.window_handler));
				
				//al_register_event_source(global.event_queue, al_get_audio_stream_event_source(global.window_handler));
			
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
		}
	}

	return return_value;
}

int init_log()
{
	char return_value = AL_OK;

	al_set_new_display_option(ALLEGRO_SINGLE_BUFFER, 0, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SWAP_METHOD, 2, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SUPPORT_SEPARATE_ALPHA, 1, ALLEGRO_REQUIRE);

    if(!al_install_system(ALLEGRO_VERSION_INT, handler_exit)) {

		al_init_native_dialog_addon();
		
		/* error message box */
		al_show_native_message_box( NULL, "[ERROR]", "In funcion al_install_system()", 
									"Failed to initialize allegro. Is it properly installed?\n", 
									NULL, ALLEGRO_MESSAGEBOX_ERROR);

		return_value = AL_ERROR_ALLEGRO_INIT;
	}
    
	else {
		int nva = al_get_num_video_adapters();

		global.string_src = NULL;
		global.string_len = 0;
		
		if(nva < 1) {
			return_value = AL_ERROR_VIDEO_ADAPTER;
		}
		
		else {
			int mode_flags[3] =
			{
				ALLEGRO_FULLSCREEN | ALLEGRO_DIRECT3D_INTERNAL,
				ALLEGRO_FULLSCREEN | ALLEGRO_OPENGL,
				ALLEGRO_FULLSCREEN | ALLEGRO_OPENGL_3_0,
			};

			const char * mode_driver_text[3] =
			{
				"ALLEGRO_DIRECT3D",
				"ALLEGRO_OPENGL",
				"ALLEGRO_OPENGL_3_0"
			};


			ALLEGRO_TEXTLOG * log = al_open_native_text_log("info", 0);

			uint32_t version = al_get_allegro_version();
			int major = version >> 24;
			int minor = (version >> 16) & 255;
			int revision = (version >> 8) & 255;
			int release = version & 255;

			al_append_native_text_log(log, "VERSION ALLEGRO: %u.%u.%u [%u]\n", 
										major, minor, revision, release);

			int i, j;
			
			for( i = 0; i < 3; i++) {
				al_set_new_display_flags(mode_flags[i]);

				int num_modes = al_get_num_display_modes();
				
				al_append_native_text_log(log, "%d modos disponibles para %s:\n", num_modes, mode_driver_text[i]);

				for( j = 0; j < num_modes; j++) {
					ALLEGRO_DISPLAY_MODE mode;

					if( al_get_display_mode(j, &mode) == &mode) {
						al_append_native_text_log(log, "Modo %d: \n", j+1);
						al_append_native_text_log(log, "\t %dx%d @ %d Hz. Pixel format: ",
													mode.width, mode.height, mode.refresh_rate);
						handler_print_pixel_format(log, mode.format);
						al_append_native_text_log(log, "\n");
					}
				}

				al_append_native_text_log(log, "\n");
			}
		}	
	}

	return return_value;
}

const char * browse_file(char const * initial_path, char const * title, char const * patterns)
{
	const char * filename = NULL;

	ALLEGRO_FILECHOOSER *window_browser = al_create_native_file_dialog(initial_path,
														title, patterns,
														ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);

	do {
		al_show_native_file_dialog(global.window_handler, window_browser);
		filename = al_get_native_file_dialog_path( window_browser, 0);
	} while(!filename);

	return filename;
}

/* private functions */
static void handler_print_pixel_format(ALLEGRO_TEXTLOG * log, int format)
{
	switch(format)
	{
		case ALLEGRO_PIXEL_FORMAT_ANY:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ANY");
			break;
		}
		
		case ALLEGRO_PIXEL_FORMAT_ANY_NO_ALPHA:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ANY_NO_ALPHA");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_ANY_WITH_ALPHA:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ANY_WITH_ALPHA");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_ANY_15_NO_ALPHA:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ANY_15_NO_ALPHA");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_ANY_16_NO_ALPHA:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ANY_16_NO_ALPHA");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_ANY_16_WITH_ALPHA:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ANY_16_WITH_ALPHA");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_ANY_24_NO_ALPHA:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ANY_24_NO_ALPHA");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_ANY_32_NO_ALPHA:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ANY_32_NO_ALPHA");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_ANY_32_WITH_ALPHA:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ANY_32_WITH_ALPHA");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_ARGB_8888:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ARGB_8888");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_RGBA_8888:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_RGBA_8888");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_ARGB_4444:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ARGB_4444");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_RGB_888:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_RGB_888");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_RGB_565:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_RGB_565");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_RGB_555:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_RGB_555");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_RGBA_5551:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_RGBA_5551");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_ARGB_1555:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ARGB_1555");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_ABGR_8888:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ABGR_8888");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_XBGR_8888:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_XBGR_8888");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_BGR_888:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_BGR_888");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_BGR_565:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_BGR_565");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_BGR_555:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_BGR_555");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_RGBX_8888:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_RGBX_8888");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_XRGB_8888:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_XRGB_8888");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_ABGR_F32:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ABGR_F32");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_ABGR_8888_LE:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_ABGR_8888_LE");
			break;
		}

		case ALLEGRO_PIXEL_FORMAT_RGBA_4444:
		{
			al_append_native_text_log(log, "ALLEGRO_PIXEL_FORMAT_RGBA_4444");
			break;
		}

		case ALLEGRO_NUM_PIXEL_FORMATS:
		{
			al_append_native_text_log(log, "ALLEGRO_NUM_PIXEL_FORMATS");
			break;
		}

		default:
		{
			al_append_native_text_log(log, "Unknown format");
			break;
		}
	}
}

static int handler_exit(void (* func_ptr) (void))
{
	if(global.window_handler) {
		al_destroy_display(global.window_handler);
		al_destroy_event_queue(global.event_queue);
	}
	
	return atexit(func_ptr);
}
