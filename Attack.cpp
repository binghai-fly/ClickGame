#include"head.h"

Projectile p1Ultimate, p2Ultimate;

void shieldCollisionBlock() {

    if (!p1.isDefending && !p2.isDefending) return;


    int distance = abs(p1.x - p2.x);

    if (distance < SHIELD_BLOCK_DIST) {

        if (p1.x < p2.x) {

            p2.x = p1.x + SHIELD_BLOCK_DIST;
            p1.x = p2.x - SHIELD_BLOCK_DIST;
        }

        else {

            p1.x = p2.x + SHIELD_BLOCK_DIST;
            p2.x = p1.x - SHIELD_BLOCK_DIST;
        }

       /* p1.x = max(50, std::min(p1.x, W - ROLE_SIZE));
        p2.x = max(50, std::min(p2.x, W - ROLE_SIZE1 - 50));*/
    }
}

// 检查攻击是否命中
bool canHit(Fighter* attacker, Fighter* target) {
    int d = abs(attacker->x - target->x);
    if (d >= 140) return false;

    int yDiff = abs(attacker->y - target->y);
    if (!target->isOnGround) {
        return yDiff < 60;
    }
    return yDiff < 40;
}


void hitCheck() {
    //if (gameStat) return;

    if (p1.isAttack && p1.attackTimer >= 5 && p1.attackTimer <= 10 && !p2.isHit && p1.attackCd == 0 && !p2.isKnockback) {
        if (canHit(&p1, &p2)) {
            if (p2.isDefending) {
                int reducedDamage = p1.damage / 3;
                if (reducedDamage > 0) {
                    p2.hp -= reducedDamage;
                    p2.isHit = true;
                    p2.hitTimer = 0;
                }
            }
            else {
                p2.hp -= p1.damage;
                p2.isHit = true;
                p2.hitTimer = 0;

                p2.isKnockback = true;
                p2.knockbackTimer = 0;
                if (p1.x < p2.x) {
                    p2.knockbackSpeed = 15;
                }
                else {
                    p2.knockbackSpeed = -15;
                }
                p2.vy = -12;
            }
            p1.attackCd = 60;
            if (p2.hp < 0) p2.hp = 0;
        }
    }

    if (p2.isAttack && p2.attackTimer >= 5 && p2.attackTimer <= 10 && !p1.isHit && p2.attackCd == 0 && !p1.isKnockback) {
        if (canHit(&p2, &p1)) {
            if (p1.isDefending) {
                int reducedDamage = p2.damage / 3;
                if (reducedDamage > 0) {
                    p1.hp -= reducedDamage;
                    p1.isHit = true;
                    p1.hitTimer = 0;
                }
            }
            else {
                p1.hp -= p2.damage;
                p1.isHit = true;
                p1.hitTimer = 0;

                p1.isKnockback = true;
                p1.knockbackTimer = 0;
                if (p2.x < p1.x) {
                    p1.knockbackSpeed = 15;
                }
                else {
                    p1.knockbackSpeed = -15;
                }
                p1.vy = -12;
            }
            p2.attackCd = 60;
            if (p1.hp < 0) p1.hp = 0;
        }
    }
}

// 大招判定
void ultimateHitCheck() {
    //if (gameOver) return;

    if (p1Ultimate.active) {
        // ignore hits for first 2 frames to avoid instant collision when spawned very close
        if (p1Ultimate.timer > 2) {
            int d = abs(p1Ultimate.x - p2.x);
            if (d < 100 && abs(p1Ultimate.y - p2.y) < 120) {
                p2.hp -= p1.ultimateDamage;
                p2.isHit = true;
                p2.hitTimer = 0;
                p2.isKnockback = true;
                p2.knockbackTimer = 0;
                // Use projectile velocity to determine knockback direction so target is pushed away
                if (p1Ultimate.vx > 0) p2.knockbackSpeed = 20;
                else p2.knockbackSpeed = -20;
                p2.vy = -15;
                p1Ultimate.active = false;
                if (p2.hp < 0) p2.hp = 0;
            }
        }
    }

    if (p2Ultimate.active) {
        if (p2Ultimate.timer > 2) {
            int d = abs(p2Ultimate.x - p1.x);
            if (d < 100 && abs(p2Ultimate.y - p1.y) < 120) {
                if (p1.isDefending) {
                    int reducedDamage = p2.ultimateDamage / 3;
                    p1.hp -= reducedDamage;
                }
                else {
                    p1.hp -= p2.ultimateDamage;
                }
                p1.isHit = true;
                p1.hitTimer = 0;
                p1.isKnockback = true;
                p1.knockbackTimer = 0;
                // Use projectile velocity to determine knockback direction so target is pushed away
                if (p2Ultimate.vx > 0) p1.knockbackSpeed = 20;
                else p1.knockbackSpeed = -20;
                p1.vy = -15;
                p2Ultimate.active = false;
                if (p1.hp < 0) p1.hp = 0;
            }
        }
    }
}

