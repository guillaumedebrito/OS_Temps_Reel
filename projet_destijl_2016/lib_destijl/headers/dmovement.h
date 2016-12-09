/**
 * \file dmovement.h
 * \brief Déclaration de la classe DMovement.
 * \author P.-E. Hladik
 * \version 0.1
 * \date 28 novembre 2011
 */

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "./dconstantes.h"
#include "./dmessage.h"


#ifdef __cplusplus
extern "C" {
#endif

    /**
     * \struct DMovement
     * \brief DMovement est un objet contenant la description d'un mouvement
     * (direction et vitesse) à réaliser par le robot.
     */
	 /*! Définition du type pour DMovement */
    typedef struct DMovement {
        void(*free) (struct DMovement *This); /*!< Appel à la fonction d_movement_free(). */
        void(*print) (struct DMovement *This); /*!< Appel de la fonction d_movement_print(). */
        void(*from_message) (struct DMovement *This, struct DMessage *msg); /*!< Appel de la fonction d_movement_from_message(). */
        void(*set) (struct DMovement *This, int direction, int speed); /*!< Appel de la fonction d_movement_set(). */
        int(*get_direction) (struct DMovement *This); /*!< Appel de la fonction d_movement_get_direction(). */
        int(*get_speed) (struct DMovement *This); /*!< Appel de la fonction d_movement_get_speed(). */
        
        int direction; /*!< Direction du mouvement. */
        int speed; /*!< Vitesse du mouvement. */
    } DMovement;

    /**
     * \fn DMovement* d_new_movement(void)
     * \brief Instanciation de l'objet DMovement.
     * \return Nouvelle instance de type DMovement.
     */
    DMovement* d_new_movement(void);

    /**
     * \fn void d_movement_from_message(DMovement *This, DMessage *msg)
     * \brief Attribution des champs d'un DMovement à partir d'un message 
     * de type #MESSAGE_TYPE_MOVEMENT.
     * \param This Auto-adressage du mouvement à définir.
     * \param msg Instance de DMessage contenant la description du mouvement.
     */
    void d_movement_from_message(DMovement *This, DMessage *msg);

    /**
     * \fn void d_movement_free(DMovement *This)
     * \brief Fonction pour désallouer un instance de l'objet DMovement.
     * \param This Auto-adressage de l'objet à désallouer.
     */
    void d_movement_free(DMovement *This);

    /**
     * \fn void d_movement_print(DMovement *This)
     * \brief Affichage d'une instance d'objet DMovement.
     * \param This Auto-adressage de l'objet à afficher.
     */
    void d_movement_print(DMovement *This);

    /**
     * \fn void d_movement_set(DMovement *This, int direction, int speed)
     * \brief Attribution des champs (directeion et vitesse) 
     * d'une instance de DMovement.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \param direction Direction du mouvement. Les valeurs possibles sont :
     * #DIRECTION_STOP, #DIRECTION_STRAIGHT, #DIRECTION_RIGHT, #DIRECTION_LEFT, 
     * #DIRECTION_FORWARD (voir dconstantes.h).
     * \param speed Vitesse du mouvement. La valeur doit être comprise entre 0
     * et 100.
     */
    void d_movement_set(DMovement *This, int direction, int speed);

    /**
     * \fn int d_movement_get_speed(DMovement *This)
     * \brief Lecture de la vitesse d'une instance de DMovement.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \return Vitesse contenue dans l'objet DMovement. Valeur comprise entre
     * 0 et 100.
     */
    int d_movement_get_speed(DMovement *This);


    /**
     * \fn int d_movement_get_direction(DMovement *This)
     * \brief Lecture de la direction d'une instance de DMovement.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \return Direction contenue dans l'objet DMovement. Les valeurs possibles sont :
     * #DIRECTION_STOP, #DIRECTION_STRAIGHT, #DIRECTION_RIGHT, #DIRECTION_LEFT, 
     * #DIRECTION_FORWARD (voir dconstantes.h).
     */
    int d_movement_get_direction(DMovement *This);

  
#ifdef __cplusplus
}
#endif

#endif