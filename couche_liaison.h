#ifndef COUCHE_LIAISON_H_INCLUDED
#define COUCHE_LIAISON_H_INCLUDED


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define MAX_Trame 100    // taille max d'une trame en octet
#define EMISSION  0
#define RECEPTION 1
/* transfert d'une unité de données */
#define L_UNIT_DATA_req  1
/* notification de la réception d'une unité de données */
#define L_UNIT_DATA_ind  2
#define NB_COMPTEUR   100


/******************
 * Types de Controle *
 ******************/
#define CON_REQ       0  /* demande d'établissement de connexion */
#define CON_ACCEPT    1  /* acceptation de connexion */
#define CON_REFUSE    2  /* refus d'établissement de connexion */
#define CON_CLOSE     3  /* notification de déconnexion */
#define CON_CLOSE_ACK 4  /* accusé de réception de la déconnexion */
#define DATA          5  /* données de l'application */
#define ACK           6  /* accusé de réception des données */
#define OTHER         7  /* extensions */


typedef struct a_char a_char;
struct a_char
{

    char fcs;

};

typedef struct trame trame;
struct trame
{
    char fcs;
    char deb_trame;
    char adr_dst[6];
    char adr_src[6];
    char Ctrl;
    int num_seq;
    int lg_info;
    char info[100];
    char fin_trame;

};





/* Réception d'une trame arrivée (cf. fonction Attendre)
* Paramètres : trame pointeur vers votre structure de données trame
* taille doit être sizeof(trame_t) où trame_t est votre type trame */
int de_canal(trame *tram, int taille);

/* Emission d'une trame (paramètres identiques à DeCanal) */
int vers_canal(trame *tram, int taille);

char generer_controle(trame *tram);


int verifier_controle(trame *tram);

#endif // COUCHE_LIAISON_H_INCLUDED
