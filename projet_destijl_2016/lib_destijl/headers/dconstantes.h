/**
 * \file dconstantes.h
 * \brief Déclaration des constantes du projet
 * \author P.-E. Hladik
 * \version 0.1
 * \date 29 novembre 2011
 *
 * Déclaration des constantes du projet
 *
 */

#ifndef CONSTANTES_H
#define CONSTANTES_H

/*! \def ACTION_FIND_ARENA
    \brief Valeur transportée par l'action pour trouver l'arène
*/
#define ACTION_FIND_ARENA                    (1)

/*! \def ACTION_ARENA_FAILED
    \brief Valeur transportée par l'action pour signaler l'arrêt de la recherche de l'arène
*/
#define ACTION_ARENA_FAILED                  (2)

/*! \def ACTION_ARENA_IS_FOUND
    \brief Valeur transportée par l'action pour signaler que l'arène a été trouvée
*/
#define ACTION_ARENA_IS_FOUND                (3)

/*! \def ACTION_COMPUTE_CONTINUOUSLY_POSITION
    \brief Valeur transportée par l'action pour commencer le calcul de la position du robot
*/
#define ACTION_COMPUTE_CONTINUOUSLY_POSITION (4)

/*! \def ACTION_STOP_COMPUTE_POSITION
    \brief Valeur transportée par l'action pour arrêter le calcul de la position du robot
*/
#define ACTION_STOP_COMPUTE_POSITION		(5)

/*! \def ACTION_CONNECT_ROBOT
    \brief Valeur transportée par l'action pour demander la connexion avec le boîtier de communication du robot
*/
#define ACTION_CONNECT_ROBOT                 (10)

/*! \def BATTERY_LEVEL_HIGH
    \brief Valeur décrivant l'état haut de la batterie
*/
#define BATTERY_LEVEL_HIGH                  (2)

/*! \def BATTERY_LEVEL_MEDIUM
    \brief Valeur décrivant l'état moyen de la batterie
*/
#define BATTERY_LEVEL_MEDIUM                (1)

/*! \def BATTERY_LEVEL_LOW
    \brief Valeur décrivant l'état bas de la batterie
*/
#define BATTERY_LEVEL_LOW                   (0)

/*! \def BATTERY_LEVEL_UNKNOWN
    \brief Valeur décrivant un état inconnu de la batterie
*/
#define BATTERY_LEVEL_UNKNOWN               (-1)

/*! \def MESSAGE_TYPE_UNKNOWN
    \brief Valeur du type d'un message quelconque 
*/
#define MESSAGE_TYPE_UNKNOWN                ('U')

/*! \def MESSAGE_TYPE_CHAR
    \brief Valeur du type d'un message portant un char 
*/
#define MESSAGE_TYPE_CHAR                   ('C')

/*! \def MESSAGE_TYPE_INT
    \brief Valeur du type d'un message portant un entier
*/
#define MESSAGE_TYPE_INT                    ('I')

/*! \def MESSAGE_TYPE_STRING
    \brief Valeur du type d'un message portant une chaîne de caractère
*/
#define MESSAGE_TYPE_STRING                 ('S')

/*! \def MESSAGE_TYPE_STATE
    \brief Valeur du type d'un message portant l'état du robot
*/
#define MESSAGE_TYPE_STATE                  ('R')

/*! \def MESSAGE_TYPE_IMAGE
    \brief Valeur du type d'un message portant une image compressée
*/
#define MESSAGE_TYPE_IMAGE                  ('V')

/*! \def MESSAGE_TYPE_BATTERY
    \brief Valeur du type d'un message portant la valeur du niveau de la batterie du robot
*/
#define MESSAGE_TYPE_BATTERY                ('B')

/*! \def MESSAGE_TYPE_MOVEMENT
    \brief Valeur du type d'un message portant un mouvement à réaliser.
*/
#define MESSAGE_TYPE_MOVEMENT              ('M')

/*! \def MESSAGE_TYPE_ACTION
    \brief Valeur du type d'un message portant une action à réaliser.
*/
#define MESSAGE_TYPE_ACTION                 ('A')

/*! \def MESSAGE_TYPE_ORDER
    \brief Valeur du type d'un message portant un ordre à suivre.
*/
#define MESSAGE_TYPE_ORDER                  ('I')

/*! \def MESSAGE_TYPE_POSITION
    \brief Valeur du type d'un message portant la position du robot.
*/
#define MESSAGE_TYPE_POSITION               ('P')

/*! \def MESSAGE_TYPE_MISSION
    \brief Valeur du type d'un message portant une mission à réaliser ou terminée.
*/
#define MESSAGE_TYPE_MISSION               ('T')

/*! \def MESSAGE_TYPE_VERSION
    \brief Valeur du type d'un message portant la version du firmware du robot.
*/
#define MESSAGE_TYPE_VERSION               ('F')

/*! \def DIRECTION_STOP
    \brief Valeur associée au mouvement d'arrêt du robot.
*/
#define DIRECTION_STOP                      (0)

/*! \def DIRECTION_STRAIGHT
    \brief Valeur associée à la direction "tout droit" d'un mouvement.
*/
#define DIRECTION_STRAIGHT                  (1)

/*! \def DIRECTION_RIGHT
    \brief Valeur associée à la direction "à droite" d'un mouvement.
*/
#define DIRECTION_RIGHT                     (2)

/*! \def DIRECTION_LEFT
    \brief Valeur associée à la direction "à gauche" d'un mouvement.
*/
#define DIRECTION_LEFT                      (3)

/*! \def DIRECTION_FORWARD
    \brief Valeur associée à la direction "en arrière" d'un mouvement.
*/
#define DIRECTION_FORWARD                   (4)

/*! \def MISSION_TYPE_REACH_COORDINATE
    \brief Type de mission consistant à rejoindre une position.
*/
#define MISSION_TYPE_REACH_COORDINATE           (0)

/*! \def MISSION_TYPE_REACH_OBJECTIVE
    \brief Type de mission consistant à effectuer une action prédéfinie.
*/
#define MISSION_TYPE_REACH_OBJECTIVE            (1)

/*! \def MISSION_TYPE_STOP
    \brief La mission en cours doit être stoppée.
*/
#define MISSION_TYPE_STOP                       (2)

/*! \def MISSION_OBJECTIVE_GREEN_AREA
    \brief Le robot doit rejoindre la zone verte.
*/
#define MISSION_OBJECTIVE_GREEN_AREA            (0)

/*! \def MISSION_OBJECTIVE_RED_AREA
    \brief Le robot doit rejoindre la zone rouge.
*/
#define MISSION_OBJECTIVE_RED_AREA              (1)

/*! \def MISSION_OBJECTIVE_GET_THE_BALL
    \brief Le robot doit attraper le palet.
*/
#define MISSION_OBJECTIVE_GET_THE_BALL          (2)

/*************************************
*DEFINE ROBOT
*************************************/
/*! \def STATUS_OK
\brief La communication avec le robot est correcte
*/
#define STATUS_OK                               (0)

/*! \def STATUS_ERR_NO_FILE
\brief La communication avec le robot est correcte
*/
#define STATUS_ERR_NO_FILE                      (1)

/*! \def STATUS_ERR_TIMEOUT
\brief Le délai de communicatio est expiré
*/
#define STATUS_ERR_TIMEOUT                      (2)

/*! \def STATUS_ERR_UNKNOWN_CMD
\brief La commande n'est pas reconnue
*/
#define STATUS_ERR_UNKNOWN_CMD					(3)

/*! \def STATUS_ERR_INVALID_PARAMS
\brief les paramètres de la commande ne sont pas conformes
*/
#define STATUS_ERR_INVALID_PARAMS				(4)

/*! \def STATUS_ERR_WDT_EXPIRED
\brief Le watchdog du timer a expiré
*/
#define STATUS_ERR_WDT_EXPIRED					(5)

/*! \def STATUS_ERR_SELECT
\brief Le boîtier n'est pas connecté
*/
#define STATUS_ERR_SELECT                       (6)       

/*! \def STATUS_ERR_UNKNOWN
\brief Erreur inconnue
*/
#define STATUS_ERR_UNKNOWN                      (0xFF)

/*! \def STATUS_ERR_CHECKSUM
\brief Erreur de checksum à la réception
*/
#define STATUS_ERR_CHECKSUM                     (7)

/*! \def MOTEUR_STOP
\brief La vitesse à appliquer au moteur est nulle
*/
#define MOTEUR_STOP								(0)

/*! \def MOTEUR_AVANT_LENT
\brief Le moteur tourne dans le sens horaire lentement
*/
#define MOTEUR_AVANT_LENT                       (1)

/*! \def MOTEUR_AVANT_RAPIDE
\brief Le moteur tourne dans le sens horaire rapidement
*/
#define MOTEUR_AVANT_RAPIDE                     (2)

/*! \def MOTEUR_ARRIERE_LENT
\brief Le moteur tourne dans le sens anti-horaire lentement
*/
#define MOTEUR_ARRIERE_LENT                     (-1)

/*! \def MOTEUR_ARRIERE_RAPIDE
\brief Le moteur tourne dans le sens anti-horaire rapidement
*/
#define MOTEUR_ARRIERE_RAPIDE					(-2)

/*! \def SENSOR_EMPTY
\brief Valeur de retour si la pince du robot est vide
*/
#define SENSOR_EMPTY                            (0)

/*! \def SENSOR_FULL
\brief Valeur de retour si la pince du robot est pleine
*/
#define SENSOR_FULL                             (1)

/*! \def BATTERY_OK
\brief Valeur de retour si la batterie a un niveau suffisant
*/
#define BATTERY_OK                              (2)

/*! \def BATTERY_LOW
\brief Valeur de retour si la batterie a un niveau faible
*/
#define BATTERY_LOW                             (1)
/*! \def BATTERY_OFF
\brief Valeur de retour si la batterie atteint un niveau de coupure
*/
#define BATTERY_OFF                             (0)
    
/*! \def HORAIRE
\brief Sens horaire de rotation du robot
*/
#define HORAIRE									(0)

/*! \def ANTI_HORAIRE
\brief Sens anti-horaire de rotation du robot
*/
#define ANTI_HORAIRE							(1)

#endif