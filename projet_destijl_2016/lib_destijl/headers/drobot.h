/* 
 * File:   DRobot.h
 * Author: pehladik
 *
 * Created on 5 janvier 2012, 17:05
 *
 ============================================================================
 Name        : robot.h
 Author      : Sebastien DI MERCURIO
 Version     :
 Copyright   :
 Description : Interface de la bibliotheque de commande du robot
 ============================================================================
 */

#ifndef ROBOT_H
#define	ROBOT_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include <stdio.h>
#include "dconstantes.h"

    /*
     * Code de retour des fonctions
     */


    extern char *RobotComFilename;
    typedef int RobotStatus;

    /**
     * \struct DRobot
     * \brief DRobot est un objet contenant la description d'une robot
     * à réaliser par le superviseur.
     */
    typedef struct DRobot {
        void(*free) (struct DRobot * This); /*!< Appel à la fonction d_robot_free(). */
        void(*print) (struct DRobot * This); /*!< Appel de la fonction d_robot_print(). */
        RobotStatus(*open_device)(struct DRobot * This); /*!< Appel à la fonction d_robot_open_device(). */
        RobotStatus(*close_com)(struct DRobot * This); /*!< Appel à la fonction d_robot_close_com(). */
        RobotStatus(*start)(struct DRobot * This); /*!< Appel à la fonction d_robot_start(). */
        RobotStatus(*start_insecurely)(struct DRobot * This); /*!< Appel à la fonction d_robot_start_insecurely(). */
        RobotStatus(*stop)(struct DRobot * This); /*!< Appel à la fonction d_robot_stop(). */
        RobotStatus(*set_motors)(struct DRobot * This, int motor_left, int motor_right); /*!< Appel à la fonction d_robot_set_motors(). */
        RobotStatus(*reload_wdt)(struct DRobot * This); /*!< Appel à la fonction d_robot_reload_wdt(). */
        RobotStatus(*get_sensor)(struct DRobot * This, int *sensor); /*!< Appel à la fonction d_robot_get_sensor(). */
        RobotStatus(*get_odo)(struct DRobot * This, int *odo_left, int *odo_right); /*!< Appel à la fonction d_robot_get_odo(). */
        RobotStatus(*get_vbat)(struct DRobot * This, int *vbat); /*!< Appel à la fonction d_robot_gte_vbat(). */
        RobotStatus(*get_version)(struct DRobot * This, int *versionMajor, int *versionMinor); /*!< Appel à la fonction d_robot_get_version(). */
        RobotStatus(*get_status)(struct DRobot * This); /*!< Appel à la fonction d_robot_get_status(). */
        RobotStatus(*move)(struct DRobot * This, int range); /*!< Appel à la fonction d_robot_move(). */
        RobotStatus(*turn)(struct DRobot * This, int angle, int direction); /*!< Appel à la fonction d_robot_turn(). */
        RobotStatus(*is_busy)(struct DRobot * This, int *busy); /*!< Appel à la fonction d_robot_is_busy(). */
        RobotStatus status; /*!< Type d'ordre de l'robot. */
    } DRobot;

    /**
     * \fn DRobot* d_new_robot(void)
     * \brief Instanciation de l'objet DRobot.
     * \return Nouvelle instance de l'objet DRobot.
     */
    DRobot* d_new_robot(void);

    /**
     * \fn void d_robot_free(DRobot*)
     * \brief Fonction pour désallouer un instance de l'objet DRobot.
     * \param This Auto-adressage de l'objet à désallouer.
     */
    void d_robot_free(DRobot *This);

    /**
     * \fn void d_robot_print(DRobot*)
     * \brief Affichage d'une instance de l'objet DRobot.
     * \param This Auto-adressage de l'objet à afficher.
     */
    void d_robot_print(DRobot *This);

    /**
     * \fn RobotStatus d_robot_open_device(struct DRobot * This)
     * \brief <b>A APPELER EN PRIORITE !!!</b> Permet d'ouvrir le port de 
     * communication (defini dans RobotComFilename) pour permettre la 
     * communication avec le robot.
     * Renvoi STATUS_OK si tout s'est bien passé, STATUS_ERR_NO_FILE si 
     * le fichier indiqué dans RobotComFilename n'existe pas ou ne peut pas
     * etre ouvert.
     * <b>Remarque:</b> si le status est STATUS_OK, ca n'indique en rien que le 
     * robot est pret a recevoir des commande. Cela permet juste de pouvoir 
     * envoyer des commandes ...
     *
     * \param This Auto-adressage du robot
     * \return Etat de la communication :
     *   - STATUS_OK => Sortie sans erreur
     *   - STATUS_ERR_NO_FILE => Le fichier indiqué par RobotComFilename n'existe pas ou ne peut pas etre ouvert
     */
    RobotStatus d_robot_open_device(struct DRobot * This);

    /**
     * \fn RobotStatus d_robot_close_com(struct DRobot * This)
     * \brief Ferme le port de communication avec le robot.
     * <b>attention !</b> Cela ne fait aucun "reset" sur le robot !
     * \param This Auto-adressage du robot.
     * \return Etat de la communication :
     *   - STATUS_OK => Sortie sans erreur
     */
    RobotStatus d_robot_close_com(struct DRobot * This);

    /**
     * \fn RobotStatus d_robot_start(struct DRobot * This)
     * \brief Demarre le robot, et active le watchdog interne.
     * Après cette commande, il faut penser à remettre le watchdog à zero toutes
     * les 500 ms.
     * Le robot passe dans l'etat "ACTIF".
     * \param This Auto-adressage du robot.
     * \return Etat de la communication :
     *  - STATUS_OK => Sortie sans erreur
     *  - STATUS_ERR_TIMEOUT => Erreur de timeout dans l'envoi de la comamnde (le robot est allumé ?)
     *  - STATUS_ERR_UNKNOWN_CMD => commande inconnue (le firmware du robot est a jour ? parasitage de la com ?)
     *  - STATUS_ERR_INVALID_PARAMS => Parametre ou commande rejetée (le watchdog a expiré? Le firmware est a jour ? les parametres sont les bons ?)
     */
    RobotStatus d_robot_start(struct DRobot * This);

    /** 
     * \fn RobotStatus d_robot_start_insecurely(struct DRobot * This)
     * \brief Demarre le robot sans activer le watchdog interne/
     * Il n'est donc pas necessaire de remettre le watchdog à zero toutes les
     * 500 ms par la suite.
     * Le robot passe dans l'etat "ACTIF".
     * \param This Auto-adressage du robot.
     * \return Etat de la communication :
     *  - STATUS_OK => Sortie sans erreur
     *  - STATUS_ERR_TIMEOUT => Erreur de timeout dans l'envoi de la comamnde (le robot est allumé ?)
     *  - STATUS_ERR_UNKNOWN_CMD => commande inconnue (le firmware du robot est a jour ? parasitage de la com ?)
     *  - STATUS_ERR_INVALID_PARAMS => Parametre ou commande rejetée (le watchdog a expiré? Le firmware est a jour ? les parametres sont les bons ?)
     */
    RobotStatus d_robot_start_insecurely(struct DRobot * This);

    /** 
     * \fn RobotStatus d_robot_stop(struct DRobot * This)
     * \brief Arrete le robot, le watchdog et stoppe les moteurs.
     * Le robot passe dans l'etat "ATTENTE".
     * \param This Auto-adressage du robot.
     * \return Etat de la communication :
     *  - STATUS_OK => Sortie sans erreur
     *  - STATUS_ERR_TIMEOUT => Erreur de timeout dans l'envoi de la comamnde (le robot est allumé ?)
     *  - STATUS_ERR_UNKNOWN_CMD => commande inconnue (le firmware du robot est a jour ? parasitage de la com ?)
     *  - STATUS_ERR_INVALID_PARAMS => Parametre ou commande rejetée (le watchdog a expiré? Le firmware est a jour ? les parametres sont les bons ?)
     */

    RobotStatus d_robot_stop(struct DRobot * This);

    /** 
     * \fn RobotStatus d_robot_set_motors(struct DRobot * This, int motor_left, int motor_right)
     * \brief Commande les moteurs.
     * \param This Auto-adressage du robot.
     * \param les commandes pour le moteur gauche et le moteur droit.
     * Valeurs pour les commandes de moteur:
     *  - MOTEUR_STOP           0
     *  - MOTEUR_AVANT_LENT     1
     *  - MOTEUR_AVANT_RAPIDE   2
     *  - MOTEUR_ARRIERE_LENT   -1
     *  - MOTEUR_ARRIERE_RAPIDE -2
     * \return Etat de la communication
     *  - STATUS_OK => Sortie sans erreur
     *  - STATUS_ERR_TIMEOUT => Erreur de timeout dans l'envoi de la comamnde (le robot est allumé ?)
     *  - STATUS_ERR_UNKNOWN_CMD => commande inconnue (le firmware du robot est a jour ? parasitage de la com ?)
     *  - STATUS_ERR_INVALID_PARAMS => Parametre ou commande rejetée (le watchdog a expiré? Le firmware est a jour ? les parametres sont les bons ?)
     */

    RobotStatus d_robot_set_motors(struct DRobot * This, int motor_left, int motor_right);

    /** 
     * \fn RobotStatus d_robot_reload_wdt(struct DRobot * This)
     * \brief Remet le watchdog a zero.
     * Le watchdog doit etre remit à zero entre 450 ms et 550 ms, trop tôt ou
     *  trop tard ce n'est pas bon.
     * <b>Remarque:</b> si le robot a été lancé avec la commande RobotStartInsecurely, cette commande
     * est sans effet.
     * \param This Auto-adressage du robot.
     * \return Etat de la communication :
     *  - STATUS_OK => Sortie sans erreur
     *  - STATUS_ERR_TIMEOUT => Erreur de timeout dans l'envoi de la comamnde (le robot est allumé ?)
     *  - STATUS_ERR_UNKNOWN_CMD => commande inconnue (le firmware du robot est a jour ? parasitage de la com ?)
     *  - STATUS_ERR_INVALID_PARAMS => Parametre ou commande rejetée (le watchdog a expiré? Le firmware est a jour ? les parametres sont les bons ?)
     */

    RobotStatus d_robot_reload_wdt(struct DRobot * This);

    /** 
     * \fn RobotStatus d_robot_get_sensor(struct DRobot * This, int *sensor)
     * \brief Retourne l'etat du capteur de balle/palet.
     * Le watchdog doit etre remit à zero entre 450 ms et 550 ms, trop tôt ou 
     * trop tard ce n'est pas bon.
     * <b>Remarque:</b> si le robot a été lancé avec la commande 
     * RobotStartInsecurely, cette commande est sans effet.
     * \param This Auto-adressage du robot
     * \param sensor Pointeur sur int pour recuperer l'etat du capteur (le 
     * pointeur doit pointer sur un espace memoire alloué avant l'appel)
     * L'espace memoire contient l'etat du capteur au retour :
     *  - SENSOR_EMPTY: aucun objet n'est dans la "bouche" du robot.
     *  - SENSOR_FULL:  un objet est present dans la "bouche".
     * \return Etat de la communication :
     *  - STATUS_OK => Sortie sans erreur
     *  - STATUS_ERR_TIMEOUT => Erreur de timeout dans l'envoi de la comamnde (le robot est allumé ?)
     *  - STATUS_ERR_UNKNOWN_CMD => commande inconnue (le firmware du robot est a jour ? parasitage de la com ?)
     *  - STATUS_ERR_INVALID_PARAMS => Parametre ou commande rejetée (le watchdog a expiré? Le firmware est a jour ? les parametres sont les bons ?)
     */

    RobotStatus d_robot_get_sensor(struct DRobot * This, int *sensor);

    /** 
     * \fn RobotStatus d_robot_get_odo(struct DRobot * This, int *odo_left, int *odo_right)
     * \ brief Retourne la distance parcourue par chaque roue.
     * \param This Auto-adressage du robot.
     * \param odo_left Pointeurs sur int pour recuperer l'etat de l'odometrie de
     * la roue gauche (le pointeur doit pointer sur un espace memoire alloué
     *  avant l'appel). L'espace memoire pointé contient au retour la distance
     *  parcourue (avant le firmware 1.4, retourne toujours 0).
     * \param odo_right Pointeurs sur int pour recuperer l'etat de l'odometrie de
     * la roue droite (le pointeur doit pointer sur un espace memoire alloué
     *  avant l'appel). L'espace memoire pointé contient au retour la distance
     *  parcourue (avant le firmware 1.4, retourne toujours 0).
     * \return Etat de la communication :
     *  - STATUS_OK => Sortie sans erreur
     *  - STATUS_ERR_TIMEOUT => Erreur de timeout dans l'envoi de la comamnde (le robot est allumé ?)
     *  - STATUS_ERR_UNKNOWN_CMD => commande inconnue (le firmware du robot est a jour ? parasitage de la com ?)
     *  - STATUS_ERR_INVALID_PARAMS => Parametre ou commande rejetée (le watchdog a expiré? Le firmware est a jour ? les parametres sont les bons ?)
     */

    RobotStatus d_robot_get_odo(struct DRobot * This, int *odo_left, int *odo_right);

    /** 
     * \fn RobotStatus d_robot_get_vbat(struct DRobot * This, int *vbat)
     * \brief Lit l'etat de la batterie.
     * Seul trois niveau de batterie sont remontés:
     *  - BATTERY_OK si la batterie est assez chargée,
     *  - BATTERY_LOW si le niveau commence a etre faible, et
     *  - BATTERY_STOP si le niveau est trop faible.
     * Dans ce dernier cas, le robot passe en mode "BATTERY_OFF" et refuse de 
     * commander les moteurs.
     * \param This Auto-adressage du robot.
     * \param vbat Pointeur sur int pour recuperer l'etat de la batterie (le 
     * pointeur doit pointer sur un espace memoire alloué avant l'appel). Il 
     * contient l'etat de la batterie au retour :
     *  - BATTERY_OK => batterie assez chargé, fonctionnement normal,
     *  - BATTERY_LOW => batterie faible, mais fonctionnement normal,
     *  - BATTERY_OFF => batterie vide, moteurs arretés.
     * \return Etat de la communication :
     *  - STATUS_OK => Sortie sans erreur
     *  - STATUS_ERR_TIMEOUT => Erreur de timeout dans l'envoi de la comamnde (le robot est allumé ?)
     *  - STATUS_ERR_UNKNOWN_CMD => commande inconnue (le firmware du robot est a jour ? parasitage de la com ?)
     *  - STATUS_ERR_INVALID_PARAMS => Parametre ou commande rejetée (le watchdog a expiré? Le firmware est a jour ? les parametres sont les bons ?)
     */
    RobotStatus d_robot_get_vbat(struct DRobot * This, int *vbat);

    /** 
     * \fn RobotStatus d_robot_get_version(struct DRobot * This, int *versionMajor, int *versionMinor)
     * \brief Retourne la version du firmware du robot
     * \param This Auto-adressage du robot
     * \param versionMajor Pointeur sur int pour recuperer le numero de version 
     * (le pointeurs doit pointer sur un espace memoire alloué avant l'appel).
     * Il contient la version au retour.
     * \return versionMinor: Pointeur sur int pour recuperer le numero de version 
     * (le pointeurs doit pointer sur un espace memoire alloué avant l'appel).
     * Il contient la version au retour.
     * \return Etat de la communication :
     *  - STATUS_OK => Sortie sans erreur
     *  - STATUS_ERR_TIMEOUT => Erreur de timeout dans l'envoi de la comamnde (le robot est allumé ?)
     *  - STATUS_ERR_UNKNOWN_CMD => commande inconnue (le firmware du robot est a jour ? parasitage de la com ?)
     *  - STATUS_ERR_INVALID_PARAMS => Parametre ou commande rejetée (le watchdog a expiré? Le firmware est a jour ? les parametres sont les bons ?)
     */
    RobotStatus d_robot_get_version(struct DRobot * This, int *versionMajor, int *versionMinor);


    /** 
     * \fn RobotStatus d_robot_get_status(struct DRobot * This)
     * \brief Retourne l'etat du robot.
     * \param This Auto-adressage du robot.
     * \return Etat de la communication :
     *  - STATUS_OK => Sortie sans erreur
     *  - STATUS_ERR_TIMEOUT => Erreur de timeout dans l'envoi de la comamnde (le robot est allumé ?)
     *  - STATUS_ERR_UNKNOWN_CMD => commande inconnue (le firmware du robot est a jour ? parasitage de la com ?)
     *  - STATUS_ERR_INVALID_PARAMS => Parametre ou commande rejetée (le watchdog a expiré? Le firmware est a jour ? les parametres sont les bons ?)
     */
    RobotStatus d_robot_get_status(struct DRobot * This);

    /** 
     * \fn RobotStatus d_robot_move(struct DRobot * This, int range)
     * \brief Fait avancer le robot en ligen droite pour sur une distance donnee
     * par range.
     * le robot passe dans l'etat "BUSY"
     * \param This Auto-adressage du robot.
     * \param range Distance � parcourir (en mm). Si range est >0, le robot avance, si range est <0, le robot recule.
     * \return Etat de la communication :
     *  - STATUS_OK => Sortie sans erreur
     *  - STATUS_ERR_TIMEOUT => Erreur de timeout dans l'envoi de la comamnde (le robot est allumé ?)
     *  - STATUS_ERR_UNKNOWN_CMD => commande inconnue (le firmware du robot est a jour ? parasitage de la com ?)
     *  - STATUS_ERR_INVALID_PARAMS => Parametre ou commande rejetée (le watchdog a expiré? Le firmware est a jour ? les parametres sont les bons ?)
     */
    RobotStatus d_robot_move(struct DRobot * This, int range);

    /** 
     * \fn d_robot_turn(struct DRobot * This, int angle, int direction)
     * \brief Fait tourner le robot de la valeur de l'angle passe.
     * le robot passe dans l'etat "BUSY".
     * \param This Auto-adressage du robot.
     * \param angle Angle dont le robot doit tourner (en degr�).
     * \param direction Sens dans lequel le robot doit tourner. Les valeurs 
     * possibles sont :
     *  - HORAIRE       0
     *  - ANTI_HORAIRE  1
     * \return Etat de la communication :
     *  - STATUS_OK => Sortie sans erreur
     *  - STATUS_ERR_TIMEOUT => Erreur de timeout dans l'envoi de la comamnde (le robot est allumé ?)
     *  - STATUS_ERR_UNKNOWN_CMD => commande inconnue (le firmware du robot est a jour ? parasitage de la com ?)
     *  - STATUS_ERR_INVALID_PARAMS => Parametre ou commande rejetée (le watchdog a expiré? Le firmware est a jour ? les parametres sont les bons ?)
     */
    RobotStatus d_robot_turn(struct DRobot * This, int angle, int direction);
    
    /** 
     * \fn RobotStatus d_robot_is_busy(struct DRobot *This, int *busy)
     * \brief Retourne si le robot est en cours de mouvement (etat "BUSY") ou
     *  non.
     * \param This Auto-adressage du robot.
     * \param busy Pointeur sur int pour recuperer l'occupation du robot
     * (le pointeurs doit pointer sur un espace memoire alloué avant l'appel).
     * Il contient la valeur :
     *  - 0 si le robot n'est pas "BUSY",
     *  - 1 si le robot est "BUSY".
     * \return Etat de la communication :
     *  - STATUS_OK => Sortie sans erreur
     *  - STATUS_ERR_TIMEOUT => Erreur de timeout dans l'envoi de la comamnde (le robot est allumé ?)
     *  - STATUS_ERR_UNKNOWN_CMD => commande inconnue (le firmware du robot est a jour ? parasitage de la com ?)
     *  - STATUS_ERR_INVALID_PARAMS => Parametre ou commande rejetée (le watchdog a expiré? Le firmware est a jour ? les parametres sont les bons ?)
     */
    RobotStatus d_robot_is_busy(struct DRobot * This, int *busy);

#ifdef	__cplusplus
}
#endif

#endif	/* DRobot_H */

