#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constantes.h"
#include "algorithme.h"
#include "jeu.h"

int Algorithme(int Grille[TailleGrille][TailleGrille])
{
    int i = 0, j = 0, a=0;
    int Ligne=0; int Colonne=0; int Grille1[TailleGrille][TailleGrille]; int Grille2[TailleGrille][TailleGrille];

   //Copie des données de l'univers
   
    for (i = 0 ; i < TailleGrille ; i++)
    {
        for (j = 0 ; j < TailleGrille ; j++)
        {
            Grille1[i][j] = Grille[i][j];
        }
    }
		///----- French -----///
		/*Pour toutes les cases : on regarde quelles conditions sont vérifiées en séparant les recherches sur les bords de l'univers. 
		Cette spécificité entraine une particularité qui peut-être approchée par la physique : les effets de bords. 
		On sépare les données du nouvel univers (à t+1) et de l'ancien pour ne pas gêner le déroulement de l'algorithme */
		
		///----- English ----///
		/*For each cells, we look which conditions are fulfilled by separating the search on the universe' borders.
		This specificity lead to features that can approach by physics : boardings effects.
		For the algorithms, we split the data from the universe at t+1 time	from the one at t to not bring interferences.*/
		
        for (Ligne = 0; Ligne < TailleGrille ; Ligne++)
        {
            for (Colonne = 0; Colonne < TailleGrille ; Colonne++)
            {
				//living cell
                if (Grille1[Ligne][Colonne] == 1)
                {
					//top ligne
                    if (Ligne == 0)
                    {
						//left point
                        if (Colonne == 0)
                        {
                            if ((Grille1[Ligne][Colonne+1] + Grille1[Ligne+1][Colonne+1] + Grille1[Ligne+1][Colonne])==2 || (Grille1[Ligne][Colonne+1] + Grille1[Ligne+1][Colonne+1] + Grille1[Ligne+1][Colonne])==3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                Grille2[Ligne][Colonne]=0;
                            }
                        }
						//right point
                        else if (Colonne == (TailleGrille-1))
                        {
                            if ((Grille1[Ligne+1][Colonne-1]+Grille1[Ligne+1][Colonne]+Grille1[Ligne][Colonne-1])==2 || (Grille1[Ligne+1][Colonne-1]+Grille1[Ligne+1][Colonne]+Grille1[Ligne][Colonne-1])==3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                 Grille2[Ligne][Colonne]=0;
                            }
                        }
                        else
                        {
                            if ((Grille1[Ligne][Colonne-1]+Grille1[Ligne+1][Colonne]+Grille1[Ligne][Colonne+1]+Grille1[Ligne+1][Colonne+1]+Grille1[Ligne+1][Colonne-1])==2 || (Grille1[Ligne][Colonne-1]+Grille1[Ligne+1][Colonne]+Grille1[Ligne][Colonne+1]+Grille1[Ligne+1][Colonne+1]+Grille1[Ligne+1][Colonne-1])==3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                Grille2[Ligne][Colonne]=0;
                            }
                        }
                    }
					//without top and bottom borders
                    else if (Ligne>0 && Ligne<(TailleGrille-1))
                    {
						//border left
                        if (Colonne==0)
                        {
                            if ((Grille1[Ligne-1][Colonne+1]+Grille1[Ligne-1][Colonne]+Grille1[Ligne][Colonne+1]+Grille1[Ligne+1][Colonne+1]+Grille1[Ligne+1][Colonne])==2 || (Grille1[Ligne-1][Colonne+1]+Grille1[Ligne-1][Colonne]+Grille1[Ligne][Colonne+1]+Grille1[Ligne+1][Colonne+1]+Grille1[Ligne+1][Colonne])==3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                 Grille2[Ligne][Colonne]=0;
                            }
                        }
						//border top
                        else if (Colonne == TailleGrille)
                        {
                            if ((Grille1[Ligne-1][Colonne-1]+Grille1[Ligne-1][Colonne]+Grille1[Ligne][Colonne-1]+Grille1[Ligne+1][Colonne-1]+Grille1[Ligne+1][Colonne]) == 2 || (Grille1[Ligne-1][Colonne-1]+Grille1[Ligne-1][Colonne]+Grille1[Ligne][Colonne-1]+Grille1[Ligne+1][Colonne-1]+Grille1[Ligne+1][Colonne]) == 3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                Grille2[Ligne][Colonne]=0;
                            }
                        }
						//every other cells
                        else
                        {
                            if ((Grille1[Ligne-1][Colonne+1]+Grille[Ligne-1][Colonne]+Grille[Ligne-1][Colonne-1]+Grille[Ligne][Colonne+1]+Grille[Ligne][Colonne-1]+Grille[Ligne+1][Colonne-1]+Grille[Ligne+1][Colonne]+Grille[Ligne+1][Colonne+1])==2 || (Grille1[Ligne-1][Colonne+1]+Grille[Ligne-1][Colonne]+Grille[Ligne-1][Colonne-1]+Grille[Ligne][Colonne+1]+Grille[Ligne][Colonne-1]+Grille[Ligne+1][Colonne-1]+Grille[Ligne+1][Colonne]+Grille[Ligne+1][Colonne+1])==3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                Grille2[Ligne][Colonne]=0;
                            }
                        }
                    }
					//bottom border
                    else if(Ligne == TailleGrille)
                    {
						//left point
                        if (Colonne==0)
                        {
                            if ((Grille1[Ligne-1][Colonne+1]+Grille1[Ligne-1][Colonne]+Grille1[Ligne][Colonne+1])==2 || (Grille1[Ligne-1][Colonne+1]+Grille1[Ligne-1][Colonne]+Grille1[Ligne][Colonne+1])==3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                Grille2[Ligne][Colonne]=0;
                            }
                        }
						//right point
                        else if (Colonne==TailleGrille)
                        {
                            if ((Grille1[Ligne-1][Colonne-1]+Grille1[Ligne-1][Colonne]+Grille[Ligne][Colonne-1])==2 || (Grille1[Ligne-1][Colonne-1]+Grille1[Ligne-1][Colonne]+Grille[Ligne][Colonne-1])==3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                Grille2[Ligne][Colonne]=0;
                            }
                        }
                        else
                        {
                            if ((Grille1[Ligne-1][Colonne]+Grille1[Ligne][Colonne-1]+Grille1[Ligne-1][Colonne-1]+Grille1[Ligne-1][Colonne+1]+Grille1[Ligne][Colonne+1])==2 || (Grille1[Ligne-1][Colonne]+Grille1[Ligne][Colonne-1]+Grille1[Ligne-1][Colonne-1]+Grille1[Ligne-1][Colonne+1]+Grille1[Ligne][Colonne+1])==3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                Grille2[Ligne][Colonne]=0;
                            }
                        }

                    }
                }
				//empty cells, the same architecture is used for the search.
                else if (Grille1[Ligne][Colonne] == 0)
                {
                    
                    if (Ligne == 0)
                    {
                        if (Colonne == 0)
                        {
                            if ((Grille1[Ligne][Colonne+1] + Grille1[Ligne+1][Colonne+1] + Grille1[Ligne+1][Colonne]) == 3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                Grille2[Ligne][Colonne]=0;
                            }
                        }
                        else if (Colonne == (TailleGrille-1))
                        {
                            if ((Grille1[Ligne+1][Colonne-1]+Grille1[Ligne+1][Colonne]+Grille1[Ligne][Colonne-1]) == 3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                 Grille2[Ligne][Colonne]=0;
                            }
                        }
                        else
                        {
                            if ((Grille1[Ligne][Colonne-1]+Grille1[Ligne+1][Colonne]+Grille1[Ligne][Colonne+1]+Grille1[Ligne+1][Colonne+1]+Grille1[Ligne+1][Colonne-1])==3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                Grille2[Ligne][Colonne]=0;
                            }
                        }
                    }
                    else if (Ligne>0 && Ligne<(TailleGrille-1))
                    {
                        if (Colonne==0)
                        {
                            if ((Grille1[Ligne-1][Colonne+1]+Grille1[Ligne-1][Colonne]+Grille1[Ligne][Colonne+1]+Grille1[Ligne+1][Colonne+1]+Grille1[Ligne+1][Colonne])==3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                 Grille2[Ligne][Colonne]=0;
                            }
                        }
                        else if (Colonne == TailleGrille)
                        {
                            if ((Grille1[Ligne-1][Colonne-1]+Grille1[Ligne-1][Colonne]+Grille1[Ligne][Colonne-1]+Grille1[Ligne+1][Colonne-1]+Grille1[Ligne+1][Colonne]) == 3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                Grille2[Ligne][Colonne]=0;
                            }
                        }
                        else
                        {
                            if ((Grille1[Ligne-1][Colonne+1]+Grille[Ligne-1][Colonne]+Grille[Ligne-1][Colonne-1]+Grille[Ligne][Colonne+1]+Grille[Ligne][Colonne-1]+Grille[Ligne+1][Colonne-1]+Grille[Ligne+1][Colonne]+Grille[Ligne+1][Colonne+1])==3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                Grille2[Ligne][Colonne]=0;
                            }
                        }
                    }
                    else if(Ligne == TailleGrille)
                    {
                        if (Colonne==0)
                        {
                            if ((Grille1[Ligne-1][Colonne+1]+Grille1[Ligne-1][Colonne]+Grille1[Ligne][Colonne+1])==3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                Grille2[Ligne][Colonne]=0;
                            }
                        }
                        else if (Colonne == TailleGrille)
                        {
                            if ((Grille1[Ligne-1][Colonne-1]+Grille1[Ligne-1][Colonne]+Grille[Ligne][Colonne-1])==3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                Grille2[Ligne][Colonne]=0;
                            }
                        }
                        else
                        {
                            if ((Grille1[Ligne-1][Colonne]+Grille1[Ligne][Colonne-1]+Grille1[Ligne-1][Colonne-1]+Grille1[Ligne-1][Colonne+1]+Grille1[Ligne][Colonne+1])==3)
                            {
                                Grille2[Ligne][Colonne]=1;
                            }
                            else
                            {
                                Grille2[Ligne][Colonne]=0;
                            }
                        }

                    }
                }
            }
    }

    for (i = 0 ; i < TailleGrille ; i++)
    {
        for (j = 0 ; j < TailleGrille ; j++)
        {
            Grille[i][j] = Grille2[i][j];
        }
    }

    return Grille[TailleGrille][TailleGrille];
}
