#include "Player.h"

/* CAR LOCATION INDEXES on the X axis
0->281
1->388
2->530
3->637
*/

    Player::Player(HTEXTURE CTexture, hgeVector StartingPoint, float LeftRightSpeed, HGE *h){
        CarTexture = CTexture;
        CarLocation = StartingPoint;
        CarSprite = new hgeSprite(CarTexture, 0, 0, 84, 183);
        LocationIndex = 2; //It's 3 because it spawns on the third lane (530 on X axis)

        this->LeftRightSpeed = LeftRightSpeed;
        hgep = h;


        LocationCoordinates[0] = 281;
        LocationCoordinates[1] = 388;
        LocationCoordinates[2] = 530;
        LocationCoordinates[3] = 637;
    }

    Player::~Player(){
        //TODO release textures
        delete CarSprite;
    }

    void Player::RenderCar(){
        CarSprite->Render(CarLocation.x, CarLocation.y);
    }

    void Player::SetCarLocation(float newLocation){
        CarLocation.x = newLocation;
    }

    void Player::MoveLeft(float dt, float speed){
        CarLocation.x = CarLocation.x - speed *dt;
    }

    void Player::MoveRight(float dt, float speed){
        CarLocation.x = CarLocation.x + speed *dt;
    }

    void Player::TeleportCar(){
        CarLocation.x = LocationCoordinates[LocationIndex];
    }

    void Player::SmoothlyMoveCar(){
    }


    void Player::DecrementIndex(){
        LocationIndex--;
    }

    void Player::IncrementIndex(){
        LocationIndex++;
    }

    int Player::GetIndex(){
        return LocationIndex;
    }

    float Player::GetCarXLocation(){
        return CarLocation.x;
    }

    float Player::NeededCarXCoordinate(){
        return LocationCoordinates[LocationIndex];
    }



