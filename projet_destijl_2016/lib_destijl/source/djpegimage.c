/**
 * \file djpegimage.c
 * \brief Source de la classe DJpegimage
 * \author P.-E. Hladik
 * \version 0.1
 * \date 29 novembre 2011
 *
 * Implémentation de la classe DJpegimage
 *
 */

#include "../headers/djpegimage.h"

static void d_jpegimage_init(DJpegimage*);

static void d_jpegimage_init(DJpegimage *This) {
    This->print = d_jpegimage_print;
    This->compress = d_jpegimage_compress;
    This->get_data = d_jpegimage_get_data;
    This->release = d_jpegimage_release;
    This->data = NULL;
}

DJpegimage* d_new_jpegimage(void) {
    DJpegimage *This = malloc(sizeof (DJpegimage));
    if (This == NULL) {
        printf("\nAttempt to allocate DJpegimage failed.\n");
        exit(1);
    }
    if (!This) return NULL;
    d_jpegimage_init(This);
    This->free = d_jpegimage_free;
    return This;
}

void d_jpegimage_print(DJpegimage *This) {
    printf("jpegimage{size:(%i,%i)}\n", This->data->cols,This->data->rows);
}

void d_jpegimage_free(DJpegimage *This) {
    d_jpegimage_release(This);
    free(This);
}

void d_jpegimage_release(DJpegimage *This) {
    if (This->data != NULL) cvReleaseMat(&(This->data));
}

void d_jpegimage_compress(DJpegimage *This, DImage *image){
    d_jpegimage_release(This);
    int jpeg_params[] = {CV_IMWRITE_JPEG_QUALITY, 80, 0};
    This->data = cvEncodeImage(".jpeg", image->get_ipl(image), jpeg_params);
    //This->data = cvEncodeImage(".jpeg", image->get_ipl(image), NULL);
}

CvMat* d_jpegimage_get_data(DJpegimage *This){
    return This->data;
}