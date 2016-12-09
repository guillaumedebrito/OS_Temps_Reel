/**
 * \file dimage.h
 * \brief Déclaration de la classe DImage.
 * \author P.-E. Hladik
 * \version 0.1
 * \date 28 novembre 2011
 */
#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include "./dposition.h"
#include "./darena.h"
#include "./dtools.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * \struct DImage
     * \brief DImage est un objet contenant la description d'une image.
     */
	 /*! Définition du type pour DImage */
    typedef struct DImage {
        void(*free) (struct DImage *This); /*!< Appel à la fonction d_image_free(). */
        void(*release)(struct DImage *This); /*!< Appel à la fonction d_image_release(). */
        void(*print) (struct DImage *This); /*!< Appel de la fonction d_image_print(). */
        void(*set_ipl) (struct DImage *This, IplImage *img); /*!< Appel de la fonction d_image_set_ipl(). */
        IplImage * (*get_ipl) (struct DImage *This); /*!< Appel de la fonction d_image_get_ipl(). */
        DPosition*(*compute_robot_position)(struct DImage *This, DArena *arena); /*!< Appel de la fonction d_image_compute_robot_position(). */
        DArena*(*compute_arena_position)(struct DImage *This); /*!< Appel de la fonction d_image_compute_arena_position(). */

        IplImage* myiplimg; /*!< L'IplImage (objet OpenCV) encapsulée.*/
        //long long date;
    } DImage;

    /**
     * \fn DImage *This d_new_image(void)
     * \brief Instanciation de l'objet DImage.
     * \return Nouvelle instance allouée d'un objet de type DImage.
     */
    DImage* d_new_image(void);

    /**
     * \fn void d_image_free(DImage *This)
     * \brief Fonction pour désallouer un instance de l'objet DImage.
     * \param This Auto-adressage de l'objet à désallouer.
     */
    void d_image_free(DImage *This);

    /**
     * \fn void d_image_release(DImage *This)
     * \brief Fonction pour désallouer l'IplImage (objet OpenCV) contenu dans l'objet DImage.
     * \param This Auto-adressage de l'objet à désallouer.
     */
    void d_image_release(DImage *This);

    /**
     * \fn void d_image_print(DImage *This)
     * \brief Affichage des caractéristiques de l'objet DImage.
     * \param This Auto-adressage de l'objet à afficher.
     */
    void d_image_print(DImage *This);

    /**
     * \fn     void d_image_set_ipl(DImage *This, IplImage *img)
     * \brief Attribution d'une IplImage (objet OpenCV) à l'objet DImage.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \param img IplImage à passer à l'objet DImage.
     */
    void d_image_set_ipl(DImage *This, IplImage *img);

    /**
     * \fn     IplImage* d_image_get_ipl(DImage *This)
     * \brief Récupération de l'IplImage (objet OpenCV) contenu dans une instance de DImage.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \return IplImage (objet OpenCV) contenu dans l'instance de This.
     */
    IplImage* d_image_get_ipl(DImage *This);

    /**
     * \fn     DPosition* d_image_compute_robot_position(DImage *This , DArena *arena)
     * \brief Calcul de la position du robot dans l'image.
     * \param This Auto-adressage de l'instance de DImage dans laquelle rechercher le robot.
     * \param arena Arème servant de cadre pour rechercher le robot (NULL par défaut).
	 * \return Une instance de DPosition contenant la position du robot.
     */
    DPosition* d_image_compute_robot_position(DImage *This , DArena *arena);

    /**
     * \fn    DArena* d_image_compute_arena_position(DImage *This)
     * \brief Calcul de la position de l'arène dans l'image.
     * \param This Auto-adressage de l'instance de DImage dans laquelle rechercher l'arène.
     * \return Une instance de DArena contenant la description de l'arène.
     */
    DArena* d_image_compute_arena_position(DImage *This);

#ifdef __cplusplus
}
#endif



#endif
