/**
 * \file dserver.h
 * \brief Déclaration de la classe DServer.
 * \author P.-E. Hladik
 * \version 0.1
 * \date 01 décembre 2011
 *
 */

#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>
#include <stdio.h>
#include "./dmessage.h"
#include "./dconstantes.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * \struct DServer
     * \brief DServer est un objet contenant la description d'un serveur 
     * de messages.
     */
	 /*! Définition du type pour DServer */
    typedef struct DServer {
        void(*free) (struct DServer *This); /*!< Appel à la fonction d_server_free(). */
        void(*print) (struct DServer *This); /*!< Appel de la fonction d_server_print(). */
        int(*open) (struct DServer *This, char * port); /*!< Appel de la fonction d_server_open(). */
        void(*close) (struct DServer *This); /*!< Appel de la fonction d_server_close(). */
        int(*send) (struct DServer *This, DMessage *message); /*!< Appel de la fonction d_server_send(). */
        int(*receive) (struct DServer *This, DMessage *message); /*!< Appel de la fonction d_server_receive(). */
        int(*is_active) (struct DServer *This); /*!< Appel de la fonction d_server_is_active(). */
        int socketID; /*!< Identifiant du serveur. */
        int active; /*!< Etat du serveur. */
    } DServer;

    /**
     * \fn DServer* d_new_server(void)
     * \brief Instanciation de l'objet DServer.
     * \return Nouvelle instance de type DServer.
     */
    DServer* d_new_server(void);

    /**
     * \fn void d_server_free(DServer *This)
     * \brief Fonction pour désallouer un instance de l'objet DServer.
     * \param This Auto-adressage de l'objet à désallouer.
     */
    void d_server_free(DServer *This);

    /**
     * \fn void d_server_print(DServer *This)
     * \brief Affichage d'une instance d'objet DServer.
     * \param This Auto-adressage de l'objet à afficher.
     */
    void d_server_print(DServer *This);

    /**
     * \fn int d_server_open(DServer *This, char * port)
     * \brief Ouverture du serveur.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \param port Numéro du port associé au serveur.
     * \return 0 si l'ouverture s'est déroulée normalement.
     */
    int d_server_open(DServer *This, char * port);
    
    /**
     * \fn void d_server_close(DServer *This)
     * \brief Fermeture du serveur.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     */
    void d_server_close(DServer *This);

    /**
     * \fn int d_server_send(DServer *This, DMessage *msg)
     * \brief Envoi d'un message.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \param msg Instance de DMessage à envoyer.
     * \return Normbre d'octets envoyés (valeur négative si la connexion 
     * est perdue)
     */
    int d_server_send(DServer *This, DMessage *msg);
    
    
    /**
     * \fn int d_server_receive(DServer *This, DMessage *msg)
     * \brief Attente bloquante d'un message.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
	 * \param msg Pointeur sur le message qui stocke le message reçu 
     * \return Nombre d'octets reçus.
     */
    int d_server_receive(DServer *This, DMessage *msg);
    
    
    /**
     * \fn int d_server_is_active(DServer *This)
     * \brief Retourne l'état du serveur.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \return Etat du serveur. O si la connexion n'est plus active.
     */
    int d_server_is_active(DServer *This);

#ifdef __cplusplus
}
#endif

#endif