/**
 * \file darena.c
 * \brief Source de la classe DArena
 * \author P.-E. Hladik
 * \version 0.1
 * \date 28 novembre 2011
 *
 * Implémentation de la classe DArena
 *
 */

#include "../headers/darena.h"

static void d_arena_init(DArena*);

static void d_arena_init(DArena *This) {
    This->print = d_arena_print;
    This->get_angle = d_arena_get_angle;
    This->get_box = d_arena_get_box;
    This->get_height = d_arena_get_height;
    This->get_width = d_arena_get_width;
    This->get_x = d_arena_get_x;
    This->get_y = d_arena_get_y;
    This->set = d_arena_set;

    This->set(This, 0.0, 0.0, 0.0, 0.0, 0.0);
}

DArena* d_new_arena(void) {
    DArena *This = malloc(sizeof (DArena));
    if (This == NULL) {
        printf("\nAttempt to allocate DArena failed.\n");
        exit(1);
    }
    if (!This) return NULL;
    d_arena_init(This);
    This->free = d_arena_free;
    return This;
}

void d_arena_print(DArena *This) {
    printf("arena{x:%f,y:%f,h:%f,w:%f,angle:%f)}\n"
            , This->get_x(This)
            , This->get_y(This)
            , This->get_height(This)
            , This->get_width(This)
            , This->get_angle(This));
}

void d_arena_free(DArena *This) {
    free(This);
}

void d_arena_set(DArena *This, float x, float y, float height, float width, float angle) {
    This->box.angle = angle;
    This->box.center.x = x;
    This->box.center.y = y;
    This->box.size.height = height;
    This->box.size.width = width;
}

float d_arena_get_x(DArena *This) {
    return This->box.center.x;
}

float d_arena_get_y(DArena *This) {
    return This->box.center.y;
}

float d_arena_get_height(DArena *This) {
    return This->box.size.height;
}

float d_arena_get_width(DArena *This) {
    return This->box.size.width;
}

float d_arena_get_angle(DArena *This) {
    return This->box.angle;
}

CvBox2D d_arena_get_box(DArena *This) {
    return This->box;
}
