/*
 * File:   global.h
 * Author: pehladik
 *
 * Created on 21 avril 2011, 12:14
 */

#include "global.h"

RT_TASK tServeur;
RT_TASK tconnect;
RT_TASK tmove;
RT_TASK tenvoyer;




RT_MUTEX mutexEtat;
RT_MUTEX mutexMove;

RT_SEM semConnecterRobot;

RT_QUEUE queueMsgGUI;

int etatCommMoniteur = 1;
int etatCommRobot = 1;


//########################## THOMAS #########################

//permet de définir si l'arene doit être calibré, si elle est en attente d'acceptation, si elle est acceptée ou refusée
#define ACTION_WAINTING_ARENA                    (6)
int etatArene = ACTION_WAINTING_ARENA ;


DArena *arena;

//###########################################################

DRobot *robot;
DMovement *move;
DServer *serveur;

DCamera *cam;
DImage *image;
DJpegimage *jpegimage;



int MSG_QUEUE_SIZE = 10;

int PRIORITY_TSERVEUR = 30;
int PRIORITY_TCONNECT = 20;
int PRIORITY_TMOVE = 10;
int PRIORITY_TENVOYER = 25;

/**
RAMA-DORITO
**/
RT_TASK twatchdog;   //(calcul aussi la battery : a voir) 
RT_TASK tcamera;
RT_TASK tcalibration;
RT_TASK tcalculposition;


int PRIORITY_TWATCHDOG =  18; 
int PRIORITY_TCAMERA = 12 ; //(on sait pas vraiment) 
int PRIORITY_TCALIBRATION = 16 ; 
int PRIORITY_TCALCULPOSITION = 14 ; //(on sait pas vraiment) 


RT_SEM semDeplacerRobot; 
RT_SEM semWatchdog;     //(REGARDER SI BATTERY AVEC)
RT_SEM semFindArena;
RT_SEM semCalculPosition;  //(Attention il en existe déjà un jamais libéré !!!)
RT_SEM semCalibration; //(?????????)
RT_SEM semCamera; 

RT_MUTEX mutexCompt;




