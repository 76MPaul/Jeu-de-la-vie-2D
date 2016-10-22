#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "algorithme.h"
#include "jeu.h"
#include "option.h"

void Affichage(SDL_Surface* ecran)
{
    SDL_Surface *vide = NULL, *plein = NULL, *menu_2 = NULL ;
    SDL_Rect position;
    SDL_Rect positionMenu;
    SDL_Event event;

    int Etapes = 0;
    int NombreEtape = 1;
    int IndexMenu = 1;
    int Grille[TailleGrille][TailleGrille] = {0};
    int GrilleInit[TailleGrille][TailleGrille] = {0};
    int continuer = 1, i = 0, j = 0;

    //chargement des images

    vide = SDL_LoadBMP("vide.bmp");
    plein = SDL_LoadBMP("plein.bmp");

    positionMenu.x = (LARGEUR_FENETRE / 2) - (600 / 2);
    positionMenu.y = (HAUTEUR_FENETRE);

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
            case SDLK_ESCAPE:
            continuer = 0;
            break;
            }
        break;
		//on mouse event
            case SDL_MOUSEBUTTONDOWN:
             if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (event.button.y < HAUTEUR_FENETRE)
                {
				//cells click interaction : it switch the cell state
                    if (Grille[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC]==VIDE)
                    {
                    Grille[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC]=1;
                    }
                    else
                    {
                    Grille[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC]=0;
                    }
                }
                else
                {
					//handle the iterations after clicking on the "Etapes suivantes" button.
                    if (event.button.y > (HAUTEUR_FENETRE) && event.button.y < (HAUTEUR_FENETRE + 16) && event.button.x > ((LARGEUR_FENETRE / 2) - (600 / 2)  + 11) && event.button.x < ((LARGEUR_FENETRE / 2) - (600 / 2) + 128))
                    {
                        for (Etapes = 0; Etapes < (NombreEtape) ; Etapes++)
                        {
                            Algorithme(Grille);

                            for (i = 0 ; i < TailleGrille ; i++)
                            {
                                for (j = 0 ; j < TailleGrille ; j++)
                                {
                                position.x = i * TAILLE_BLOC;
                                position.y = j * TAILLE_BLOC;

                                    switch(Grille[i][j])
                                    {
                                        case VIDE:
                                        SDL_BlitSurface(vide, NULL, ecran, &position);
                                        break;
                                        case PLEIN:
                                        SDL_BlitSurface(plein, NULL, ecran, &position);
                                        break;
                                    }
                                }
                            }

                        SDL_Flip(ecran);
                        SDL_Delay(50);

                        }
                    }
					//opening screen to chose the number of iterations
                    else if (event.button.y > (HAUTEUR_FENETRE) && event.button.y < (HAUTEUR_FENETRE + 16) && event.button.x > ((LARGEUR_FENETRE / 2) - (600 / 2) + 347) && event.button.x < ((LARGEUR_FENETRE / 2) - (600 / 2) + 364))
                    {
                        IndexMenu = 4;
                    }
                    else if (event.button.y > (HAUTEUR_FENETRE+33) && event.button.y < (HAUTEUR_FENETRE + 49) && event.button.x > ((LARGEUR_FENETRE / 2) - (600 / 2) + 11) && event.button.x < ((LARGEUR_FENETRE / 2) - (600 / 2) + 64))
                    {
                        option(Grille,ecran);
                    }
					//reset of the grid
                    else if (event.button.y > (HAUTEUR_FENETRE) && event.button.y < (HAUTEUR_FENETRE + 16) && event.button.x > ((LARGEUR_FENETRE / 2) - (600 / 2) + 430) && event.button.x < ((LARGEUR_FENETRE / 2) - (600 / 2) + 470))
                    {
                        for (i = 0 ; i < TailleGrille ; i++)
                            {
                                for (j = 0 ; j < TailleGrille ; j++)
                                {
                                    Grille[i][j] = 0;
                                }
                            }
                    }
					//stopping menu
                    else if (event.button.y > (HAUTEUR_FENETRE + 33) && event.button.y < (HAUTEUR_FENETRE + 49) && event.button.x > ((LARGEUR_FENETRE / 2) - (600 / 2) + 537) && event.button.x < ((LARGEUR_FENETRE / 2) - (600 / 2)+591))
                    {
                        continuer=0;
                    }
					//menu number of iterations menu
                    else if (IndexMenu==4)
                    {
                        if (event.button.y > (HAUTEUR_FENETRE + 16) && event.button.y < (HAUTEUR_FENETRE + 30) && event.button.x > ((LARGEUR_FENETRE / 2) - (600 / 2) + 302) && event.button.x < ((LARGEUR_FENETRE / 2) - (600 / 2)+ 347))
                        {
                            NombreEtape=1;
                            IndexMenu = 1;
                        }
                        else if (event.button.y > HAUTEUR_FENETRE + 31 && event.button.y < HAUTEUR_FENETRE + 45 && event.button.x > ((LARGEUR_FENETRE / 2) - (600 / 2) + 302) && event.button.x < ((LARGEUR_FENETRE / 2) - (600 / 2)+ 347))
                        {
                            NombreEtape=10;
                            IndexMenu = 10;
                        }
                        else if (event.button.y > (HAUTEUR_FENETRE + 46) && event.button.y < (HAUTEUR_FENETRE + 60) && event.button.x > ((LARGEUR_FENETRE / 2) - (600 / 2) + 302) && event.button.x < ((LARGEUR_FENETRE / 2) - (600 / 2)+ 347))
                        {
                            NombreEtape=100;
                            IndexMenu = 100;
                        }
                        else if (event.button.y > (HAUTEUR_FENETRE + 61) && event.button.y < (HAUTEUR_FENETRE + 75) && event.button.x > ((LARGEUR_FENETRE / 2) - (600 / 2) + 302) && event.button.x < ((LARGEUR_FENETRE / 2) - (600 / 2)+ 347))
                        {
                            NombreEtape=1000;
                            IndexMenu = 1000;
                        }
                    }
                }
            }
    }

    // Effacement de l'écran
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

	//loading of the different screens menus depending of the number of iterations
    if (IndexMenu == 1)
    {
        vide = SDL_LoadBMP("vide.bmp");
        plein = SDL_LoadBMP("plein.bmp");
        menu_2 = IMG_Load("menu 1.jpg");
    }
    else if (IndexMenu == 10)
    {
        menu_2 = IMG_Load("menu 10.jpg");
    }
    else if (IndexMenu == 100)
    {
        menu_2 = IMG_Load("menu 100.jpg");
    }
    else if (IndexMenu == 1000)
    {
        menu_2 = IMG_Load("menu 1000.jpg");
    }
    else if (IndexMenu == 4)
    {
        menu_2 = IMG_Load("menu ouvert.jpg");
    }
    if (IndexMenu == 2)
    {
        menu_2 = IMG_Load("Options.jpg");
    }

    SDL_BlitSurface(menu_2, NULL, ecran, &positionMenu);

    //placement de objets - Cells positionning
    for (i = 0 ; i < TailleGrille ; i++)
    {
        for (j = 0 ; j < TailleGrille ; j++)
        {
            position.x = i * TAILLE_BLOC;
            position.y = j * TAILLE_BLOC;

            switch(Grille[i][j])
            {
                case VIDE:
                    SDL_BlitSurface(vide, NULL, ecran, &position);
                    break;
                case PLEIN:
                    SDL_BlitSurface(plein, NULL, ecran, &position);
                    break;
            }
        }
    }

    SDL_Flip(ecran);
    }

    // Libération des surfaces chargées
SDL_FreeSurface(vide);
SDL_FreeSurface(plein);
SDL_FreeSurface(menu_2);

}

