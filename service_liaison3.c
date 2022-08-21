#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "Primitives.h"




int etablir_connexion_liaison(char* adr_src, char* adr_dest)
{

    printf("\nEtablissement connection  ....");
    trame *trame_connect = malloc(sizeof(trame));
    trame_connect->Ctrl=0;
    trame_connect->info[0]='\0';
    trame_connect->lg_info=0;
    vers_canal(trame_connect,24);

    free(trame_connect);
    trame *recept_demande_connect = malloc(sizeof(trame));
    recept_demande_connect->lg_info=0;
    while(de_canal(recept_demande_connect,24)==2)
    {

    }
    int i=recept_demande_connect->Ctrl;

    if(i==1)
    {
        printf("\nConnection reussie\n");
    }
    else printf("\nConnection refusee");
    free(recept_demande_connect);
    return i;
}


/* Primitive pour notifier d’une demande de connexion */
/* Equivalent dans le monde OSI : L_CONNECT.ind */
void recevoir_demande_connexion_liaison(char* adr_src, char* adr_dest)
{
    trame *recept_demande_conect=malloc(sizeof(trame));
    recept_demande_conect->lg_info=0;
    de_canal(recept_demande_conect,24);
    int e=0,z=0;
    if(recept_demande_conect->Ctrl==0)
    {
        printf("\n Une machine demande de connection, voulez vous accepter ?: \n");
        printf("1==OUI\n 2==NON \nChoix :  ");
        scanf("%d",&z);
        repondre_demande_connexion_liaison(z);
        free(recept_demande_conect);
    }

}


/* Primitive de réponse à la demande de connexion */
/* Equivalent dans le monde OSI : L_CONNECT.resp */
void repondre_demande_connexion_liaison(int reponse)
{
    trame *repondre_demande_conect=malloc(sizeof(trame));
    repondre_demande_conect->lg_info=0;
    repondre_demande_conect->Ctrl=reponse;
    vers_canal(repondre_demande_conect,24);
    free(repondre_demande_conect);
}


/* Primitive pour transférer une unité de données au sein d'une connexion */
/* Equivalent dans le monde OSI : L_TX_DATA.req */
void emettre_sur_liaison_connectee(int *nbsequence,char* msg, int lg_msg)
{

    emettre_sur_liaison_PAR(nbsequence,NULL,NULL,NULL,msg,lg_msg);

}



/* Primitive pour récupérer une unité de données au sein d'une connexion */
/* Equivalent dans le monde OSI : L_TX_DATA.ind */
/* Valeur de retour : taille du message */
int recevoir_de_liaison_connectee(int *nbsequence,char* msg)
{
    //recevoir_demande_connexion_liaison(NULL,NULL);
    return recevoir_de_liaison_PAR(nbsequence,0,NULL,NULL,msg);
}



/* Primitive pour mettre fin à une connexion */
/* Equivalent dans le monde OSI : L_DISCONNECT.req */
void terminer_connexion_liaison()
{
    printf("\nDconnection en cours .....");
    trame *tram_deconect=malloc(sizeof(trame));
    tram_deconect->Ctrl=3;
    tram_deconect->lg_info=0;
    vers_canal(tram_deconect,24);
    trame *tram_recept_deconect=malloc(sizeof(trame));
    tram_recept_deconect->lg_info=0;
    de_canal(tram_recept_deconect,24);
    sleep(2000);
    if(tram_recept_deconect->Ctrl==3)
    {
        printf("\nDeconnection avec succes\n");
    }
    else
    {
        printf("\nEchec de deconnection\n");
    }
    free(tram_recept_deconect);
}



/* Primitive de notification d'une fermeture de connexion */
/* Equivalent dans le monde OSI : L_DISCONNECT.ind */
void recevoir_terminaison_connexion_liaison()
{
    trame *tram_recept_deconect=malloc(sizeof(trame));
    tram_recept_deconect->lg_info=0;
    de_canal(tram_recept_deconect,24);
    trame *tram_deconect=malloc(sizeof(trame));
    tram_deconect->Ctrl=3;
    tram_deconect->lg_info=0;
    vers_canal(tram_deconect,24);
    free(tram_deconect);
}
