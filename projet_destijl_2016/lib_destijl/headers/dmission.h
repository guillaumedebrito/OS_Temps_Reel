/**
 * \file dmission.h
 * \brief Déclaration de la classe DMission.
 * \author P.-E. Hladik
 * \version 0.1
 * \date 12 décembre 2011
 */

#ifndef MISSION_H
#define MISSION_H

#include "./dconstantes.h"
#include "./dmessage.h"
#include "./dposition.h"


#ifdef __cplusplus
extern "C" {
#endif

    /**
     * \struct DMission
     * \brief DMission est un objet contenant la description d'une mission à
     * réaliser par un robot.
     */
	 /*! Définition du type pour DMission */
    typedef struct DMission {
        void(*free) (struct DMission * This); /*!< Appel à la fonction d_mission_free(). */
        void(*print) (struct DMission * This); /*!< Appel de la fonction d_mission_print(). */
        void(*from_message) (struct DMission *This, struct DMessage * msg); /*!< Appel de la fonction d_mission_from_message(). */
        
        void(*get_position) (struct DMission * This, DPosition *position); /*!< Appel de la fonction d_mission_get_position(). */
        int(*get_id) (struct DMission *This); /*!< Appel de la fonction d_mission_get_id(). */

        int id; /*!< Identifiant de la mission*/
        int type; /*!< Type de mission à réaliser. Les valeurs possibles sont : #MISSION_TYPE_REACH_COORDINATE, #MISSION_TYPE_REACH_OBJECTIVE, #MISSION_TYPE_STOP */
        int x; /*!< Coordonnée en X à atteindre pour une mission de type #MISSION_TYPE_REACH_COORDINATE */
        int y; /*!< Coordonnée en Y à atteindre pour une mission de type #MISSION_TYPE_REACH_COORDINATE */
        int orientation; /*!< Orientation à atteindre pour une mission de type #MISSION_TYPE_REACH_COORDINATE */
        int objective; /*!< Description d'une mission pré-définie. */
    } DMission;

    /**
     * \fn DMission* d_new_mission(void)
     * \brief Instanciation de l'objet DMission.
     * \return Nouvelle instance de type DMission.
     */
    DMission* d_new_mission(void);

    /**
     * \fn void d_mission_free(DMission *This)
     * \brief Fonction pour désallouer un instance de l'objet DMission.
     * \param This Auto-adressage de l'objet à désallouer.
     */
    void d_mission_free(DMission *This);

    /**
     * \fn void d_mission_print(DMission *This)
     * \brief Affichage d'une instance d'objet DMission.
     * \param This Auto-adressage de l'objet à afficher.
     */
    void d_mission_print(DMission *This);
    
    
    /**
     * \fn void d_mission_from_message(DMission *This, DMessage *msg)
     * \brief Attribution des champs d'un DMission à partir d'un message.
     * de type #MESSAGE_TYPE_MISSION.
     * \param This Auto-adressage de la mission à définir.
     * \param msg Instance de DMessage contenant la description de la mission.
     */
    void d_mission_from_message(DMission *This, DMessage *msg);

    /**
     * \fn void d_mission_get_position(DMission * This, DPosition *position)
     * \brief Lecture de la position à atteindre pour une mission de 
     * type #MISSION_TYPE_REACH_COORDINATE
     * \param This Auto-adressage de l'objet à afficher.
     * \param position Position à atteindre.
     */
    void d_mission_get_position(DMission * This, DPosition *position);
    
        /**
     * \fn int d_mission_get_id(DMission * This)
     * \brief Lecture de l'identifiant de la mission
     * \param This Auto-adressage de l'objet à afficher.
     * \return Identifiant de la mission.
     */
    int d_mission_get_id(DMission * This);
    

#ifdef __cplusplus
}
#endif

#endif