/* 
 * File:   global.h
 * Author: pehladik
 *
 * Created on 12 janvier 2012, 10:11
 */

#ifndef GLOBAL_H
#define	GLOBAL_H

#include "includes.h"

/* @descripteurs des tâches */
extern RT_TASK tServeur;
extern RT_TASK tconnect;
extern RT_TASK tmove;
extern RT_TASK tenvoyer;
extern RT_TASK twatchdog;
extern RT_TASK tcamera;
extern RT_TASK tcalibration;
extern RT_TASK tcalculposition;

/* @descripteurs des mutex */
extern RT_MUTEX mutexEtat;
extern RT_MUTEX mutexMove;
extern RT_MUTEX mutexCompt;


/* @descripteurs des sempahore */
extern RT_SEM semConnecterRobot;



/* @descripteurs des files de messages */
extern RT_QUEUE queueMsgGUI;

/* @variables partagées */
extern int etatCommMoniteur;
extern int etatCommRobot;
extern DServer *serveur;
extern DRobot *robot;
extern DMovement *move;

extern DCamera *cam;
extern DImage *image;
extern DJpegimage *jpegimage;


/* @constantes */
extern int MSG_QUEUE_SIZE;


extern int PRIORITY_TSERVEUR;
extern int PRIORITY_TCONNECT;
extern int PRIORITY_TMOVE;
extern int PRIORITY_TENVOYER;
extern int PRIORITY_TWATCHDOG; 
extern int PRIORITY_TCAMERA;
extern int PRIORITY_TCALIBRATION; 
extern int PRIORITY_TCALCULPOSITION;

extern RT_SEM semDeplacerRobot; 
extern RT_SEM semWatchdog;     //(REGARDER SI BATTERY AVEC)
extern RT_SEM semFindArena;
extern RT_SEM semCalculPosition;  //(Attention il en existe déjà un jamais libéré !!!)
extern RT_SEM semCalibration; //(?????????)
extern RT_SEM semCamera; 

#endif	/* GLOBAL_H */

