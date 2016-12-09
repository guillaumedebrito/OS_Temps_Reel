/**
 * \file dmessage.h
 * \brief Déclaration de la classe DMessage.
 * \author P.-E. Hladik
 * \version 0.1
 * \date 28 novembre 2011
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>

#include "./dconstantes.h"
#include "./dposition.h"
#include "./dbattery.h"
#include "./djpegimage.h"



#ifdef __cplusplus
extern "C" {
#endif

    /**
     * \struct DMessage
     * \brief DMessage est un objet permettant de mettre en forme les messages 
     * à envoyer vers le superviseur
     */

    /*! Définition du type pour DMessage */
    typedef struct DMessage {
        void(*free)(struct DMessage * This); /*!< Appel à la fonction d_message_free(). */
        void(*set)(struct DMessage *This, char type, int l, char *d); /*!< Appel à la fonction d_message_set(). */
        void(*put_int)(struct DMessage *This, int value); /*!< Appel à la fonction d_message_put_int(). */
        void(*put_char)(struct DMessage *This, char c); /*!< Appel à la fonction d_message_put_char(). */
        void(*put_string)(struct DMessage *This, char* str); /*!< Appel à la fonction d_message_put_string(). */
        void(*put_state)(struct DMessage *This, int value); /*!< Appel à la fonction d_message_put_state(). */
        void(*put_jpeg_image)(struct DMessage *This, DJpegimage * jpegimage); /*!< Appel à la fonction d_message_put_jpeg_image(). */
        void(*put_position)(struct DMessage *This, DPosition * p); /*!< Appel à la fonction d_message_put_position(). */
        void(*put_battery_level)(struct DMessage *This, DBattery * b); /*!< Appel à la fonction d_message_put_battery_level(). */

        void(*mission_terminate)(struct DMessage *This, int missionId); /*!< Appel à la fonction d_message_mission_terminate(). */

        char(*get_type)(struct DMessage * This); /*!< Appel à la fonction d_message_get_type(). */
        int(*get_lenght)(struct DMessage * This); /*!< Appel à la fonction d_message_get_lenght(). */
        char*(*get_data)(struct DMessage * This); /*!< Appel à la fonction d_message_get_data(). */
        int(*get_payload_size)(struct DMessage * This); /*!< Appel à la fonction d_message_get_payload_size(). */
        char*(*get_payload)(struct DMessage * This); /*!< Appel à la fonction d_message_get_payload(). */

        void(*print)(struct DMessage *This, int maxChar); /*!< Appel à la fonction d_message_print(). */

        /* Données*/
        char dataType; /*!< Type du message.*/
        int len; /*!< Taille du message.*/
        char *data; /*!< Buffer contenant les données du message.*/
    } DMessage;

    /**
     * \fn DMessage *This d_new_message(void)
     * \brief Instanciation de l'objet DMessage
     * \return Nouvelle instance de type DMessage
     */
    DMessage* d_new_message(void);

    /**
     * void d_message_free(DMessage *This)
     * \brief Fonction pour désallouer une instance de l'objet DMessage
     * \param This Auto-adressage de l'objet à désallouer
     */
    void d_message_free(DMessage *This);

    /**
     * \fn void d_message_set(DMessage *This, char type, int l, char *d)
     * \brief Attribution des champs d'un message (type et données)
     * \param This Auto-adressage de l'objet DMessage à valuer.
     * \param type Type du nouveau message
     * \param l Taille en octets des données utiles à stocker dans le buffer du
     * DMessage.
     * \param d Buffer contenant les données à stocker dans le message.
     */
    void d_message_set(DMessage *This, char type, int l, char *d);

    /**
     * \fn void d_message_put_int(DMessage *This, int value)
     * \brief Attribution des champs d'un message de type entière (#MESSAGE_TYPE_INT).
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \param value Valeur entière à passer dans le message.
     */
    void d_message_put_int(DMessage *This, int value);

    /**
     * \fn void d_message_put_char(DMessage *This, char c)
     * \brief Attribution des champs d'un message de type caractère (#MESSAGE_TYPE_CHAR).
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \param c Caractère à passer dans le message.
     */
    void d_message_put_char(DMessage *This, char c);

    /**
     * \fn void d_message_put_string(struct DMessage *This, char* str)
     * \brief Attribution des champs d'un message de type chaîne de
     * caractères (#MESSAGE_TYPE_STRING).
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \param str Chaîne de caractères à passer dans le message.
     */
    void d_message_put_string(DMessage *This, char* str);

    /**
     * \fn void d_message_put_state(DMessage *This, int value)
     * \brief Attribution des champs d'un message de type état du robot
     *  (#MESSAGE_TYPE_STATE).
     * \param This Auto-adressage de l'objet auquel changer la valeur
     * \param value Valeur entière décrivant l'état du robot. Les valeurs
     * possibles sont : (voir drobot.h).
     */
    void d_message_put_state(DMessage *This, int value);

    /**
     * \fn void d_message_put_jpeg_image(DMessage *This, DJpegimage *jpegimage)
     * \brief Attribution des champs d'un message de type
     * image (#MESSAGE_TYPE_IMAGE).
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \param jpegimage Image compressée à passer dans le message.
     */
    void d_message_put_jpeg_image(DMessage *This, DJpegimage *jpegimage);

    /**
     * \fn void d_message_put_position( DMessage *This, DPosition* p)
     * \brief Attribution des champs d'un message de type DPosition 
     * (#MESSAGE_TYPE_POSITION).
     * \param This Auto-adressage du message.
     * \param p Instance de DPosition à passer dans le message
     */
    void d_message_put_position(DMessage *This, DPosition* p);

    /**
     * \fn void d_message_put_battery_level( DMessage *This, DBattery* b)
     * \brief Attribution des champs d'un message de type DBattery 
     * (#MESSAGE_TYPE_BATTERY).
     * \param This Auto-adressage de l'objet auquel changer la valeur
     * \param b Instance de DBattery à passer dans le message
     */
    void d_message_put_battery_level(DMessage *This, DBattery* b);

    /**
     * \fn void d_message_mission_terminate(DMessage *This, int missionId)
     * \brief Attribution des champs d'un message signalant la fin d'une mission.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \param missionId identifiant de la mission terminée.
     */
    void d_message_mission_terminate(DMessage *This, int missionId);

    /**
     * \fn d_message_put_version(DMessage *This, int versionMajeure, int versionMineure)
     * \brief Attribution des champs d'un message pour l'envoi de la version
     * du firmware du robot.
     * \param This Auto-adressage de l'objet auquel changer la valeur.
     * \param versionMajeure chaîne de caractère contenant la version du firmware.
     * \param versionMineure chaîne de caractère contenant la version mineure du firmware.
     */
    void d_message_put_version(DMessage *This, int versionMajeure, int versionMineure);

    /**
     * \fn char d_message_get_type(struct DMessage *This)
     * \brief Lecture du type du message.
     * \param This Auto-adressage du message.
     * \return Type du message. Les différents types sont : 
     * #MESSAGE_TYPE_UNKNOWN, #MESSAGE_TYPE_CHAR, #MESSAGE_TYPE_INT, 
     * #MESSAGE_TYPE_STRING, #MESSAGE_TYPE_STATE, #MESSAGE_TYPE_IMAGE,
     * #MESSAGE_TYPE_BATTERY, #MESSAGE_TYPE_MOVEMENT, #MESSAGE_TYPE_ACTION, 
     * #MESSAGE_TYPE_ORDER, #MESSAGE_TYPE_POSITION, #MESSAGE_TYPE_MISSION
     * (voir dconstantes.h).
     */
    char d_message_get_type(DMessage *This);

    /**
     * \fn int d_message_get_lenght(struct DMessage *This)
     * \brief Lecture de la taille du message (entêt comprise).
     * \param This Auto-adressage du message.
     * \return Taille en octet du message.
     */
    int d_message_get_lenght(DMessage *This);

    /**
     * \fn char* d_message_get_data(struct DMessage *This)
     * \brief Récupération du buffer contenant les données (entête comprise)
     *  contenu dans une instance de DMessage.
     * \param This Auto-adressage du message source.
     * \return Buffer contenant les données de l'objet DMessage.
     */
    char* d_message_get_data(DMessage *This);

    /**
     * \fn char* d_message_get_payload(struct DMessage *This)
     * \brief Lecture des données utiles du message (sans l'entête).
     * \param This Auto-adressage du message source.
     * \return Buffer contenant les données utiles (sans entête) de l'objet 
     * DMessage.
     */
    char* d_message_get_payload(DMessage *This);

    /**
     * \fn int d_message_get_payload_size(struct DMessage *This)
     * \brief Lecture de la taille des données utiles (sans entête) d'une 
     * instance de DMessage.
     * \param This Auto-adressage du message source.
     * \return Taille des données utiles (sans entête) de l'objet DMessage.
     */
    int d_message_get_payload_size(DMessage *This);

    /**
     * \fn void d_message_print(struct DMessage *This, int maxChar)
     * \brief Affichage d'une instance d'objet DMessage.
     * \param This Auto-adressage de l'objet à afficher.
     * \param maxChar Nombre maximum de caractères à afficher (100 par défaut).
     */
    void d_message_print(DMessage *This, int maxChar);

#ifdef __cplusplus
}
#endif

#endif
