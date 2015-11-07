#include "Road.h"

        Road::Road(int StartX, int StartY, HTEXTURE _Texture){
            TrackSprite = new hgeSprite(_Texture, 0, 0, 249, 195);
            StartLoc.x = StartX;
            StartLoc.y = StartY;
            SpawnedNext = false;

            CurrentLoc = StartLoc;
        }

        Road::~Road(){
            delete TrackSprite;
        }

        bool Road::ReadyToSpawnNextSprite(){
            if(SpawnedNext == true){
                return false;
            }

            if(CurrentLoc.y >= StartLoc.y + 195){
                return true;
            }else{
                return false;
            }

        }

        bool Road::OutOfBounds(){
            if(CurrentLoc.y > 1000){
                return true;
            }else{
                return false;
            }
        }

        void Road::MoveRoad(float dt, float speed){
            CurrentLoc.y = CurrentLoc.y + speed * dt;
        }

        void Road::RenderRoad(){
            TrackSprite->Render(CurrentLoc.x, CurrentLoc.y);
        }

        void Road::SetSpawnedStatus(bool b){
            SpawnedNext = b;
        }
