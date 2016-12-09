/**
 * \file dmovement.c
 * \brief Source de la classe DMovement
 * \author P.-E. Hladik
 * \version 0.1
 * \date 28 novembre 2011
 *
 * Implémentation de la classe DMovement
 *
 */

#include "../headers/dmovement.h"
#include "../headers/dtools.h"

static void d_movement_init(DMovement*);

static void d_movement_init(DMovement *This) {
    This->print = d_movement_print;
    This->get_direction = d_movement_get_direction;
    This->get_speed = d_movement_get_speed;
    This->set = d_movement_set;
    This->from_message = d_movement_from_message;
    This->direction = DIRECTION_STOP;
    This->speed = 0;
}

DMovement* d_new_movement(void) {
    DMovement *This = malloc(sizeof (DMovement));
    if (This == NULL) {
        printf("\nAttempt to allocate DMovement failed.\n");
        exit(1);
    }
    if (!This) return NULL;
    d_movement_init(This);
    This->free = d_movement_free;
    return This;
}

void d_movement_print(DMovement *This) {
    printf("movement{direction:%i,speed:%i}\n", This->direction, This->speed);
}

void d_movement_from_message(DMovement *This, DMessage *message) {

    if (message->dataType != MESSAGE_TYPE_MOVEMENT) {
        printf("Attention le message n'est pas un mouvement. Il n'a pas été traduit en DMovement\n");
    } else {
        int d = d_tools_bytes2int(message->get_payload(message));
        int s =  d_tools_bytes2int(message->get_payload(message)+4);
        d_movement_set(This,d,s);
    }
}

void d_movement_free(DMovement *This) {
    free(This);
}

void d_movement_set(DMovement *This, int direction, int speed) {
    if (((direction == DIRECTION_FORWARD) ||
            (direction == DIRECTION_LEFT) ||
            (direction == DIRECTION_RIGHT) ||
            (direction == DIRECTION_STOP) ||
            (direction == DIRECTION_STRAIGHT)) &&
            ((speed >= 0) && (speed <= 100))){
        This->direction = direction;
        This->speed = speed;
    } else {
        printf("La mise à jour du mouvement n'a pas été faite car les valeurs ne sont pas admissibles.\n");
    }

}

int d_movement_get_direction(DMovement *This) {
    return This->direction;
}

int d_movement_get_speed(DMovement *This) {
    return This->speed;
}