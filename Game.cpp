

#include "Game.h"


    Game::Game(HGE *h){

        BackGroundTexture = h->Texture_Load("Textures\\Background.png");
        BackgroundSprite = new hgeSprite(BackGroundTexture, 0, 0, 1024, 768);

        CarTexture = h->Texture_Load("Textures\\Vehicles\\pickup.png");
        PlayerSpawnPoint.x = 530;
        PlayerSpawnPoint.y = 500;

        maxRight = false;
        maxLeft = false;

        p = new Player(CarTexture, PlayerSpawnPoint, 550, h);

        engineSoundEffect = h->Effect_Load("Sounds\\engine.wav");
        engineSoundPitch = 1.0;


        hgep = h;
    }

    Game::~Game(){

        hgep->Effect_Free(engineSoundEffect);
        hgep->Texture_Free(CarTexture);
        delete p;
    }

    void Game::RenderBackground(){
        BackgroundSprite->Render(0, 0);
    }

    void Game::RenderVehicle(){
        p->RenderCar();
    }

    void Game::PlayVehicleSound(){
        engineSoundChannel = hgep->Effect_PlayEx(engineSoundEffect, 10, 0, engineSoundPitch, true);
    }

    float Game::GetVehicleXLocation(){
        return p->GetCarXLocation();
    }

    float Game::NeededVehicleXCoordtinate(){
        return p->NeededCarXCoordinate();
    }

    int Game::GetVehicleLocationIndex(){
        return p->GetIndex();
    }


    void Game::SlideCarToRight(float dt, float speed){
        p->MoveRight(dt, speed);
    }

    void Game::SlideCarToLeft(float dt, float speed){
        p->MoveLeft(dt, speed);
    }



    void Game::MoveVehicleRight(){
        p->IncrementIndex();

        if(GetVehicleLocationIndex() == 3){
            //Car reaached the right lane, setting maxright to true
            maxRight = true;
        }
        maxLeft = false;
    }

    void Game::MoveVehicleLeft(){
        p->DecrementIndex();


        if(GetVehicleLocationIndex() == 0){
            //Car reaached the left lane, setting maxleft to true
            maxLeft = true;
        }
        maxRight = false;
    }

    bool Game::IsMaxLeft(){
        if(maxLeft){
            return true;
        }else{
            return false;
        }
    }


    bool Game::IsMaxRight(){
        if(maxRight){
            return true;
        }else{
            return false;
        }
    }

    void Game::SetEngineSoundPitch(float pitch){
        engineSoundPitch = pitch;
        hgep->Channel_SetPitch(engineSoundChannel, engineSoundPitch);

    }




