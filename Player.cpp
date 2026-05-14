#include"head.h"

Player player; // 全局玩家实例

// 玩家初始化（移除地面/跳跃相关初始化）
void PlayerInit(Player* p) {
    // 普通皮肤
    loadimage(&p->idle, _T("picture/tile_0000.png"), 24, 24);
    loadimage(&p->run, _T("picture/tile_0001.png"), 24, 24);
    // Q技能皮肤
    loadimage(&p->skill_idle, _T("picture/tile_0006.png"), 24, 24);
    loadimage(&p->skill_run, _T("picture/tile_0007.png"), 24, 24);

    p->x = W / 2;
    p->y = H / 2;
    p->anim_frame = 0;
    p->anim_timer = 0;
    p->anim_speed = 5;
    p->state = 0;

    // 新增：初始状态
    p->hp = 3;         // 3条命
    p->coins = 0;      // 金币0
    p->is_invincible = false;
    p->skill_using = false;
    p->skill_time = 0;
    p->lastHitTime = 0;
}

// 玩家动画更新（移除跳跃状态判断）
void PlayerUpdateAnim(Player* p)
{
    static int lastState = -1;        // 记录上一帧的状态
    if (p->state != lastState) {
        // 状态切换：重置计时与帧
        p->anim_timer = 0;
        p->anim_frame = 0;
        lastState = p->state;
    }

    if (p->state == 1) {              // 移动中
        p->anim_timer++;
        if (p->anim_timer >= p->anim_speed) {
            p->anim_timer = 0;
            p->anim_frame = 1 - p->anim_frame;   // 0↔1 交替
        }
    }
    // 空闲状态不额外处理，保持 frame=0（由状态切换时的重置保证）
}

// 玩家绘制（移除jump帧逻辑）
void PlayerDraw(Player* p)
{
    IMAGE* curImg = NULL;

    // 根据动画帧选择贴图
    if (p->is_invincible) {
        curImg = (p->anim_frame == 0) ? &p->skill_idle : &p->skill_run;
    }
    else {
        curImg = (p->anim_frame == 0) ? &p->idle : &p->run;
    }

    
    if (curImg == NULL) return;

    int w = curImg->getwidth();
    int h = curImg->getheight();

    HDC dstDC = GetImageHDC(NULL);
    HDC srcDC = GetImageHDC(curImg);

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    AlphaBlend(dstDC, p->x, p->y, w * 1.5, h * 1.5,
        srcDC, 0, 0, w, h, blend);
}

// 玩家输入（纯自由移动，移除跳跃/地面判断）
void PlayerInput(Player* p) {
    if (gameState != PLAYING) return;
    // WASD/方向键移动
    int up = (GetAsyncKeyState('W') & 0x8000);
    int down = (GetAsyncKeyState('S') & 0x8000);
    int left = (GetAsyncKeyState('A') & 0x8000);
    int right = (GetAsyncKeyState('D') & 0x8000);
    int qat = (GetAsyncKeyState('Q') & 0x8000);
    int e= (GetAsyncKeyState('E') & 0x8000);
    
    // 自由移动逻辑（速度可自行调整）
    if (left)  p->x -= 5;
    if (right) p->x += 5;
    if (up)    p->y -= 5;
    if (down)  p->y += 5;
    if (qat) {
        if (!p->skill_using && p->coins >= 5) {
            p->coins -= 5;          // 扣金币
            p->is_invincible = true;// 无敌
            p->skill_using = true;  // 技能使用中
            p->skill_time = GetTickCount();
        }
    }
    if (p->skill_using && GetTickCount() - p->skill_time > 3000) {
        p->is_invincible = false;
        p->skill_using = false;
    }

    if (e) {
        TryBuyLife();
    }
    // 状态判断：有移动则为移动状态，否则空闲
    p->state = (left || right || up || down) ? 1 : 0;

    // 修复：边界限制适配1.5倍缩放（24*1.5=36）
    int playerScaledW = 24 * 1.5;
    int playerScaledH = 24 * 1.5;
    if (p->x < 0) p->x = 0;
    if (p->x > W - playerScaledW) p->x = W - playerScaledW;
    if (p->y < 0) p->y = 0;
    if (p->y > H - playerScaledH) p->y = H - playerScaledH;
}