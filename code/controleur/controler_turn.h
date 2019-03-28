//
// Created by tgaborit on 27/03/19.
//

#ifndef CATANE_CONTROLER_TURN_H
#define CATANE_CONTROLER_TURN_H

#define CARDW 115
#define CARDH 166

typedef enum {NO_BUTTON, WOOD_BUTTON, WHEAT_BUTTON, CLAY_BUTTON, SHEEPS_BUTTON, ROCK_BUTTON} ControlerButton ;

void controlerTurn(SDL_bool program_launched/*, partie * the_partie*/);
void quit(SDL_bool * program_launched);
void initWoodCard();
void initWheatCard();
void initClayCard();
void initSheepsCard();
void initRockCard();
void initCardsAreas();
ControlerButton whichButtonTurn(SDL_MouseButtonEvent mouse_button);

#endif //CATANE_CONTROLER_TURN_H
