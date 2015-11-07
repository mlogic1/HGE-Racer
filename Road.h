#include <hgesprite.h>
#include <hgevector.h>

class Road{
    private:
        hgeSprite *TrackSprite;
        hgeVector StartLoc;
        hgeVector CurrentLoc;
        bool SpawnedNext;

    public:
        Road(int StartX, int StartY, HTEXTURE _Texture);

        ~Road();

        bool ReadyToSpawnNextSprite();

        void MoveRoad(float dt, float speed);

        void DoRoadLogic();

        void RenderRoad();

        void SetSpawnedStatus(bool b);

        bool OutOfBounds();

};
