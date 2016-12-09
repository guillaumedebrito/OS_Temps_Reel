/**
 * \file daction.h
 * \brief Déclaration de la classe DAction.
 * \author P.-E. Hladik
 * \version 0.1
 * \date 28 novembre 2011
 */

#ifndef ACTION_H
#define ACTION_H

#include <stdlib.h>
#include <stdio.h>
#include "./dmessage.h"
#include "./dconstantes.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * \struct DAction
     * \brief DAction est un objet contenant la description d'une action
     * à réaliser par le superviseur.
     */
	 /*! Définition du type pour DAction */
    typedef struct DAction {
        void(*free) (struct DAction *This); /*!< Appel à la fonction d_action_free(). */
        void(*print) (struct DAction *This); /*!< Appel de la fonction d_action_print(). */
        void(*from_message) (struct DAction *This, struct DMessage *message); /*!< Appel de la fonction d_action_from_message(). */
        void(*set_order) (struct DAction *This, int order); /*!< Appel de la fonction d_action_set_order(). */
        int(*get_order) (struct DAction *This); /*!< Appel de la fonction d_action_get_order(). */
        int order; /*!< Type d'ordre de l'action. */
    } DAction;

    /**
     * \fn DAction* d_new_action(void)
     * \brief Instanciation de l'objet DAction.
     * \return Nouvelle instance de l'objet DAction.
     */
    DAction* d_new_action(void);

    /**
     * \fn void d_action_free(DAction*)
     * \brief Fonction pour désallouer un instance de l'objet DAction.
     * \param This Auto-adressage de l'objet à désallouer.
     */
    void d_action_free(DAction *This);

    /**
     * \fn void d_action_print(DAction*)
     * \brief Affichage d'une instance de l'objet DAction.
     * \param This Auto-adressage de l'objet à afficher.
     */
    void d_action_print(DAction *This);

    /**
     * \fn  void d_action_from_message(DAction *This, DMessage *message)
     * \brief Remise en forme de la description d'une action contenue dans un message.
     * \param This Adressage de l'objet dans lequel sera contenu la description de l'action.
     * \param message Message dans lequel est stockée la description de l'action.
     */
    void d_action_from_message(DAction *This, DMessage *message);

    /**
     * \fn d_action_set_order(DAction *This, int order)
     * \brief Attribution d'un type d'ordre pour l'action.
     * \param This Auto-adressage de l'action.
     * \param order Type de l'ordre à affecter. Les valeurs 
	 * possibles sont : #ACTION_FIND_ARENA, #ACTION_ARENA_FAILED,
	 * #ACTION_ARENA_IS_FOUND, #ACTION_COMPUTE_CONTINUOUSLY_POSITION,
	 * #ACTION_CONNECT_ROBOT, #ACTION_ARENA_FAILED (voir dconstantes.h pour 
	 * les détails).
     */
    void d_action_set_order(DAction *This, int order);

    /**
     * \fn int d_action_get_order(DAction *This)
     * \brief Récupération du type d'ordre contenu dans l'action.
     * \param This Auto-adressage de l'action dans laquelle récupérer l'ordre.
     * \return Type d'ordre contenu dans l'objet DAction. Les valeurs 
	 * possibles sont :#ACTION_FIND_ARENA, #ACTION_ARENA_FAILED,
	 * #ACTION_ARENA_IS_FOUND, #ACTION_COMPUTE_CONTINUOUSLY_POSITION,
	 * #ACTION_CONNECT_ROBOT, #ACTION_ARENA_FAILED (voir dconstantes.h pour 
	 * les détails).
     */
    int d_action_get_order(DAction *This);

#ifdef __cplusplus
}
#endif

#endif