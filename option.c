#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "algorithme.h"
#include "jeu.h"

int option(int Grille[TailleGrille][TailleGrille], SDL_Surface* ecran)
{

    TTF_Init();

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }


    SDL_Surface *option = NULL, *barre_verte1 = NULL, *texte = NULL,*texte2 = NULL,*barre_verte2 = NULL;
    SDL_Rect positionOption,positionBarre1,positionBarre2, positionChiffres1, positionChiffres2;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};


    int GrilleInitiale[TailleGrille][TailleGrille];
    int IndexMenu = 1;
    int continuer = 1, i = 0, j = 0, NombresCasesRemplies=0, NombresCasesConcerne=0, Pourcent=0;
    char CasesConcerne[6] = "";
    char PourcentARemplir[6] = "";

	/* Load option picture */
    option = IMG_Load("Options.png");
    barre_verte1 = IMG_Load("barre_verte.jpg");
    barre_verte2 = IMG_Load("barre_verte.jpg");

    /* Chargement de la police */
    police = TTF_OpenFont("angelina.ttf", 20);

    texte = TTF_RenderText_Solid(police, CasesConcerne, couleurNoire);
    texte2 = TTF_RenderText_Solid(police, PourcentARemplir, couleurNoire);


    /*positions initiales*/
    positionChiffres1.x = (LARGEUR_FENETRE / 2) - (550 / 2) +365;
    positionChiffres1.y = (HAUTEUR_FENETRE + 75) / 2 - (550 / 2)+398;

    positionChiffres2.x = (LARGEUR_FENETRE / 2) - (550 / 2) +365;
    positionChiffres2.y = (HAUTEUR_FENETRE + 75) / 2 - (550 / 2)+422;

    positionOption.x = (LARGEUR_FENETRE / 2) - (550 / 2);
    positionOption.y = (HAUTEUR_FENETRE + 75) / 2 - (550 / 2);

    positionBarre1.x = (LARGEUR_FENETRE / 2) - (550 / 2) +156;
    positionBarre1.y = (HAUTEUR_FENETRE + 75) / 2 - (550 / 2)+398;

    positionBarre2.x = (LARGEUR_FENETRE / 2) - (550 / 2) +156;
    positionBarre2.y = (HAUTEUR_FENETRE + 75) / 2 - (550 / 2)+422;


    /*initialisation grille*/

    for (i = 0 ; i < TailleGrille ; i++)
    {
        for (j = 0 ; j < TailleGrille ; j++)
        {
            Grille[i][j] = 0;
        }
    }


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
            case SDL_MOUSEBUTTONDOWN:

			//launch button
               if (event.button.x>((LARGEUR_FENETRE / 2) - (550 / 2) +81) && event.button.x<((LARGEUR_FENETRE / 2) - (550 / 2) +146) && event.button.y> ((HAUTEUR_FENETRE + 75) / 2 - (550 / 2) + 446) && event.button.y<((HAUTEUR_FENETRE + 75) / 2 - (550 / 2)+ 465))
                   {
                    NombresCasesRemplies = 0;
                    int NbCase = 0;
                    NbCase = ((Pourcent*NombresCasesConcerne*NombresCasesConcerne)/100+1);
                    srand(time(NULL)); // attention une seule instruction srand par programme
                    do
                    {
                        i = (rand() % (NombresCasesConcerne)) + (TailleGrille)/2 - NombresCasesConcerne/2;
                        j = (rand() % (NombresCasesConcerne)) + (TailleGrille)/2 - NombresCasesConcerne/2;
                        if (Grille[i][j]==0)
                        {
                            Grille[i][j]=1;
                            NombresCasesRemplies ++;
                        }
                    }while(NombresCasesRemplies < NbCase );
                    continuer=0;

                }
					
					// number of cells from the center of the screen that will be concerned by the filling
                else if (event.button.x>((LARGEUR_FENETRE / 2) - (550 / 2) +250) && event.button.x<((LARGEUR_FENETRE / 2) - (550 / 2) +356) && event.button.y> ((HAUTEUR_FENETRE + 75) / 2 - (550 / 2) + 398) && event.button.y<((HAUTEUR_FENETRE + 75) / 2 - (550 / 2)+ 410))
                    {
                        positionBarre1.x = (event.button.x-100);
                        positionBarre1.y = (HAUTEUR_FENETRE + 75) / 2 - (550 / 2)+398;
						//positioning of the green bar
                        if ((event.button.x - 100 - ((LARGEUR_FENETRE / 2) - (550 / 2) +153))>79)
                        {
                            NombresCasesConcerne = 79;
                        }
                        else if ((event.button.x-100 - ((LARGEUR_FENETRE / 2) - (550 / 2) +153))<0)
                        {
                            NombresCasesConcerne = 0;
                        }
                        else
                        {
                            NombresCasesConcerne = (event.button.x-100 - ((LARGEUR_FENETRE / 2) - (550 / 2) +153));
                        }

                        sprintf(CasesConcerne, "%d", NombresCasesConcerne);
                        SDL_FreeSurface(texte);
                        texte = TTF_RenderText_Solid(police, CasesConcerne, couleurNoire);

                    }
					// percentage of cells that may be filled
                else if (event.button.x>((LARGEUR_FENETRE / 2) - (550 / 2) +250) && event.button.x<((LARGEUR_FENETRE / 2) - (550 / 2) +356) && event.button.y> ((HAUTEUR_FENETRE + 75) / 2 - (550 / 2) + 422) && event.button.y<((HAUTEUR_FENETRE + 75) / 2 - (550 / 2)+ 434))
                {
                    positionBarre2.x = event.button.x - 100;
                    positionBarre2.y = (HAUTEUR_FENETRE + 75) / 2 - (550 / 2) + 422;
					//positioning of the green bar
                    if ((event.button.x - 100 - ((LARGEUR_FENETRE / 2) - (550 / 2) +153))>100)
                    {
                        Pourcent = 100;
                    }
                    else if ((event.button.x-100 - ((LARGEUR_FENETRE / 2) - (550 / 2) +153))<0)
                    {
                        Pourcent = 0;
                    }
                    else
                    {
                        Pourcent = (event.button.x-100 - ((LARGEUR_FENETRE / 2) - (550 / 2) +153));
                    }

                    sprintf(PourcentARemplir, "%d", Pourcent);
                    SDL_FreeSurface(texte2);
                    texte2 = TTF_RenderText_Solid(police, PourcentARemplir, couleurNoire);

                }

        }


     // Effacement de l'écran
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    SDL_BlitSurface(barre_verte1, NULL, ecran, &positionBarre1);
    SDL_BlitSurface(barre_verte2, NULL, ecran, &positionBarre2);
    SDL_BlitSurface(option, NULL, ecran, &positionOption);
    SDL_BlitSurface(texte, NULL, ecran, &positionChiffres1);
    SDL_BlitSurface(texte2, NULL, ecran, &positionChiffres2);
    SDL_Flip(ecran);

    }

    // Libération des surfaces chargées
    SDL_FreeSurface(option);
    SDL_FreeSurface(barre_verte1);
    SDL_FreeSurface(barre_verte2);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte2);
    TTF_CloseFont(police);

    TTF_Quit();

    return Grille[TailleGrille][TailleGrille];

}



