/*
 * reset_scores.c
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
#define JUGADORES 5
#define MAX_NAME_LEN 20

typedef struct jugador{
    char name[MAX_NAME_LEN];
    int points;
} jugador_t;

int main(void)
{
	int i;
	jugador_t empty_player = {"empty", 0};
	FILE *cfPtr;
	
	if ((cfPtr = fopen ("scores.dat", "w+")) == NULL) {
		printf ("File could not be opened.\n");
		return 1;
	}
	
	else {
		for (i = 0; i < JUGADORES; i++) {
			fwrite (&empty_player, sizeof(jugador_t), 1, cfPtr);
		}

		fclose(cfPtr);	
	}
	
	printf("New \"scores.dat\" file has been created with default values.\n");
	return 0;
}
