#ifndef Main_PROG_C
#define Main_PROG_C
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "constantes.h"
#include "jeu.h"
#include "editeur.h"

int main(int agrc, char* argv[])
{
    SDL_Surface* Screen = NULL;
    SDL_Surface* Menu = NULL;
    SDL_Surface* Icon = NULL;
    SDL_Event event;
    SDL_Rect position;

    int continuer = 1;
    int reset = 0;

    if(SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur initialisation video [%s]\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Screen = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);

    if(Screen == NULL)
    {
        fprintf(stderr, "Erreur SetVideoMode [%s]\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    Icon = SDL_LoadBMP("Sprit/Decor_Interactio/caisse.bmp");

    if(Icon == NULL)
    {
        fprintf(stderr, "Erreur Icon [%s]\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

        SDL_WM_SetIcon(Icon, NULL);
        SDL_WM_SetCaption("Sokoban", NULL);

        position.x = 0;
        position.y = 0;

        reset = 0;

        Menu = SDL_LoadBMP("Sprit/Decor_Interactio/Menu.bmp");

        if(Menu == NULL)
        {
            fprintf(stderr, "Erreur Image MENU [%s]\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        SDL_Delay(1);

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
                case SDLK_KP1:
                    jouer(Screen);
                    break;
                case SDLK_KP2:
                    editeur(Screen);
                    break;
                case SDLK_KP3:
                    Info();
                    break;
                case SDLK_1:
                    jouer(Screen);
                    break;
                case SDLK_2:
                    editeur(Screen);
                    break;
                case SDLK_3:
                    Info();
                    break;
                case SDLK_r:
                    reset = 1;
                    break;
                }
                break;
            }

            if(reset == 0)
            {
                SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0, 0, 0));
                SDL_BlitSurface(Menu, NULL, Screen, &position);
                SDL_Flip(Screen);
            }
            else if(reset == 1)
            {
                position.x = 0;
                position.y = 0;
                Screen = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
                Icon = SDL_LoadBMP("Sprit/Decor_Interactio/caisse.bmp");
                Menu = SDL_LoadBMP("Sprit/Decor_Interactio/Menu.bmp");
                SDL_WM_SetIcon(Icon, NULL);
                SDL_WM_SetCaption("Sokoban", NULL);
                reset = 0;
                SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0, 0, 0));
                SDL_BlitSurface(Menu, NULL, Screen, &position);
                SDL_Flip(Screen);
            }
        }

        SDL_FreeSurface(Menu);
        SDL_FreeSurface(Icon);
        SDL_Quit();

    return EXIT_SUCCESS;
}

#endif
