#pragma once
#include<easyx.h>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include<stdlib.h>
#include <time.h>
#include <cmath>  
#include<vector>
#include<mmsystem.h>
#include<algorithm>
#include<tchar.h>
#include <fstream>
#include <wingdi.h> 
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"msimg32.lib")

#define W 1280
#define H 720
#define MAX_MONSTERS 10
#define MAX_ATTACKS 5
#define MAX_MONSTER_ATTACKS 8
#define MAX_BOSS_ATTACKS 8
#define MAX_LANDMINE 8
#define MAX_BOOM 8
#define BOSS_ATTACK_COOLDOWN 1500 
#define GROUND_Y  650
#define GRAVITY  1

#define ROLE_SIZE  150
#define ROLE_SIZE1  180
#define SHIELD_BLOCK_DIST  (ROLE_SIZE + ROLE_SIZE1) / 2 

enum GameState {
    MENU0,
    MENU1,
    MENU2,
    PLAYING1,
    PLAYING2,
    PLAYING2_2,
    INTRO1,
    INTRO2,
    INTRO2_1,
    INTRO2_2,
    WIN1,
    WIN2,
    LOSE1,
    LOSE2
};
extern GameState gameState;


struct Player {
    IMAGE idle, run;      
    IMAGE skill_idle, skill_run; 
    int x, y;
    int anim_frame;
    int anim_timer;
    int anim_speed;
    int state;

    int hp;             
    int coins;         
    bool is_invincible;   
    DWORD skill_time;     
    bool skill_using;   
    DWORD lastHitTime;
};
extern Player player;

struct Gem {
    int x, y, w, h;
    int state;
    int skill_time;
    IMAGE img1, img2;
    bool isAlive;
};
extern Gem gem;

struct Monster {
    int x, y, w, h, vx, vy;
    IMAGE img;
    bool isAlive;
    DWORD attackCD;
};
extern Monster monsters[MAX_MONSTERS];


struct Attack {
    int x, y, w, h, vx, vy;
    IMAGE img;
    bool isAlive;
};
extern Attack attacks[MAX_ATTACKS];


struct MonsterAttack {
    int x, y, w, h, vx, vy;
    IMAGE img;
    bool isAlive;
};
extern MonsterAttack monsterAttacks[MAX_MONSTER_ATTACKS];




struct Boss {
    int x, y, w, h, vx, vy;
    IMAGE img1, img2, img3;
    int anim_frame;
    int anim_timer;
    int anim_speed;
    int hp;
    int state;
    bool isAlive;
    bool bossSpawned;
    DWORD attackCD;              
};
extern Boss boss;

struct BossAttack {
    int x, y, w, h, vx, vy;
    IMAGE img;
    bool isAlive;
};
extern BossAttack bossAttacks[MAX_BOSS_ATTACKS];

extern int monstersKilledCount;

struct Landmine {
    int x, y;
    int w, h;
    IMAGE img;
    bool isAlive;
};
extern Landmine lm[MAX_LANDMINE];

struct Boom {
    int x, y, w, h;
    bool isAlive;
    IMAGE img;
    int startTime;
};
extern Boom boom[MAX_BOOM];


struct Fighter {
    int x, y;
    int speed;
    int vy;
    bool isOnGround;
    int face;

    bool isAttack;
    int attackTimer;
    bool isHit;
    int hitTimer;
    int attackCd;

    bool isDefending;
    int defendTimer;
    int defendCd;

    bool isUltimate;
    int ultimateTimer;
    int ultimateCd;

    bool isKnockback;
    int knockbackTimer;
    int knockbackSpeed;

    int hp;
    int maxHp;
    int damage;
    int ultimateDamage;
    int ultimateFace;
};
extern Fighter p1, p2;

extern IMAGE p1_run[3];
extern IMAGE p1_attack[4];
extern IMAGE p1_jump;
extern IMAGE p2_stand[3];
extern IMAGE p2_attack[3];
extern IMAGE p2_jump[3];
extern IMAGE bg;
extern IMAGE shield[2];
extern IMAGE dragon;
extern IMAGE snake;
extern IMAGE start;
extern IMAGE wini2;
extern IMAGE losei2;
extern IMAGE dd;
extern IMAGE btd;
extern IMAGE bt;
extern IMAGE btdgn;
extern IMAGE btgn;
extern IMAGE btdyw;
extern IMAGE btyw;


// 大招飞行物
struct Projectile {
    int x, y;
    int vx;
    bool active;
    int timer;
};

extern Projectile p1Ultimate, p2Ultimate;

void BossInit();
void BossSpawn();
void BossUpdate();
void BossDraw();
void BossUpdateAnim();
void BossTakeDamage(int damage);
void BossAttackInit();
void BossAttackSpawn(int bossX, int bossY);
void BossAttackUpdate();
void BossAttackDraw();
bool isBossAlive();
void TryBuyLife();       

extern int btnX, btnY,btnx,btny;
extern const int BTN_W, BTN_H;
extern MOUSEMSG m;
extern int closeBtnX;
extern int closeBtnY;
extern TCHAR num[20];
extern DWORD spawnTime;
extern DWORD attackCD;
extern const DWORD ATTACK_COOLDOWN;
extern IMAGE al;
extern IMAGE ar;
extern IMAGE bs;
extern IMAGE bSt;
extern IMAGE cross;
extern IMAGE home;
extern IMAGE mds;
extern IMAGE bkk;

void PlayerInit(Player* p);
void PlayerDraw(Player* p);
void PlayerInput(Player* p);
void PlayerUpdateAnim(Player* p);


void initMenu();
void drawMenu();
void GemInit();
void GemDraw();
void MonsterInit();
void MonsterSpawn();
void MonsterUpdate();
void MonsterDraw();
void AttackInit();
void AttackFire(int x, int y, int targetX, int targetY);
void AttackUpdate();
void AttackDraw();
int CheckGameCollision();
void DrawTransparentImage(int x, int y, IMAGE* img);

void MonsterAttackInit();
void MonsterAttackSpawn(int monsterX, int monsterY);
void MonsterAttackUpdate();
void MonsterAttackDraw();
void drawIntro();
void DrawUI();
void drawWin();
void lmInit();
void LayLm(int x, int y);
void lmDraw();
void drawLose();
void PlayBGM(const TCHAR* name);
void StopBGM();
void PlayWinMusic(const TCHAR* name);
void PlayLoseMusic(const TCHAR* name);
void PlayMineExplode(const TCHAR* name);
void bkDraw();
void drawMenu1();
bool isValidImage(IMAGE* img);
void safeLoadImage(IMAGE* img, const TCHAR* filename, int width, int height);
void drawHp(int x, int y, int w, int h, int hp, int maxHp, COLORREF color);
void drawFlip(IMAGE* img, int x, int y, int size, bool flip);
void Imageinit();
void drawAttackCd(int x, int y, int cd, int maxCd, const TCHAR* name);
void hitCheck();
bool canHit(Fighter* attacker, Fighter* target);
void ultimateHitCheck();
void shieldCollisionBlock();
void resetGame();
// Fighter module functions (defined in Fighter.cpp / Draw.cpp)
void update();      // update fighter game logic

void drawEvery();   // draw helper in Draw.cpp that doesn't Begin/Flush batch
void drawMenu2();   // menu 2 (拳皇) 绘制
// main loop update implemented in Update.cpp
void Update();
void drawlose2();
void drawWin2();
void drawIntro2();
void drawCross();
void drawRight();
void drawIntro2_1();
void drawIntro2_2();
void drawHome();
void PlayBGM2(const TCHAR* name);
void drawButton(int btx, int bty, IMAGE imgbt, IMAGE imgbtd);