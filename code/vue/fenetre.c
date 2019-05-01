/**
 * \file fenetre.c
 * \brief Implémente les fonctions de fenetre.h
 * \author Pauline.M
 * \version 1.0
 * \date 01 mai 2019
 *
 * Implémente les fonctions utiles à l'affichage du jeu.
 */

#include "fenetre.h"

#define WINDOWW 1920
#define WINDOWH 950
#define RED 64
#define GREEN 159
#define BLUE 255


/**
 * \fn void SDL_ExitWithError(const char *message)
 * \brief Fonction renvoyant un message d'erreur en SDL.
 *
 *
 * \param message, un pointeur vers le message d'erreur
 * \return aucun
 */
void SDL_ExitWithError(const char *message)
{
	SDL_Log("ERREUR : Initialisation SDL > %s\n", SDL_GetError());
	SDL_Quit();
        exit(EXIT_FAILURE);
}


/**
 * \fn SDL_Window* InitFenetre()
 * \brief Fonction créant une fenêtre.
 *
 *
 * \param aucun
 * \return Affiche une fenêtre
 */
SDL_Window* InitFenetre(){
    SDL_Window *window = NULL;

	if(SDL_Init(SDL_INIT_VIDEO)!=0)
		SDL_ExitWithError("Initialisation SDL impossible");

	//Creation de la fenetre en fullscreen et rendu
	if((window = SDL_CreateWindow("Catane",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWW, WINDOWH, SDL_WINDOW_FULLSCREEN_DESKTOP)) == NULL)
		SDL_ExitWithError("Impossible de creer la fenetre");

    return window;
}


/**
 * \fn SDL_Renderer* updateFenetre(Partie* p, SDL_Window* window, SDL_Renderer* oldrenderer)
 * \brief Fonction mettant à jour le plateau de jeu en focntion de la partie
 *
 *
 * \param p, la partie de jeu
 * \param window, la fenêtre du jeu
 * \param oldrenderer, le rendu actuel à détruire pour mettre le jeu à jour
 * \return le nouveau renderer, et affiche le plateau à jour
 */
SDL_Renderer* updateFenetre(Partie* p, SDL_Window* window, SDL_Renderer* oldrenderer){
    SDL_DestroyRenderer(oldrenderer);

    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

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



	if(renderer == NULL)
		SDL_ExitWithError("Creation rendu echouee");

    AfficheDe(renderer);

	AfficheChevalier(renderer);
	AfficheMonopole(renderer);
	AfficheInvention(renderer);
	AfficheRouteDev(renderer);
	AfficheUniversite(renderer);
	AfficheGrandeArmee(renderer);
	AfficheGrandeRoute(renderer);


	AfficheTuilePlateau(p, renderer);

	AfficheRandomProbaPlateau(p, renderer);

	AfficheTuile(renderer);

	AfficheCarteArgile(renderer);
	AfficheCarteBle(renderer);
	AfficheCarteBois(renderer);
	AfficheCarteMouton(renderer);
	AfficheCarteRoche(renderer);

	AfficheVoleur(p, renderer);

	AfficheJoueur(renderer);

	AfficheSkip(renderer);

	AfficheHelp(renderer);

	AfficheBouttonDev(renderer);
	AfficheBouttonRoute(renderer);
	AfficheBouttonColonie(renderer);
	AfficheBouttonVille(renderer);

    SDL_RenderPresent(renderer);
    return renderer;

}

/**
 * \fn void destroyFenetre(SDL_Window* window, SDL_Renderer* renderer)
 * \brief Fonction détruisant la fenêtre et le renderer, et permettant de quitter SDL.
 *
 *
 * \param window, la fenêtre du jeu
 * \param renderer, le rendu actuel
 * \return aucun
 */
void destroyFenetre(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

/*void AfficheFenetre(){

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

	AfficheDe(renderer);

	AfficheChevalier(renderer);
	AfficheMonopole(renderer);
	AfficheInvention(renderer);
	AfficheRouteDev(renderer);
	AfficheUniversite(renderer);
	AfficheGrandeArmee(renderer);
	AfficheGrandeRoute(renderer);

    Partie* p = init_partie();
	AfficheTuilePlateau(p, renderer);

	AfficheRandomProbaPlateau(p, renderer);

	AfficheTuile(renderer);

	AfficheCarteArgile(renderer);
	AfficheCarteBle(renderer);
	AfficheCarteBois(renderer);
	AfficheCarteMouton(renderer);
	AfficheCarteRoche(renderer);

	AfficheVoleur(p, renderer);

	AfficheJoueur(renderer);

	AfficheSkip(renderer);

	AfficheHelp(renderer);

	AfficheBouttonDev(renderer);
	AfficheBouttonRoute(renderer);
	AfficheBouttonColonie(renderer);
	AfficheBouttonVille(renderer);



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
}*/


/**
 * \fn void AfficheJoueur(SDL_Renderer* renderer)
 * \brief Fonction affichant les noms et les scores des joueurs
 *
 *
 * \param renderer, le rendu actuel
 * \return aucun
 */
void AfficheJoueur(SDL_Renderer* renderer)
{

	//Creation de la barre avec les noms des joueurs et le score
	if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
		SDL_ExitWithError("Impossible de changer la couleur du rendu");

	SDL_Rect barrejoueurs;
	barrejoueurs.x = 0;
	barrejoueurs.y = 0;
	barrejoueurs.w = WINDOWW;
	barrejoueurs.h = 35;

	if(SDL_RenderFillRect(renderer, &barrejoueurs) != 0)
		SDL_ExitWithError("Impossible de remplir un rectangle");

	SDL_RenderPresent(renderer);
}

/**
 * \fn void AfficheSkip(SDL_Renderer* renderer)
 * \brief Fonction affichant le bouton pour passer son tour
 *
 *
 * \param renderer, le rendu actuel
 * \return aucun
 */
void AfficheSkip(SDL_Renderer* renderer)
{

	SDL_Surface *image = NULL;
	SDL_Texture *skip = NULL;

	image = SDL_LoadBMP("imagecatane/skip.bmp");

	if(image == NULL)
		SDL_ExitWithError("Impossible de charger l'image");

	skip = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);


	if(skip == NULL)
		SDL_ExitWithError("impossible de creer la texture");

	SDL_Rect rectskip;

	if(SDL_QueryTexture(skip, NULL, NULL, &rectskip.w, &rectskip.h) != 0)
		SDL_ExitWithError("Impossible de charger la texture");

	rectskip.x = 300;
	rectskip.y = 820;


	if(SDL_RenderCopy(renderer, skip, NULL, &rectskip) !=0)
		SDL_ExitWithError("Impossible d'afficher la texture");

	SDL_RenderPresent(renderer);
}

/**
 * \fn void AfficheDe(SDL_Renderer* renderer)
 * \brief Fonction affichant le dé
 *
 *
 * \param renderer, le rendu actuel
 * \return aucun
 */
void AfficheDe(SDL_Renderer* renderer)
{
	if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
		SDL_ExitWithError("Impossible de changer la couleur du rendu");

	SDL_Rect de;
	de.x = 1570;
	de.y = 110;
	de.w = 100;
	de.h = 100;

	if(SDL_RenderFillRect(renderer, &de) != 0)
		SDL_ExitWithError("Impossible de remplir un rectangle");

	SDL_RenderPresent(renderer);
}

/**
 * \fn void AfficheHelp(SDL_Renderer* renderer)
 * \brief Fonction affichant le bouton "?" (help)
 *
 *
 * \param renderer, le rendu actuel
 * \return aucun
 */
void AfficheHelp(SDL_Renderer* renderer)
{
	SDL_Surface *image = NULL;
	SDL_Texture *help = NULL;

	image = SDL_LoadBMP("imagecatane/help.bmp");

	if(image == NULL)
		SDL_ExitWithError("Impossible de charger l'image");

	help = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);


	if(help == NULL)
		SDL_ExitWithError("impossible de creer la texture");

	SDL_Rect recthelp;

	if(SDL_QueryTexture(help, NULL, NULL, &recthelp.w, &recthelp.h) != 0)
		SDL_ExitWithError("Impossible de charger la texture");

	recthelp.x = 1875;
	recthelp.y = 0;


	if(SDL_RenderCopy(renderer, help, NULL, &recthelp) !=0)
		SDL_ExitWithError("Impossible d'afficher la texture");

	SDL_RenderPresent(renderer);

}


/**
 * \fn void AfficheJetonVoleur(Partie* p, double x, double y, SDL_Renderer* renderer, double posimx, double posimy)
 * \brief Fonction affichant le jeton du voleur
 *
 *
 * \param p, la partie de jeu actuel
 * \param x et y les coordonnées du noeud recherché
 * \param renderer, le rendu actuel
 * \param posimx et posimy les position en pixel dans la fenetre
 * \return aucun
 */
void AfficheJetonVoleur(Partie* p, double x, double y, SDL_Renderer* renderer, double posimx, double posimy)
{
	int v = getVoleur(p, x, y);

	if (v!= 1) return;

	else {

		SDL_Surface *image = NULL;
		SDL_Texture *voleur = NULL;

		image = SDL_LoadBMP("imagecatane/voleur.bmp");

		if(image == NULL)
			SDL_ExitWithError("Impossible de charger l'image");

		voleur = SDL_CreateTextureFromSurface(renderer, image);
		SDL_FreeSurface(image);

		if(voleur == NULL)
			SDL_ExitWithError("impossible de creer la texture");

		SDL_Rect rectvoleur;

		if(SDL_QueryTexture(voleur, NULL, NULL, &rectvoleur.w, &rectvoleur.h) != 0)
			SDL_ExitWithError("Impossible de charger la texture");

		rectvoleur.x = posimx;
		rectvoleur.y = posimy;


		if(SDL_RenderCopy(renderer, voleur, NULL, &rectvoleur) !=0)
			SDL_ExitWithError("Impossible d'afficher la texture");

		SDL_RenderPresent(renderer);
	}
}

/**
 * \fn void AfficheVoleur(Partie* p, SDL_Renderer* renderer)
 * \brief Fonction affichant le voleur
 *
 *
 * \param p, la partie actuelle
 * \param renderer, le rendu actuel
 * \return aucun
 */
void AfficheVoleur(Partie* p, SDL_Renderer* renderer)
{
	AfficheJetonVoleur(p, -1, 2, renderer, 792, 152);
	AfficheJetonVoleur(p, 0, 2, renderer, 928, 152);
	AfficheJetonVoleur(p, 1, 2, renderer, 1063, 152);

	AfficheJetonVoleur(p, -1.5, 1, renderer, 724, 270);
	AfficheJetonVoleur(p, -0.5, 1, renderer, 860, 270);
	AfficheJetonVoleur(p, 0.5, 1, renderer, 996, 270);
	AfficheJetonVoleur(p, 1.5, 1, renderer, 1130, 270);

	AfficheJetonVoleur(p, -2, 0, renderer, 656, 388);
	AfficheJetonVoleur(p, -1, 0, renderer, 792, 388);
	AfficheJetonVoleur(p, 0, 0, renderer, 928, 388);
	AfficheJetonVoleur(p, 1, 0, renderer, 1063, 388);
	AfficheJetonVoleur(p, 2, 0, renderer, 1198, 388);

	AfficheJetonVoleur(p, -1.5, -1, renderer, 724, 506);
	AfficheJetonVoleur(p, -0.5, -1, renderer, 860, 506);
	AfficheJetonVoleur(p, 0.5, -1, renderer, 996, 506);
	AfficheJetonVoleur(p, 1.5, -1, renderer, 1130, 506);

	AfficheJetonVoleur(p, -1, -2, renderer, 792, 624);
	AfficheJetonVoleur(p, 0, -2, renderer, 928, 624);
	AfficheJetonVoleur(p, 1, -2, renderer, 1063, 624);

}
