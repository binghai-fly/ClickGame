#pragma once
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <cmath>  
#include<vector>
#include<mmsystem.h>
#include<tchar.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"msimg32.lib")

#define W 918
#define H 515
#define MAX_MONSTERS 10
#define MAX_ATTACKS 5
#define MAX_BG_TILES 1
#define MAX_MONSTER_ATTACKS 8
#define MAX_BOSS_ATTACKS 8
#define MAX_LANDMINE 8
#define MAX_BOOM 8
#define BOSS_ATTACK_COOLDOWN 1500 

enum GameState {
    MENU,       
    PLAYING,  
    INTRO,
    WIN,
    LOSE
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


struct BackgroundTile {
    int x, y, w, h;
    IMAGE img;
};
extern BackgroundTile bgTiles[MAX_BG_TILES];


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

// ȫ�ֻ�ɱ����
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
// ��������
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
extern int numm;

void PlayerInit(Player* p);
void PlayerDraw(Player* p);
void PlayerInput(Player* p);
void PlayerUpdateAnim(Player* p);
void BGLoad();
void DrawAllBgTiles();
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
