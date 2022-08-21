#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "Primitives.h"

float	physique_proba_perte = 0;
/* proba d'erreurs */
float physique_proba_erreur = 0;
int reception;


trame *trame_att;
/// Mode non connecté

//PAR : PAR "Protocole avec Acquittement et Retransmission"

void emettre_sur_liaison_PAR(int *nbsequence,char fcs,char* adr_src, char* adr_dest, char* msg, int lg_msg)
{

    trame *trame_emmis=malloc(sizeof(trame));

    trame_emmis->lg_info=lg_msg;
    trame_emmis->num_seq=*nbsequence;
    int i=0;
    for(i=0; i<lg_msg; i++)
    {
        trame_emmis->info[i]=msg[i];
    }
    trame_emmis->info[lg_msg]='\0';
    trame_emmis->fcs=generer_controle(trame_emmis);

    initialisation_simple(0.5,0.5,1);
    float o1 =random();
    float o2=random();
    if(o1>physique_proba_perte)
    {
        if(o2>=physique_proba_erreur)
        {
            vers_canal(trame_emmis,trame_emmis->lg_info);
        }
        else
        {
            trame_emmis->info[0]=trame_emmis->info[0]+1;
            vers_canal(trame_emmis,trame_emmis->lg_info);
        }

    }

    // printf("%s",msg);
    int u;
moh :

    u=attendre();
    if(u==2)
    {
        printf("\n Aucune reception !!");
        vers_canal(trame_emmis,trame_emmis->lg_info);

        goto moh;
    }
    else
    {
        if(u==1)
        {
            //printf("\njuhygtyf\n");
            *nbsequence=*nbsequence+1;
        }

    }
    free(trame_emmis);
}


/* Primitive pour récupérer une unité de données */
/* Equivalent dans le monde OSI : L_UNIT_DATA.ind */
/* Valeur de retour : taille du message */
int recevoir_de_liaison_PAR(int *nbsequence,char *fcs,char* adr_src, char* adr_dest, char* msg)
{
    trame *trame_recept=malloc(sizeof(trame));

    trame_recept->lg_info=0;
    trame_recept->num_seq=0;
// trame_recept->fcs='\0';
    int i=0;

    initialisation_simple(0,0,1);
    i=de_canal(trame_recept,124);
    initialisation_simple(0.5,0.5,0);
    trame_recept->info[trame_recept->lg_info]='\0';
    int y=0;
    for(y==0; y<trame_recept->lg_info; y++)
    {
        msg[y]=trame_recept->info[y];
    }
    msg[y]='\0';
    if(verifier_controle(trame_recept)==1)
    {
        if(i>0 && i!=2)
        {
            trame *trame_ack=malloc(sizeof(trame));
            trame_ack->info[0]='a';
            trame_ack->info[1]='c';
            trame_ack->info[2]='k';
            trame_ack->lg_info=3;
            if(trame_recept->num_seq==*nbsequence)
            {
                printf("\nTrame deja recue\n");

                if(random()>physique_proba_perte)
                {
                    vers_canal(trame_ack,MAX_Trame);
                }
            }
            else
            {
                *nbsequence=trame_recept->num_seq;
                if(random()>physique_proba_perte)
                {
                    vers_canal(trame_ack,100);
                }
            }
            printf("\n NB de sequence de trames recues : %d\n",*nbsequence);
            free(trame_ack);
// free(trame_att);
            free(trame_recept);
        }
    }
// printf("hadi hia  : %s \n",trame_recept->info);
//printf("\ni= %d\n",i);

    return i;
}

initialisation_simple(float proba_perte, float proba_erreur, int recept)
{
    physique_proba_erreur=proba_perte;
    physique_proba_perte=proba_erreur;
    reception=recept;

}



int attendre()
{
    sleep(2000);
    trame *tr=malloc(sizeof(trame));
    tr->lg_info=0;
    return(de_canal(tr,124));
    free(tr);
}


