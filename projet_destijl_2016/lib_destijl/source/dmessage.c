/**
 * \file dmessage.c
 * \brief Source de la classe DMessage
 * \author P.-E. Hladik
 * \version 0.1
 * \date 29 novembre 2011
 *
 * Implémentation de la classe DMessage
 *
 */

#include "../headers/dmessage.h"
#include "../headers/dtools.h"

static void d_message_init(DMessage*);

static void d_message_init(DMessage *This) {
    This->data = NULL;
    This->dataType = MESSAGE_TYPE_UNKNOWN;
    This->len = 0;

    This->get_data = d_message_get_data;
    This->get_lenght = d_message_get_lenght;
    This->get_type = d_message_get_type;
    This->print = d_message_print;
    This->set = d_message_set;
    This->put_char = d_message_put_char;
    This->put_int = d_message_put_int;
    This->put_string = d_message_put_string;
    This->put_state = d_message_put_state;
    This->put_jpeg_image = d_message_put_jpeg_image;
    This->put_position = d_message_put_position;
    This->put_battery_level = d_message_put_battery_level;
    This->get_payload = d_message_get_payload;
    This->get_payload_size = d_message_get_payload_size;
    This->mission_terminate = d_message_mission_terminate;

}

DMessage* d_new_message(void) {
    DMessage *This = malloc(sizeof (DMessage));
    if (!This) return NULL;
    d_message_init(This);
    This->free = d_message_free;
    return This;
}

void d_message_free(DMessage *This) {
    free(This->data);
    free(This);
}

void d_message_print(DMessage *This, int maxChar) {
    int i;
    if (maxChar > This->len)
        maxChar = This->len;

    printf("Message{type:%c size:", This->data[0]);
    for (i = 1; i < 5; i++) {
        printf("%d", (int) This->data[i]);
    }
    printf(" payload:");
    for (i = 5; i < maxChar; i++) {
        printf("%d ", (int) This->data[i]);
    }
    printf("}\n");
}

void d_message_set(DMessage *This, char type, int datalen, char *d) {
    This->dataType = type;
    This->len = datalen + 5;

    /* liberation de la memoire */
    if (This->data != NULL)
        free(This->data);

    /* reservation memoire pour le nouveau packet */
    This->data = (char*) malloc(datalen + 5);

    /* construction du packet */
    This->data[0] = type;
    char *size = malloc(4 * sizeof (char));
    d_tools_int2bytes(datalen, size);
    memcpy(This->data + 1, size, 4);
    free(size);
    memcpy(This->data + 5, d, datalen);
}

void d_message_put_state(DMessage *This, int value) {
    d_message_put_int(This, value);
    This->dataType = MESSAGE_TYPE_STATE;
    This->data[0] = MESSAGE_TYPE_STATE;
}

void d_message_put_int(DMessage *This, int value) {
    char *b = malloc(4 * sizeof (char));
    d_tools_int2bytes(value, b);
    d_message_set(This, MESSAGE_TYPE_INT, 4, b);
    free(b);
}

void d_message_put_char(DMessage *This, char c) {
    d_message_set(This, MESSAGE_TYPE_CHAR, 1, &c);
}

void d_message_put_string(DMessage *This, char* str) {
    d_message_set(This, MESSAGE_TYPE_STRING, strlen(str), str);
}

void d_message_put_jpeg_image(DMessage *This, DJpegimage *jpegimage) {
    d_message_set(This
            , 'V'
            , (jpegimage->get_data(jpegimage)->cols) * sizeof (uchar)
            , (char *) jpegimage->get_data(jpegimage)->data.ptr);
}

void d_message_put_position(DMessage *This, DPosition *position) {
    int datalen = 3 * sizeof (int);
    char* data = malloc(3 * sizeof (int));
    d_tools_int2bytes((int) position->get_x(position), data);
    d_tools_int2bytes((int) position->get_y(position), data + sizeof (int));
    d_tools_int2bytes((int) (position->get_orientation(position)*360.0 / (2 * M_PI)), data + 2 * sizeof (int));
    d_message_set(This, MESSAGE_TYPE_POSITION, datalen, data);
    free(data);
}

void d_message_put_battery_level(DMessage *This, DBattery *battery) {
    char * buffer = malloc(4);
    d_tools_int2bytes(battery->get_level(battery), buffer);
    d_message_set(This, MESSAGE_TYPE_BATTERY, 4, buffer);
    free(buffer);
}

void d_message_mission_terminate(DMessage *This, int missionId) {
    char * buffer = malloc(4);
    d_tools_int2bytes(missionId, buffer);
    d_message_set(This, MESSAGE_TYPE_MISSION, 4, buffer);
    free(buffer);
}

void d_message_put_version(DMessage *This, int versionMajeure, int versionMineure) {
    char st[30];
    sprintf(st, "v.%d.%d", versionMajeure, versionMineure);
    d_message_put_string(This, st);
    This->data[0] = MESSAGE_TYPE_VERSION;
}

char d_message_get_type(struct DMessage *This) {
    return This->dataType;
}

int d_message_get_lenght(struct DMessage*This) {
    return This->len;
}

char* d_message_get_data(struct DMessage*This) {
    return This->data;
}

char* d_message_get_payload(struct DMessage*This) {
    return (This->data) + 5;
}

int d_message_get_payload_size(struct DMessage *This) {
    return This->len - 5;
}