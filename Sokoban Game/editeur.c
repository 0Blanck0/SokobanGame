#ifndef EDITION_C
#define EDITION_C
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "constantes.h"
#include "editeur.h"
#include "fichiers.h"

void editeur(SDL_Surface* Screen)
{
    SDL_Surface *mur = NULL, *caisse = NULL, *objectif = NULL, *Playeur = NULL;
    SDL_Rect position;
    SDL_Event event;

    int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
    int objetActuel = MUR, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    mur = SDL_LoadBMP("Sprit/Decor_Interactio/mur.bmp");
    caisse = SDL_LoadBMP("Sprit/Decor_Interactio/caisse.bmp");
    objectif = SDL_LoadBMP("Sprit/Decor_Interactio/objectif.bmp");
    Playeur = SDL_LoadBMP("Sprit/Perso/Perso2.bmp");

    SDL_SetColorKey(objectif, SDL_SRCCOLORKEY, SDL_MapRGB(objectif->format, 255, 0, 255));
    SDL_SetColorKey(Playeur, SDL_SRCCOLORKEY, SDL_MapRGB(Playeur->format, 255, 0, 255));

    if (!chargerNiveau(carte))
        exit(EXIT_FAILURE);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {

                    carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
                    clicGaucheEnCours = 1;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC] = VIDE;
                    clicDroitEnCours = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    clicGaucheEnCours = 0;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    clicDroitEnCours = 0;
                break;
            case SDL_MOUSEMOTION:
                if (clicGaucheEnCours)
                {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
                }
                else if (clicDroitEnCours)
                {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_s:
                        sauvegarderNiveau(carte);
                        break;
                    case SDLK_r:
                        chargerNiveau(carte);
                        break;
                    case SDLK_KP1:
                        objetActuel = MUR;
                        break;
                    case SDLK_KP2:
                        objetActuel = CAISSE;
                        break;
                    case SDLK_KP3:
                        objetActuel = OBJECTIF;
                        break;
                    case SDLK_KP4:
                        objetActuel = PLAYEUR;
                        break;
                    case SDLK_1:
                        objetActuel = MUR;
                        break;
                    case SDLK_2:
                        objetActuel = CAISSE;
                        break;
                    case SDLK_3:
                        objetActuel = OBJECTIF;
                        break;
                    case SDLK_4:
                        objetActuel = PLAYEUR;
                        break;
                }
                break;
        }

        SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));

        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
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
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, Screen, &position);
                        break;
                    case PLAYEUR:
                        SDL_BlitSurface(Playeur, NULL, Screen, &position);
                        break;
                }
            }
        }

        SDL_Flip(Screen);
    }

    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(Playeur);
}

#endif // EDITION_C

