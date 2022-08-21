#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "Primitives.h"




///un protocole liaison en mode non connecté, sans contrôle de flux ni contrôle/reprise sur erreurs.

/* Primitive pour transférer une unité de données */
/* Equivalent dans le monde OSI : L_UNIT_DATA.req */
void emettre_sur_liaison(int nbsequence,int fcs,char* adr_src, char* adr_dest, char* msg, int lg_msg)
{


    trame *trame_emmis=malloc(sizeof(trame));

    strcpy(trame_emmis->info,msg);

    trame_emmis->lg_info=lg_msg;
    trame_emmis->num_seq=nbsequence;
    vers_canal(trame_emmis,trame_emmis->info+24);
    free(trame_emmis);

}


/* Primitive pour récupérer une unité de données */
/* Equivalent dans le monde OSI : L_UNIT_DATA.ind */
/* Valeur de retour : taille du message */
int recevoir_de_liaison(int *nbsequence,int *fcs,char* adr_src, char* adr_dest, char* msg)
{

    trame *trame_recept=malloc(sizeof(trame));
    trame_recept->lg_info=0;
    int i= de_canal(trame_recept,trame_recept->lg_info+24);

    nbsequence=trame_recept->num_seq;
    trame_recept->info[trame_recept->lg_info]='\0';

    strcpy(msg,trame_recept->info);
    msg[strlen(trame_recept->info)]='\0';
    free(trame_recept);
    return i;

}



