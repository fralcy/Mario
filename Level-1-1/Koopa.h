#pragma once
#include "GameObject.h"
#include "Pathfinder.h"

#define KOOPA_GRAVITY 0.002f

#define KOOPA_WALKING_SPEED 0.025f
#define KOOPA_SPINNING_SPEED 0.2f
#define KOOPA_FLYING_SPEED_X 0.05f
#define KOOPA_FLYING_SPEED_Y 0.4f

#define KOOPA_KNOCKED_SPEED_X 0.1f
#define KOOPA_KNOCKED_SPEED_Y 0.3f

#define KOOPA_WIDTH 16
#define KOOPA_HEIGHT 24
#define KOOPA_SHELL_HEIGHT 14

#define KOOPA_HIDE_TIME 4000
#define KOOPA_RECOVER_TIME 2000
#define KOOPA_FLY_DELAY_TIME 500

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_SHELL 200
#define KOOPA_STATE_RECOVER 300
#define KOOPA_STATE_KNOCKED 400

#define ID_ANI_KOOPA_WALKING_LEFT_RED 33110
#define ID_ANI_KOOPA_WALKING_RIGHT_RED 33120
#define ID_ANI_KOOPA_SHELL_RED 33130
#define ID_ANI_KOOPA_SPINNING_LEFT_RED 33140
#define ID_ANI_KOOPA_SPINNING_RIGHT_RED 33150
#define ID_ANI_KOOPA_RECOVER_RED 33160

#define ID_ANI_KOOPA_WALKING_LEFT_GREEN 33200
#define ID_ANI_KOOPA_WALKING_RIGHT_GREEN 33210
#define ID_ANI_KOOPA_SHELL_GREEN 33220
#define ID_ANI_KOOPA_SPINNING_LEFT_GREEN 33230
#define ID_ANI_KOOPA_SPINNING_RIGHT_GREEN 33240
#define ID_ANI_KOOPA_RECOVER_GREEN 33250
#define ID_ANI_PARAKOOPA_WALKING_LEFT_GREEN 33260
#define ID_ANI_PARAKOOPA_WALKING_RIGHT_GREEN 33270

#define KOOPA_COLOR_RED 1
#define KOOPA_COLOR_GREEN 2

#define KOOPA_TYPE_NORMAL 0
#define KOOPA_TYPE_WINGED 1
class CKoopa : public CGameObject
{
protected:
    int color;
    int type;
    float ax;
    float ay;
    CPathfinder* pathfinder;
    ULONGLONG hide_start, recover_start, fly_start;
    bool isKnocking = false;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }
    virtual void OnNoCollision(DWORD dt);

    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
    void OnCollisionWithMysteryBlock(LPCOLLISIONEVENT e);
    void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
    void OnCollisionWithPlant(LPCOLLISIONEVENT e);
    void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
    void Fly();
public:
    CKoopa(float x, float y, int color, int type);
    virtual void SetState(int state);
    void Render();
    int GetType() { return type; }
    void SetType(int type) { this->type = type; if (type == KOOPA_TYPE_NORMAL) SetState(KOOPA_STATE_WALKING); }
};
