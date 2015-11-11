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

        EnemySpeed = 350;
        EnemyTexture = hgep->Texture_Load("Textures\\Vehicles\\sedan.png");


        t = new timer();
        t->start();



    }

    Game::~Game(){

        hgep->Effect_Free(engineSoundEffect);
        hgep->Texture_Free(CarTexture);
        delete p;
        delete t;
    }

    void Game::UpdateSpawnData(){
        EnemiesToSpawn = hgep->Random_Int(1,3);
        TimeUntillNextSpawn = hgep->Random_Int(4,7);
        t->reset();
    }


    //call this once per frame
    void Game::CheckTimer(){
        if(t->getTime() == TimeUntillNextSpawn){
            //Spawn enemies and request data restart




            UpdateSpawnData();
        }
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


    bool Game::CheckForCollision(){
        hgeVector PlayerVector;
        hgeVector EnemyVector;

        PlayerVector = p->GetPlayerLocationVector();

        for(int i=0; i < (int)Enemies.size(); i++){
            EnemyVector = Enemies[i]->GetEnemyLocationVector();

            if(PlayerVector.x < EnemyVector.x + 70 || PlayerVector.x + 70 < EnemyVector.x){
                if(PlayerVector.y < EnemyVector.y + 178 && PlayerVector.y + 178 > EnemyVector.y){
                    //Player collided enemy
                    return true;
                }
            }
        }

        return false;
    }


    void Game::RenderEnemies(){
        for(int i=0; i < (int)Enemies.size(); i++){
            Enemies[i]->RenderEnemy();
        }
    }



    //Call this once per frame
    void Game::EnemyLogicFunction(float dt){
        for(int i=0; i < (int)Enemies.size(); i++){
            Enemies[i]->MoveDown(dt, EnemySpeed);

            if(Enemies[i]->OutOfBounds()){
                //Delete enemy if he is out of bounds
                Enemies[i]->~Enemy();
                Enemies.erase(Enemies.begin() + i);
            }
        }
    }


    void Game::SpawnEnemy(int number){
        hgeVector DummySpawnPoint;
        DummySpawnPoint.x = 281;
        DummySpawnPoint.y = 0;
        Enemies.push_back(new Enemy(EnemyTexture, DummySpawnPoint, hgep));
    }



