#include <AEEngine.h>
#include <imgui/imgui.h>
#include "Level 1.h"
#include "src/Game/Player.h"
#include "src/Game/Aliens.h"
#include "src/Framework/event_handlers.hh"
#include "src/Events/customEvents.h"
#include "src/Game/DestroiableBlock.h"
#include "src/Events/InputManager.h"
#include "src/Events/CollisionManager.h"

int mode = 0;
inputEventManager* iEventManager = nullptr;
collisionEventManager* cEventManager = nullptr;

//Distrubution of aliens
const float aliensInRow = 9;
const int numOfRows = 5;

//Entities
Player* player = nullptr;
std::vector<Alien*> aliens;
#define NUMBER_OF_BLOCKS 5
std::vector<DestroiableBlock*> blocks; 
Bullet* alienBullet; //Bullet used by the aliens

//Timer for aliens shooting
float timer = 0.0f;
const float aShootCooldown = 2.5f;

bool ShowFrameworkMenu();

void randomAlienShoot()
{
    //number of the picked alien
    int n = (int)AERandFloat(0, aliens.size());
    while (!aliens[n]->getAlive())
    {
        if (n < aliens.size())
            n++;
        else
            n = 0;
    }
    aliens[n]->Shoot(alienBullet);
}
void AlienShootTimer()
{
    timer += (float)AEGetFrameTime();
    if (timer > aShootCooldown)
    {
        timer = 0.0f;
        randomAlienShoot();
    }
}

void Level_1_Load()
{
}

void Level_1_Init()
{
    //CREATE PLAYER AND ALIENS
    player = new Player(0, -250, 3);
    //Get window width and create all the aliens with their corresponding position in x (They will assign their position in y)
    float halfWindowWidth = (float)AEGetSysWindowWidth() / 3.0f; //Is divided by more than 2 to have an offset
    for (int i = 0; i < numOfRows; i++)
    {
        for (int j = 0; j <= aliensInRow; j++)
        {
            float posX = -halfWindowWidth + (halfWindowWidth * 2 / aliensInRow) * j;
            aliens.push_back(new Alien(i, posX));
        }
    }
    for (int i = 0; i < NUMBER_OF_BLOCKS; i++)
    {
        blocks.push_back(new DestroiableBlock(-halfWindowWidth + 2 * BLOCK_WIDTH * i + 25, -150));
    }
    alienBullet = new Bullet; //Bullet used by the aliens

    //CREATE EVENT MANAGERS
    iEventManager = new inputEventManager;
    cEventManager = new collisionEventManager(player, aliens, alienBullet);
    
    //REGISTER HANDLERS
    iEventManager->registerEventHandler(player->getInputHandler());
    //Register all the aliens & player collisions handlers
    std::for_each(aliens.begin(), aliens.end(), [](Alien* a)->void {cEventManager->registerEventHandler(a->getCollisionHandler()); });
    cEventManager->registerEventHandler(player->getCollisionHandler());
    
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
    alienBullet->Update();
    AlienShootTimer();
}

void Level_1_Render()
{
    // clear frame buffer, do not delete this code
    AEGfxSetClearColor(AEGfxColor(0, 0, 0));
    AEGfxClearBuffer();

    player->Draw();
    std::for_each(aliens.begin(), aliens.end(), [](Alien* a) -> void {a->Draw(); }); //Draw each alien
    std::for_each(blocks.begin(), blocks.end(), [](DestroiableBlock* b) -> void {b->Draw(); }); //Draw each block
    alienBullet->Draw();

    //Texts
    int bulletsAvailable = std::count_if(player->getBullets().begin(), player->getBullets().end(), [](Bullet* b)->bool { return b->getReady(); });
    const char* t1 = "Available bullets: ";
    const char* t2 = "Player lives: ";
    std::string bulletsText = t1 + std::to_string(bulletsAvailable);
    std::string livesText = t2 + std::to_string(player->getLives());
    AEGfxPrint(20, 570, AEGfxColor(255, 255, 255), bulletsText.c_str());
    AEGfxPrint(650, 570, AEGfxColor(255, 255, 255), livesText.c_str());
}

void Level_1_Free()
{
    delete player;
    player = nullptr;

    std::for_each(aliens.begin(), aliens.end(), [](Alien* a)->void {delete a; });
    aliens.clear();

    std::for_each(blocks.begin(), blocks.end(), [](DestroiableBlock* b)->void {delete b; });
    blocks.clear();

    delete alienBullet;
    alienBullet = nullptr;
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

