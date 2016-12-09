/**
 * \file DArena.h
 * \brief Déclaration de la classe DArena.
 * \author P.-E. Hladik
 * \version 0.1
 * \date 28 novembre 2011
 */

#ifndef arena_H
#define arena_H

#include <stdlib.h>
#include <stdio.h>
#include <opencv/cv.h> 

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * \struct DArena
     * \brief DArena est un objet contenant la description d'une arène.
     */
	 /*! Définition du type pour DArena */
    typedef struct DArena {
        void(*free) (struct DArena *This); /*!< Appel à la fonction d_arena_free(). */
        void(*print) (struct DArena *This); /*!< Appel de la fonction d_arena_print(). */
        void(*set) (struct DArena *This, float x, float y, float height, float width, float angle); /*!< Appel de la fonction d_arena_set(). */
        float(*get_x) (struct DArena *This); /*!< Appel de la fonction d_arena_get_x().*/
        float(*get_y) (struct DArena *This); /*!< Appel de la fonction d_arena_get_y().*/
        float(*get_height) (struct DArena *This); /*!< Appel de la fonction d_arena_get_height().*/
        float(*get_width) (struct DArena *This); /*!< Appel de la fonction d_arena_get_width().*/
        float(*get_angle) (struct DArena *This); /*!< Appel de la fonction d_arena_get_angle().*/
        CvBox2D(*get_box) (struct DArena *This); /*!< Appel de la fonction d_arena_get_box(). */
        CvBox2D box; /*!< Descripteur OpenCV de l'arena. */
    } DArena;

    /**
     * \fn DArena *This d_new_arena(void)
     * \brief Instanciation de l'objet DArena.
     * \return Nouvelle instance d'un objet de type DArena.
     */
    DArena* d_new_arena(void);

    /**
     * \fn void d_arena_free(DArena *This)
     * \brief Fonction pour désallouer un instance de l'objet DArena.
     * \param This Auto-adressage de l'objet à désallouer.
     */
    void d_arena_free(DArena *This);

    /**
     * \fn void d_arena_print(DArena *This)
     * \brief Affichage d'une instance d'objet DArena.
     * \param This Auto-adressage de l'objet à afficher.
     */
    void d_arena_print(DArena *This);

    /**
     * \fn     void d_arena_set(DArena *This, float x, float y, float height, float width, float angle)
     * \brief Mise à jour des champs d'un objet DArena.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \param x Position suivant l'axe des X de l'arène.
	 * \param y Position suivant l'axe des Y de l'arène.
	 * \param height Hauteur de l'arène.
	 * \param width Largeur de l'arène.
	 * \param angle Orientation de l'arène.	  
     */
    void d_arena_set(DArena *This, float x, float y, float height, float width, float angle);

    /**
     * \fn     float d_arena_get_x(DArena *This)
     * \brief Lecture de la position en x de l'arena.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \return Position en x de l'arène.
     */
    float d_arena_get_x(DArena *This);


    /**
     * \fn     float d_arena_get_y(DArena *This)
     * \brief Lecture de la position en y de l'arena.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \return Position en y de l'arène.
     */
    float d_arena_get_y(DArena *This);


    /**
     * \fn     float d_arena_get_height(DArena *This)
     * \brief Lecture de la hauteur de l'arena.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \return hauteur de l'arène.
     */
    float d_arena_get_height(DArena *This);


    /**
     * \fn     float d_arena_get_width(DArena *This)
     * \brief Lecture de la largeur de l'arena.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \return Largeur de l'arène.
     */
    float d_arena_get_width(DArena *This);

    /**
     * \fn     float d_arena_get_angle(DArena *This)
     * \brief Lecture de l'angle de l'arena.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \return Angle de l'arène.
     */
    float d_arena_get_angle(DArena *This);


    /**
     * \fn     CvBox2D d_arena_get_box(DArena *This)
     * \brief Lecture de la box décrivantl'arena.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \return Box contenant la description de l'arène.
     */
    CvBox2D d_arena_get_box(DArena *This);

#ifdef __cplusplus
}
#endif

#endif