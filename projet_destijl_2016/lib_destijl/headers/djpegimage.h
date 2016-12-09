/**
 * \file djpegimage.h
 * \brief Déclaration de la classe DJpegimage.
 * \author P.-E. Hladik
 * \version 0.1
 * \date 29 novembre 2011
 */

#ifndef JPEGIMAGE_H
#define JPEGIMAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>

#include "./dimage.h"
#include "./dconstantes.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * \struct DJpegimage
     * \brief DJpegimage est un objet contenant la description d'une jpegimage.
     */
	 /*! Définition du type pour DJpegimage */
    typedef struct DJpegimage {
        void(*free) (struct DJpegimage * This); /*!< Appel à la fonction d_jpegimage_free(). */
        void(*release) (struct DJpegimage * This); /*!< Appel à la fonction d_jpegimage_release(). */
        void(*print) (struct DJpegimage * This); /*!< Appel de la fonction d_jpegimage_print(). */
        void(*compress) (struct DJpegimage *This, DImage * img); /*!< Appel de la fonction d_jpegimage_compress(). */
        CvMat * (*get_data) (struct DJpegimage * This); /*!< Appel de la fonction d_jpegimage_get_data(). */

        CvMat* data; /*!< Matrice (objet OpenCV) contenant l'image compressée. */
        //long long date;
    } DJpegimage;

    /**
     * \fn DJpegimage *This d_new_jpegimage(void)
     * \brief Instanciation de l'objet DJpegimage.
     * \return Nouvelle instance de type DJpegimage.
     */
    DJpegimage* d_new_jpegimage(void);

    /**
     * \fn void d_jpegimage_free(DJpegimage *This)
     * \brief Fonction pour désallouer une instance de l'objet DJpegimage.
     * \param This Auto-adressage de l'objet à désallouer.
     */
    void d_jpegimage_free(DJpegimage *This);

    /**
     * \fn vvoid d_jpegimage_release(DJpegimage *This)
     * \brief Fonction pour uniquement désallouer les données de l'image compressée.
     * \param This Auto-adressage de l'objet à désallouer.
     */
    void d_jpegimage_release(DJpegimage *This);

    /**
     * \fn void d_jpegimage_print(DJpegimage *This)
     * \brief Affichage d'une instance d'objet DJpegimage.
     * \param This Auto-adressage de l'objet à afficher.
     */
    void d_jpegimage_print(DJpegimage *This);

    /**
     * \fn void d_jpegimage_compress(DJpegimage *This, DImage *img)
     * \brief Compression et stockage d'une image dans l'objet DJpegimage.
     * \param This Auto-adressage de l'instance de DJpegimage dans laquelle sera
     * stockée l'image compressée.
     * \param img Image à compresser.
     */
    void d_jpegimage_compress(DJpegimage *This, DImage *img);

    /**
     * \fn CvMat* d_jpegimage_get_data(DJpegimage *This)
     * \brief Renvoi la matrice contenant l'image compressée.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \return La matrice CvMat (objet OpenCV) contenant les données compressées.
     */
    CvMat* d_jpegimage_get_data(DJpegimage *This);

#ifdef __cplusplus
}
#endif

#endif