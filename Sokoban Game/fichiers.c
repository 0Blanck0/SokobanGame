#ifndef FICHIER_C
#define FICHIER_C
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "constantes.h"
#include "fichiers.h"

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR])
{
   FILE* fichier = NULL;
   char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0};
   int i = 0, j = 0;

   fichier = fopen("Niveaux.txt", "r");
   if(fichier == NULL)
   {
       fichier = fopen("Niveaux.txt", "w+");
       if(fichier == NULL)
       {
           fprintf(stderr, "Erreur Chargement niveau\n");
           exit(EXIT_FAILURE);
       }
       else
       {
           fprintf(fichier, "111111111111111030001111111101211111111000001111111000300011111121121111111103001111110000001111111111001111111102001111111140031111111111111111");
       }
   }

   fclose(fichier);

   fichier = fopen("Niveaux.txt", "r");
   if(fichier == NULL)
   {
       fprintf(stderr, "Erreur Niveau.txt!\n"),
       exit(EXIT_FAILURE);
   }

   fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);

   for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j])
            {
                case '0':
                    niveau[j][i] = 0;
                    break;
                case '1':
                    niveau[j][i] = 1;
                    break;
                case '2':
                    niveau[j][i] = 2;
                    break;
                case '3':
                    niveau[j][i] = 3;
                    break;
                case '4':
                    niveau[j][i] = 4;
                    break;
            }
        }
    }

    fclose(fichier);
    return 1;

}

int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR])
{
    FILE* fichier = NULL;
    FILE* fichier2 = NULL;
    int i = 0, j = 0;
    char Logs = NULL;

    fichier = fopen("Niveaux.txt", "w");
    if (fichier == NULL)
    {
        fprintf(stderr, "Erreur sauvegarde\n");
        return 0;
    }

    fichier2 = fopen("Logs.txt", "r");
    if(fichier2 == NULL)
    {
        fichier2 = fopen("Logs.txt", "w+");
        if(fichier2 == NULL)
            fprintf(stderr, "Erreur Logs!\n");
        else
            fprintf(fichier2, "Carte de base by nox: [111111111111111030001111111101211111111000001111111000300011111121121111111103001111110000001111111111001111111102001111111140031111111111111111]\n");
    }
    fclose(fichier2);

    fichier2 = fopen("Logs.txt", "a+");
    if(fichier2 == NULL)
        fprintf(stderr, "Erreur auvegarde Logs!\n");
    else
        fprintf(fichier2, "\nCarte édité! [");


    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            fprintf(fichier, "%d", niveau[j][i]);
            if(fichier2 != NULL)
            fprintf(fichier2, "%d", niveau[j][i]);
        }
    }

    fprintf(fichier2, "]\n");

    fclose(fichier);
    fclose(fichier2);
    return 1;
}

void Info()
{
    FILE* fichier = NULL;
    fichier = fopen("InfoJeu.txt", "w+");

    if(fichier == NULL)
    {
        fprintf(stderr, "Erreur Fichier Info!\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fichier, "Bonjour à toi utilisateur!\nCeci est un Sokoban Game, le but est donc de résoudre le casse-tête le plus vite possible (ton temps est chonométré).\nPour démarrer le jeu, appuyez sur 1 (du pavé numérique) sinon vous pouvez créer vos propres niveaux.\n");
    fprintf(fichier, "Sachez qu'un seul niveau peut être stocké à la fois! toute sauvegarde de niveau supprimera le niveau précédent!\n");
    fprintf(fichier, "Pour créer un niveau, appyez sur 2 (toujour sur le pad a chiffre) puis avec les touches 1 à 4 plus les clics de la souris pour placer les diffèrents éléments.\n");
    fprintf(fichier, "Pour sauvegarder un niveau, appuyez sur S.\nEn jeu appuyez sur R pour reset le niveau et appyez à tout moment sur echap pour fermer le jeu.\n");
    fprintf(fichier, "Arriverez vous à placer toutes les caisses à temps?\nBonne chance!\n");
    fprintf(fichier, "\n\nJeu en version beta! Amelioraton en cours...\n");
    fprintf(fichier, "\n\n\nDiscord: https://discord.gg/Fts4pGf\n");

    fclose(fichier);

    system("Start InfoJeu.txt");
}

#endif // FICHIER_C
