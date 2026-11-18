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

Player* player = nullptr;
std::vector<Alien*> aliens;

bool ShowFrameworkMenu();

void Level_1_Load()
{
}

void Level_1_Init()
{
    //Create the gameobjects + suscribe event handlers
    iEventManager = new inputEventManager;
    player = new Player(0, 0);
    aliens.push_back(new Alien(300, 200));
    aliens.push_back(new Alien(300, 100));
}

void Level_1_Update()
{
    // core keyboard shortcuts and GUI, do not delete this code!
    KeyboardInput();
    bool guiActive = ShowFrameworkMenu();


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

