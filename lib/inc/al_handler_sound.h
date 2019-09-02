/*
 * al_handler_sound.h
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

#ifndef AL_HANDLER_SOUND_H_
#define AL_HANDLER_SOUND_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

ALLEGRO_SAMPLE * load_sound(const char * audio_filename, int simultaneous_instances);
void play_sound(ALLEGRO_SAMPLE * sample, ALLEGRO_PLAYMODE playmode);

#endif // AL_HANDLER_SOUND_H_
