#include"head.h"

Fighter p1, p2;

IMAGE p1_run[3];
IMAGE p1_attack[4];
IMAGE p1_jump;
IMAGE p2_stand[3];
IMAGE p2_attack[3];
IMAGE p2_jump[3];
IMAGE bg;
IMAGE shield[2];
IMAGE dragon;
IMAGE snake;



void updateAI() {
    if ( gameState == LOSE2 || gameState == WIN2 ) return;
    if (p2.hp <= 0) return;
    if (p2.isHit) return;
    if (p2.isKnockback) return;

    int distance = p1.x - p2.x;
    int absDistance = abs(distance);

    // If enemy is far, move toward player. Reduced threshold to avoid dead zone where AI stands still.
    if (absDistance > 80) {
        if (distance > 0) p2.x += p2.speed;
        else p2.x -= p2.speed;
        p2.face = (distance > 0) ? 1 : -1;
    }
    else if (absDistance < 60 && !p2.isAttack && p2.attackCd == 0) {
        if (distance > 0) p2.x -= p2.speed;
        else p2.x += p2.speed;
    }

    if (p2.x < 10) p2.x = 10;
    if (p2.x > W - ROLE_SIZE1 - 10) p2.x = W - ROLE_SIZE1 - 10;

    // 当血量低时优先防御，但不应完全放弃进攻：使用概率决定防御或主动进攻
    if (p2.hp < 120 && !p2.isDefending && !p2.isAttack && p2.defendTimer == 0 && absDistance < 120) {
        int defendChance = 70; 
        if (p2.attackCd == 0 && (rand() % 100) >= defendChance) {
            // 尝试主动进攻
            p2.isAttack = true;
            p2.attackTimer = 0;
        }
        else {
            // 选择防御
            p2.isDefending = true;
            p2.defendTimer = 30;
            p2.defendCd = 60;
            if (p1.x > p2.x) p2.face = 1;
            else p2.face = -1;
        }
    }

    if (p2.isOnGround && !p2.isAttack && p2.attackCd == 0 && rand() % 100 == 0) {
        if (absDistance < 180) {
            p2.vy = -18;
            p2.isOnGround = false;
        }
    }

    if (!p2.isAttack && !p2.isHit && absDistance < 120 && p2.isOnGround && p2.attackCd == 0) {
        int attackChance = 0;
        if (absDistance < 80) attackChance = 12;
        else if (absDistance < 120) attackChance = 8;

        if (rand() % 100 < attackChance) {
            p2.isAttack = true;
            p2.attackTimer = 0;
        }
    }

    if (p2.ultimateCd == 0 && !p2.isUltimate && !p2.isAttack && absDistance < 200) {
        bool shouldUltimate = false;
        if (p2.hp < 150) shouldUltimate = true;
        else if (rand() % 200 == 0) shouldUltimate = true;

        if (shouldUltimate) {
            p2.isUltimate = true;
            p2.ultimateTimer = 0;
            p2.ultimateCd = 180;
        }
    }
}


void update() {
    if (p1.hp <= 0 ) {
        gameState = LOSE2;
    }

    if (p2.hp <= 0) {
        gameState = WIN2;
    }

    if (gameState==LOSE2||gameState==WIN2) {
        p1.isAttack = false;
        p2.isAttack = false;
        p1.isUltimate = false;
        p2.isUltimate = false;
       
    }

    if (p1.attackCd > 0) p1.attackCd--;
    if (p2.attackCd > 0) p2.attackCd--;
    if (p1.ultimateCd > 0) p1.ultimateCd--;
    if (p2.ultimateCd > 0) p2.ultimateCd--;
    if (p1.defendCd > 0) p1.defendCd--;    // 防御CD递减
    if (p2.defendCd > 0) p2.defendCd--;

    if (p1.defendTimer > 0) {
        p1.defendTimer--;
        if (p1.defendTimer <= 0) p1.isDefending = false;
    }
    if (p2.defendTimer > 0) {
        p2.defendTimer--;
        if (p2.defendTimer <= 0) p2.isDefending = false;
    }

    if (p1.isKnockback) {
        p1.x += p1.knockbackSpeed;
        p1.knockbackTimer++;
        if (p1.knockbackTimer >= 10) {
            p1.isKnockback = false;
            p1.knockbackSpeed = 0;
        }
        if (p1.x < 50) p1.x = 50;
        if (p1.x > W - ROLE_SIZE - 50) p1.x = W - ROLE_SIZE - 50;
    }

    if (p2.isKnockback) {
        p2.x += p2.knockbackSpeed;
        p2.knockbackTimer++;
        if (p2.knockbackTimer >= 10) {
            p2.isKnockback = false;
            p2.knockbackSpeed = 0;
        }
        if (p2.x < 50) p2.x = 50;
        if (p2.x > W - ROLE_SIZE1 - 50) p2.x = W - ROLE_SIZE1 - 50;
    }

    if (!p1.isHit && !p1.isKnockback && p1.hp > 0) {
        if (GetAsyncKeyState('A') & 0x8000) {
            p1.x -= p1.speed;
            p1.face = 1;
        }
        if (GetAsyncKeyState('D') & 0x8000) {
            p1.x += p1.speed;
            p1.face = -1;
        }

        static bool sWasPressed = false;
        bool sIsPressed = (GetAsyncKeyState('S') & 0x8000);
        if (sIsPressed && !sWasPressed && !p1.isDefending && p1.defendCd == 0) {
            sWasPressed = true;
            p1.isDefending = true;
            p1.defendTimer = 30;
            p1.defendCd = 60;    // 冷却 1 秒
        }
        if (!sIsPressed) sWasPressed = false;

        if (p1.x < 10) p1.x = 0;
        if (p1.x > W - ROLE_SIZE - 10) p1.x = W - ROLE_SIZE - 10;

        static bool spaceWasPressed = false;
        bool spaceIsPressed = (GetAsyncKeyState(VK_SPACE) & 0x8000);
        if (spaceIsPressed && !spaceWasPressed && p1.isOnGround) {
            p1.vy = -18;
            p1.isOnGround = false;
        }
        spaceWasPressed = spaceIsPressed;

        static bool jdown = 0;
        if ((GetAsyncKeyState('J') & 0x8000) && !jdown && !p1.isAttack && p1.attackCd == 0) {
            jdown = 1;
            p1.isAttack = true;
            p1.attackTimer = 0;
        }
        if (!(GetAsyncKeyState('J') & 0x8000)) jdown = 0;

        static bool kWasPressed = false;
        bool kIsPressed = (GetAsyncKeyState('K') & 0x8000);
        if (kIsPressed && !kWasPressed && !p1.isUltimate && p1.ultimateCd == 0 && p1.hp > 0) {
            p1.isUltimate = true;
            p1.ultimateFace = p1.face; // lock facing when ultimate starts
            p1.ultimateTimer = 0;
            p1.ultimateCd = 180;
        }
        kWasPressed = kIsPressed;
    }

    // P1大招释放
    if (p1.isUltimate) {
        p1.ultimateTimer++;
        if (p1.ultimateTimer == 10) {
            p1Ultimate.active = true;
            // use locked facing stored at activation time
            if (p1.ultimateFace == -1) {
                p1Ultimate.x = p1.x + ROLE_SIZE/2;
                p1Ultimate.vx = 15;
            }
            else {
                p1Ultimate.x = p1.x - 80/2;
                p1Ultimate.vx = -15;
            }
            p1Ultimate.y = p1.y + 40;
            p1Ultimate.timer = 0;
            p1.isUltimate = false;
        }
    }

    // P2大招释放
    if (p2.isUltimate) {
        p2.ultimateTimer++;
        if (p2.ultimateTimer == 10) {
            p2Ultimate.active = true;
            // p2.face == 1 means facing right (set in updateAI), spawn projectile accordingly
            // Determine direction towards player at the moment of release (AI should aim at player)
            if (p1.x > p2.x) {
                p2Ultimate.x = p2.x + ROLE_SIZE1/2;
                p2Ultimate.vx = 15;
            }
            else {
                p2Ultimate.x = p2.x - 80/2;
                p2Ultimate.vx = -15;
            }
            p2Ultimate.y = p2.y + 40;
            p2Ultimate.timer = 0;
            p2.isUltimate = false;
        }
    }

    if (p1Ultimate.active) {
        p1Ultimate.x += p1Ultimate.vx;
        p1Ultimate.timer++;
        if (p1Ultimate.timer > 60 || p1Ultimate.x < -100 || p1Ultimate.x > W + 100) {
            p1Ultimate.active = false;
        }
    }

    if (p2Ultimate.active) {
        p2Ultimate.x += p2Ultimate.vx;
        p2Ultimate.timer++;
        if (p2Ultimate.timer > 60 || p2Ultimate.x < -100 || p2Ultimate.x > W + 100) {
            p2Ultimate.active = false;
        }
    }

    static bool rWasPressed = false;
    bool rIsPressed = (GetAsyncKeyState('R') & 0x8000);
    if (rIsPressed && !rWasPressed) {
        resetGame();
    }
    rWasPressed = rIsPressed;

    shieldCollisionBlock();
    updateAI();

    p1.vy += GRAVITY;
    p1.y += p1.vy;
    p2.vy += GRAVITY;
    p2.y += p2.vy;

    if (p1.y >= GROUND_Y - ROLE_SIZE) {
        p1.y = GROUND_Y - ROLE_SIZE;
        p1.vy = 0;
        p1.isOnGround = true;
    }
    else {
        p1.isOnGround = false;
    }

    if (p2.y >= GROUND_Y - ROLE_SIZE1) {
        p2.y = GROUND_Y - ROLE_SIZE1;
        p2.vy = 0;
        p2.isOnGround = true;
    }
    else {
        p2.isOnGround = false;
    }

    if (p1.isAttack) {
        p1.attackTimer++;
        if (p1.attackTimer >= 20) {
            p1.isAttack = false;
            p1.attackTimer = 0;
        }
    }
    if (p2.isAttack) {
        p2.attackTimer++;
        if (p2.attackTimer >= 20) {
            p2.isAttack = false;
            p2.attackTimer = 0;
        }
    }

    if (p1.isHit) {
        p1.hitTimer++;
        if (p1.hitTimer >= 12) p1.isHit = false;
    }
    if (p2.isHit) {
        p2.hitTimer++;
        if (p2.hitTimer >= 12) p2.isHit = false;
    }

    hitCheck();
    ultimateHitCheck();
}




void resetGame() {
    // 重置玩家1
    p1.x = 200;
    p1.y = GROUND_Y - ROLE_SIZE;
    p1.speed = 8;
    p1.vy = 0;
    p1.isOnGround = true;
    p1.face = -1;
    p1.hp = 200;
    p1.maxHp = 200;
    p1.damage = 15;
    p1.ultimateDamage = 40;
    p1.isAttack = false;
    p1.attackTimer = 0;
    p1.isHit = false;
    p1.hitTimer = 0;
    p1.attackCd = 0;
    p1.isDefending = false;
    p1.defendTimer = 0;
    p1.defendCd = 0;
    p1.isUltimate = false;
    p1.ultimateTimer = 0;
    p1.ultimateCd = 0;
    p1.isKnockback = false;
    p1.knockbackTimer = 0;
    p1.knockbackSpeed = 0;

    // 重置玩家2
    p2.x = 900;
    p2.y = GROUND_Y - ROLE_SIZE1;
    p2.speed = 6;
    p2.vy = 0;
    p2.isOnGround = true;
    p2.face = -1;
    p2.hp = 300;
    p2.maxHp = 300;
    p2.damage = 18;
    p2.ultimateDamage = 55;
    p2.isAttack = false;
    p2.attackTimer = 0;
    p2.isHit = false;
    p2.hitTimer = 0;
    p2.attackCd = 0;
    p2.isDefending = false;
    p2.defendTimer = 0;
    p2.defendCd = 0;
    p2.isUltimate = false;
    p2.ultimateTimer = 0;
    p2.ultimateCd = 0;
    p2.isKnockback = false;
    p2.knockbackTimer = 0;
    p2.knockbackSpeed = 0;

    // 重置大招飞行物
    p1Ultimate.active = false;
    p2Ultimate.active = false;
}

