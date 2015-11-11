#include "Enemy.h"




Enemy::Enemy(HTEXTURE EnemyTexture, hgeVector StartingPosition, HGE *h){
    hgep = h;
    CurrentLoc = StartingPosition;
    CarTexture = EnemyTexture;
    EnemySprite = new hgeSprite(CarTexture, 0, 0, 84, 183);

    ModifiedVelocity = false;
    VelocityModifier = 0;
}

Enemy::~Enemy(){
    delete EnemySprite;
}

void Enemy::RenderEnemy(){
    EnemySprite->Render(CurrentLoc.x, CurrentLoc.y);
}

void Enemy::MoveDown(float dt, float speed){
    //Logic function dictates that the base movement velocity for Enemy object is 350 units, it gets modified ONCE, this makes the cars go different speeds instead of robotish behaviour
    //TODO
    CurrentLoc.y = CurrentLoc.y + speed * dt;
}

hgeVector Enemy::GetEnemyLocationVector(){
    return CurrentLoc;
}

bool Enemy::OutOfBounds(){
    if(CurrentLoc.y > 800){
        return true;
    }else{
        return false;
    }
}

