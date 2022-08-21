#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "Primitives.h"
#include "conio2.h"
#include "conio.c"


HANDLE g_hCOM = NULL;
/* Délais d'attente sur le port COM */
COMMTIMEOUTS g_cto =
{
    MAX_WAIT_READ,  /* ReadIntervalTimeOut          */
    0,              /* ReadTotalTimeOutMultiplier   */
    MAX_WAIT_READ,  /* ReadTotalTimeOutConstant     */
    0,              /* WriteTotalTimeOutMultiplier  */
    0               /* WriteTotalTimeOutConstant    */
};

/* Configuration du port COM */
DCB g_dcb =
{
    sizeof(DCB),        /* DCBlength            */
    75,               /* BaudRate             */
    TRUE,               /* fBinary              */
    FALSE,              /* fParity              */
    FALSE,              /* fOutxCtsFlow         */
    FALSE,              /* fOutxDsrFlow         */
    DTR_CONTROL_ENABLE, /* fDtrControl          */
    FALSE,              /* fDsrSensitivity      */
    FALSE,              /* fTXContinueOnXoff    */
    FALSE,              /* fOutX                */
    FALSE,              /* fInX                 */
    FALSE,              /* fErrorChar           */
    FALSE,              /* fNull                */
    RTS_CONTROL_ENABLE, /* fRtsControl          */
    FALSE,              /* fAbortOnError        */
    0,                  /* fDummy2              */
    0,                  /* wReserved            */
    0x100,              /* XonLim               */
    0x100,              /* XoffLim              */
    8,                  /* ByteSize             */
    NOPARITY,           /* Parity               */
    ONESTOPBIT,         /* StopBits             */
    0x11,               /* XonChar              */
    0x13,               /* XoffChar             */
    '?',                /* ErrorChar            */
    0x1A,               /* EofChar              */
    0x10                /* EvtChar              */
};


void LireSeq(FILE* f,char *buf)
{
    int i=0;
    while((!feof(f))&& (i<100))
    {
        buf[i]=fgetc(f);
        i++;
    }
    buf[i]='\0';
}



void sleep (int seconde)

{
    seconde=seconde/1000;
    int current_time_init = time(NULL);

    int current_time = time(NULL);

    while (current_time <= (current_time_init + seconde))

    {

        current_time = time(NULL);

    }

}


char *bin(char lettre)
{
    int dec=lettre;
    printf("%d",dec);
    char bin[8];
    bin[0]='\0';

    int j=0;
    while(dec>0)
    {
        if(dec%2==1)
        {
            bin[j]='1';

        }
        else
        {
            bin[j]='0';
        }

        j++;
        dec=dec/2;
    }
    bin[j]='\0';
    char binss[8];
    binss[0]='\0';
    int z=0;
    for(z=strlen(bin)-1; z>=0; z--)
    {
        binss[strlen(bin)-1-z]=bin[z];
    }
    binss[7]='\0';
    printf("%s",binss);
    // return binss;
}



float random()
{

    float nombre_aleatoire = 0;
    srand(time(NULL)); // initialisation de rand

    nombre_aleatoire = (float)(rand()%100)/100;
    //printf("%f ",nombre_aleatoire);

    return (float)nombre_aleatoire;
}
int Menu(chaine *tab,int nb,int pos_x,int pos_y,int couleur_text,int couleur_fond,int couleur_fond_extr)
//générer un style de Menu rempli avec des choix dans tab(de chaines)
{

    clrscr();
    textcolor(couleur_text);
    int i=0,fin=0,j=1;
    char ch;
    printf("\n\n");
    //title("Menu Principal");
    textbackground(BLACK);
    cadre(10,4,50,10);  ///Pour les parametres de la console courante .
    textcolor(LIGHTBLUE);
    cputsxy(25,4,"SIMULATION COUCHE LAISON");
    gotoxy(25,5);
    underline(strlen("SIMULATION COUCHE LAISON"));
    gotoxy(pos_x,pos_y);
    textcolor(LIGHTRED);
    printf("%c",16);
    textcolor(couleur_text);
    printf("  ");
    textbackground(couleur_fond);
    printf("%s",tab[0]);
    textbackground(couleur_fond_extr);

    for(i=1; i<nb; i++)
    {
        gotoxy(pos_x,i+pos_y);
        printf("%s\n",tab[i]);
    }
    while(!fin)
    {
        ch=getch();

        if((int)ch ==13)
        {
            fin=1;   //Fin de parcour
        }

        else if((int)ch==80)        //Direction Bas
        {
            j=j%nb;
            j++;
            clrscr();
            textbackground(couleur_fond_extr);
            printf("\n\n");
            cadre(10,4,50,10);   ///Pour les parametres de la console courante .
            textcolor(LIGHTBLUE);
            cputsxy(25,4,"SIMULATION COUCHE LAISON");
            gotoxy(25,5);
            underline(strlen("SIMULATION COUCHE LAISON"));
            //title("Menu Principal");
            gotoxy(pos_x,pos_y);
            textcolor(LIGHTRED);
            printf("%c",16);
            textcolor(couleur_text);
            for(i=0; i<nb; i++)
            {
                gotoxy(pos_x,i+pos_y);
                printf("%s\n",tab[i]);
            }
            gotoxy(pos_x,j+pos_y-1);
            textcolor(LIGHTRED);
            printf("%c",16);
            textcolor(couleur_text);
            printf("  ");
            textbackground(couleur_fond);
            printf("%s",tab[j-1]);
            textbackground(couleur_fond_extr);
        }
        else if((int)ch==72)        //Direction Haut
        {
            j--;
            if(j<=0)
            {
                j=nb;
            }
            clrscr();

            //title("Menu Principal");
            cadre(10,4,50,10);  ///Pour les parametres de la console courante .
            textcolor(LIGHTBLUE);
            cputsxy(25,4,"SIMULATION COUCHE LAISON");
            gotoxy(25,5);
            underline(strlen("SIMULATION COUCHE LAISON"));
            textcolor(WHITE);
            textbackground(couleur_fond_extr);
            gotoxy(pos_x,pos_y);
            for(i=0; i<nb; i++)
            {
                gotoxy(pos_x,i+pos_y);

                printf("%s\n",tab[i]);
            }
            gotoxy(pos_x,j+pos_y-1);
            textcolor(LIGHTRED);
            printf("%c",16);
            textcolor(couleur_text);
            printf("  ");
            textbackground(couleur_fond);
            printf("%s",tab[j-1]);
            textbackground(couleur_fond_extr);
        }
    }
    gotoxy(5,20);
    return j;
}
void cadre(int x,int y,int L,int l)
{
    int i;
    textcolor(LIGHTBLUE);
    gotoxy(x,y);
    printf("%c",201);
    for (i=1; i<L; i++) printf("%c",205); // ----
    printf("%c",187);
    for (i=1; i<l; i++)
    {
        gotoxy(x,y+i);    // |....
        printf("%c",186);
    }
    gotoxy(x+L,y+1);
    for (i=1; i<=l; i++)
    {
        printf("%c",186);    //     ....|
        gotoxy(x+L,y+i);
    }

    gotoxy(x,y+l);
    printf("%c",200);
    for (i=1; i<L; i++)   printf("%c",205);
//gotoxy(x+L,l);
    printf("%c",188);

}
void underline(int l)  // longueur de la chaine (strlen)
{
    int i;
    for(i=0; i<l; i++)printf("%c",196);
}
///--------------------------------------------------
int vers_canal(trame *tram,int taille)
{
    int nBytesWritten=0;
    //printf("ldkahal  :%s\n" ,tram->info) ;
    tram->info[tram->lg_info]='\0';

    if(WriteCOM(tram, 124, &nBytesWritten))
    {

        if(strcmp(tram->info,"CDT")==0 ) printf("\n une notification CDT a ete envoyee ");
        if( strcmp(tram->info,"ACK")==0)printf("\n une notification ACK a ete envoyee ");



        else
        {
            if (strcmp(tram->info,"'arrete'")==0)

                printf("\nune notification de fin de transmission a ete envoyee");

            else       printf("\n donnees envoyees :\n %s",tram->info);
        }


    }
    else printf("Erreur lors de l'envoi.\r\n");
}



int de_canal(trame *tram,int taille)
{
    int nBytesReaden=0;

    tram->info[0]='\0';
    if(ReadCOM(tram, 124, &nBytesReaden))
    {
        //  tram->info[nBytesReaden]='\0';
        tram->info[tram->lg_info]='\0';

        if(strcmp(tram->info,"'arrete'")==0 )
        {
            return 0; /// signal de fin
        }
        else if(nBytesReaden==0)
        {
            // printf("////////\n");
            return 2; /// rien n'est Lu
        }
        else
        {
            if(strcmp(tram->info,"CDT")!=0)
            {
                printf("\n CDT de liaison recue .\n");
                //printf("\n%s\n",tram->info);
            }

            return 1;
        }

    }
    else return 0;
    // printf("Erreur lors de reception.\r\n");




}
/*Fonction permettant de renvoyer un caractère special représentant les données d'une trame*/

char generer_controle(trame *tram)
{
    char c='\0';
    int i;
    for(i=0 ; i<tram->lg_info; i++) c = c ^ tram->info[i];
    return c;
}


int verifier_controle(trame *tram)
{
    char c='\0';
    c = generer_controle(tram);

    // printf("fcs  = %c\n",tram->fcs);
    if(c == tram->fcs) return 1;
    else return 0;
}



void depart_compteur(int n, int ms)
{

    if (n < 1 || n > NB_COMPTEUR)
    {
        printf("Le numero de compteur (%d) n'existe pas\n",n);
        return;
    }

}

/* Arrête le timer numéro n */
void arreter_compteur(int n)
{


}
BOOL OpenCOM(int nId)
{
    /* variables locales */
    char szCOM[16];

    /* construction du nom du port, tentative d'ouverture */
    sprintf(szCOM, "COM%d", nId);
    g_hCOM = CreateFile(szCOM, GENERIC_READ|GENERIC_WRITE, 0, NULL,
                        OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, NULL);
    if(g_hCOM == INVALID_HANDLE_VALUE)
    {
        printf("Erreur lors de l'ouverture du port COM%d", nId);
        return FALSE;
    }

    /* affectation taille des tampons d'émission et de réception */
    SetupComm(g_hCOM, RX_SIZE, TX_SIZE);

    /* configuration du port COM */
    if(!SetCommTimeouts(g_hCOM, &g_cto) || !SetCommState(g_hCOM, &g_dcb))
    {
        printf("Erreur lors de la configuration du port COM%d", nId);
        CloseHandle(g_hCOM);
        return FALSE;
    }

    /* on vide les tampons d'émission et de réception, mise à 1 DTR */
    PurgeComm(g_hCOM, PURGE_TXCLEAR|PURGE_RXCLEAR|PURGE_TXABORT|PURGE_RXABORT);
    EscapeCommFunction(g_hCOM, SETDTR);
    return TRUE;
}

BOOL CloseCOM()
{
    /* fermeture du port COM */
    CloseHandle(g_hCOM);
    return TRUE;
}

BOOL ReadCOM(void* buffer, int nBytesToRead, int* pBytesRead)
{
    return ReadFile(g_hCOM, buffer, nBytesToRead, pBytesRead, NULL);
}

BOOL WriteCOM(void* buffer, int nBytesToWrite, int* pBytesWritten)
{
    /* écriture sur le port */
    return WriteFile(g_hCOM, buffer, nBytesToWrite, pBytesWritten, NULL);
}

