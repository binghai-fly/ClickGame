#include "head.h"

int main() {
    DWORD attackCD = 0;
    const DWORD ATTACK_COOLDOWN = 200;

    initgraph(W, H);
    BeginBatchDraw();
    srand((unsigned)time(NULL));

    BGLoad();
    initMenu();

    PlayBGM(_T("b1.mp3"));

    DWORD spawnTime = GetTickCount();

    while (1) {
        cleardevice();

        // 全局鼠标消息
        
        while (PeekMouseMsg(&m, true)) {
            if (gameState == MENU && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= btnX && m.x <= btnX + BTN_W &&
                    m.y >= btnY && m.y <= btnY + BTN_H) {
                    InputBox(num, 20, _T("Enter the number of monsters to kill before BOSS appears"));
                    numm = _ttoi(num);
                    gameState = PLAYING;
                    PlayBGM(_T("bgm.mp3"));
                    PlayerInit(&player);
                    GemInit();
                    MonsterInit();
                    lmInit();
                    AttackInit();
                    BossInit();
                    monstersKilledCount = 0;
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
                    PlayBGM(_T("b1.mp3"));
                }
            }
            else if (gameState == PLAYING && m.uMsg == WM_LBUTTONDOWN) {
                if (GetTickCount() - attackCD > ATTACK_COOLDOWN) {
                    AttackFire(player.x, player.y, m.x, m.y);
                    attackCD = GetTickCount();
                }
            }
            else if (gameState == WIN && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= btnX && m.x <= btnX + BTN_W &&
                    m.y >= btnY && m.y <= btnY + BTN_H) {
                    gameState = MENU;
                    PlayBGM(_T("b1.mp3"));
                }
                else if (m.x >= btnx && m.x <= btnx + BTN_W &&
                    m.y >= btny && m.y <= btny + BTN_H) {
                    gameState = PLAYING;
                    PlayBGM(_T("bgm.mp3"));
                    PlayerInit(&player);
                    GemInit();
                    MonsterInit();
                    lmInit();
                    AttackInit();
                    BossInit();
                    monstersKilledCount = 0;
                    spawnTime = GetTickCount();
                }
            }
            else if (gameState == LOSE && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= btnX && m.x <= btnX + BTN_W &&
                    m.y >= btnY && m.y <= btnY + BTN_H) {
                    gameState = MENU;
                    PlayBGM(_T("b1.mp3"));

                }
                else if (m.x >= btnx && m.x <= btnx + BTN_W &&
                    m.y >= btny && m.y <= btny + BTN_H) {
                    gameState = PLAYING;
                    PlayBGM(_T("bgm.mp3"));
                    PlayerInit(&player);
                    GemInit();
                    MonsterInit();
                    lmInit();
                    AttackInit();
                    BossInit();
                    monstersKilledCount = 0;
                    spawnTime = GetTickCount();
                }
            }
            if (gameState == PLAYING && m.uMsg == WM_RBUTTONDOWN) {
                LayLm(m.x, m.y);
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
            if (!boss.isAlive && monstersKilledCount >= numm) {
                BossSpawn();
                boss.bossSpawned = true;
            }


            PlayerInput(&player);
            PlayerUpdateAnim(&player);
            MonsterUpdate();
            AttackUpdate();
            MonsterAttackUpdate(); // 新增：更新怪兽攻击
            BossUpdate();
            BossAttackUpdate();

            if (CheckGameCollision() == 1) {
                gameState = LOSE;
                StopBGM();          // 专门停止背景音乐
                PlayLoseMusic(_T("lose.mp3"));
            }

            if (!boss.isAlive&&boss.bossSpawned) {
                gameState = WIN;
                StopBGM();
                PlayWinMusic(_T("win.mp3"));
                continue;
            }
            
            DrawAllBgTiles();
            GemDraw();
            lmDraw();
            MonsterDraw();
            AttackDraw();
            MonsterAttackDraw(); // 新增：绘制怪兽攻击
            PlayerDraw(&player);  
            BossDraw();
            BossAttackDraw();
            DrawUI();
            
        }
        else if (gameState == WIN) {
            drawWin();
        }
        else if (gameState == LOSE) {
            drawLose();
        }

        FlushBatchDraw();
        Sleep(20);
    }

    closegraph();
    return 0;
}