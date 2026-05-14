#include "head.h"

Boss boss;
BossAttack bossAttacks[MAX_BOSS_ATTACKS];
IMAGE bossImg[3];
IMAGE bossAttackImg;

void BossAttackInit() {
    loadimage(&bossAttackImg, _T("picture/tile_0157.png"), 40, 40);
    for (int i = 0; i < MAX_BOSS_ATTACKS; i++) {
        bossAttacks[i].isAlive = false;
        bossAttacks[i].w = 40;
        bossAttacks[i].h = 40;
        bossAttacks[i].img = bossAttackImg;
        bossAttacks[i].vx = 0;
        bossAttacks[i].vy = 0;
    }
}

void BossInit() {
    loadimage(&bossImg[0], _T("picture/b1.png"), 24, 24);
    loadimage(&bossImg[1], _T("picture/b2.png"), 24, 24);
    loadimage(&bossImg[2], _T("picture/b3.png"), 24, 24);

    boss.img1 = bossImg[0];
    boss.img2 = bossImg[1];
    boss.img3 = bossImg[2];
    boss.w = 24;
    boss.h = 24;
    boss.vx = 2;
    boss.vy = 2;
    boss.anim_frame = 0;
    boss.anim_timer = 0;
    boss.anim_speed = 8;
    boss.hp = 10;
    boss.isAlive = false;
    boss.attackCD = 0;
    boss.bossSpawned = false;
    BossAttackInit();
}

void BossSpawn() {
    if (boss.isAlive) return;
    boss.isAlive = true;
    boss.hp = 10;
    boss.anim_frame = 0;
    boss.anim_timer = 0;
    boss.attackCD = GetTickCount();

    int side = rand() % 4;
    switch (side) {
    case 0: boss.x = rand() % (W - boss.w); boss.y = -boss.h; break;
    case 1: boss.x = rand() % (W - boss.w); boss.y = H; break;
    case 2: boss.x = -boss.w; boss.y = rand() % (H - boss.h); break;
    case 3: boss.x = W; boss.y = rand() % (H - boss.h); break;
    }
}

void BossUpdateAnim() {
    if (!boss.isAlive) return;
    boss.anim_timer++;
    if (boss.anim_timer >= boss.anim_speed) {
        boss.anim_timer = 0;
        boss.anim_frame = (boss.anim_frame + 1) % 4;
    }
}

void BossAttackSpawn(int bossX, int bossY) {
    int dirs[8][2] = {
        {-5, 0}, {5, 0}, {0, -5}, {0, 5},
        {-4, -4}, {4, -4}, {-4, 4}, {4, 4}
    };
    for (int i = 0; i < 8; i++) {
        int idx = -1;
        for (int j = 0; j < MAX_BOSS_ATTACKS; j++) {
            if (!bossAttacks[j].isAlive) {
                idx = j;
                break;
            }
        }
        if (idx == -1) break;
        BossAttack& ba = bossAttacks[idx];
        ba.isAlive = true;
        ba.x = bossX + 20 - ba.w / 2;
        ba.y = bossY + 20 - ba.h / 2;
        ba.vx = dirs[i][0];
        ba.vy = dirs[i][1];
    }
}

void BossUpdate() {
    if (!boss.isAlive) return;
    // ׷�����
    if (boss.x < player.x) boss.x += boss.vx;
    if (boss.x > player.x) boss.x -= boss.vx;
    if (boss.y < player.y) boss.y += boss.vy;
    if (boss.y > player.y) boss.y -= boss.vy;
    // �߽�
    if (boss.x < 0) boss.x = 0;
    if (boss.x > W - boss.w) boss.x = W - boss.w;
    if (boss.y < 0) boss.y = 0;
    if (boss.y > H - boss.h) boss.y = H - boss.h;
    // ����
    DWORD now = GetTickCount();
    if (now - boss.attackCD > BOSS_ATTACK_COOLDOWN) {
        BossAttackSpawn(boss.x, boss.y);
        boss.attackCD = now;
    }
    BossUpdateAnim();
}

void BossDraw() {
    if (!boss.isAlive) return;
    IMAGE* curImg = NULL;
    switch (boss.anim_frame) {
    case 0: curImg = &boss.img1; break;
    case 1: curImg = &boss.img2; break;
    case 2: curImg = &boss.img3; break;
    case 3: curImg = &boss.img1; break;
    }
    if (curImg) DrawTransparentImage(boss.x, boss.y, curImg);

    // ========== 新增：Boss 血条 UI ==========
    int barWidth = 60;          // 血条宽度
    int barHeight = 8;          // 血条高度
    int maxHp = 10;             // Boss 最大生命值（与 BossInit 中 hp=10 一致）
    int hpPercent = boss.hp * 100 / maxHp;
    int fillWidth = barWidth * boss.hp / maxHp;

    // 血条位置：Boss 头顶中央
    int barX = boss.x + (boss.w - barWidth) / 2;
    int barY = boss.y - 15;

    // 1. 灰色背景
    setfillcolor(RGB(40, 40, 40));
    solidrectangle(barX, barY, barX + barWidth, barY + barHeight);

    // 2. 红色生命值（按剩余比例填充）
    setfillcolor(RGB(255, 0, 0));
    solidrectangle(barX, barY, barX + fillWidth, barY + barHeight);

    // 3. 白色边框
    setlinecolor(WHITE);
    rectangle(barX, barY, barX + barWidth, barY + barHeight);
}

void BossTakeDamage(int damage) {
    if (!boss.isAlive) return;
    boss.hp -= damage;
    if (boss.hp <= 0) {
        boss.isAlive = false;
    }
}

void BossAttackUpdate() {
    for (int i = 0; i < MAX_BOSS_ATTACKS; i++) {
        if (bossAttacks[i].isAlive) {
            bossAttacks[i].x += bossAttacks[i].vx;
            bossAttacks[i].y += bossAttacks[i].vy;
            if (bossAttacks[i].x < 0 || bossAttacks[i].x > W ||
                bossAttacks[i].y < 0 || bossAttacks[i].y > H) {
                bossAttacks[i].isAlive = false;
            }
        }
    }
}

void BossAttackDraw() {
    for (int i = 0; i < MAX_BOSS_ATTACKS; i++) {
        if (bossAttacks[i].isAlive)
            DrawTransparentImage(bossAttacks[i].x, bossAttacks[i].y, &bossAttacks[i].img);
    }
}

bool isBossAlive() {
    return boss.isAlive;
}

void TryBuyLife() {
    if (boss.isAlive && player.coins >= 5 && player.hp < 3) {
        player.coins -= 5;
        player.hp++;
    }
}
