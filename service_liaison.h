#ifndef SERVICE_LIAISON_H_INCLUDED
#define SERVICE_LIAISON_H_INCLUDED
#include "couche_liaison.h"

///mode non connecté
/* Primitive pour transférer une unité de données */
/* Equivalent dans le monde OSI : L_UNIT_DATA.req */
void emettre_sur_liaison(int nbsequence,int fcs,char* adr_src, char* adr_dest, char* msg, int lg_msg);


/* Primitive pour récupérer une unité de données */
/* Equivalent dans le monde OSI : L_UNIT_DATA.ind */
/* Valeur de retour : taille du message */
int recevoir_de_liaison(int *nbsequence,int *fcs,char* adr_src, char* adr_dest, char* msg);


void emettre_sur_liaison_ctrl_flux(int nbsequence,int fcs,char* adr_src, char* adr_dest, char* msg, int lg_msg);


int recevoir_de_liaison_ctrl_flux(int *nbsequence,int *fcs,char* adr_src, char* adr_dest, char* msg);



int recevoir_de_liaison_PAR(int *nbsequence,char *fcs,char* adr_src, char* adr_dest, char* msg);

void emettre_sur_liaison_PAR(int *nbsequence,char fcs,char* adr_src, char* adr_dest, char* msg, int lg_msg);

/// mode connecté

/* Primitive de demande d'établissement d'une connexion */
/* Equivalent dans le monde OSI : L_CONNECT.req et L_CONNECT.conf */
/* Valeur de retour : réponse à la demande de connexion
(1 acceptation, 0 refus) */
int etablir_connexion_liaison(char* adr_src, char* adr_dest);


/* Primitive pour notifier d’une demande de connexion */
/* Equivalent dans le monde OSI : L_CONNECT.ind */
void recevoir_demande_connexion_liaison(char* adr_src, char* adr_dest);


/* Primitive de réponse à la demande de connexion */
/* Equivalent dans le monde OSI : L_CONNECT.resp */
void repondre_demande_connexion_liaison(int reponse);


/* Primitive pour transférer une unité de données au sein d'une connexion */
/* Equivalent dans le monde OSI : L_TX_DATA.req */
void emettre_sur_liaison_connectee(int *nbsequence,char* msg, int lg_msg);



/* Primitive pour récupérer une unité de données au sein d'une connexion */
/* Equivalent dans le monde OSI : L_TX_DATA.ind */
/* Valeur de retour : taille du message */
int recevoir_de_liaison_connectee(int *nbsequence,char* msg);



/* Primitive pour mettre fin à une connexion */
/* Equivalent dans le monde OSI : L_DISCONNECT.req */
void terminer_connexion_liaison();



/* Primitive de notification d'une fermeture de connexion */
/* Equivalent dans le monde OSI : L_DISCONNECT.ind */
void recevoir_terminaison_connexion_liaison();




///annexe///////////////////


/* Initialisation simple pour tests en local
* Paramètres : proba_perte taux de pertes (entre 0 et 1)
* proba_erreur taux d'erreurs (entre 0 et 1)
* reception vaut 1 pour récepteur (sinon émetteur) */
void initialisation_simple(float proba_perte, float proba_erreur, int recept);



/* Initialisation pour tests en distribué (émetteur et récepteur sur machines distinctes)
* Paramètres : proba_perte taux de pertes (entre 0 et 1)
* proba_erreur taux d'erreurs (entre 0 et 1)
* autres paramètres réseau, cf. votre enseignant de TP */
void initialisation(float proba_perte, float proba_erreur, unsigned short port_local,
                    char* destination, unsigned short port_destination);







///couche physique

/* Attend un évènement
* Retourne 0 si une trame reçue est disponible
* un numéro de timer si un timeout a été généré */
int attendre();

/* Démarre le timer numéro n (0 < n < 100) qui s'arrête
* après ms millisecondes (ms doit être un multiple de 100) */
void depart_compteur(int n, int ms);

/* Arrête le timer numéro n */
void arreter_compteur(int n);


#endif // SERVICE_LIAISON_H_INCLUDED
