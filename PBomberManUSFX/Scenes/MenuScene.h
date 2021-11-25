#ifndef _BOMBERMAN_SCENES_MENU_SCENE_H_
#define _BOMBERMAN_SCENES_MENU_SCENE_H_

#include <SDL.h>
#include <memory>

#include "../Entities/Music.h"
#include "../Entities/Text.h"
#include "../Scenes/Scene.h"

/**
    * @brief Menu id
    *
    */
enum class MenuItem
{
    None,
    Start,
    StartCartoon,
    StartPersonalizado,
    StartRealista,
    Exit,
    Last
};
/**
    * @brief Menu Scene
    *
    */
class MenuScene : public Scene
{
    public:
    /**
        * @brief Construct a new Menu Scene
        *
        * @param game
        */
    MenuScene(GameManager* game);
    /**
        * @brief Called when scene was activated
        *
        */
    virtual void onEnter() override;
    /**
        * @brief Called when scene was deactivated
        *
        */
    virtual void onExit() override;
    /**
        * @brief Trigger on SDL2 event if scene is active
        *
        * @param event - SDL2 event
        */
    virtual void onEvent(const SDL_Event& event) override;
    //aa
   // int onMenuItemPress();

    private:
    /**
        * @brief called when menu item was selected
        *
        */
    void onMenuItemSelect();
    /**
        * @brief called when menu item was pressed
        *
        */
    void onMenuItemPress();

    std::shared_ptr<Text> startText = nullptr;      // menu start
    std::shared_ptr<Text> startTextCartoon = nullptr;
    std::shared_ptr<Text> startTextPersonalizado = nullptr;
    std::shared_ptr<Text> startTextRealista = nullptr;
    std::shared_ptr<Text> exitText = nullptr;       // menu exit
    std::shared_ptr<Music> menuMusic = nullptr;     // menu music
    MenuItem currentSelectedMenu = MenuItem::Start; // current selected menu
   /* MenuItem currentSelectedMenu = MenuItem::StartCartoon;
    MenuItem currentSelectedMenu = MenuItem::StartPersonalizado;
    MenuItem currentSelectedMenu = MenuItem::StartRealista;*/
    // const colors for menu selection
    const SDL_Color colorStandard = {255, 255, 255, 255};
    const SDL_Color colorPressed = {66, 134, 244, 255};
};

#endif // _BOMBERMAN_SCENES_MENU_SCENE_H_
