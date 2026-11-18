#include <AEEngine.h>
#include <imgui/imgui.h>
#include "Level 1.h"
#include "src/Game/Player.h"
#include "src/Game/Aliens.h"
#include "src/Framework/event_handlers.hh"
#include "src/Events/customEvents.h"
#include "src/Events/InputManager.h"
#include "src/Events/CollisionManager.h"

int mode = 0;
inputEventManager* iEventManager = nullptr;
collisionEventManager* cEventManager = nullptr;

//Distrubution of aliens
const float aliensInRow = 9;
const int numOfRows = 5;

Player* player = nullptr;
std::vector<Alien*> aliens;

bool ShowFrameworkMenu();

void Level_1_Load()
{
}

void Level_1_Init()
{
    //CREATE PLAYER AND ALIENS
    player = new Player(0, -250, 4);
    //Get window width and create all the aliens with their corresponding position in x (They will assign their position in y)
    float halfWindowWidth = AEGetSysWindowWidth() / 3.0f; //Is divided by more than 2 to have an offset
    for (int i = 0; i < numOfRows; i++)
    {
        for (int j = 0; j <= aliensInRow; j++)
        {
            float posX = -halfWindowWidth + (halfWindowWidth * 2 / aliensInRow) * j;
            aliens.push_back(new Alien(i, posX));
        }
    }

    //CREATE EVENT MANAGERS
    iEventManager = new inputEventManager;
    cEventManager = new collisionEventManager(player, aliens);
    
    //REGISTER HANDLERS
    iEventManager->registerEventHandler(player->getInputHandler());
    //Register all the aliens collisions handlers
    std::for_each(aliens.begin(), aliens.end(), [](Alien* a)->void {cEventManager->registerEventHandler(a->getCollisionHandler()); });
    
}

void Level_1_Update()
{
    // core keyboard shortcuts and GUI, do not delete this code!
    KeyboardInput();
    bool guiActive = ShowFrameworkMenu();

    //Update event managers
    iEventManager->update();
    cEventManager->update();

    //Update player & aliens
    player->Update();
    std::for_each(aliens.begin(), aliens.end(), [](Alien* a)->void { a->Update(); });
}

void Level_1_Render()
{
    // clear frame buffer, do not delete this code
    AEGfxSetClearColor(AEGfxColor(0, 0, 0));
    AEGfxClearBuffer();

    player->Draw();
    std::for_each(aliens.begin(), aliens.end(), [](Alien* a) -> void {a->Draw(); }); //Draw each alien
}

void Level_1_Free()
{

}

void Level_1_Unload()
{
}

void KeyboardInput()
{
    if (AEInputKeyTriggered('R'))
        AESetGameStateNext(AE_GS_RESTART);
    if (AEInputKeyTriggered('Q') && AEInputKeyPressed(AE_KEY_CTRL))
        AESetGameStateNext(AE_GS_QUIT);
}

bool ShowFrameworkMenu()
{
    bool isGuiActive = false;
    mode = 0;

    // show File options 
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Mode")) {

            if (ImGui::MenuItem("Restart", "1"))
                mode = 1;

            ImGui::EndMenu();
        }

        auto mSize = ImGui::GetWindowHeight();
        AEVec2 mouseVP = AEGetMouseData().position + AEVec2((float)AEGetSysWindowWidth() / 2.0f, (float)AEGetSysWindowHeight() / 2.0f);
        auto inMenu = mouseVP.y >= (AEGetSysWindowHeight() - mSize);
        isGuiActive = ImGui::IsAnyItemActive() || ImGui::IsAnyItemHovered() || inMenu;

        ImGui::EndMainMenuBar();
    }

    if (mode == 1) {
        AESetGameStateNext(AE_GS_RESTART);
    }

    return isGuiActive;
}

