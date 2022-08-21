#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED
#include "service_liaison.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>


#define RX_SIZE         4096    /* taille tampon d'entrée  */
#define TX_SIZE         4096    /* taille tampon de sortie */
#define MAX_WAIT_READ   5000    /* temps max d'attente pour lecture (en ms) */

typedef char chaine[200];

// lecture de 100 octets
void LireSeq(FILE* f,char *buf);


void sleep (int seconde);

/*Fonction sleep*/
int Menu(chaine *tab,int nb,int pos_x,int pos_y,int couleur_text,int couleur_fond,int couleur_fond_extr);

void cadre(int x,int y,int L,int l);
char * bin(char lettre);
void underline(int l);

BOOL OpenCOM(int nId);

BOOL CloseCOM();


BOOL ReadCOM(void* buffer, int nBytesToRead, int* pBytesRead);


BOOL WriteCOM(void* buffer, int nBytesToWrite, int* pBytesWritten);

float random();

#endif // STRUCTURE_H_INCLUDED


