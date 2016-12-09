/**
 * \file daction.c
 * \brief Source de la classe DAction
 * \author P.-E. Hladik
 * \version 0.1
 * \date 28 novembre 2011
 *
 * Implémentation de la classe DAction
 *
 */

#include "../headers/daction.h"
#include "../headers/dtools.h"

static void d_action_init(DAction *This);

static void d_action_init(DAction *This) {
    This->print = d_action_print;
    This->get_order = d_action_get_order;
    This->set_order = d_action_set_order;
    This->from_message = d_action_from_message;
    This->order = -1;
}

DAction* d_new_action(void) {
    DAction *This = malloc(sizeof (DAction));
    if (This == NULL) {
        printf("\nAttempt to allocate DAction failed.\n");
        exit(1);
    }
    if (!This) return NULL;
    d_action_init(This);
    This->free = d_action_free;
    return This;
}

void d_action_print(DAction *This) {
    printf("Action{order:%i}\n", This->order);
}

void d_action_from_message(DAction *This, DMessage *message) {

    if (message->dataType != MESSAGE_TYPE_ACTION) {
        printf("Attention le message n'est pas un ordre. Il n'a pas été traduit en action\n");
    } else {
        This->order = d_tools_bytes2int(message->get_payload(message));
    }
}

void d_action_free(DAction *This) {
    free(This);
}

void d_action_set_order(DAction *This, int order) {
    This->order = order;
}

int d_action_get_order(DAction *This) {
    return This->order;
}