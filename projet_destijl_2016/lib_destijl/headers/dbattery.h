/**
 * \file dbattery.h
 * \brief Déclaration de la classe DBattery.
 * \author P.-E. Hladik
 * \version 0.1
 * \date 29 novembre 2011
 */

#ifndef BATTERY_H
#define BATTERY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include "./dconstantes.h"

    /**
     * \struct DBattery
     * \brief DBattery est un objet contenant la description de l'état de la batterie.
     */
	 /*! Définition du type pour DBattery */
    typedef struct DBattery {
        void(*free) (struct DBattery *This); /*!< Appel à la fonction d_battery_free(). */
        void(*print) (struct DBattery *This); /*!< Appel à la fonction d_battery_print(). */
        void(*set_level) (struct DBattery *This, int level); /*!< Appel à la fonction d_battery_set_level(). */
        int(*get_level) (struct DBattery *This); /*!< Appel à la fonction d_battery_get_level(). */
        int level; /*!< Niveau de la batterie. */
    } DBattery;

    /**
     * \fn DBattery *This d_new_battery(void)
     * \brief Instanciation de l'objet DBattery.
     * \return Nouvelle instance de type DBattery.
     */
    DBattery* d_new_battery(void);

    /**
     * \fn void d_battery_free(DBattery *This)
     * \brief Fonction pour désallouer un instance de l'objet DBattery.
     * \param This Auto-adressage de l'objet à désallouer.
     */
    void d_battery_free(DBattery *This);

    /**
     * \fn void d_battery_print(DBattery *This)
     * \brief Affichage d'une instance d'objet DBattery.
     * \param This Auto-adressage de l'objet à afficher.
     */
    void d_battery_print(DBattery *This);

    /**
     * \fn void d_battery_set_level(DBattery *This, int level)
     * \brief Mise à jour du niveau de la batterie décrit par un objet DBattery.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \param level Nouvelle valeur du niveau de la batterie. Les valeurs possibles 
	 * sont #BATTERY_LEVEL_HIGH, #BATTERY_LEVEL_MEDIUM #BATTERY_LEVEL_LOW et
	 * #BATTERY_LEVEL_UNKNOWN (voir dconstantes.h)
	 */
    void d_battery_set_level(DBattery *This, int level);

    /**
     * \fn int d_battery_get_level(DBattery *This)
     * \brief Lecture du niveau d'un objet DBattery.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
	 * \return Niveau de la batterie.  Les valeurs possibles 
	 * sont #BATTERY_LEVEL_HIGH, #BATTERY_LEVEL_MEDIUM #BATTERY_LEVEL_LOW et
	 * #BATTERY_LEVEL_UNKNOWN (voir dconstantes.h)
     */
    int d_battery_get_level(DBattery *This);

#ifdef __cplusplus
}
#endif
#endif