#include "Primitives.h"

int main()
{


    int chno=1;
    int nId1;
    char src[1];
    char dest[1];
    char buff[100];
    FILE *f;
    chaine tab []= {"[1]-Liaison non connectee, non fiable",
                    "[2]-Liaison avec arret et attente  ",
                    "[3]-Liaison non connectee, fiable",
                    "[4]-Liaison connectee, fiable",
                    "[5]-Quitter"
                   } ;

    printf("\n\n\nEntrez le numero du port COM utilse dans la transmission: ");
    scanf("%d", &nId1);

    /* tentative d'ouverture */
    printf("Ouverture et configuration du port COM%d...\n", nId1);
    Sleep(1000);
    if(!OpenCOM(nId1)) return -1;
    while(1)
    {




        int nmseq=0;

        switch(Menu(tab,4,15,8,15,9,0))
        {

        case 1 :
            clrscr();
            printf("(1)-Transmision de donnees\n");
            printf("(2)-Reception de donnees\n");
            printf("Votre choix:");
            scanf("%d",&chno);

            switch(chno)
            {
            case 1:
                f=fopen("fichier.txt","r");
                if(nId1==1)
                {
                    src[0]=1;
                    dest[0]=2;
                }
                if(nId1==2)
                {
                    src[0]=2;
                    dest[0]=1;
                }


                //gets(buff);
                while(!feof(f))
                {
                    fflush(stdin);

                    LireSeq(f,buff);

                    emettre_sur_liaison(0,0,src,dest,buff,strlen(buff));
                    // printf("%s",buff);
                }
                emettre_sur_liaison(0,0,src,dest,"'arrete'",strlen("'arrete'"));
                fclose(f);



                break;
            case 2:
                if(nId1==1)
                {
                    src[0]=1;
                    dest[0]=2;
                }
                if(nId1==2)
                {
                    src[0]=2;
                    dest[0]=1;
                }
                FILE *f=fopen("recept.txt","w");
                fflush(stdin);
                while(recevoir_de_liaison(0,0,src,dest,buff))
                {
                    fputs(buff,f);
                    fflush(stdin);

                }

                fclose(f);


                break;
            }
            break;

///--------------------------------------------------------------------


        case 2 :
            clrscr();
            if(nId1==1)
            {
                src[0]=1;
                dest[0]=2;
            }
            if(nId1==2)
            {
                src[0]=2;
                dest[0]=1;
            }
            printf("(1)-Transmision de donnees\n");
            printf("(2)-Reception de donnees\n");
            scanf("%d",&chno);
            clrscr();
            switch(chno)
            {
            case 1 :

                f=fopen("fichier.txt","r");



                char *buff=malloc(sizeof(char)*100);

                fflush(stdin);

                while(!feof(f) )
                {

                    // attente
                    while(recevoir_de_liaison(&nmseq,CON_REQ ,src,dest,buff)==2)
                    {
                        printf("\n attente de reception");
                    }



                    fflush(stdin);
                    LireSeq(f,buff);

                    emettre_sur_liaison_ctrl_flux(0,CON_REQ ,src,dest,buff,strlen(buff));

                }

                // envoi d'un signal de STOP
                emettre_sur_liaison_ctrl_flux(0,CON_REQ ,src,dest,"'arrete'",strlen("'arrete'"));
                fclose(f);


                break;

            case 2 :

                if(nId1==1)
                {
                    src[0]=1;
                    dest[0]=2;
                }
                if(nId1==2)
                {
                    src[0]=2;
                    dest[0]=1;
                }

                /* if(recevoir_de_liaison_ctrl_flux(src,dest,buff)>0)
                 printf("%s\n",buff);*/
                char *buff1=malloc(sizeof(char)*100);
                FILE *f=fopen("recept.txt","w");
                fflush(stdin);

                nmseq=1; /// nb de trames reçus
                // Signaler pret pour reception
                emettre_sur_liaison(0,CON_REQ ,src,dest,"CDT",strlen("CDT"));
                fflush(stdin);
                while(recevoir_de_liaison_ctrl_flux(&nmseq,CON_REQ ,src,dest,buff1)>0)
                {
                    fputs(buff1,f);
                    nmseq++;
                    fflush(stdin);
                }
                fclose(f);



                break;


            }

            break;
///---------------------------------------------------------
        case 3 :
            clrscr();
            if(nId1==1)
            {
                src[0]=1;
                dest[0]=2;
            }
            if(nId1==2)
            {
                src[0]=2;
                dest[0]=1;
            }
            printf("(1)-Transmision de donnees\n");
            printf("(2)-Reception de donnees\n");

            scanf("%d",&chno);
            char *bef=malloc(sizeof(char)*100);
            switch(chno)
            {

            case 1:
                f=fopen("fichier.txt","r");

                int nbseq1=0;

                bef[0]='\0';
                fflush(stdin);
                while(!feof(f) )
                {
                    fflush(stdin);
                    LireSeq(f,bef);
                    // printf("bef : %s\n",bef);
                    emettre_sur_liaison_PAR(&nbseq1,0,src,dest,bef,strlen(bef));

                }
                emettre_sur_liaison(&nbseq1,0,src,dest,"'arrete'",strlen("'arrete'"));
                fclose(f);

                break;


            case 2 :
                if(nId1==1)
                {
                    src[0]=1;
                    dest[0]=2;
                }
                if(nId1==2)
                {
                    src[0]=2;
                    dest[0]=1;
                }
                int nbseq2=-1;
                /* if(recevoir_de_liaison_ctrl_flux(src,dest,buff)>0)
                 printf("%s\n",buff);*/
                FILE *f=fopen("recept.txt","w");
                fflush(stdin);
                while(recevoir_de_liaison_PAR(&nbseq2,0,src,dest,bef)>0)
                {
                    fputs(bef,f);
                    fflush(stdin);
                }
                fclose(f);

                break;

            }

            break;
///-----------------------------------------------------------
        case 4 :
            clrscr();
            printf("(1)-Transmision de donnees\n");
            printf("(2)-Reception de donnees\n");
            scanf("%d",&chno);
            f=fopen("fichier.txt","r");
            char *bef1=malloc(sizeof(char)*100);
            int nbseq11=0;


            switch(chno)
            {
            case 1 :
                if(nId1==1)
                {
                    src[0]=1;
                    dest[0]=2;
                }
                if(nId1==2)
                {
                    src[0]=2;
                    dest[0]=1;
                }

                if(etablir_connexion_liaison(NULL,NULL)==1)
                {
                    while(!feof(f))
                    {
                        fflush(stdin);
                        LireSeq(f,bef1);

                        //emettre_sur_liaison_PAR(&nbseq11,0,src,dest,bef1,strlen(bef1));
                        emettre_sur_liaison_connectee(&nbseq11,bef1,strlen(bef1));
                    }
                    emettre_sur_liaison(0,NULL,NULL,NULL,"'arrete'",strlen("'arrete'"));
                    terminer_connexion_liaison();
                    fclose(f);
                }
                else
                {
                    emettre_sur_liaison(0,NULL,NULL,NULL,"'arrete'",strlen("'arrete'"));
                }

                break;
            case 2 :
                recevoir_demande_connexion_liaison(NULL,NULL);
                FILE *f=fopen("recept.txt","w");
                int nbseq2=-1;
                while(recevoir_de_liaison_connectee(&nbseq2,bef1))
                {
                    fputs(bef1,f);
                    fflush(stdin);
                }
                recevoir_terminaison_connexion_liaison();
                fclose(f);

                break;

            }
            break;
        }
        printf("\n");
        system("pause");
        system("cls");

    }

}

