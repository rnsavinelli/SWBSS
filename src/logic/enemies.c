/*
 * enemies.c
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

void generate_enemy(int window_width, int window_height, app_t *app_struct)
{
    assert(app_struct);

    ALLEGRO_BITMAP * enemy = app_struct->images[IMG_ENEMY];

    assert(enemy);

    int enemy_h = al_get_bitmap_height(enemy);
    int i, j, q = 0;
    int random;
    float k = (window_width/(2*NUM_ENEMIES));

    /* if all enemies are set to false: new wave */
    for(j = 0; j < NUM_FILAS; j++) {
        for(i = 0; i < NUM_ENEMIES; i++) {    
            if(!(app_struct->enemigo[(NUM_ENEMIES * j) + i]).flag) {
                q++;
            }            
        }
    }

    /* symmetric fist wave: not random */
    if ((app_struct->gameplay).velocidad <= (DEFAULT_SPEED + 0.05)) {
        random = 1;
    }
    
    else {
        random = (rand() % 4) + 1;
    }
    
    /* enemy generation */
    if (q == NUM_ENEMIES * NUM_FILAS) {
        for(i = 0; i < NUM_FIRE; i++) {
            if((app_struct->disparo[i]).y < window_height/4) {
                (app_struct->disparo[i]).x = window_width;
                (app_struct->disparo[i]).y = 0;
                (app_struct->disparo[i]).flag = false;
            }
        }
        
        if (random == 1) {
            for(j = 0; j < NUM_FILAS; j++) {
                for(i = 0; i < NUM_ENEMIES; i++) {    
                    (app_struct->enemigo[(NUM_ENEMIES * j) + i]).flag = true;
                    (app_struct->enemigo[(NUM_ENEMIES * j) + i]).x = window_width/4 + (k * i) + (k/8)*5;
                    (app_struct->enemigo[(NUM_ENEMIES * j) + i]).y = enemy_h*(j+1) - 20;
                }
            }
        }
        
        else if (random == 2) {
            for(j = 0; j < NUM_FILAS; j++) {
                for(i = 0; i < (NUM_ENEMIES); i++) {
                    if (i % 2 == 0) {
                        (app_struct->enemigo[(NUM_ENEMIES * j) + i]).flag = true;
                        (app_struct->enemigo[(NUM_ENEMIES * j) + i]).x =  window_width/4 + (k * i) + (k/8)*5;
                        (app_struct->enemigo[(NUM_ENEMIES * j) + i]).y = enemy_h*(j+1) - 25;
                    }
                    
                    else {
                        (app_struct->enemigo[(NUM_ENEMIES * j) + i]).flag = true;
                        (app_struct->enemigo[(NUM_ENEMIES * j) + i]).x =  window_width/4 + (k * i) + (k/8)*5;
                        (app_struct->enemigo[(NUM_ENEMIES * j) + i]).y = enemy_h*(j+1) + 15;
                    }
                }
            }
        }
        
        else if (random == 3) {
            for(j = 0; j < NUM_FILAS; j++) {
                for(i = 0; i < (NUM_ENEMIES); i++) {
                    if (i % 2 == 0) {
                        (app_struct->enemigo[(NUM_ENEMIES * j) + i]).flag = true;
                        (app_struct->enemigo[(NUM_ENEMIES * j) + i]).x =  window_width/4 + (k * i) + (k/8)*5;
                        (app_struct->enemigo[(NUM_ENEMIES * j) + i]).y = enemy_h*(j+1) + 15;
                    }
                    
                    else {
                        (app_struct->enemigo[(NUM_ENEMIES * j) + i]).flag = true;
                        (app_struct->enemigo[(NUM_ENEMIES * j) + i]).x =  window_width/4 + (k * i) + (k/8)*5;
                        (app_struct->enemigo[(NUM_ENEMIES * j) + i]).y = enemy_h*(j+1) - 25;
                    }
                }
            }
        }
        
        if ((app_struct->gameplay).velocidad <= 2.5) {
            (app_struct->gameplay).velocidad +=  0.1;
        }
        
        else {
            (app_struct->gameplay).velocidad += 0.03;
        }
    }    
}

void move_enemy(int window_width, int window_height, app_t *app_struct)
{    
    assert(app_struct);

    float desplazamiento =  (app_struct->gameplay).velocidad;
    
    int i, j;
    
    for(j = 0; j < NUM_FILAS; j++) {
        for(i = 0; i < NUM_ENEMIES; i++) {
            if((app_struct->enemigo[(NUM_ENEMIES * j) + i]).flag == true) {
                (app_struct->enemigo[(NUM_ENEMIES * j) + i]).y += desplazamiento;
            
                if((app_struct->enemigo[(NUM_ENEMIES * j) + i]).y > window_height) {
                    (app_struct->enemigo[(NUM_ENEMIES * j) + i]).flag = false;
                    ((app_struct->gameplay).tolerance)--;
                }
            }            
        }
    }
}
