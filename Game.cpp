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

        EnemySpeed = 500;   //Original value: 350
        EnemyTexture = hgep->Texture_Load("Textures\\Vehicles\\sedan.png");


        t = new timer();
        t->start();


        EnemiesToSpawn = hgep->Random_Int(1,3); //Must set this to something, otherwise the game is going to try to spawn negative amount of enemies
    }

    Game::~Game(){

        hgep->Effect_Free(engineSoundEffect);
        hgep->Texture_Free(CarTexture);
        delete p;
        delete t;
    }

    void Game::UpdateSpawnData(){
        EnemiesToSpawn = hgep->Random_Int(1,3);
        TimeUntillNextSpawn = hgep->Random_Int(1,2);        //Time between enemy spawn intervals 1 and 2 seconds, this function is provided by the engine
        t->reset();
    }

    /*
    Try:
    change the time to a double and use xxx = Random_Int(100,300)/100

    */

    //call this once per frame
    void Game::CheckTimer(){
        if(t->getTime() >= TimeUntillNextSpawn){
            //Spawn enemies and request data restart
            SpawnEnemy(EnemiesToSpawn);
            UpdateSpawnData();
        }
    }

    unsigned long Game::GetTimerTime(){
        return t->getTime();
    }

    int Game::GetNextIntervalEnemyCount(){
        return EnemiesToSpawn;
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
        //hgeVector EnemyVector;

        PlayerVector = p->GetPlayerLocationVector();        //p is the player class (basically the red car and some logic behind it)

        int CarY = PlayerVector.y;
        int CarWidth = 84;
        int CarHeight = 183;



        for(int i = 0 ; i < (int)Enemies.size(); i ++){
            hgeVector EnemyVector = Enemies[i]->GetEnemyLocationVector();


            if(PlayerVector.x + CarWidth > EnemyVector.x && PlayerVector.x < EnemyVector.x + CarWidth){
                if(CarY + CarHeight > EnemyVector.y && CarY < EnemyVector.y + CarHeight){
                    return true;    //collision happened
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
        /*  Fixed X Axis spawn points for the enemy  */
        int LocationCoordinates[4];
        LocationCoordinates[0] = 281;
        LocationCoordinates[1] = 388;
        LocationCoordinates[2] = 530;
        LocationCoordinates[3] = 637;

        int RandomInt13;
        hgeVector StartingPoint;
        StartingPoint.y = -200;
        vector<int> OccupiedIndexes;
        bool Prepared = false;


        /*
        1. Generate Random number (0,3)
        2. Check if that number exists
            YES->Go to step 1
            NO-> Add it to the vector
        3. Is the vector Size == number (from parameter?)
            YES ->Spawn to step 4
            NO -> Go to step 1
        4. Spawn the enemies
        5. Clear the vector

        */

        RandomInt13 = hgep->Random_Int(0,3);
        OccupiedIndexes.push_back(RandomInt13);


        while(!Prepared){
            RandomInt13 = hgep->Random_Int(0,3);
            int vectorsize = (int)OccupiedIndexes.size();
            for(int i=0;i < vectorsize; i++){
                if(OccupiedIndexes[i] == RandomInt13){
                    //it exists, do nothing
                }else{
                    OccupiedIndexes.push_back(RandomInt13);
                    break;
                }
            }

            if(vectorsize == number){
                Prepared = true;
            }
        }






        for(int i = 0; i < number ; i++){
            StartingPoint.x = LocationCoordinates[OccupiedIndexes[i]];
            Enemies.push_back(new Enemy(EnemyTexture, StartingPoint, hgep));
        }


        OccupiedIndexes.clear();    //Clear for the next interval
    }


    void Game::PrintPlayerLocation(hgeFont *text){
        int X1, Y1, X2, Y2;
        hgeVector Vector = p->GetPlayerLocationVector();
        X1 = Vector.x;
        Y1 = Vector.y;

        X2 = Vector.x + 70;
        Y2 = Vector.y + 178;

        text->printf(3,203, HGETEXT_LEFT, "X1: %d Y1: %d X2:%d Y2: %d", X1, Y1, X2, Y2);
    }



