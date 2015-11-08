#include <hgevector.h>
#include <hgesprite.h>
#include <hgefont.h>
#include <vector>

#include "Timer.h"
#include "Game.h"
#include "Road.h"

using namespace std;


HGE *hgep;

hgeFont *text;
timer *t;

Game *g;


/*Road variable*/
//These vectors store left and right in-game lane road objects

HTEXTURE TrackTexture;
vector<Road*> RoadsRight;
vector<Road*> RoadsLeft;


//This method checks if the player vehicle isn't in position it's supposed to be and then calls methods in Game object to correct the location if needed
void SmoothCarMovement(float dt){
    float transitionSpeed = 500;    //Speed the car moves left / right


    if(g->GetVehicleXLocation() != g->NeededVehicleXCoordtinate()){
        if(g->GetVehicleXLocation() < g->NeededVehicleXCoordtinate()){
            //Car needs to go right
            g->SlideCarToRight(dt, transitionSpeed);
            g->SetEngineSoundPitch(1.1);
        }else{
            //car needs to go left
            g->SlideCarToLeft(dt, transitionSpeed);
            g->SetEngineSoundPitch(1.1);
        }
    }else{
        g->SetEngineSoundPitch(1.0);
    }
}



//Creates a new Road object in road vector(s)
void AddRoadSpriteToVector(int x){
    if(x == 1){
        RoadsLeft.push_back(new Road(251, -250, TrackTexture));
    }

    if(x == 2){
        RoadsRight.push_back(new Road(500, -250, TrackTexture));
    }

}


void KeyboardInput(){
    /*MOVEMENT KEYS*/

    if(hgep->Input_KeyDown(HGEK_A)){
        //move car left
        if(g->IsMaxLeft()){
            //car is on the most left lane, so it cannot go left
        }else{
            g->MoveVehicleLeft();
        }
    }

    if(hgep->Input_KeyDown(HGEK_D)){
        //move car right
        if(g->IsMaxRight()){
            //car is on the most right lane, so it cannot go right
        }else{
            g->MoveVehicleRight();
        }
    }

}

bool GameFrameFunction(){
    if (hgep->Input_GetKeyState(HGEK_ESCAPE)) return true;

    float dt = hgep->Timer_GetDelta();

    SmoothCarMovement(dt);


    for(int i=0;i<(int)RoadsRight.size();i++){
        RoadsRight[i]->MoveRoad(dt, 400);
        if(RoadsRight[i]->ReadyToSpawnNextSprite()){
            AddRoadSpriteToVector(2);
            RoadsRight[i]->SetSpawnedStatus(true);
        }
        //sprite is out of bounds, delete it
        if(RoadsRight[i]->OutOfBounds()){
            RoadsRight[i]->~Road();
            RoadsRight.erase(RoadsRight.begin() + i);
        }
    }


    for(int i=0;i<(int)RoadsLeft.size();i++){
        RoadsLeft[i]->MoveRoad(dt, 400);
        if(RoadsLeft[i]->ReadyToSpawnNextSprite()){
            AddRoadSpriteToVector(1);
            RoadsLeft[i]->SetSpawnedStatus(true);
        }
        //sprite is out of bounds, delete it
        if(RoadsLeft[i]->OutOfBounds()){
            RoadsLeft[i]->~Road();
            RoadsLeft.erase(RoadsLeft.begin() + i);
        }
    }


    KeyboardInput();

    return false;
}


bool GameRenderFunction(){
    hgep->Gfx_BeginScene();
    hgep->Gfx_Clear(0);

    /*RENDER GOES HERE*/
    //render background first
    g->RenderBackground();

    int RoadCount;
    RoadCount = (int)RoadsLeft.size() + (int)RoadsRight.size();
    text->printf(3 , 3, HGETEXT_LEFT, "Get time: %u \nIs running: %s\nRoad Objects: %d\nVehicle loc. index: %d", t->getTime(), t->isRunning() ? "true" : "false", RoadCount, g->GetVehicleLocationIndex());


    //render roads
    for(int i=0;i<(int)RoadsRight.size();i++){
        RoadsRight[i]->RenderRoad();
    }

    for(int i=0;i<(int)RoadsLeft.size();i++){
        RoadsLeft[i]->RenderRoad();
    }

    g->RenderVehicle();


    hgep->Gfx_EndScene();
    /*RENDER ENDS HERE*/

    return false;
    }

void StartSinglePlayerGame(HGE *h){
    hgep = h;

    g = new Game(hgep);


    text = new hgeFont("Fonts\\font1.fnt");
    TrackTexture = hgep->Texture_Load("Textures\\Track1.png");
    t = new timer();

    AddRoadSpriteToVector(1);
    AddRoadSpriteToVector(2);

    g->PlayVehicleSound();

    //This piece of code is supposed to take over rendering and logic from main menu
    hgep->System_SetState(HGE_FRAMEFUNC, GameFrameFunction);
    hgep->System_SetState(HGE_RENDERFUNC, GameRenderFunction);
    hgep->System_SetState(HGE_HIDEMOUSE, true);

}








