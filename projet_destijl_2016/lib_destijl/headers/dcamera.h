/**
 * \file dcamera.h
 * \brief Déclaration de la classe DCamera.
 * \author P.-E. Hladik
 * \version 0.1
 * \date 05 décembre 2011
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <stdlib.h>
#include <stdio.h>
#include "dimage.h"
#include <opencv/highgui.h>

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * \struct DCamera
     * \brief DCamera est un objet contenant la description d'une camera
     * servant à la capture d'une image.
     */
	 /*! Définition du type pour DCamera */
    typedef struct DCamera {
        void(*free) (struct DCamera *This); /*!< Appel à la fonction d_camera_free(). */
        void(*print) (struct DCamera *This); /*!< Appel de la fonction d_camera_print(). */
        void(*open) (struct DCamera *This); /*!< Appel de la fonction d_camera_open(). */
        void(*open_number) (struct DCamera *This, int number); /*!< Appel de la fonction d_camera_open_number(). */
        void(*close) (struct DCamera *This); /*!< Appel de la fonction d_camera_close(). */
        void(*get_frame) (struct DCamera *This, DImage * img); /*!< Appel de la fonction d_camera_get_frame(). */
        CvCapture* mCapture; /*!< Pointeur sur un obbejt Capture (OpenCV)*/
        int mIndice; /*!< Numéro de la camera. */
    } DCamera;

    /**
     * \fn DCamera *This d_new_camera(void)
     * \brief Instanciation de l'objet DCamera.
     * \return Nouvelle instance d'un objet de type DCamera.
     */
    DCamera* d_new_camera(void);

    /**
     * \fn void d_camera_free(DCamera *This)
     * \brief Fonction pour désallouer une instance de l'objet DCamera.
     * \param This Auto-adressage de l'objet à désallouer.
     */
    void d_camera_free(DCamera *This);

    /**
     * \fn void d_camera_print(DCamera *This)
     * \brief Affichage d'une instance d'objet DCamera.
     * \param This Auto-adressage de la camera.
     */
    void d_camera_print(DCamera *This);

    /**
     * \fn void d_camera_open(DCamera *This)
     * \brief Ouverture de la camera dont le numéro est contenu dans mIndice (par défaut -1).
     * \param This Auto-adressage de la camera à ouvrir.
     */
    void d_camera_open(DCamera *This);
    
    
    /**
     * \fn  void d_camera_open_number(DCamera *This, int number)
     * \brief Ouverture de la camera spécifiée par son numéro. 
     * \param This Auto-adressage de la camera à ouvrir.
     * \param number Numéro de la camera à ouvrir.
     */
    void d_camera_open_number(DCamera *This, int number);

    /**
     * \fn void d_camera_close(DCamera *This)
     * \brief Fermeture de la camera.
     * \param This Auto-adressage de la camera à fermer
     */
    void d_camera_close(DCamera *This);

    /**
     * \fn void d_camera_get_frame(DCamera *This, DImage *img)
     * \brief Capture d'une image à partir de la camera.
     * \param This Auto-adressage de la camera sur laquelle faire la capture.
     * \param img Pointeur sur l'image capturée.
     */
    void d_camera_get_frame(DCamera *This, DImage *img);

#ifdef __cplusplus
}
#endif

#endif
