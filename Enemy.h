#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h>
#include <hgerect.h>


class Enemy{
private:
    HGE *hgep;
    int StartingXCoordinates[4];
    hgeSprite *EnemySprite;
    hgeVector CurrentLoc;
    HTEXTURE CarTexture;

    bool ModifiedVelocity;
    int VelocityModifier;


public:
    Enemy(HTEXTURE EnemyTexture, hgeVector StartingPosition, HGE *h);

    ~Enemy();

    void RenderEnemy();

    void MoveDown(float dt, float speed);

    hgeVector GetEnemyLocationVector();

    bool OutOfBounds();


};
