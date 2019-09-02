/*
 * save_score.c
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
#include <stdio_ext.h>
#include "save_score.h"

int save_score(score_t* player, app_t *app_struct)
{	
	assert(app_struct);

    FILE *fd;
    top_t *buffer = NULL;
    int i, tam = 0;
    
    if ((fd = fopen("./scores/scores.dat", "a")) == NULL) {
		perror("Failed to read scores.dat file");
		return -1;
    }

    strcpy( (player->last_play).top_name , player->name );
    (player->last_play).top_points = player->points;

    fwrite(&(player->last_play), sizeof(top_t), 1 ,fd);
    
    fclose(fd);
    
    /* generates dynamic vector */
    if (generar (&buffer, fd, &tam) == -1) {
		return -1;
	}
	
    ordenar(&buffer, tam);

    /* prints first PODIO positions */
	for(i = 0; i < PODIO; i++) {
        strcpy( (app_struct->best[i]).top_name, (buffer+i)->top_name );
        (app_struct->best[i]).top_points = (buffer+i)->top_points;
    }

	free(buffer);
	
   	return 0;
}

/* function to generate the dynamic vector */
int generar(top_t ** ref, FILE *fd, int * t)
{
    top_t buffer;
    
    if ((fd = fopen("./scores/scores.dat", "r")) == NULL) {
		perror("Failed to read scores.dat file");
		return -1;
    }
    
	rewind(fd);
    fread(&buffer, sizeof(top_t), 1, fd);
    
	while (!feof(fd)) {    
		(*t)++;

		if ((*ref)== NULL) {
			if((*ref = (top_t*) malloc (sizeof (top_t))) == NULL) {
				perror("There was an error allocating memory");
				return -1;
			}

			strcpy ( (*ref)->top_name , buffer.top_name);
			(*ref)->top_points = buffer.top_points;
		}
    
		else {	
			if((*ref = (top_t*) realloc ((*ref), (*t) * sizeof(top_t))) == NULL) {
				perror("There was an error allocating memory");
				return -1;
			}
			
			strcpy ( (*ref + (*t) - 1)->top_name , buffer.top_name);
			(*ref + (*t) - 1)->top_points = buffer.top_points;
		}
    
    	fread(&buffer, sizeof(top_t), 1, fd);
	}
    
	fclose(fd);
    
	return 0;
}

void ordenar (top_t **ref, int tam)
{
    	top_t aux;
    	int i, j;

    	for (i = 0; i < tam; i++) {
        	for(j = 0; j < tam-1; j++) {
            		if (((*ref+j)->top_points) < ((*ref+j+1)->top_points)) {
                		strcpy(aux.top_name, (*ref+j)->top_name);
                		aux.top_points = (*ref+j)->top_points;
          
                		strcpy ((*ref+j)->top_name, (*ref+j+1)->top_name);
                		(*ref+j)->top_points = (*ref+j+1)->top_points;
                
                		strcpy ((*ref+j+1)->top_name, aux.top_name);
                		(*ref+j+1)->top_points = aux.top_points;
            		}
        	}
    	}
}
