/**
* \file controler_turn.c
* \brief Fonctions du contrôleur du tour du joueur
* \author Titouan Gaborit
* \date 27 mars 2019
*
* Programme gérant les actions du joueur lors de son tour de jeu : les intéractions avec les cartes ressources ainsi que le bouton de fin de tour.
*
*/

#include <SDL.h>
#include "controler.h"
#include "controler_turn.h"

static SDL_Rect wood_card_area;        /*!< Rectangle correspondant à la zone de la carte Bois*/
static SDL_Rect wheat_card_area;       /*!< Rectangle correspondant à la zone de la carte Blé*/
static SDL_Rect clay_card_area;        /*!< Rectangle correspondant à la zone de la carte Argile*/
static SDL_Rect sheeps_card_area;      /*!< Rectangle correspondant à la zone de la carte Moutons*/
static SDL_Rect rock_card_area;        /*!< Rectangle correspondant à la zone de la carte Roche*/
static SDL_Rect end_turn_area;         /*!< Rectangle correspondant à la zone du bouton Fin de tour*/

/**
* \fn void controlerTurn(SDL_bool program_launched, partie * the_partie)
* \brief Fonction principale du contrôleur du tour du joueur
*
* Cette fonction se répète tant que le joueur reste dans l'environnement de son tour de jeu.
* Elle détecte les actions du joueur et fait appel aux fonctions de callback en fonction de ces actions.
*
* \param[in,out] program_launched Etat du programme : si devient SDL_False, on sort de la fonction et on quitte le programme.
* \param[in,out] the_partie Etat de la partie en cours qui sera modifié en fonction des actions du joueur
*/
void controlerTurn(SDL_bool program_launched, SDL_Renderer* renderer/*, partie * the_partie*/) /*à appeler avec la structure the_partie*/
{
    initCardsAreas();
    initEndTurnArea();
    drawButtons(renderer);
    SDL_RenderPresent(renderer);
    while(program_launched)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_USEREVENT:
                /*AffichePlateau(the_partie);*/
                printf("Appel de la fonction AffichePlateau(the_partie)\n");
                break;

            case SDL_MOUSEBUTTONDOWN :
                switch(whichButtonTurn(event.button))
                {
                case WOOD_BUTTON :
                    printf("Clic sur carte bois\n");
                    //echange(BOIS); /* fonction
                    break;

                case WHEAT_BUTTON :
                    printf("Clic sur carte ble\n");
                    break;

                case CLAY_BUTTON :
                    printf("Clic sur carte argile\n");
                    break;

                case SHEEPS_BUTTON :
                    printf("Clic sur carte moutons\n");
                    break;

                case ROCK_BUTTON :
                    printf("Clic sur carte roche\n");
                    break;

                case ENDTURN_BUTTON :
                    printf("Clic sur bouton Fin de tour\n");
                    break;

                default :
                    continue;
                }

            case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                case SDLK_q :
                    quit(&program_launched);
                    break;

                default :
                    continue;
                }

            case SDL_QUIT :
                quit(&program_launched);
                break;

            default :
                break;
            }
        }
    }
}

/**
* \fn void quit(SDL_bool * program_launched)
* \brief Fonction activant la fin du jeu
*
* Donne la valeur SDL_False à l'état du programme, ce qui le fera sortir de la boucle de controlerTurn et quitter du programme
*
* \param[in,out] pprogram_launched Pointeur vers l'état du programme
*
*/
void quit(SDL_bool * pprogram_launched)
{
    *pprogram_launched = SDL_FALSE;
    printf("execution fonction quit()\n");
}

/**
* \fn void initWoodCard()
* \brief Fonction d'initialisation des champs du rectangle de la zone de la carte bois
*
* Assigne les valeurs de largeur et hauteur d'après les macros correspondant à la largeur et à la hauteur des cartes ressources.
* Assigne les valeurs de position selon le placement de la carte Bois sur l'écran du joueur.
*
*/
void initWoodCard()
{
    wood_card_area.w = CARDW;
    wood_card_area.h = CARDH;

    wood_card_area.x = WINDOWW/2 - CARDW/2;/* regler positions par rapport à la vue */
    wood_card_area.y = WINDOWH - CARDH;
}

/**
* \fn void initWheatCard()
* \brief Fonction d'initialisation des champs du rectangle de la zone de la carte blé
*
* Assigne les valeurs de largeur et hauteur d'après les macros correspondant à la largeur et à la hauteur des cartes ressources.
* Assigne les valeurs de position selon le placement de la carte Blé sur l'écran du joueur.
*
*/
void initWheatCard()
{
    wheat_card_area.w = CARDW;
    wheat_card_area.h = CARDH;

    wheat_card_area.x = wood_card_area.x-58-wheat_card_area.w;
    wheat_card_area.y = WINDOWH - CARDH;
}

/**
* \fn void initClayCard()
* \brief Fonction d'initialisation des champs du rectangle de la zone de la carte argile
*
* Assigne les valeurs de largeur et hauteur d'après les macros correspondant à la largeur et à la hauteur des cartes ressources.
* Assigne les valeurs de position selon le placement de la carte Argile sur l'écran du joueur.
*
*/
void initClayCard()
{
    clay_card_area.w = CARDW;
    clay_card_area.h = CARDH;

    clay_card_area.x = wheat_card_area.x-58-clay_card_area.w;
    clay_card_area.y = WINDOWH - CARDH;
}

/**
* \fn void initSheepsCard()
* \brief Fonction d'initialisation des champs du rectangle de la zone de la carte moutons
*
* Assigne les valeurs de largeur et hauteur d'après les macros correspondant à la largeur et à la hauteur des cartes ressources.
* Assigne les valeurs de position selon le placement de la carte Moutons sur l'écran du joueur.
*
*/
void initSheepsCard()
{
    sheeps_card_area.w = CARDW;
    sheeps_card_area.h = CARDH;

    sheeps_card_area.x = wood_card_area.x+wood_card_area.w+58;
    sheeps_card_area.y = WINDOWH - CARDH;
}

/**
* \fn void initRockCard()
* \brief Fonction d'initialisation des champs du rectangle de la zone de la carte roche
*
* Assigne les valeurs de largeur et hauteur d'après les macros correspondant à la largeur et à la hauteur des cartes ressources.
* Assigne les valeurs de position selon le placement de la carte Roche sur l'écran du joueur.
*
*/
void initRockCard()
{
    rock_card_area.w = CARDW;
    rock_card_area.h = CARDH;

    rock_card_area.x = sheeps_card_area.x+sheeps_card_area.w+58;
    rock_card_area.y = WINDOWH - CARDH;
}

/**
* \fn void initCardsAreas()
* \brief Fonction d'initialisation des cartes ressources
*
* Initialise les champs des rectangles des zones correspondant aux cartes ressources.
* Fait appel aux fonctions d'initialisation pour la carte Bois, la carte Blé, la carte Argile, la carte Moutons et la carte Roche.
*
*/
void initCardsAreas()
{
    initWoodCard();
    initWheatCard();
    initClayCard();
    initSheepsCard();
    initRockCard();
}

/**
* \fn void initEndTurnArea()
* \brief Fonction d'initialisation des champs du rectangle de la zone du bouton Fin de tour
*
* Assigne les valeurs de largeur et hauteur d'après la taille souhaitée.
* Assigne les valeurs de position selon le placement souhaité.
*
*/
void initEndTurnArea()
{
    end_turn_area.w = 150;
    end_turn_area.h = 75;

    end_turn_area.x = 300;
    end_turn_area.y = 55;
}

/**
* \fn ControlerButton whichButtonTurn(SDL_MouseButtonEvent mouse_button)
* \brief Fonction de test sur quel bouton le jouer a cliqué
*
* Teste pour chaque bouton si le clic efféctué correspond à la zone de ce bouton.
* Si c'est le cas, communique lequel.
*
* \param[in] mouse_button Clic qui a été effectué par le joueur. Contient les informations sur sa position notamment.
* \return Le bouton de l'environnement "Tour du joueur" qui a été cliqué.
*/
TurnButton whichButtonTurn(SDL_MouseButtonEvent mouse_button){
    if(isInArea(mouse_button, wood_card_area) == SDL_TRUE)
        return WOOD_BUTTON;
    if(isInArea(mouse_button, wheat_card_area) == SDL_TRUE)
        return WHEAT_BUTTON;
    if(isInArea(mouse_button, clay_card_area) == SDL_TRUE)
        return CLAY_BUTTON;
    if(isInArea(mouse_button, sheeps_card_area) == SDL_TRUE)
        return SHEEPS_BUTTON;
    if(isInArea(mouse_button, rock_card_area) == SDL_TRUE)
        return ROCK_BUTTON;
    if(isInArea(mouse_button, end_turn_area) == SDL_TRUE)
        return ENDTURN_BUTTON;
    return NO_BUTTON;
}

void drawButtons(SDL_Renderer* renderer)
{
    SDL_Rect turn_buttons[6] = {wood_card_area, wheat_card_area, clay_card_area, sheeps_card_area, rock_card_area, end_turn_area};
    if(SDL_RenderDrawRects(renderer, turn_buttons, 6) != 0)
        SDL_ExitWithError("Impossible de dessiner les cartes ressource");
}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}
