#include "fonctions.h"

int write_in_queue(RT_QUEUE *msgQueue, void * data, int size);

void envoyer(void * arg) {
    DMessage *msg;
    int err;

    while (1) {
        rt_printf("tenvoyer : Attente d'un message\n");
        if ((err = rt_queue_read(&queueMsgGUI, &msg, sizeof (DMessage), TM_INFINITE)) >= 0) {
            rt_printf("tenvoyer : envoi d'un message au moniteur\n");
            serveur->send(serveur, msg);
            msg->free(msg);
        } else {
            rt_printf("Error msg queue write: %s\n", strerror(-err));
        }
    }
}

void connecter(void * arg) {
    int status;
    DMessage *message;

    rt_printf("tconnect : Debut de l'exécution de tconnect\n");

    while (1) {
        rt_printf("tconnect : Attente du sémarphore semConnecterRobot\n");
        rt_sem_p(&semConnecterRobot, TM_INFINITE);
        rt_printf("tconnect : Ouverture de la communication avec le robot\n");
        status = robot->open_device(robot);

        rt_mutex_acquire(&mutexEtat, TM_INFINITE);
        etatCommRobot = status;
        rt_mutex_release(&mutexEtat);

        if (status == STATUS_OK) {
            status = robot->start_insecurely(robot);
            if (status == STATUS_OK){
                rt_printf("tconnect : Robot démarrer\n");
            }
        }

        message = d_new_message();
        message->put_state(message, status);

        rt_printf("tconnecter : Envoi message\n");
        message->print(message, 100);

        if (write_in_queue(&queueMsgGUI, message, sizeof (DMessage)) < 0) {
            message->free(message);
        }
    }
}

void communiquer(void *arg) {
    DMessage *msg = d_new_message();
    int var1 = 1;
    int num_msg = 0;

    rt_printf("tserver : Début de l'exécution de serveur\n");
    serveur->open(serveur, "8000");
    rt_printf("tserver : Connexion\n");

    rt_mutex_acquire(&mutexEtat, TM_INFINITE);
    etatCommMoniteur = 0;
    rt_mutex_release(&mutexEtat);


    rt_sem_v(&semCamera);

    while (var1 > 0) {
        rt_printf("tserver : Attente d'un message\n");
        var1 = serveur->receive(serveur, msg);
        num_msg++;
        if (var1 > 0) {
            switch (msg->get_type(msg)) {
                case MESSAGE_TYPE_ACTION:
                    rt_printf("tserver : Le message %d reçu est une action\n",
                            num_msg);
                    DAction *action = d_new_action();
                    action->from_message(action, msg);
                    switch (action->get_order(action)) {
                        case ACTION_CONNECT_ROBOT:
                            rt_printf("tserver : Action connecter robot\n");
                            rt_sem_v(&semConnecterRobot);
                            break;
                            //########################## THOMAS ##############################
                        case ACTION_FIND_ARENA :
                            rt_printf("tserver : Action chercher l'arene\n");
                            etatArene = ACTION_FIND_ARENA ;
                            break;
                        case ACTION_ARENA_FAILED :
                            rt_printf("tserver : Action de non acceptation de l'arene\n");
                            etatArene = ACTION_ARENA_FAILED ;
                            break;
                        case ACTION_ARENA_IS_FOUND :
                            rt_printf("tserver : Action d'acceptation de l'arene\n");
                            etatArene = ACTION_ARENA_IS_FOUND ;
                            break;
                        case ACTION_COMPUTE_CONTINUOUSLY_POSITION :
                            rt_printf("tserver : Calcul de position du robot en continue\n");
                            rt_sem_v(&semCalculPosition);
                            break;
                        case ACTION_STOP_COMPUTE_POSITION:
                            rt_printf("tserver : Arret du calcul de position du robot en continue\n");
                            rt_sem_p(&semCalibration,TM_INFINITE);
                            break;
                            //################################################################
                    }
                    break;
                case MESSAGE_TYPE_MOVEMENT:
                    rt_printf("tserver : Le message reçu %d est un mouvement\n",
                            num_msg);
                    rt_mutex_acquire(&mutexMove, TM_INFINITE);
                    move->from_message(move, msg);
                    move->print(move);
                    rt_mutex_release(&mutexMove);
                    break;
            }
        } else {
	        rt_sem_p(&semDeplacerRobot,TM_INFINITE);
	        rt_sem_p(&semWatchdog,TM_INFINITE);
       		rt_sem_p(&semCamera,TM_INFINITE);
        	rt_sem_p(&semCalibration,TM_INFINITE);
        	rt_sem_p(&semCalculPosition,TM_INFINITE);
			printf("Tous les threads du robots sont bloqués\n") ; 
   			rt_mutex_acquire(&mutexEtat, TM_INFINITE);
		    etatCommMoniteur = 1;
        	rt_mutex_release(&mutexEtat);
			printf("Etat communication moniteur à 1\n") ; 
			
		    rt_printf("tserver : Début de l'exécution de serveur\n");
    		serveur->open(serveur, "8000");
    		rt_printf("tserver : Re-Connexion\n");

    		rt_mutex_acquire(&mutexEtat, TM_INFINITE);
    		etatCommMoniteur = 0;
    		rt_mutex_release(&mutexEtat);
			var1=1 ; 
	        rt_sem_v(&semDeplacerRobot);
	        rt_sem_v(&semWatchdog);
       		rt_sem_v(&semCamera);
        	rt_sem_v(&semCalibration);
        	rt_sem_v(&semCalculPosition);
		}
    }
}

void deplacer(void *arg) {
    int status = 1;
    int gauche;
    int droite;
    DMessage *message;
    
    int compteurmessage;

    rt_printf("tmove : Debut de l'éxecution de periodique à 1s\n");
    rt_task_set_periodic(NULL, TM_NOW, 1000000000);
	

	rt_sem_v(&semDeplacerRobot);
    while (1) {

        if(compteurmessage>1000){
            rt_printf("Connexion lost due to too many lost messages");
            message = d_new_message();
            rt_mutex_acquire(&mutexEtat, TM_INFINITE);
            etatCommRobot=0;
            rt_mutex_release(&mutexEtat);
            message->put_state(message, status);
            break;
        }

        /* Attente de l'activation périodique */

		

        rt_task_wait_period(NULL);
        rt_printf("tmove : Activation périodique\n");



		//Semaphore bloquant si connexion perdue 
        rt_sem_p(&semDeplacerRobot,TM_INFINITE);

        rt_mutex_acquire(&mutexEtat, TM_INFINITE);
        status = etatCommRobot;
        rt_mutex_release(&mutexEtat);

        if (status == STATUS_OK) {
            rt_mutex_acquire(&mutexMove, TM_INFINITE);
            switch (move->get_direction(move)) {
                case DIRECTION_FORWARD:
                    gauche = MOTEUR_ARRIERE_LENT;
                    droite = MOTEUR_ARRIERE_LENT;
                    break;
                case DIRECTION_LEFT:
                    gauche = MOTEUR_ARRIERE_LENT;
                    droite = MOTEUR_AVANT_LENT;
                    break;
                case DIRECTION_RIGHT:
                    gauche = MOTEUR_AVANT_LENT;
                    droite = MOTEUR_ARRIERE_LENT;
                    break;
                case DIRECTION_STOP:
                    gauche = MOTEUR_STOP;
                    droite = MOTEUR_STOP;
                    break;
                case DIRECTION_STRAIGHT:
                    gauche = MOTEUR_AVANT_LENT;
                    droite = MOTEUR_AVANT_LENT;
                    break;
            }
            rt_mutex_release(&mutexMove);

            status = robot->set_motors(robot, gauche, droite);

            if (status != STATUS_OK) {
                rt_mutex_acquire(&mutexEtat, TM_INFINITE);
                etatCommRobot = status;
                rt_mutex_release(&mutexEtat);

                message = d_new_message();
                message->put_state(message, status);

                rt_printf("tmove : Envoi message\n");
                if (write_in_queue(&queueMsgGUI, message, sizeof (DMessage)) < 0) {
                    message->free(message);
                    compteurmessage=0; //Message reçue donc remise à zéro du compteur de messages perdus
                }
                else{
                    compteurmessage++;
                    rt_printf("Message lost ! %d messages lost", compteurmessage);
                }
            }
        }

        rt_sem_v(&semDeplacerRobot);
    }
}

int write_in_queue(RT_QUEUE *msgQueue, void * data, int size) {
    void *msg;
    int err;

    msg = rt_queue_alloc(msgQueue, size);
    memcpy(msg, &data, size);

    if ((err = rt_queue_send(msgQueue, msg, sizeof (DMessage), Q_NORMAL)) < 0) {
        rt_printf("Error msg queue send: %s\n", strerror(-err));
    }
    rt_queue_free(&queueMsgGUI, msg);

    return err;
}






void watchdog(void *arg){
	rt_printf("twatchdog : Debut de l'éxecution de periodique à 250ms\n");
    rt_task_set_periodic(NULL, TM_NOW, 250000000);
    rt_sem_v(&semWatchdog);
	while(1){
		rt_printf("watchdog\n");
		rt_task_wait_period(NULL);
        rt_printf("twatchdog : Activation périodique\n");

		//Semaphore bloquant si connexion perdue 
        rt_sem_p(&semWatchdog,TM_INFINITE);

        rt_sem_v(&semWatchdog);
	}
}

void camera(void *arg){
	int status = 1;
	DMessage *message;
    rt_sem_p(&semCamera,TM_INFINITE);
	cam->open(cam); //connexion usb qui marche forcèment donc pas

	rt_printf("tcamera : Debut de l'éxecution de periodique à 600ms\n");
    rt_task_set_periodic(NULL, TM_NOW, 1000000000);
    rt_sem_v(&semCamera);
    
    rt_mutex_acquire(&mutexEtat, TM_INFINITE);
    status=etatCommMoniteur;
    rt_mutex_release(&mutexEtat);
    
    if(status!=STATUS_OK){
        printf("coucou\n") ; 
    }
    else{
    
        while(1){
            rt_printf("Je suis dans la caméra\n");
            rt_task_wait_period(NULL);
            rt_printf("tmove : Activation périodique\n");

            //Semaphore bloquant si connexion perdue
            rt_sem_p(&semCamera,TM_INFINITE);
        
            rt_printf("tcamera : Ouverture de la communication avec le robot\n");
            
            //de nécessité de tester si ça a marché
            
            //faire le test de l'arène
            
            //recuperation de l'image
            
            cam->get_frame(cam,image);
            jpegimage->compress(jpegimage,image);
            
            message = d_new_message();
            d_message_put_jpeg_image(message, jpegimage);
            
            rt_printf("Arena_calibration : Envoi de l'image de l'arene au moniteur\n");
            if (write_in_queue(&queueMsgGUI, message, sizeof (DMessage)) < 0) {
                message->free(message);
            }
            rt_sem_v(&semCamera);
        }
    }
}



int
void calibration(void *arg){
	rt_printf("tcalibration : Debut de l'éxecution de periodique à 500ms\n");
    rt_task_set_periodic(NULL, TM_NOW, 500000000);
    rt_sem_v(&semCalibration);
	while(1){
		rt_printf("Je suis dans la calibration\n");
		rt_task_wait_period(NULL);
        rt_printf("tcalibration : Activation périodique\n");
		//Semaphore bloquant si connexion perdue 
        rt_sem_p(&semCalibration,TM_INFINITE);
        
        //########################## THOMAS ########################
        
        //tant qu'on a pas demandé à chercher l'arène on ne fait rien
        while (etatArene!=ACTION_FIND_ARENA){}
        //tant qu'on demande à chercher l'arène on la chercher
        while(etatArene==ACTION_FIND_ARENA){
            //on crée un image de l'arène
            DImage * img_arena=d_new_image();
            cam->get_frame(img_arena);
            
            //on crée une arène à partir de cette image
            DArena * new_arena=d_new_arena();
            new_arena=img_arena->compute_arena_position();
            
            //on dessine l'arene sur l'image de l'arène (ou on doit creer une autre image ?)
            d_imageshop_draw_arena(img_arena,new_arena);
            
            //on convertis l'image en jpeg
            DJpegimage* img_arena_jpeg=d_new_jpegimage();
            img_arena_jpeg->compress(img_arena);
            img_arena->free();
            
            //on envoie l'image jpeg de l'arene au moniteur
            DMessage* message_img_arena=d_new_message();
            message_img_arena->put_jpeg_image(img_arena_jpeg);
            img_arena_jpeg->free();
            
            //on met l'arene en etat d'attente d'acceptation et on attend
            etatArene = ACTION_WAINTING_ARENA ;
            while(etatArene == ACTION_WAINTING_ARENA){}
        }
        
        //si l'utilisateur accepte la nouvelle arene elle devient officielement l'arene
        if (etatArene==ACTION_ARENA_IS_FOUND){
            arena=new_arena;
            new_arena->free();
        }
        else if (etatArene==ACTION_ARENA_FAILED){
            new_arena->free();
        }
        rt_sem_v(&semCalibration);
	}
}

void calculposition(void *arg){
	rt_printf("tcalculposition : Debut de l'éxecution de periodique à 600ms\n");
    rt_task_set_periodic(NULL, TM_NOW, 600000000);
    rt_sem_v(&semCalculPosition);
	while(1){
		rt_printf("Je suis dans le calcul position\n");
		rt_task_wait_period(NULL);
        rt_printf("tcalculposition : Activation périodique\n");

		//Semaphore bloquant si connexion perdue 
        rt_sem_p(&semCalculPosition,TM_INFINITE);

        rt_sem_v(&semCalculPosition);
	}
}




