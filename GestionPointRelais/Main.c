/*
 * Main.c
 *
 *  Created on: 23 mars 2020
 *      Author: sdklm
 */


/* --- fichiers d'entête --- */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* --- contantes --- */
#define MAX_COLIS 100
#define T_MAX_NOM 20
#define T_MAX_DATE 30
#define T_MAX_TEXTE_TYPE 30
#define NON_TROUVE -1

/* --- type global --- */
struct TColis
    {
      int numero                     ;
      char nomExpediteur[T_MAX_NOM]  ;
      char nomClient[T_MAX_NOM]      ;
      int  statut                    ;
      char dateReception[T_MAX_DATE] ;
      char dateStatut[T_MAX_DATE]    ;
    };

/* --- variables globales --- */
struct TColis TabColis[MAX_COLIS]  ;
int NbColis = 0                    ;

/* --- déclarations préliminaires --- */
void saisie()                                     ;
void affichage_tout()                             ;
void affichage_selon_statut()                     ;
void conv_maj(char ch[])                          ;
void quitter()                                    ;
void interprete_statut(int statut, char texte[])  ;
int recherche_colis(int num_colis)                ;
void lance_recherche()                            ;
void modifier_statut()                            ;

/* =========================== */
/* === programme principal === */
/* =========================== */
int main()
{
 int choix = -1 ;

 while (choix != 0)
 {
    printf("-1- Ajout/Saisie de nouveaux colis\n")         ;
    printf("-2- Affichage de tous les colis\n")            ;
    printf("-3- Rechercher un colis\n")                    ;
    printf("-4- Modifier le statut d’un colis\n")          ;
    printf("-5- Affichage des colis selon leur statut\n")  ;
    printf("-0- Quitter\n")                                ;
    printf("Choix : ")  ;
    scanf("%d",&choix)  ;
    switch(choix)
    {
        case 1 : saisie()                 ;
                 break                    ;
        case 2 : affichage_tout()         ;
                 break                    ;
        case 3 : lance_recherche()        ;
                 break                    ;
        case 4 : modifier_statut()        ;
                 break                    ;
        case 5 : affichage_selon_statut() ;
                 break                    ;
        case 0 : quitter()                ;
                 break                    ;
        default: printf("Choix erroné\n") ;
                 break                    ;
    }
 }
}

/* ----------------------------------------- */
/* --- saisie d'une liste de colis --- */
/* ----------------------------------------- */
void saisie()
{
 struct TColis Colis               ;
 int i = NbColis                   ;

 Colis.numero = 9999  ;
 while (Colis.numero != 0)
 {
   printf("Numero du colis (0 pour terminer) : ")  ;
   scanf("%d", &Colis.numero)                      ;
   if (Colis.numero != 0 )
   {
    printf("Nom de l'expediteur : ")               ;
    scanf("%s", Colis.nomExpediteur)               ;
    conv_maj(Colis.nomExpediteur)                  ;
    printf("Nom du client       : ")               ;
    scanf("%s", Colis.nomClient)                   ;
    conv_maj(Colis.nomClient)                      ;
    Colis.statut=1                                 ;
    printf("Date de reception   : ")               ;
    scanf("%s", Colis.dateReception)               ;
    strcpy(Colis.dateStatut,Colis.dateReception)   ;
    TabColis[i++] = Colis                          ;
   }
 }
 NbColis = i ;
}

/* ----------------------------------------------- */
/* --- interprétation du statut de la TColis --- */
/* ----------------------------------------------- */
void interprete_statut(int statut, char texte[])
{
  switch (statut)
  {
    case 1 : strcpy(texte,"Recu")       ;
             break ;
    case 2 : strcpy(texte,"Retrait")    ;
             break ;
    case 3 : strcpy(texte,"Retourne")   ;
             break ;
    case 4 : strcpy(texte,"Perdu")      ;
             break ;
    default: strcpy(texte,"Inconnu")    ;
             break ;
  }
}

/* --------------------------------------------- */
/* --- affichage_tout de la liste des colis --- */
/* --------------------------------------------- */
void affichage_tout()
{
  struct TColis Colis                 ;
  int i                               ;
  char texte_statut[T_MAX_TEXTE_TYPE] ;

  if (NbColis == 0)
   printf("Aucun colis a afficher\n")  ;
  else
  {
   printf("%5s %-8s %-20s %-20s %-15s %10s\n","Colis","Statut","Expediteur","Client","DateReception","DateStatut");
   for (i = 0 ; i<NbColis ; i++)
   {
     Colis = TabColis[i]                       ;
     interprete_statut(Colis.statut, texte_statut)   ;
     printf("%5d %-8s %-20s %-20s %-15s %10s\n",Colis.numero,texte_statut,Colis.nomExpediteur,Colis.nomClient,Colis.dateReception,Colis.dateStatut);
   }
  }
}

/* ------------------------------------------------------- */
/* --- affichage de la liste des colis selon le statut --- */
/* ------------------------------------------------------- */
void affichage_selon_statut()
{
  struct TColis Colis                 ;
  int i, statut                       ;
  char texte_statut[T_MAX_TEXTE_TYPE] ;

  if (NbColis == 0)
   printf("Aucun colis a afficher\n")  ;
  else
  {
   printf("Entrez un statut pour filtrer l'affichage : ");
   scanf("%d",&statut);
   printf("%5s %-8s %-20s %-20s %-15s %10s\n","Colis","Statut","Expediteur","Client","DateReception","DateStatut");
   for (i = 0 ; i<NbColis ; i++)
   {
     Colis = TabColis[i] ;
     if (statut == Colis.statut)
     {
       interprete_statut(Colis.statut, texte_statut);
       printf("%5d %-8s %-20s %-20s %-15s %10s\n",Colis.numero,texte_statut,Colis.nomExpediteur,Colis.nomClient,Colis.dateReception,Colis.dateStatut);
     }
   }
  }
}


/* --------------- */
/* --- quitter --- */
/* --------------- */
void quitter()
{
    printf("Au revoir\n");
}

/* -------------------------------------------------------------------- */
/* --- outil de conversion en majuscules d'une chaîne de caractères --- */
/* -------------------------------------------------------------------- */
void conv_maj(char ch[])
{
  int i, taille       ;

  taille = strlen(ch) ;
  for (i=0 ; i< taille ; i++)
  {
    ch[i] = toupper(ch[i]) ;
  }
}

/* ---------------------------- */
/* --- recherche d'un colis --- */
/* ---------------------------- */
int recherche_colis(int num_colis)
{
  struct TColis Colis         ;
  int i                       ;
  int num_retour = NON_TROUVE ;


  for (i = 0 ; i<NbColis ; i++)
  {
     Colis = TabColis[i]  ;
     if (num_colis == Colis.numero)
     {
       num_retour = i ;
     }
  }
  return num_retour ;
}

/* ----------------------------------------- */
/* --- procédure de recherche d'un colis --- */
/* ----------------------------------------- */
void lance_recherche()
{
  struct TColis Colis                 ;
  int num, num_retour                 ;
  char texte_statut[T_MAX_TEXTE_TYPE] ;

  printf("Numero du colis a rechercher : ");
  scanf("%d",&num)  ;
  num_retour = recherche_colis(num);
  if (num_retour == NON_TROUVE)
  {
    printf("Aucun colis trouve avec le numero %d\n",num);
  }
  else
  {
   printf("%5s %-8s %-20s %-20s %-15s %10s\n","Colis","Statut","Expediteur","Client","DateReception","DateStatut");
   Colis = TabColis[num_retour]                    ;
   interprete_statut(Colis.statut, texte_statut)   ;
   printf("%5d %-8s %-20s %-20s %-15s %10s\n",Colis.numero,texte_statut,Colis.nomExpediteur,Colis.nomClient,Colis.dateReception,Colis.dateStatut);
  }
}

/* ----------------------------------------- */
/* --- modification du statut d'un colis --- */
/* ----------------------------------------- */
void modifier_statut()
{
  struct TColis Colis                 ;
  int num, num_retour                 ;
  char texte_statut[T_MAX_TEXTE_TYPE] ;

  printf("Numero du colis a modifier    : ");
  scanf("%d",&num)  ;
  num_retour = recherche_colis(num);
  if (num_retour == NON_TROUVE)
  {
    printf("Aucun colis trouve avec le numero %d\n",num);
  }
  else
  {
   printf("%5s %-8s %-20s %-20s %-15s %10s\n","Colis","Statut","Expediteur","Client","DateReception","DateStatut");
   Colis = TabColis[num_retour]                    ;
   interprete_statut(Colis.statut, texte_statut)   ;
   printf("%5d %-8s %-20s %-20s %-15s %10s\n",Colis.numero,texte_statut,Colis.nomExpediteur,Colis.nomClient,Colis.dateReception,Colis.dateStatut);

   printf("Nouveau statut (1, 2, 3 ou 4) : ")                  ;
   scanf("%d",&Colis.statut)                                   ;
   interprete_statut(Colis.statut, texte_statut)               ;
   printf("Nouveau statut                : %s\n",texte_statut) ;
   printf("Date du statut                : ")                  ;
   scanf("%s",Colis.dateStatut)                                ;
   printf("Résultat de la modification   : \n")                ;
   printf("%5d %-8s %-20s %-20s %-15s %10s\n",Colis.numero,texte_statut,Colis.nomExpediteur,Colis.nomClient,Colis.dateReception,Colis.dateStatut);

   /* On met à jour le tableau avec les modifications apportées */
   TabColis[num_retour] = Colis                                ;

  }
}
