#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>

#include "Player.h"



class Game{
private:
    hgeSprite *BackgroundSprite;
    HTEXTURE BackGroundTexture;

    Player *p;
    HTEXTURE CarTexture;
    hgeVector PlayerSpawnPoint;

    HGE *hgep;
    HCHANNEL engineSoundChannel;
    HEFFECT engineSoundEffect;
    float engineSoundPitch;

    bool maxRight;
    bool maxLeft;



public:
    Game(HGE *h);

    ~Game();

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

};
