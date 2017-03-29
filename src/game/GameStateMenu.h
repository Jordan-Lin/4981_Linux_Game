#ifndef GAMESTATE_MENU_H
#define GAMESTATE_MENU_H

#include <string>
#include <sstream>
#include <iomanip>

#include "../game/Level.h"
#include "../view/Camera.h"
#include "GameState.h"
#include "Game.h"

static constexpr size_t maxLength = 15;

//Color Data
static constexpr SDL_Color SDL_WHITE_RGB = {255, 255, 255};
static constexpr SDL_Color SDL_RED_RGB = {143, 63, 61};
static constexpr SDL_Color SDL_BLACK_RGB = {0, 0, 0};
static constexpr SDL_Color SDL_GREEN_RGB = {54, 96, 81};

//RGB color information
static constexpr size_t WHITE_RGB[3] = {255, 255, 255};
static constexpr size_t YELLOW_RGB[3] = {148, 139, 77};
static constexpr size_t LT_GREEN_RGB[3] = {92, 133, 108};
static constexpr int MAX_RGB = 255;

static constexpr int FONT_SIZE = 30;

class GameStateMenu : public GameState {
public:
    GameStateMenu(Game& g);
    ~GameStateMenu();

    virtual bool load();
    virtual void loop();

private:
    virtual void sync() override;
    virtual void handle() override;
    virtual void update(const float delta) override;
    void positionElements();
    virtual void render() override;

    TTF_Font *headingFont;
    TTF_Font *textboxFont;
    TTF_Font *menuFont;

    SDL_Rect usernameTextBox;
    SDL_Rect hostIPTextBox;

    SDL_Rect joinRect;
    SDL_Rect optionsRect;

    SDL_Rect screenRect;
};

#endif
