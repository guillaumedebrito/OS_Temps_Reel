/**
 * \file dimage.c
 * \brief Source de la classe DImage
 * \author P.-E. Hladik
 * \version 0.1.2
 * \date 10 mai 2012
 *
 * Impl√©mentation de la classe DImage
 * Correction J. Marchand de d_image_polar_conversion, utilisation de atan2
 * Modification 20/02/2013 PEH : calcul du threshold pour la detection de l'arene
 *
 */

#include "../headers/dimage.h"
#include "../headers/dimageshop.h"


static void d_image_init(DImage*);

/**
 * Resize an image according to the public ImageFactor
 */
IplImage * d_image_resize_with_factor(DArena *, IplImage *, int);

/**
 * Filter the image to extract the shape of the robot
 */
IplImage * d_image_hard_filter(IplImage *imgResized,
        int filterThreshold,
        int nbIterDilate,
        int nbIterErode);

/**
 * Find the shape of the robot and compute its gravity center
 */
void d_image_find_ROI(IplImage *imgBinarized,
        CvRect* roi,
        int imageFactor,
        int robotHeihtReference,
        int robotWidthReference,
        float robotFactorReference);

/* Applt the ROi to the source image */
void d_image_apply_ROI(IplImage *imgSrc, CvRect *roi);

/* Filter the (ROI of) source image */
IplImage* d_image_filter_ROI(IplImage *imgSrc,
        int filterThreshold,
        int nbIterDilate,
        int nbIterErode);

/* Find the three spots for the robot's position */
int d_image_find_position_points(IplImage* roiBinarized, CvPoint2D32f spots[3]);

/* compute the mass center of the spots  */
CvPoint2D32f d_image_compute_triangle_mass_center(CvPoint2D32f vertex[3]);

/* Compute tue orientation vector of the robot */
CvPoint2D32f d_image_compute_orientation(CvPoint2D32f vertex[3]);

/* Free the ROI of the image source and recompute the position
 * in the image source reference */
void d_image_free_ROI(IplImage *imgSrc, CvPoint2D32f tmpVecPosition, CvRect roi);

/* Compute the mass center of a contour in space delimited by a rectangular */
CvPoint2D32f d_image_compute_mass_center(CvSeq *c, CvRect *r);

float d_image_polar_conversion(CvPoint2D32f vec);

int d_image_find_shape_area_around_point(CvPoint2D32f pt, CvBox2D *pBox, IplImage* imgBinarized);

static void d_image_init(DImage *This) {
    This->print = d_image_print;
    This->set_ipl = d_image_set_ipl;
    This->get_ipl = d_image_get_ipl;
    This->release = d_image_release;
    This->compute_arena_position = d_image_compute_arena_position;
    This->compute_robot_position = d_image_compute_robot_position;
    This->myiplimg = NULL;
}

DImage* d_new_image(void) {
    DImage *This = malloc(sizeof (DImage));
    if (This == NULL) {
        printf("\nAttempt to allocate DImage failed.\n");
        exit(1);
    }
    if (!This) return NULL;
    d_image_init(This);
    This->free = d_image_free;
    return This;
}

void d_image_print(DImage *This) {
    printf("image{size:(%i,%i)}\n", This->myiplimg->height, This->myiplimg->width);
}

void d_image_free(DImage *This) {
    d_image_release(This);
    free(This);
}

void d_image_release(DImage *This) {
    if (This->myiplimg != NULL) cvReleaseImage(&(This->myiplimg));
}

void d_image_set_ipl(DImage *This, IplImage *image) {
    d_image_release(This);
    This->myiplimg = cvCloneImage(image);
}

IplImage* d_image_get_ipl(DImage *This) {
    return This->myiplimg;
}

DPosition* d_image_compute_robot_position(DImage *This, DArena *arena) {
    CvPoint2D32f tmpVecPosition;
    CvPoint2D32f tmpVecOrientation;

    IplImage *imgSrc;
    IplImage *imgResized;
    IplImage *imgBinarized;
    IplImage *roiBinarized;

    CvRect roi;
    CvRect rectmp;

    CvPoint2D32f spots[3];

    /* Parameters */
    int imageFactor = 2;
    int filterThreshold = 200;
    int nbIterErode = 0;
    int nbIterDilate = 0;

    /* Valeurs pour distinguer le robot des autres √©l√©ments */
    int robotHeihtReference = 38;
    int robotWidthReference = 46;
    float robotFactorReference = 1.2;

    imageFactor = 1;
    filterThreshold = 230;
    nbIterErode = 2;
    nbIterDilate = 3;

    /* Creation de l'image de travail */
    imgSrc = cvCloneImage(This->myiplimg);
    //showIplImage(imgSrc, "Image source");
    //printf("debug1.0.1\n");

    if (arena != NULL) {
        d_tools_cvbox2cvrect(arena->box, &rectmp);
        //printf("arena{x:%f,y:%f,h:%f,w:%f}\n", arena->box.center.x, arena->box.center.y, arena->box.size.height, arena->box.size.width);
        // Recalcul de la position du rectangle
        rectmp.x = arena->box.center.x - arena->box.size.width/2;
        rectmp.y = arena->box.center.y - arena->box.size.height/2;
        //printf("rect{x:%i,y:%i,h:%i,w:%i}\n", rectmp.x, rectmp.y, rectmp.height, rectmp.width);
        cvSetImageROI(imgSrc, rectmp);
    }
    /*Sous √©chantillonage de l'image*/
    imgResized = d_image_resize_with_factor(arena, imgSrc, imageFactor);
    //showIplImage(imgResized, "Image resized");
    //printf("debug1.0.2\n");
    /*Filtre sur l'image*/
    imgBinarized = d_image_hard_filter(imgResized,
            filterThreshold,
            nbIterDilate,
            nbIterErode);
    //showIplImage(imgBinarized, "Image binarized");
    //printf("debug1.0.3\n");
    /* Recherche du ROI*/
    d_image_find_ROI(imgBinarized,
            &roi,
            imageFactor,
            robotHeihtReference,
            robotWidthReference,
            robotFactorReference);
    //printf("ROI{x:%i,y:%i,h:%i,w:%i}\n", roi.x, roi.y, roi.height, roi.width);
    //printf("debug1.0.4\n");
    /* Suppression de l'ancien ROI*/

    if (arena != NULL) {
        d_image_free_ROI(imgSrc, tmpVecPosition, roi);
        //printf("debug1.0.5\n");
        roi.x += rectmp.y ;
        roi.y += rectmp.x ;
        //printf("New ROI{x:%i,y:%i,h:%i,w:%i}\n", roi.x, roi.y, roi.height, roi.width);
    }
    /*Application du ROI sur l'image source*/
    d_image_apply_ROI(imgSrc, &roi);
    //showIplImage(imgSrc, "ROI");
    //printf("debug1.0.6\n");

    filterThreshold = 200;
    nbIterErode = 1;
    nbIterDilate = 1;

    /* Filtrage du ROI */
    roiBinarized = d_image_filter_ROI(imgSrc,
            filterThreshold,
            nbIterDilate,
            nbIterErode);
    //showIplImage(roiBinarized,"ROI binarized");
    //printf("debug1.0.7\n");

    /*Recherche de la position du robot*/
    if (d_image_find_position_points(roiBinarized, spots)) {

        tmpVecPosition = d_image_compute_triangle_mass_center(spots);
        tmpVecOrientation = d_image_compute_orientation(spots);

        DPosition* position = d_new_position();
        position->set(position, roi.x + tmpVecPosition.x, roi.y + tmpVecPosition.y, d_image_polar_conversion(tmpVecOrientation));

        if (imgSrc != NULL) cvReleaseImage(&imgSrc);
        if (imgResized != NULL) cvReleaseImage(&imgResized);
        if (imgBinarized != NULL) cvReleaseImage(&imgBinarized);
        if (roiBinarized != NULL) cvReleaseImage(&roiBinarized);

        return position;
    } else {
        return NULL;
    }

}

DArena* d_image_compute_arena_position(DImage *This) {
    //CvPoint2D32f tmpVecPosition;
    //CvPoint2D32f tmpVecOrientation;

    IplImage *imgSrc;
    IplImage *imgResized;
    IplImage *imgBinarized;

    //CvRect roi;

    //CvPoint2D32f spots[3];

    /* Parameters */
    int imageFactor = 2;
    int filterThreshold = 200;
    int nbIterErode = 0;
    int nbIterDilate = 0;

    imageFactor = 1;
    filterThreshold = 230;
    nbIterErode = 2;
    nbIterDilate = 3;

    DArena *arena = NULL;

    // Copie de travail de l'image
    imgSrc = cvCloneImage(This->myiplimg);
    //showIplImage(imgSrc,"Image Source");
    /// r√©duction de l'image
    imgResized = d_image_resize_with_factor(arena, imgSrc, imageFactor);
    //showIplImage(imgResized, "Image Resized");

    // Calcul du threshold : valeur moyenne sur le centre de l'image
    //cvAddS(imgResized, cvScalar(70, 70,70,70), imgResized, NULL);
    // img is an rgb image
    int y, x;
    float val = 0;
    CvScalar s;

    int large = 15;

    for (y = (imgResized->height) / 2 - large; y < (imgResized->height) / 2 + large; y++) {
        for (x = (imgResized->width) / 2 - large; x < (imgResized->width) / 2 + large; x++) {
            // Note that color images are stored in BGR order
            s = cvGet2D(imgResized, y, x); // get the (i,j) pixel value
            //val += 0.299*s.val[2] + 0.587*s.val[1] + 0.144*s.val[0];
            val += s.val[2] + s.val[1] + s.val[0];
        }
    }
    val = val / (3 * 4 * large * large);
    //printf("val:%f\n", val);
    filterThreshold = val + 50;
    //printf("threshold:%d\n", filterThreshold);

    // Filtrage de l'image de travail

    imgBinarized = d_image_hard_filter(imgResized,
            filterThreshold,
            nbIterDilate,
            nbIterErode);
    //showIplImage(imgBinarized, "Image Binarized");

    CvPoint2D32f pt = cvPoint2D32f((double) imgBinarized->width / 2,
            (double) imgBinarized->height / 2);

    CvBox2D box = {
        {0, 0},
        {0, 0}, 0
    };
    int result = 0;
    result = d_image_find_shape_area_around_point(pt, &box, imgBinarized);

    if (result) {
        box.center.x = box.center.x*imageFactor;
        box.center.y = box.center.y*imageFactor;
        box.size.height = box.size.height*imageFactor;
        box.size.width = box.size.width*imageFactor;

        arena = d_new_arena();
        d_arena_set(arena,
                box.center.x,
                box.center.y,
                box.size.height,
                box.size.width,
                0.0);
    }

    return arena;
}

IplImage * d_image_resize_with_factor(DArena *arena, IplImage *imgSrc, int imageFactor) {
    // declare a destination IplImage object with correct size, depth and channels
    IplImage* img;
    if (arena != NULL) {
        img = cvCreateImage(
                cvSize(
                (int) (arena->get_width(arena) / imageFactor),
                (int) (arena->get_height(arena) / imageFactor)),
                imgSrc->depth,
                imgSrc->nChannels);

    } else {
        img = cvCreateImage(
                cvSize(
                (int) (imgSrc->width / imageFactor),
                (int) (imgSrc->height / imageFactor)),
                imgSrc->depth,
                imgSrc->nChannels);
    }
    //use cvResize to resize source to a destination image
    cvResize(imgSrc, img, CV_INTER_LINEAR);
    return img;
}

IplImage* d_image_hard_filter(IplImage *imgResized,
        int filterThreshold,
        int nbIterDilate,
        int nbIterErode) {
    // create memory storage that will contain all the dynamic data
    IplImage* img = NULL;
    int flip = 0;

    //Initialization

    IplImage *img_nvg_tmp = NULL;
    img_nvg_tmp = cvCreateImage(cvGetSize(imgResized), imgResized->depth, 1);

    img = cvCreateImage(cvGetSize(imgResized), imgResized->depth, 1);
    //cvCloneImage(img_nvg_tmp);

    //Morphology Kernel definition
    IplConvKernel *kernel = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_RECT, NULL);

    //Control the orientation
    if (imgResized->origin != IPL_ORIGIN_TL) {
        flip = CV_CVTIMG_FLIP;
    }

    cvConvertImage(imgResized, img_nvg_tmp, flip);
    //Binarization
    cvThreshold(img_nvg_tmp, img, filterThreshold, 255, CV_THRESH_BINARY);
    //Morphology
    // Morphological opening (inverse because we have white pixels on black background)
    if (nbIterDilate != 0)
        cvDilate(img, img, kernel, nbIterDilate);
    if (nbIterErode != 0)
        cvErode(img, img, kernel, nbIterErode);

    cvReleaseImage(&img_nvg_tmp);
    return img;
}

void d_image_find_ROI(IplImage *imgBinarized,
        CvRect* roi,
        int imageFactor,
        int robotHeihtReference,
        int robotWidthReference,
        float robotFactorReference) {
    int success = 0;
    float h = 0.0;
    float w = 0.0;
    float tmp = 0.0;
    float factor = 0.0;
    float minFactor = 99999.9;
    // create memory storage that will contain all the dynamic data
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* contours;
    CvBox2D pBox;

    cvFindContours(imgBinarized, storage, &contours, sizeof (CvContour),
            CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

    /* recherche de la forme la plus proche du robot */
    for (; contours != 0; contours = contours->h_next) {
        pBox = cvMinAreaRect2(contours, storage);
        /*IplImage *toto = cvCloneImage(imgSrc);
                 drawBox(toto, pBox);
                 showImage(toto, "box");*/
        h = pBox.size.height;
        w = pBox.size.width;
        if ((h != 0) && (w != 0)) {
            if (h > w) {
                tmp = h;
                h = w;
                w = tmp;
            }
            factor = fabs(h - robotHeihtReference) / robotHeihtReference
                    + fabs(w - robotWidthReference) / robotWidthReference
                    + fabs((w / h) - robotFactorReference) / robotFactorReference;

            if (factor < minFactor) {
                minFactor = factor;
                *roi = cvBoundingRect(contours, 1);
                success = 1;
            }
        }
    }
    cvReleaseMemStorage(&storage);

    if (success) {
        /* Increase the ROI to be sure to capture all the robot */
        roi->height = roi->height * imageFactor + 20;
        roi->width = roi->width * imageFactor + 20;
        roi->x = MAX(roi->x * imageFactor - 10, 0);
        roi->y = MAX(roi->y * imageFactor - 10, 0);
        /*IplImage *toto = cvCloneImage(imgSrc);
             drawRec(toto, roi);
             showImage(toto, "ROI");*/
        //printf("x:%d, y:%d, h:%d, w;%d\n", roi.x, roi.y, roi.height, roi.width);
    } else {
        roi->height = 1;
        roi->width = 1;
        roi->x = 0;
        roi->y = 0;
    }
}

void d_image_apply_ROI(IplImage *imgSrc, CvRect *roi) {
    cvSetImageROI(imgSrc, *roi);
}

IplImage * d_image_filter_ROI(IplImage *imgSrc,
        int filterThreshold,
        int nbIterDilate,
        int nbIterErode) {
    // create memory storage that will contain all the dynamic data
    int flip = 0;

    IplImage *img;
    //Initialization
    IplImage *img_nvg_tmp = cvCreateImage(cvGetSize(imgSrc), imgSrc->depth, 1);
    img = cvCloneImage(img_nvg_tmp);

    //Morphology Kernel definition
    IplConvKernel *kernel = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_RECT, NULL);

    //Control the orientation
    if (imgSrc->origin != IPL_ORIGIN_TL) {
        flip = CV_CVTIMG_FLIP;
    }

    cvConvertImage(imgSrc, img_nvg_tmp, flip);

    //Binarization
    cvThreshold(img_nvg_tmp, img, filterThreshold, 255, CV_THRESH_OTSU);


    //TODO: c'est quoi cette histoire de imgBinarized ???
    //Morphology
    // Morphological opening (inverse because we have white pixels on black background)
    if (nbIterDilate != 0)
        cvDilate(img, img, kernel, nbIterDilate);
    if (nbIterErode != 0)
        cvErode(img, img, kernel, nbIterErode);
    cvReleaseImage(&img_nvg_tmp);
    return img;
}

int d_image_find_position_points(IplImage* roiBinarized, CvPoint2D32f spots[3]) {
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq *contour;
    CvSeq *c;
    CvRect pRect;
    //CvPoint pt;
    int cmpt = 0;

    cvFindContours(roiBinarized, storage, &contour, sizeof (CvContour),
            CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

    for (; contour != 0; contour = contour->h_next) {
        if (contour->v_next != 0) {
            c = contour->v_next;
            for (; (c != 0) && (cmpt < 3); c = c->h_next) {
                //Trouver le rect du contour
                pRect = cvBoundingRect(c, 1);
                spots[cmpt] = d_image_compute_mass_center(c, &pRect);
                cmpt++;
            }
        }
    }
    cvReleaseMemStorage(&storage);
    if (cmpt != 3) {
        printf("ERROR spots\n");
        return 0;
    } else {
        return 1;
    }
}

CvPoint2D32f d_image_compute_mass_center(CvSeq *c, CvRect *r) {
    //int isInside = -1;
    CvPoint2D32f pt = cvPoint2D32f(0, 0);
    int x, y;
    float Mx = 0.0;
    float My = 0.0;
    int nbPt = 0;

    for (x = r->x; x < r->x + r->width; x++) {
        for (y = r->y; y < r->y + r->height; y++) {
            pt.x = x;
            pt.y = y;
            if (cvPointPolygonTest(c, pt, 0)) {
                Mx += x;
                My += y;
                nbPt++;
            }
        }
    }
    pt.x = Mx / nbPt;
    pt.y = My / nbPt;

    return pt;
}

CvPoint2D32f d_image_compute_triangle_mass_center(CvPoint2D32f vertex[3]) {
    CvPoint2D32f mc = cvPoint2D32f(0.0, 0.0);

    mc.x = vertex[2].x / 3 + ((vertex[0].x + vertex[1].x) / 3);
    mc.y = vertex[2].y / 3 + ((vertex[0].y + vertex[1].y) / 3);

    return mc;
}

CvPoint2D32f d_image_compute_orientation(CvPoint2D32f vertex[3]) {
    CvPoint2D32f vectorOrientation = cvPoint2D32f(0.0, 0.0);
    float x, y;
    float maxLength = 0.0;
    float length;
    int i, j;
    CvPoint2D32f tmpVertex[3];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            tmpVertex[j] = vertex[(i + j) % 3];
        }
        /* Compute median */
        x = ((tmpVertex[0].x + tmpVertex[1].x) / 2) - tmpVertex[2].x;
        y = ((tmpVertex[0].y + tmpVertex[1].y) / 2) - tmpVertex[2].y;
        /* find longest median */
        length = pow(x, 2) + pow(y, 2);
        if (maxLength < length) {
            maxLength = length;
            vectorOrientation.x = x;
            vectorOrientation.y = y;
        }
    }

    return vectorOrientation;
}

void d_image_free_ROI(IplImage *imgSrc, CvPoint2D32f tmpVecPosition, CvRect roi) {
    cvResetImageROI(imgSrc);
    tmpVecPosition.x += roi.x;
    tmpVecPosition.y += roi.y;
}

float d_image_polar_conversion(CvPoint2D32f vec) {
    /*float orientation = 0;
         if ((vec.x > 0.0) && (vec.y >= 0.0)) {
         orientation = atan(vec.y / vec.x);
         } else if ((vec.x > 0.0) && (vec.y >= 0.0)) {
         orientation = atan(vec.y / vec.x) + 2 * M_PI;
         } else if (vec.x < 0.0) {
         orientation = atan(vec.y / vec.x) + M_PI;
         } else if ((vec.x == 0.0) && (vec.y > 0.0)) {
         orientation = M_PI / 2;
         } else if ((vec.x == 0.0) && (vec.y < 0.0)) {
         orientation = 3 * M_PI / 2;
         }
         return orientation;*/
    return M_PI + atan2(-vec.y, -vec.x);
}

int d_image_find_shape_area_around_point(CvPoint2D32f pt, CvBox2D *pBox, IplImage* imgBinarized) {
    // create memory storage that will contain all the dynamic data
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* contours;
    CvSeq *c;
    //CvPoint2D32f pt = cvPoint2D32f((double)img_bin->width/2, (double)img_bin->height/2);

    cvFindContours(imgBinarized, storage, &contours, sizeof (CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

    c = contours;
    int isInside = -1;

    while ((c != NULL) && (isInside < 0)) {
        //printf("isInside:%d\n", isInside);
        isInside = cvPointPolygonTest(c, pt, 0);
        //printf("isInside:%d\n", isInside);
        if (isInside < 0)
            c = c->h_next;
    }
    if (c != NULL) {
        *pBox = cvMinAreaRect2(c, NULL);

        cvReleaseMemStorage(&storage);
        return 1;
        //*pRect = cvBoundingRect(c, 1);
    } else {
        cvReleaseMemStorage(&storage);
        return 0;
    }
}
