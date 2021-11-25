#include <string>

#include "../Entities/Sprite.h"
#include "../GameManager.h"
#include "../Scenes/GameOverScene.h"
#include "../Scenes/LevelScene.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/StageScene.h"

// ++increment for menu id
MenuItem& operator++(MenuItem& c)
{
    using type = typename std::underlying_type<MenuItem>::type;
    c = static_cast<MenuItem>(static_cast<type>(c) + 1);
    if(c == MenuItem::Last)
        c = static_cast<MenuItem>(static_cast<type>(MenuItem::None) + 1);
    return c;
}

// --decrement for menu id
MenuItem& operator--(MenuItem& c)
{
    using type = typename std::underlying_type<MenuItem>::type;
    c = static_cast<MenuItem>(static_cast<type>(c) - 1);
    if(c == MenuItem::None)
        c = static_cast<MenuItem>(static_cast<type>(MenuItem::Last) - 1);
    return c;
}

// increment++ for menu id
MenuItem operator++(MenuItem& c, int)
{
    MenuItem result = c;
    ++c;
    return result;
}

// decrement-- for menu id
MenuItem operator--(MenuItem& c, int)
{
    MenuItem result = c;
    --c;
    return result;
}

MenuScene::MenuScene(GameManager* _gameManager) : Scene(_gameManager)
{
    // background
    auto background = std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(Texture::MenuBack),
                                                gameManager->getRenderer());
    background->setPosition(30, 20);
    background->setSize(gameManager->getWindowWidth() - 60,
                        static_cast<int>(gameManager->getWindowHeight() / 1.5f) - 20);
    addObject(background);

    // start menu, bomber Clasico
    startText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "CLASICO");
    startText->setColor(colorPressed);
    startText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f),
                        static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    startText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - startText->getWidth() / 2.0f),
                            background->getHeight() + 40);
    addObject(startText);

    // star menu, bomber cartoon
    startTextCartoon = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "CARTOON");
    // creditText->setColor(colorPressed); marca el color 
    startTextCartoon->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f),
        static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    startTextCartoon->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - startTextCartoon->getWidth() / 2.0f),
        background->getHeight() + 80);//10
    addObject(startTextCartoon);

    // star menu, bomber personalizadp
    startTextPersonalizado = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "PERSONALIZADO");
    // creditText->setColor(colorPressed); marca el color 
    startTextPersonalizado->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f),
        static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    startTextPersonalizado->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - startTextPersonalizado->getWidth() / 2.0f),
        background->getHeight() + 120);//10
    addObject(startTextPersonalizado);

    // star menu, bomber realista
    startTextRealista = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "REAL");
    // creditText->setColor(colorPressed); marca el color 
    startTextRealista->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f),
        static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    startTextRealista->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - startTextRealista->getWidth() / 2.0f),
        background->getHeight() + 160);//10
    addObject(startTextRealista);
    //tarea

    //// exit menu
    //exitText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "EXIT");
    //exitText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    //exitText->setPosition(startText->getPositionX(),
    //                        startText->getPositionY() + exitText->getHeight() + 20);
    //addObject(exitText);

     // exit menu
  exitText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "SALIR");
  exitText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
  exitText->setPosition(startText->getPositionX(), startTextPersonalizado->getPositionY() + exitText->getHeight() + 20);
  addObject(exitText);


  




    gameManager->getSceneManager()->addScene("gameover", std::make_shared<GameOverScene>(gameManager));
    // menu music
    menuMusic = std::make_shared<Music>(gameManager->getAssetManager()->getMusic(MusicEnum::MainMenu));
}

void MenuScene::onEnter()
{
    menuMusic->play();
}

void MenuScene::onExit()
{
    menuMusic->stop();
}

void MenuScene::onEvent(const SDL_Event& event)
{
    Scene::onEvent(event);
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.scancode)
        {
            // we should select next menu item
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                currentSelectedMenu++;
                onMenuItemSelect();
                break;
            // we should select prev menu item
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                currentSelectedMenu--;
                onMenuItemSelect();
                break;
            // enter in menu item
            case SDL_SCANCODE_SPACE:
            case SDL_SCANCODE_RETURN:
                onMenuItemPress();
                break;
            default:
                break;
        }
    }
}

void MenuScene::onMenuItemSelect()
{
    // reset menu items color
    startText->setColor(colorStandard);
    startTextCartoon->setColor(colorStandard);
    startTextPersonalizado->setColor(colorStandard);
    startTextRealista->setColor(colorStandard);
    exitText->setColor(colorStandard);
    // change color of selected menu item
    switch(currentSelectedMenu)
    {
        case MenuItem::Start:
            startText->setColor(colorPressed);
            break;
        case MenuItem::StartCartoon:
            startTextCartoon->setColor(colorPressed);
            break;
        case MenuItem::StartPersonalizado:
            startTextPersonalizado->setColor(colorPressed);
            break;
        case MenuItem::StartRealista:
            startTextRealista->setColor(colorPressed);
            break;
        case MenuItem::Exit:
            exitText->setColor(colorPressed);
            break;
        default:
            break;
    }
}

int MenuScene::onMenuItemPress()
//void MenuScene::onMenuItemPress()
{

    int tipoJuego;
    switch(currentSelectedMenu)
    {
        case MenuItem::Start:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, 1, 0));
            gameManager->getSceneManager()->activateScene("stage");
            tipoJuego = 0;
            return tipoJuego;
          
            break;
      
        case MenuItem::StartCartoon:
 
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, 1, 0));
            gameManager->getSceneManager()->activateScene("stage");
            tipoJuego = 1;
            
              return tipoJuego;
            break;
        case MenuItem::StartPersonalizado:
     
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, 1, 0));
            gameManager->getSceneManager()->activateScene("stage");
            tipoJuego = 2;
         
              return tipoJuego;
            break;
        case MenuItem::StartRealista:
     
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, 1, 0));
            gameManager->getSceneManager()->activateScene("stage");
           tipoJuego = 3;
           
              return tipoJuego;
            break;
        case MenuItem::Exit:
            // stop gameManager loop
            gameManager->stop();
            break;
        default:
            break;
    }
}
