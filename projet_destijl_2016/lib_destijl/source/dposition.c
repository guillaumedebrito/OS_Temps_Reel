/**
 * \file DPosition.c
 * \brief Source de la classe DPosition
 * \author P.-E. Hladik
 * \version 0.1
 * \date 29 novembre 2011
 *
 * Implémentation de la classe DPosition
 *
 */

#include "../headers/dposition.h"

static void d_position_init(DPosition*);

static void d_position_init(DPosition *This) {
    This->print = d_position_print;
    This->get_orientation = d_position_get_orientation;
    This->get_x = d_position_get_x;
    This->get_y = d_position_get_y;
    This->set = d_position_set;

    This->x = 0.0;
    This->y = 0.0;
    This->orientation = 0.0;
}

DPosition* d_new_position(void) {
    DPosition *This = malloc(sizeof (DPosition));
    if (This == NULL) {
        printf("\nAttempt to allocate DPosition failed.\n");
        exit(1);
    }
    if (!This) return NULL;
    d_position_init(This);
    This->free = d_position_free;
    return This;
}

void d_position_print(DPosition *This) {
    printf("position{x:%f,y:%f,orientation:%f}\n",This->x, This->y, This->orientation );
}

void d_position_free(DPosition *This) {
    free(This);
}

void d_position_set(DPosition *This, float x, float y, float orientation) {
    This->x = x;
    This->y = y;
    This->orientation = orientation;
}

float d_position_get_x(DPosition *This) {
    return This->x;
}

float d_position_get_y(DPosition *This) {
    return This->y;
}

float d_position_get_orientation(DPosition *This) {
    return This->orientation;
}