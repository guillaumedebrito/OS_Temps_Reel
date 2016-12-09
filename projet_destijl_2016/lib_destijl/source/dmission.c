/**
 * \file dmission.c
 * \brief Source de la classe DMission
 * \author P.-E. Hladik
 * \version 0.1
 * \date 28 novembre 2011
 *
 * Implémentation de la classe DMission
 *
 */

#include "../headers/dmission.h"
#include "../headers/dtools.h"

static void d_mission_init(DMission*);

static void d_mission_init(DMission *This) {
    This->print = d_mission_print;
    This->from_message = d_mission_from_message;
    This->get_position = d_mission_get_position;
    This->get_id = d_mission_get_id;
    This->id = -1;
    This->objective = -1;
    This->orientation = -1;
    This->type = -1;
    This->x = -1;
    This->y = -1;

}

DMission* d_new_mission(void) {
    DMission *This = malloc(sizeof (DMission));
    if (This == NULL) {
        printf("\nAttempt to allocate DMission failed.\n");
        exit(1);
    }
    if (!This) return NULL;
    d_mission_init(This);
    This->free = d_mission_free;
    return This;
}

void d_mission_print(DMission *This) {
    printf("mission{id:%d, type:%d, x:%i,x:%i,orientation:%i}\n",
            This->id,
            This->type,
            This->x,
            This->y,
            This->orientation);
}

void d_mission_free(DMission *This) {
    free(This);
}

void d_mission_from_message(DMission *This, DMessage *message) {

    if (message->dataType != MESSAGE_TYPE_MISSION) {
        printf("Attention le message n'est pas une mission. Il n'a pas été traduit en DMission\n");
    } else {
        This->id = d_tools_bytes2int(message->get_payload(message));
        This->type = d_tools_bytes2int(message->get_payload(message) + 4);
        This->x = d_tools_bytes2int(message->get_payload(message) + 8);
        This->y = d_tools_bytes2int(message->get_payload(message)+12);
        This->orientation = d_tools_bytes2int(message->get_payload(message)+16);
        This->objective = d_tools_bytes2int(message->get_payload(message)+20);
    }
}


int d_mission_get_id(DMission * This) {
    return This->id;
}

void d_mission_get_position(DMission * This, DPosition *position){
    position->set(position, This->x, This->y, This->orientation);
}