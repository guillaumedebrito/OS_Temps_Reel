/**
 * \file daction.c
 * \brief Source de la classe DBattery
 * \author P.-E. Hladik
 * \version 0.1
 * \date 29 novembre 2011
 *
 * Implémentation de la classe DBattery
 *
 */

#include "../headers/dbattery.h"
#include <stdio.h>


static void d_battery_init(DBattery*);

static void d_battery_init(DBattery *This) {
    This->level = BATTERY_LEVEL_UNKNOWN;

    This->get_level = d_battery_get_level;
    This->set_level = d_battery_set_level;
    This->print = d_battery_print;
}

DBattery* d_new_battery(void) {
    DBattery *This = malloc(sizeof(DBattery));
    if (!This) return NULL;
    d_battery_init(This);
    This->free = d_battery_free;
    return This;
}

void d_battery_free(DBattery *This){
    free(This);
}

void d_battery_print(DBattery *This){
    printf("Niveau de la batterie:%i\n", This->level);
}

void d_battery_set_level(DBattery *This, int level){
    This->level = level;
}

int d_battery_get_level(DBattery *This){
    return This->level;
}
