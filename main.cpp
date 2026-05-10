#include "head.h"

int main() {
    DWORD attackCD = 0;
    const DWORD ATTACK_COOLDOWN = 200;

    initgraph(W, H);
    BeginBatchDraw();
    srand((unsigned)time(NULL));

    BGLoad();
    initMenu();

    DWORD spawnTime = GetTickCount();

    while (1) {
        cleardevice();

        // 全局鼠标消息
        
        while (PeekMouseMsg(&m, true)) {
            if (gameState == MENU && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= btnX && m.x <= btnX + BTN_W &&
                    m.y >= btnY && m.y <= btnY + BTN_H) {
                    gameState = PLAYING;
                    PlayerInit(&player);
                    GemInit();
                    MonsterInit();
                    AttackInit();
                    spawnTime = GetTickCount();
                }
                else if (m.x >= btnx && m.x <= btnx + BTN_W &&
                    m.y >= btny && m.y <= btny + BTN_H) {
                    gameState = INTRO;
                }
            }
            else if (gameState == INTRO && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= closeBtnX && m.x <= closeBtnX + BTN_W &&
                    m.y >= closeBtnY && m.y <= closeBtnY + BTN_H) {
                    gameState = MENU; // 点击关闭返回菜单
                }
            }
            else if (gameState == PLAYING && m.uMsg == WM_LBUTTONDOWN) {
                if (GetTickCount() - attackCD > ATTACK_COOLDOWN) {
                    AttackFire(player.x, player.y, m.x, m.y);
                    attackCD = GetTickCount();
                }
            }
        }

        if (gameState == MENU) {
            drawMenu();
        }
        else if (gameState == INTRO) {
            drawIntro();
        }
        else if (gameState == PLAYING) {
            if (GetTickCount() - spawnTime > 2000) {
                MonsterSpawn();
                spawnTime = GetTickCount();
            }
          
            PlayerInput(&player);
            PlayerUpdateAnim(&player);
            MonsterUpdate();
            AttackUpdate();
            MonsterAttackUpdate(); // 新增：更新怪兽攻击

            if (CheckGameCollision() == 1) {
                gameState = MENU;
            }
            
            DrawAllBgTiles();
            GemDraw();
            
            MonsterDraw();
            AttackDraw();
            MonsterAttackDraw(); // 新增：绘制怪兽攻击
            PlayerDraw(&player);  
            DrawUI();
            
        }

        FlushBatchDraw();
        Sleep(16);
    }

    closegraph();
    return 0;
}