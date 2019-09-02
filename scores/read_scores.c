/*
 * read_scores.c
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
#define MAX_NAME_LEN 20

typedef struct jugador{
    char name[MAX_NAME_LEN];
    int points;
} jugador_t;

int main (void)
{
	FILE *cfPtr;
	jugador_t jugador;
	
	if((cfPtr = fopen("scores.dat", "r")) == NULL) {
		printf("File could not be opened.\n");
	}
	
	else {		
		fread(&jugador, sizeof(jugador_t), 1, cfPtr);

		while (!feof(cfPtr)) {	
			printf("%s %d\n", jugador.name, jugador.points);
			fread(&jugador, sizeof(jugador_t), 1, cfPtr);
		}
	}
	
	fclose(cfPtr);
	return 0;
}
