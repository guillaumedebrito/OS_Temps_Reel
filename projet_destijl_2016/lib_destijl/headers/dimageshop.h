/**
 * \file dimageshop.h
 * \brief Outils pour dessiner.
 * \author P.-E. Hladik
 * \version 0.1
 * \date 29 novembre 2011
 */

#ifndef IMAGESHOP_H
#define IMAGESHOP_H

#include <opencv/highgui.h>
#include <opencv/cv.h>
#include "./dposition.h"
#include "./darena.h"
#include "./dimage.h"

#ifdef __cplusplus
extern "C" {
#endif
    /**
     * \fn void d_imageshop_draw_arena(DImage *img, DArena *arena)
     * \brief Dessine une arène sur une image.
     * \param img Image sur laquelle dessiner.
     * \param arena Arène à dessiner.
     */
    void d_imageshop_draw_arena(DImage *img, DArena *arena);
    
    /**
     * \fn void d_imageshop_draw_position(DImage *img, DPosition *pos)
     * \brief Dessine la position (coordonnées et orientation) d'un 
     * robot sur une image.
     * \param img Image sur laquelle dessiner.
     * \param pos Position du robot.
     */
    void d_imageshop_draw_position(DImage *img, DPosition *pos);

    void drawBox(DImage *img, CvBox2D box);
    void drawRec(DImage *img, CvRect rec);
    void showImage(DImage *img, char *title);
    void showIplImage(IplImage *img, char *title);

#ifdef __cplusplus
}
#endif
#endif
