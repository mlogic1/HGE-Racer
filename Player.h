#include <hge.h>
#include <hgevector.h>
#include <hgesprite.h>


/* CAR LOCATION INDEXES on the X axis
0->281
1->388
2->530
3->637
*/

class Player{
private:
        hgeSprite *CarSprite;
        HTEXTURE CarTexture;
        hgeVector CarLocation;
        float LeftRightSpeed;
        HGE *hgep;
        float dt;


        int LocationIndex;
        int LocationCoordinates[4];

public:

        Player(HTEXTURE CTexture, hgeVector StartingPoint, float LeftRightSpeed, HGE *h);

        ~Player();

        void RenderCar();

        void MoveLeft(float dt, float speed);

        void MoveRight(float dt, float speed);

        void DecrementIndex();

        void IncrementIndex();

        int GetIndex();

        float GetCarXLocation();

        float NeededCarXCoordinate();

};
