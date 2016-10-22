#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "algorithme.h"
#include "jeu.h"



int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    //SDL_WM_SetIcon(IMG_Load("caisse.jpg"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE +50, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Jeux de la Vie", NULL);


    menu = IMG_Load("menu.jpg");
    positionMenu.x = (LARGEUR_FENETRE / 2) - (500 / 2);
    positionMenu.y = (HAUTEUR_FENETRE + 50) / 2 - (500 / 2);

    while (continuer)
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
                    case SDLK_ESCAPE: // Veut arrêter le jeu
                    continuer = 0;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
             if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (event.button.x>280 && event.button.x<525 && event.button.y>380 && event.button.y<440)
                {
                    Affichage(ecran);
                }
            }
            break;
        }

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}
