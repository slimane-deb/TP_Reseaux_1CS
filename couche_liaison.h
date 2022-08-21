#ifndef COUCHE_LIAISON_H_INCLUDED
#define COUCHE_LIAISON_H_INCLUDED


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define MAX_Trame 100    // taille max d'une trame en octet
#define EMISSION  0
#define RECEPTION 1
/* transfert d'une unit� de donn�es */
#define L_UNIT_DATA_req  1
/* notification de la r�ception d'une unit� de donn�es */
#define L_UNIT_DATA_ind  2
#define NB_COMPTEUR   100


/******************
 * Types de Controle *
 ******************/
#define CON_REQ       0  /* demande d'�tablissement de connexion */
#define CON_ACCEPT    1  /* acceptation de connexion */
#define CON_REFUSE    2  /* refus d'�tablissement de connexion */
#define CON_CLOSE     3  /* notification de d�connexion */
#define CON_CLOSE_ACK 4  /* accus� de r�ception de la d�connexion */
#define DATA          5  /* donn�es de l'application */
#define ACK           6  /* accus� de r�ception des donn�es */
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





/* R�ception d'une trame arriv�e (cf. fonction Attendre)
* Param�tres : trame pointeur vers votre structure de donn�es trame
* taille doit �tre sizeof(trame_t) o� trame_t est votre type trame */
int de_canal(trame *tram, int taille);

/* Emission d'une trame (param�tres identiques � DeCanal) */
int vers_canal(trame *tram, int taille);

char generer_controle(trame *tram);


int verifier_controle(trame *tram);

#endif // COUCHE_LIAISON_H_INCLUDED
