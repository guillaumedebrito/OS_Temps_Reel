/**
 * \file dposition.h
 * \brief Déclaration de la classe DPosition
 * \author P.-E. Hladik
 * \version 0.1
 * \date 29 novembre 2011
 */

#ifndef POSITION_H
#define POSITION_H

#include <stdlib.h>
#include <stdio.h>
#include "./dconstantes.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * \struct DPosition
     * \brief DPosition est un objet contenant la description d'une position
     *  du robot (coordonnées et orientation).
     */
	 /*! Définition du type pour DPosition */
    typedef struct DPosition {
        void(*free) (struct DPosition * This); /*!< Appel à la fonction d_position_free(). */
        void(*print) (struct DPosition * This); /*!< Appel à la fonction d_position_print(). */
        void(*set)(struct DPosition * This, float x, float y, float orientation);/*!< Appel à la fonction d_position_set(). */
        float(*get_x)(struct DPosition * This);/*!< Appel à la fonction d_position_get_x(). */
        float(*get_y)(struct DPosition * This);/*!< Appel à la fonction d_position_get_y(). */
        float(*get_orientation)(struct DPosition * This);/*!< Appel à la fonction d_position_get_orientation(). */

        float x; /*!< Coordonnée en x. */
        float y; /*!< Coordonnée en y. */
        float orientation; /*!< Orientation en radian. */
    } DPosition;

    /**
     * \fn DPosition* d_new_position(void)
     * \brief Instanciation de l'objet DPosition.
     * \return Nouvelle instance de type DPosition.
     */
    DPosition* d_new_position(void);

    /**
     * \fn void d_position_free(DPosition *This)
     * \brief Fonction pour désallouer un instance de l'objet DPosition.
     * \param This Auto-adressage de l'objet à désallouer
     */
    void d_position_free(DPosition *This);

    /**
     * \fn void d_position_print(DPosition *This)
     * \brief Affichage d'une instance d'objet DPosition.
     * \param This Auto-adressage de l'objet à afficher.
     */
    void d_position_print(DPosition *This);

    /**
     * \fn void d_position_set(struct DPosition * This, float x, float y, float orientation)
     * \brief Attribution des champs à une instance de DPosition.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \param x Valeur en abscisse de la position.
     * \param y Valeur en ordonnée de la position.
     * \param orientation Valeur de l'orientation du robot en radian.
     */
    void d_position_set(DPosition * This, float x, float y, float orientation);

    /**
     * \fn float d_position_get_x(struct DPosition * This)
     * \brief Lecture de l'abscisse de la position.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \return Valeur en abscisse de la position.
     */
    float d_position_get_x(DPosition * This);

    /**
     * \fn float d_position_get_y(struct DPosition * This)
     * \brief Lecture de l'ordonnée de la position.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \return Valeur en ordonnée de la position.
     */
    float d_position_get_y(DPosition * This);

    /**
     * \fn float d_position_get_orientation(struct DPosition * This)
     * \brief Lecture de l'orientation de la position.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \return Valeur de l'orientation en radian de la position.
     */
    float d_position_get_orientation(DPosition * This);

#ifdef __cplusplus
}
#endif
#endif