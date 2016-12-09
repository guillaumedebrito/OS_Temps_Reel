/**
 * \file dserver.c
 * \brief Source de la classe DServer
 * \author P.-E. Hladik
 * \version 0.1
 * \date 01 décembre 2011
 *
 * Implémentation de la classe DServer
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/wait.h>
#include "../headers/dserver.h"
#include "../headers/dtools.h"

#define BACKLOG 10

static void d_server_init(DServer*);
void sigchld_handler(int s);
void *get_in_addr(struct sockaddr *sa);

static void d_server_init(DServer *This) {
    This->print = d_server_print;
    This->close = d_server_close;
    This->is_active = d_server_is_active;
    This->open = d_server_open;
    This->receive = d_server_receive;
    This->send = d_server_send;
    This->socketID = 0;
    This->active = 0;
}

DServer* d_new_server(void) {
    DServer *This = malloc(sizeof (DServer));
    if (This == NULL) {
        printf("\nAttempt to allocate DServer failed.\n");
        exit(1);
    }
    if (!This) return NULL;
    d_server_init(This);
    This->free = d_server_free;
    return This;
}

void d_server_print(DServer *This) {
    printf("server{socketID:%i, active:%i}\n", This->socketID, This->active);
}

void d_server_free(DServer *This) {
    free(This);
}

int d_server_open(DServer *This, char * port) {
    int sockfd; // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    // loop through all the results and bind to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                sizeof (int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    sin_size = sizeof their_addr;
    This->socketID = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
    if (This->socketID == -1) {
        perror("accept");
        exit(1);
    }

    inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *) &their_addr),
            s, sizeof s);

    printf("server: got connection from %s\n", s);

    close(sockfd); // child doesn't need the listener


    This->active = 1;
    return 0;
}

void d_server_close(DServer *This) {
    close(This->socketID);
    This->active = 0;
    printf("Server closed\n");


}

int d_server_send(DServer *This, DMessage *message) {
    int ret;
    size_t nb_sent = 0;
    if (This->active) {
        while (nb_sent < message->get_lenght(message)) {
            ret = send(This->socketID,
                    message->get_data(message) + nb_sent,
                    message->get_lenght(message) - nb_sent,
                    0);

            if (ret == -1) {
                perror("[tcp_client_a::send]");
                return ret;
            }
            nb_sent += ret;
        }
    }
    return nb_sent;
}

int d_server_receive(DServer *This, DMessage *message) {
    char type = 'Z';
    char buf[4];
    char* pData;
    int size = 0;
    int retour = 0;

    printf("Attente d'un message\n");
    retour = recv(This->socketID, &type, 1, 0); /* Lecture du type */
    //printf("retour:%d type:%c\n",retour, type);
    if (retour > 0) {
        retour = recv(This->socketID, buf, 4, 0);
        if (retour > 0) { /* Lecture de la taille des données*/
            size = d_tools_bytes2int(buf);
            pData = (char *) malloc(size);
            retour = recv(This->socketID, pData, size, 0);
            if (retour > 0) {
                //message = d_new_message();
                message->set(message, type, size, pData);
            }
        }
    }

    return retour;
}

int d_server_is_active(DServer *This) {
    return This->active;
}

void sigchld_handler(int s) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

// get sockaddr, IPv4 or IPv6:

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*) sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*) sa)->sin6_addr);
}