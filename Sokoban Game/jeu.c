#ifndef Jeu_C
#define Jeu_C
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "constantes.h"
#include "jeu.h"
#include "editeur.h"

void jouer(SDL_Surface* Screen)
{
    SDL_Surface* Player = NULL;
    SDL_Surface *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *Victoire = NULL;
    SDL_Rect position, positionJoueur;
    SDL_Event event;
    SDL_Surface *PersoActuel = NULL, *Loose = NULL;

    FILE* TEMPS = NULL;

    SDL_Surface* Perso1 = NULL;
    SDL_Surface* Perso2 = NULL;
    SDL_Surface* Perso3 = NULL;
    SDL_Surface* Perso4 = NULL;

    int Victori = 0;
    int reset = 0;
    int Temp = 0;
    int pause = 0;
    double tempsActuel = 0;
    double tempsEcouler = 0;
    double TempTotal = 0;
    double TempsMax = TEMPSMAX;
    double TempsTchek = 0;
    int nombreSession = 0;
    int caractereLu = 0;

    TEMPS = fopen("Temps.txt", "r");

    if(TEMPS == NULL)
    {
        TEMPS = fopen("Temps.txt", "w+");
        if(TEMPS == NULL)
        {
            fprintf(stderr, "Error porgramme! Impossible de créer le fichier de sauvegarde des scores!\n");
        }
        else
        {
            fprintf(TEMPS, "Temps par session:\n");
        }
    }

    rewind(TEMPS);

    do
    {
        caractereLu = fgetc(TEMPS);
        if (caractereLu == '\n')
            nombreSession++;
    } while(caractereLu != EOF);

    if(nombreSession == 0)
    {
        fprintf(TEMPS, "Temps par session:\n");
        nombreSession = 1;
    }

    fclose(TEMPS);

    TEMPS = fopen("Temps.txt", "a+");

    if(TEMPS == NULL)
    {
        fprintf(stderr, "Erreur programme! impossible de créer la sauvgarde du temps!\n");
        exit(EXIT_FAILURE);
    }

    TempTotal = SDL_GetTicks();

    Victoire = SDL_LoadBMP("Sprit/Decor_Interactio/Victoire.bmp");

    if(Victoire == NULL)
    {
        fprintf(stderr, "Erreur Image Victoire! [%s]\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    mur = SDL_LoadBMP("Sprit/Decor_Interactio/mur.bmp");

    if(mur == NULL)
    {
        fprintf(stderr, "Erreur Image mur [%s]\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    caisse = SDL_LoadBMP("Sprit/Decor_Interactio/caisse.bmp");

    if(caisse == NULL)
    {
        fprintf(stderr, "Erreur Image caisse [%s]\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    caisseOK = SDL_LoadBMP("Sprit/Decor_Interactio/caisse_ok.bmp");

    if(caisseOK == NULL)
    {
        fprintf(stderr, "Erreur Image caisse_ok [%s]\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Loose = SDL_LoadBMP("Sprit/Decor_Interactio/Perdu.bmp");

    if(Loose == NULL)
    {
        fprintf(stderr, "Erreur ecrant de perte! tu croyais pouvoir ne pas perdre? [%s]\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    objectif = SDL_LoadBMP("Sprit/Decor_Interactio/objectif.bmp");

    if(objectif == NULL)
    {
        fprintf(stderr, "Erreur Image objectif [%s]\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    int continuer = 1, ObjectifRestants = 0, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    Perso1 = SDL_LoadBMP("Sprit/Perso/Perso1.bmp");

    if(Perso1 == NULL)
    {
        fprintf(stderr, "Erreur sprit! [%s]\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Perso2 = SDL_LoadBMP("Sprit/Perso/Perso2.bmp");

    if(Perso2 == NULL)
    {
        fprintf(stderr, "Erreur sprit! [%s]\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Perso3 = SDL_LoadBMP("Sprit/Perso/Perso3.bmp");

    if(Perso3 == NULL)
    {
        fprintf(stderr, "Erreur sprit! [%s]\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Perso4 = SDL_LoadBMP("Sprit/Perso/Perso4.bmp");

    if(Perso4 == NULL)
    {
        fprintf(stderr, "Erreur sprit! [%s]\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetColorKey(Perso1, SDL_SRCCOLORKEY, SDL_MapRGB(Perso1->format, 255, 0, 255));
    SDL_SetColorKey(Perso2, SDL_SRCCOLORKEY, SDL_MapRGB(Perso2->format, 255, 0, 255));
    SDL_SetColorKey(Perso3, SDL_SRCCOLORKEY, SDL_MapRGB(Perso3->format, 255, 0, 255));
    SDL_SetColorKey(Perso4, SDL_SRCCOLORKEY, SDL_MapRGB(Perso4->format, 255, 0, 255));
    SDL_SetColorKey(objectif, SDL_SRCCOLORKEY, SDL_MapRGB(objectif->format, 255, 0, 255));

    SDL_BlitSurface(Perso1, NULL, Screen, &positionJoueur);
    SDL_Flip(Screen);

    if(!chargerNiveau(carte))
    {
        fprintf(stderr, "Erreur chargement carte [%s]\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            if (carte[i][j] == PLAYEUR)
            {
                positionJoueur.x = i;
                positionJoueur.y = j;
                carte[i][j] = VIDE;
            }
        }
    }

    SDL_EnableKeyRepeat(100, 100);

    PersoActuel = Perso1;
    continuer = 1;

    while(continuer)
    {
        TempTotal = SDL_GetTicks();
        TempsTchek = SDL_GetTicks();
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    continuer = 0;
                    break;
                case SDLK_UP:
                    deplacerJoueur(carte, &positionJoueur, HAUT);
                    SDL_Flip(Screen);
                    PersoActuel = Perso4;
                    break;
                case SDLK_DOWN:
                    deplacerJoueur(carte, &positionJoueur, BAS);
                    SDL_Flip(Screen);
                    PersoActuel = Perso1;
                    break;
                case SDLK_RIGHT:
                    deplacerJoueur(carte, &positionJoueur, DROITE);
                    SDL_Flip(Screen);
                    PersoActuel = Perso3;
                    break;
                case SDLK_LEFT:
                    deplacerJoueur(carte, &positionJoueur, GAUCHE);
                    SDL_Flip(Screen);
                    PersoActuel = Perso2;
                    break;
                case SDLK_r:
                    reset = 1;
                    continuer = 0;
                    break;

                }
                break;
                TempsTchek = SDL_GetTicks();
            }

            TempsTchek = SDL_GetTicks();
            Temp = Temp + tempsActuel + tempsEcouler;

            if(reset == 0);
            {
                SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
                ObjectifRestants = 0;

                for(i=0;i<NB_BLOCS_LARGEUR;i++)
            {
                for(j=0;j<NB_BLOCS_HAUTEUR;j++)
                {
                    position.x = i * TAILLE_BLOC;
                    position.y = j * TAILLE_BLOC;

                    switch(carte[i][j])
                    {
                    case MUR:
                        SDL_BlitSurface(mur, NULL, Screen, &position);
                        break;
                    case CAISSE:
                        SDL_BlitSurface(caisse, NULL, Screen, &position);
                        break;
                    case CAISSE_OK:
                        SDL_BlitSurface(caisseOK, NULL, Screen, &position);
                        break;
                    case OBJECTIF:
                        ObjectifRestants = 1;
                        SDL_BlitSurface(objectif, NULL, Screen, &position);
                        break;
                    }

                }

            }

            if(!ObjectifRestants)
                continuer = 0;
                Victori = 1;
                position.x = positionJoueur.x * TAILLE_BLOC;
                position.y = positionJoueur.y * TAILLE_BLOC;
                SDL_BlitSurface(PersoActuel, NULL, Screen, &position);
                SDL_Flip(Screen);
            }

            TempsTchek = SDL_GetTicks();
            if((TempsTchek/1000) >= TEMPSMAX)
            {
                Victori = 0;
                reset = 0;
                continuer = 0;
                tempsActuel = 0;
                TempTotal = 0;
            }

        }

            SDL_EnableKeyRepeat(0, 0);
            TempTotal = SDL_GetTicks();

        if(reset == 0)
        {
            if(Victori == 1 && !ObjectifRestants)
            {
                fprintf(TEMPS, "Votre Score a la Session %d était de %f seconde\n", nombreSession, TempTotal/1000);
                position.x = 0;
                position.y = 0;
                SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
                SDL_SetColorKey(Victoire, SDL_SRCCOLORKEY, SDL_MapRGB(Victoire->format, 0, 0, 0));
                SDL_BlitSurface(Victoire, NULL, Screen, &position);
                SDL_Flip(Screen);
                Victori = 0;
                SDL_Delay(1);
            }
            else
            {
                position.x = 0;
                position.y = 0;
                SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0, 0, 0));
                SDL_BlitSurface(Loose, NULL, Screen, &position);
                SDL_Flip(Screen);
                tempsActuel = SDL_GetTicks();
                if(tempsActuel/1000 >= TempsMax)
                    fprintf(TEMPS, "Session %d perdu part temps écouler\n", nombreSession);
                else
                    fprintf(TEMPS, "Session %d perdu/Abandonner // temps jouer %f\n", nombreSession, TempTotal/1000);

                SDL_Delay(1);
            }

            continuer = 1;

            while(continuer)
            {
                SDL_WaitEvent(&event);
                switch(event.type)
                {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_r:
                        continuer = 0;
                        reset = 1;
                        break;
                    }
                    break;
                }
            }
        }
        else
        {
            SDL_EnableKeyRepeat(0, 0);
            position.x = 0;
            position.y = 0;
            SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
            SDL_Flip(Screen);
        }

        if(reset == 1 && Victori == 1)
        {
            SDL_FreeSurface(Perso1);
            SDL_FreeSurface(Perso2);
            SDL_FreeSurface(Perso3);
            SDL_FreeSurface(Perso4);
            SDL_FreeSurface(PersoActuel);

            SDL_FreeSurface(mur);
            SDL_FreeSurface(caisse);
            SDL_FreeSurface(caisseOK);
            SDL_FreeSurface(objectif);
            SDL_FreeSurface(Victoire);
            SDL_FreeSurface(Loose);
            jouer(Screen);
        }

        SDL_FreeSurface(Perso1);
        SDL_FreeSurface(Perso2);
        SDL_FreeSurface(Perso3);
        SDL_FreeSurface(Perso4);
        SDL_FreeSurface(PersoActuel);

        SDL_FreeSurface(mur);
        SDL_FreeSurface(caisse);
        SDL_FreeSurface(caisseOK);
        SDL_FreeSurface(objectif);
        SDL_FreeSurface(Victoire);
        SDL_FreeSurface(Loose);
        fclose(TEMPS);

        if(reset == 1)
        {
            tempsActuel = 0;
            tempsEcouler = 0;
            TempTotal = 0;
            jouer(Screen);
        }
}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction)
{
    switch(direction)
    {
    case HAUT:
        if(pos->y - 1 < 0)
            break;
        if(carte[pos->x][pos->y - 1] == MUR)
            break;
        if((carte[pos->x][pos->y -1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) && (pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR || carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
            break;
        deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);
        pos->y--;
        break;
    case BAS:
        if(pos->y + 1 < 0)
            break;
        if(carte[pos->x][pos->y + 1] == MUR)
            break;
        if((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) && (pos->y + 2 < 0 || carte[pos->x][pos->y + 2] == MUR || carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK))
            break;
        deplacerCaisse(&carte[pos->x][pos->y +1], &carte[pos->x][pos->y + 2]);
        pos->y++;
        break;
    case DROITE:
        if(pos->x + 1 < 0)
            break;
        if(carte[pos->x + 1][pos->y] == MUR)
            break;
        if((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK) && (pos->x + 2 < 0 || carte[pos->x + 2][pos->y] == MUR || carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK))
            break;
        deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);
        pos->x++;
        break;
    case GAUCHE:
        if(pos->x - 1 < 0)
            break;
        if(carte[pos->x - 1][pos->y] == MUR)
            break;
        if((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK) && (pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR || carte[pos->x - 2][pos->y] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK))
            break;
        deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);
        pos->x--;
        break;
    }
}

void deplacerCaisse(int *premiereCase, int *SecondeCase)
{
    if(*premiereCase == CAISSE || *premiereCase == CAISSE_OK)
    {
        if(*SecondeCase == OBJECTIF)
            *SecondeCase = CAISSE_OK;
        else
            *SecondeCase = CAISSE;

        if(*premiereCase == CAISSE_OK)
            *premiereCase = OBJECTIF;
        else
            *premiereCase = VIDE;
    }
}

#endif // Jeu_C
