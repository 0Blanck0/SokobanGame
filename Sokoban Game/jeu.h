#ifndef Jeu_H
#define Jeu_H

void jouer(SDL_Surface* Screen);
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction);
void deplacerCaisse(int *premiereCase, int *SecondeCase);


#endif // Jeu_H
