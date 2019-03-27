#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "Plateau.h"
#include "carte.c"

#define WINDOWW 1920
#define WINDOWH 950
#define RED 64
#define GREEN 159
#define BLUE 255



void AfficheFenetre(){

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
 
	if(SDL_Init(SDL_INIT_VIDEO)!=0)		
		SDL_ExitWithError("Initialisation SDL impossible");

	//Creation de la fenetre en fullscreen et rendu
	if(SDL_CreateWindowAndRenderer(WINDOWW, WINDOWH, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer) != 0)
		SDL_ExitWithError("Impossible de creer la fenetre et le rendu");


	SDL_SetWindowTitle(window, "Catane");
		
	//Couleur fond 
	if(SDL_SetRenderDrawColor(renderer, RED, GREEN, BLUE, SDL_ALPHA_OPAQUE) != 0)
		SDL_ExitWithError("Impossible de changer la couleur du rendu");

	SDL_Rect rectangle;
	rectangle.x = 0;
	rectangle.y = 0;
	rectangle.w = WINDOWW;
	rectangle.h = WINDOWH;
	
	if(SDL_RenderFillRect(renderer, &rectangle) != 0)	
		SDL_ExitWithError("Impossible de remplir un rectangle");	
	
	SDL_RenderPresent(renderer);
		
	//AfficheTuile(renderer);

	AfficheCarteArgile(renderer);
	AfficheCarteBle(renderer);
	AfficheCarteBois(renderer);
	AfficheCarteMouton(renderer);
	AfficheCarteRoche(renderer);		

	AfficheJoueur(renderer);

	//Event fermeture fenetre
	SDL_bool program_launched = SDL_TRUE;

	while(program_launched)
	{
		SDL_Event event;
		
		while(SDL_PollEvent(&event))	
		{
			switch(event.type)
			{

				case SDL_KEYDOWN :
					switch(event.key.keysym.sym)
					{
						case SDLK_q :
							program_launched = SDL_FALSE;
							break;
						default :
							continue;
					}
 
				case SDL_QUIT :
					program_launched = SDL_FALSE;
					break;
				

				default :
					break;	
			}
		}
	}	
	

	//Fermeture fenetre avec destruction rendu et fenetre
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit(); 	
}




void AfficheTuile(SDL_Renderer* renderer)		//changer l'image et mettre ruche
{
	SDL_Surface *image = NULL;
	SDL_Texture *texture = NULL;
	
	image = SDL_LoadBMP("planete.bmp");

	if(image == NULL)
		SDL_ExitWithError("Impossible de charger l'image");

	texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	
	//switch avec fonction manu ?
	if(texture == NULL)
		SDL_ExitWithError("impossible de creer la texture");

	SDL_Rect rectangle;

	if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0)
		SDL_ExitWithError("Impossible de charger la texture");
	
	rectangle.x = (800 - rectangle.w) / 2;		
	rectangle.y = (600 - rectangle.h) / 2;


	if(SDL_RenderCopy(renderer, texture, NULL, &rectangle) !=0) 
		SDL_ExitWithError("Impossible d'afficher la texture");
	
	SDL_RenderPresent(renderer);
}



void AfficheJoueur(SDL_Renderer* renderer)
{
	
	//Creation de la barre avec les noms des joueurs et le score
	if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
		SDL_ExitWithError("Impossible de changer la couleur du rendu");
	
	SDL_Rect barrejoueurs;
	barrejoueurs.x = 0;
	barrejoueurs.y = 0;
	barrejoueurs.w = WINDOWW;
	barrejoueurs.h = 50;
	
	if(SDL_RenderFillRect(renderer, &barrejoueurs) != 0)	
		SDL_ExitWithError("Impossible de remplir un rectangle");
	
	SDL_RenderPresent(renderer);
}




