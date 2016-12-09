/**
 * \file dtools.h
 * \brief Déclaration des méthodes pour convertir différents types de données
 * du projet.
 * \author P.-E. Hladik
 * \version 0.1
 * \date 29 novembre 2011
 *
 */

#ifndef TOOLS_H
#define TOOLS_H

#include <stdlib.h>
#include <stdio.h>
#include <opencv/cv.h>

#ifdef __cplusplus
extern "C" {
#endif


    /**
     * \fn void d_tools_int2bytes(unsigned int i, char* b)
     * \brief Fonction pour convertir un entier en un tableau d'octets.
     * \param i Valeur entière à convertir.
     * \param b Buffer de quatre octets qui stockera le résultat.
     */
    void d_tools_int2bytes(unsigned int i, char* b);

    /**
     * \fn unsigned int d_tools_bytes2int(char *b)
     * \brief Fonction pour convertir un tableau d'octets en un entier.
     * \param b Buffer contenant les données à convertir (taille de 4).
     * \return Valeur convertie.
     */
    unsigned int d_tools_bytes2int(char *b);

    /**
     * \fn void d_tools_cvbox2cvrect(CvBox2D box, CvRect *rect)
     * \brief Fonction pour convertir un objet Box2D (objet OpenCV) en un 
     * objet Rect (objet OpenCV).
     * \param box à convertir
     * \param rect contenant le résultat de la conversion
     */
    void d_tools_cvbox2cvrect(CvBox2D box, CvRect *rect);

    /**
     * \fn long long d_tools_get_time_in_millisec()
     * \brief Fonction qui retourne l'heure en millisecondes.
     * \return Date en millisecondes.
     */
    long long d_tools_get_time_in_millisec();

#ifdef __cplusplus
}
#endif
#endif
