#include "head.h"

GameState gameState = MENU;
Gem gem;
Monster monsters[MAX_MONSTERS];
Attack attacks[MAX_ATTACKS];
IMAGE monsterImg;
IMAGE monsterAttackImg;
MonsterAttack monsterAttacks[MAX_MONSTER_ATTACKS];
DWORD monsterAttackCD = 0;
const DWORD MONSTER_ATTACK_COOLDOWN = 1000;

void GemInit() {
    gem.w = 40;
    gem.h = 40;
    gem.x = W / 2 - gem.w / 2;
    gem.y = H / 2 - gem.h / 2;
    gem.isAlive = true;
    loadimage(&gem.img, _T("gem.png"), gem.w, gem.h);
}

void GemDraw() {
    if (gem.isAlive)
        DrawTransparentImage(gem.x, gem.y, &gem.img);
}

void MonsterInit() {
    loadimage(&monsterImg, _T("monster.png"), 40, 40);
    for (int i = 0; i < MAX_MONSTERS; i++) {
        monsters[i].isAlive = false;
        monsters[i].w = 40;
        monsters[i].h = 40;
        monsters[i].vx = 2;
        monsters[i].vy = 2;
        monsters[i].img = monsterImg;
        monsters[i].attackCD = 0;
    }
    MonsterAttackInit();
}

void MonsterAttackInit() {
    loadimage(&monsterAttackImg, _T("monster_attack.png"), 24, 24);
    for (int i = 0; i < MAX_MONSTER_ATTACKS; i++) {
        monsterAttacks[i].isAlive = false;
        monsterAttacks[i].w = 24;
        monsterAttacks[i].h = 24;
        monsterAttacks[i].img = monsterAttackImg;
        monsterAttacks[i].vx = 0;
        monsterAttacks[i].vy = 0;
    }
}

void MonsterAttackSpawn(int monsterX, int monsterY) {
    int dirs[8][2] = {
        {-5, 0}, {5, 0}, {0, -5}, {0, 5},
        {-4, -4}, {4, -4}, {-4, 4}, {4, 4}
    };

    for (int i = 0; i < 8; i++) {
        int idx = -1;
        for (int j = 0; j < MAX_MONSTER_ATTACKS; j++) {
            if (!monsterAttacks[j].isAlive) {
                idx = j;
                break;
            }
        }
        if (idx == -1) break;

        MonsterAttack& ma = monsterAttacks[idx];
        ma.isAlive = true;
        ma.x = monsterX + 24 - ma.w / 2;
        ma.y = monsterY + 24 - ma.h / 2;
        ma.vx = dirs[i][0];
        ma.vy = dirs[i][1];
    }
}

void MonsterSpawn() {
    int idx = -1;
    for (int i = 0; i < MAX_MONSTERS; i++) {
        if (!monsters[i].isAlive) {
            idx = i;
            break;
        }
    }
    if (idx == -1) return;
    Monster& m = monsters[idx];
    m.isAlive = true;
    int side = rand() % 4;
    if (side == 0) { m.x = rand() % W; m.y = -40; }
    if (side == 1) { m.x = rand() % W; m.y = H; }
    if (side == 2) { m.x = -40; m.y = rand() % H; }
    if (side == 3) { m.x = W; m.y = rand() % H; }
}

void MonsterUpdate() {
    for (int i = 0; i < MAX_MONSTERS; i++) {
        if (!monsters[i].isAlive) continue;
        Monster& m = monsters[i];
        if (m.x < gem.x) m.x += m.vx;
        if (m.x > gem.x) m.x -= m.vx;
        if (m.y < gem.y) m.y += m.vy;
        if (m.y > gem.y) m.y -= m.vy;
    }

    DWORD now = GetTickCount();
    for (int i = 0; i < MAX_MONSTERS; i++) {
        Monster& monster = monsters[i];
        if (!monster.isAlive) continue;
        if (now - monster.attackCD > MONSTER_ATTACK_COOLDOWN) {
            MonsterAttackSpawn(monster.x, monster.y);
            monster.attackCD = now;
        }
    }
}

void MonsterAttackUpdate() {
    for (int i = 0; i < MAX_MONSTER_ATTACKS; i++) {
        if (monsterAttacks[i].isAlive) {
            monsterAttacks[i].x += monsterAttacks[i].vx;
            monsterAttacks[i].y += monsterAttacks[i].vy;
            if (monsterAttacks[i].x < 0 || monsterAttacks[i].x > W ||
                monsterAttacks[i].y < 0 || monsterAttacks[i].y > H) {
                monsterAttacks[i].isAlive = false;
            }
        }
    }
}

void MonsterDraw() {
    for (int i = 0; i < MAX_MONSTERS; i++) {
        if (monsters[i].isAlive)
            DrawTransparentImage(monsters[i].x, monsters[i].y, &monsters[i].img);
    }
}

void MonsterAttackDraw() {
    for (int i = 0; i < MAX_MONSTER_ATTACKS; i++) {
        if (monsterAttacks[i].isAlive)
            DrawTransparentImage(monsterAttacks[i].x, monsterAttacks[i].y, &monsterAttacks[i].img);
    }
}

void AttackInit() {
    for (int i = 0; i < MAX_ATTACKS; i++) {
        attacks[i].isAlive = false;
        attacks[i].w = 20;
        attacks[i].h = 20;
        loadimage(&attacks[i].img, _T("attack.png"), 20, 20);
    }
}

void AttackFire(int x, int y, int targetX, int targetY) {
    int count = player.is_invincible ? 3 : 1;
    float angles[] = { -0.3f, 0, 0.3f };

    // 玩家缩放后中心坐标
    int centerX = x + 18;      // 24*1.5/2 = 18
    int centerY = y + 18;
    if (count == 1) {
        int idx = -1;
        for (int i = 0; i < MAX_ATTACKS; i++) {
            if (!attacks[i].isAlive) {
                idx = i;
                break;
            }
        }
        if (idx == -1) return;

        Attack& attack = attacks[idx];
        attack.x = x + 12;
        attack.y = y + 12;
        attack.isAlive = true;

        int dx = targetX - attack.x;
        int dy = targetY - attack.y;
        float dist = sqrt(dx * dx + dy * dy);
        if (dist == 0) dist = 1;

        attack.vx = (dx / dist) * 12;
        attack.vy = (dy / dist) * 12;
    }
    else {
        for (int i = 0; i < count; i++) {
            int idx = -1;
            for (int j = 0; j < MAX_ATTACKS; j++) {
                if (!attacks[j].isAlive) {
                    idx = j;
                    break;
                }
            }
            if (idx == -1) return;

            Attack& a = attacks[idx];
            a.x = centerX - 12;    // 子弹左上角 = 中心 - 半宽(20/2)
            a.y = centerY - 12;
            a.isAlive = true;

            int dx = targetX - centerX;
            int dy = targetY - centerY;

            float rad = angles[i];
            float new_dx = dx * cos(rad) - dy * sin(rad);
            float new_dy = dx * sin(rad) + dy * cos(rad);

            float dist = sqrt(new_dx * new_dx + new_dy * new_dy);
            if (dist == 0) dist = 1;
            a.vx = (new_dx / dist) * 12;
            a.vy = (new_dy / dist) * 12;
        }
    
    }
}

void AttackUpdate() {
    for (int i = 0; i < MAX_ATTACKS; i++) {
        if (attacks[i].isAlive) {
            attacks[i].x += attacks[i].vx;
            attacks[i].y += attacks[i].vy;
            if (attacks[i].x < 0 || attacks[i].x > W ||
                attacks[i].y < 0 || attacks[i].y > H) {
                attacks[i].isAlive = false;
            }
        }
    }
}

void AttackDraw() {
    for (int i = 0; i < MAX_ATTACKS; i++) {
        if (attacks[i].isAlive)
            DrawTransparentImage(attacks[i].x, attacks[i].y, &attacks[i].img);
    }
}

bool AABBCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    return (x1 < x2 + w2) && (x1 + w1 > x2) && (y1 < y2 + h2) && (y1 + h1 > y2);
}

int CheckGameCollision() {
    // 玩家攻击 vs 怪兽
    for (int i = 0; i < MAX_MONSTERS; i++) {
        if (!monsters[i].isAlive) continue;
        for (int j = 0; j < MAX_ATTACKS; j++) {
            if (!attacks[j].isAlive) continue;
            if (AABBCollision(attacks[j].x, attacks[j].y, 20, 20, monsters[i].x, monsters[i].y, 40, 40)) {
                monsters[i].isAlive = false;
                attacks[j].isAlive = false;
                player.coins += 1;
            }
        }
    }

    if (player.is_invincible) return 0;

    // 怪兽攻击 vs 玩家
    for (int i = 0; i < MAX_MONSTER_ATTACKS; i++) {
        if (monsterAttacks[i].isAlive && AABBCollision(monsterAttacks[i].x, monsterAttacks[i].y, 24, 24, player.x, player.y, 36, 36)) {
            player.hp--;
            monsterAttacks[i].isAlive = false;
            return player.hp <= 0 ? 1 : 0;
        }
    }

    // 怪兽碰撞玩家或宝石
    for (int i = 0; i < MAX_MONSTERS; i++) {
        if (!monsters[i].isAlive) continue;
        if (AABBCollision(monsters[i].x, monsters[i].y, 40, 40, player.x, player.y, 36, 36)) {
            player.hp--;
            monsters[i].isAlive = false;
            return player.hp <= 0 ? 1 : 0;
        }
        if (AABBCollision(monsters[i].x, monsters[i].y, 40, 40, gem.x, gem.y, gem.w, gem.h)) {
            return 1; // 宝石被摧毁，游戏结束
        }
    }

    return 0;
}

void DrawTransparentImage(int x, int y, IMAGE* img) {
    if (!img) return;
    int w = img->getwidth();
    int h = img->getheight();
    HDC dst = GetImageHDC(NULL);
    HDC src = GetImageHDC(img);
    BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    AlphaBlend(dst, x, y, w, h, src, 0, 0, w, h, bf);
}