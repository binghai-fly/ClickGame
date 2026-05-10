#pragma once
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <cmath>  
#include<vector>
#pragma comment(lib,"msimg32.lib")

#define W 918
#define H 515
#define MAX_MONSTERS 10
#define MAX_ATTACKS 5
#define MAX_BG_TILES 1
#define MAX_MONSTER_ATTACKS 8  // 新增：怪兽攻击最大数量

// 游戏状态
enum GameState {
    MENU,        // 菜单
    PLAYING,     // 游戏中
    INTRO        // 游戏介绍界面（新增）
};
extern GameState gameState;

// 玩家结构体
struct Player {
    IMAGE idle, run;       // 普通皮肤
    IMAGE skill_idle, skill_run; // Q技能皮肤
    int x, y;
    int anim_frame;
    int anim_timer;
    int anim_speed;
    int state;

    // 新增！！！
    int hp;               // 血量 0-3
    int coins;            // 金币
    bool is_invincible;   // 无敌状态
    DWORD skill_time;     // 技能计时
    bool skill_using;    // 技能使用中
};
extern Player player;

// 背景
struct BackgroundTile {
    int x, y, w, h;
    IMAGE img;
};
extern BackgroundTile bgTiles[MAX_BG_TILES];

// 宝石
struct Gem {
    int x, y, w, h;
    IMAGE img;
    bool isAlive;
};
extern Gem gem;

// 怪兽
struct Monster {
    int x, y, w, h, vx, vy;
    IMAGE img;
    bool isAlive;
    DWORD attackCD;
};
extern Monster monsters[MAX_MONSTERS];

// 玩家攻击
struct Attack {
    int x, y, w, h, vx, vy;
    IMAGE img;
    bool isAlive;
};
extern Attack attacks[MAX_ATTACKS];

// 新增：怪兽攻击结构体
struct MonsterAttack {
    int x, y, w, h, vx, vy;
    IMAGE img;
    bool isAlive;
};
extern MonsterAttack monsterAttacks[MAX_MONSTER_ATTACKS];

// 菜单全局变量
extern int btnX, btnY,btnx,btny;
extern const int BTN_W, BTN_H;
extern MOUSEMSG m;
extern int closeBtnX;
extern int closeBtnY;
// 函数声明
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
// 新增：怪兽攻击相关函数声明
void MonsterAttackInit();
void MonsterAttackSpawn(int monsterX, int monsterY);
void MonsterAttackUpdate();
void MonsterAttackDraw();
void drawIntro();

void PlayerInit(Player* p);
void PlayerDraw(Player* p);
void PlayerInput(Player* p);
void PlayerUpdateAnim(Player* p);
void DrawUI();