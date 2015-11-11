#include "Enemy.h"




Enemy::Enemy(HTEXTURE EnemyTexture, hgeVector StartingPosition, HGE *h){
    hgep = h;
    CurrentLoc = StartingPosition;
    CarTexture = EnemyTexture;
    EnemySprite = new hgeSprite(CarTexture, 0, 0, 84, 183);
}

Enemy::~Enemy(){
    delete EnemySprite;
}

void Enemy::RenderEnemy(){
    EnemySprite->Render(CurrentLoc.x, CurrentLoc.y);
}

void Enemy::MoveDown(float dt, float speed){
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

