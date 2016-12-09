/**
 * \file DPosition.c
 * \brief Source des outils de conversion
 * \author P.-E. Hladik
 * \version 0.1
 * \date 29 novembre 2011
 *
 * Implémentation des outils de conversions
 *
 */

#include "../headers/dtools.h"

#include <time.h>
#include <sys/time.h>

#include <math.h>

#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <sys/select.h>

void d_tools_int2bytes(unsigned int i, char* b) {
    *b = (i >> 24) & 0xFF;
    *(b + 1) = (i >> 16) & 0xFF;
    *(b + 2) = (i >> 8) & 0xFF;
    *(b + 3) = i & 0xFF;
}

unsigned int d_tools_bytes2int(char *b) {
    unsigned int i;
    i = (unsigned int) ((*(b) << 24)& 0xFF000000)
            + (unsigned int) ((*(b + 1) << 16)& 0xFF0000)
            + (unsigned int) ((*(b + 2) << 8)& 0xFF00)
            + (unsigned int) (*(b + 3) & 0xFF);
    return i;
}

void d_tools_cvbox2cvrect(CvBox2D box, CvRect *rect) {
    CvPoint2D32f box_vtx[4];
    cvBoxPoints(box, box_vtx);

    rect->x = box_vtx[3].x;
    rect->y = box_vtx[0].y;
    rect->height = abs(box_vtx[0].y - box_vtx[2].y);
    rect->width = abs(box_vtx[1].x - box_vtx[3].x);

}

long long d_tools_get_time_in_millisec() {
    // On récupère l'heure dans une structure "timeval"
    struct timeval tv;
    gettimeofday(&tv, NULL);

    // On la convertit en millisecondes à partir des secondes et
    // des microsecondes
    long long l = tv.tv_usec / 1000;
    l += tv.tv_sec * 1000;

    return l;
}

