#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>
#include <hgerect.h>
#include <hgefont.h>
#include <vector>

#include "Player.h"
#include "Enemy.h"
#include "Timer.h"

using namespace std;

class Game{
private:
    hgeSprite *BackgroundSprite;
    HTEXTURE BackGroundTexture;

    Player *p;
    HTEXTURE CarTexture;
    hgeVector PlayerSpawnPoint;
    hgeRect PlayerRectangle;

    HGE *hgep;
    HCHANNEL engineSoundChannel;
    HEFFECT engineSoundEffect;
    float engineSoundPitch;

    bool maxRight;
    bool maxLeft;


    vector<Enemy*> Enemies;
    HTEXTURE EnemyTexture;
    float EnemySpeed;


    //Timing and spawning variables
    timer *t;
    int EnemiesToSpawn;     //Must be between 1 and 3
    unsigned int TimeUntillNextSpawn; //Try between 4 and 7



public:
    Game(HGE *h);

    ~Game();

    void UpdateSpawnData();

    void CheckTimer();

    unsigned long GetTimerTime();

    int GetNextIntervalEnemyCount();

    void RenderBackground();

    void RenderVehicle();

    void PlayVehicleSound();

    void MoveVehicleRight();

    void MoveVehicleLeft();

    bool IsMaxLeft();

    bool IsMaxRight();

    float GetVehicleXLocation();

    void SlideCarToLeft(float dt, float speed);

    void SlideCarToRight(float dt, float speed);

    float NeededVehicleXCoordtinate();

    int GetVehicleLocationIndex();

    void SetEngineSoundPitch(float pitch);

    bool CheckForCollision();

    void RenderEnemies();

    void EnemyLogicFunction(float dt);

    void SpawnEnemy(int number);

    void PrintPlayerLocation(hgeFont *text);

    void PrintEnemyLocations(hgeFont *text);

};
