#include "head.h"

int main() {
    DWORD attackCD = 0;
    const DWORD ATTACK_COOLDOWN = 200;

    initgraph(W, H);
    BeginBatchDraw();
    srand((unsigned)time(NULL));

    int numm = rand()%10 + 20;
    
    initMenu();
    Imageinit();
   
    DWORD spawnTime = GetTickCount();

    while (1) {
        cleardevice();

        // 全局鼠标消息

        while (PeekMouseMsg(&m, true)) {
            if (gameState == MENU0 && m.uMsg == WM_LBUTTONDOWN) {
                
                if (m.x >= btnX && m.x <= btnX + BTN_W &&
                    m.y >= btnY && m.y <= btnY + BTN_H) {
                    PlayBGM(_T("b1.mp3"));
                    gameState = MENU1;
                    
                }
                else if (m.x >= btnx && m.x <= btnx + BTN_W &&
                    m.y >= btny && m.y <= btny + BTN_H) {

                    gameState =MENU2;
                }
                

            }
            else if (gameState == MENU1 && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= btnX && m.x <= btnX + BTN_W &&
                    m.y >= btnY && m.y <= btnY + BTN_H) {
                    gameState = PLAYING1;
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
                    gameState = INTRO1;
                }
                else if (m.x >= 0 && m.x <= 100 &&
                    m.y >= H - 200 && m.y <= H) {
                    gameState = MENU0;
                }
            }
            else if (gameState == MENU2 && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= btnX && m.x <= btnX + BTN_W &&
                    m.y >= btnY && m.y <= btnY + BTN_H) {
                    gameState = PLAYING2;
                    resetGame();
                   
                }
                else if (m.x >= btnx && m.x <= btnx + BTN_W &&
                    m.y >= btny && m.y <= btny + BTN_H) {
                    gameState = INTRO2;
                }
                else if (m.x >= 0 && m.x <= 100 &&
                    m.y >= H - 200 && m.y <= H) {
                    gameState = MENU0;
                }
            }
            else if (gameState == INTRO1 && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= closeBtnX && m.x <= closeBtnX + BTN_W &&
                    m.y >= closeBtnY && m.y <= closeBtnY + BTN_H) {
                    gameState = MENU1; // 点击关闭返回菜单
                   // PlayBGM(_T("b1.mp3"));
                }
                else if (m.x >= 0 && m.x <= 100 &&
                    m.y >= H - 200 && m.y <= H) {
                    gameState = MENU0;
                }
            }
            else if (gameState == INTRO2 && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= W - 60 && m.x <= W - 10 && m.y >= 20 && m.y <= 70) {
                    gameState = MENU2;
                }

                else if (m.x >= W - 100 && m.x <= W &&
                    m.y >= H / 2 - 100 && m.y <= H / 2) {
                    PlayBGM2(_T("bh.mp3"));
                    gameState = INTRO2_1;
                    
                }
                else if (m.x >= 0 && m.x <= 100 &&
                    m.y >= H - 200 && m.y <= H) {
                    gameState = MENU0;
                }
            }
            else if (gameState == INTRO2_1 && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= W - 60 && m.x <= W - 10 && m.y >= 20 && m.y <= 70) {
                    gameState = MENU2;
                }
                else if (m.x >= W - 100 && m.x <= W &&
                    m.y >= H / 2 - 100 && m.y <= H / 2) {
                    gameState = INTRO2_2;
                }
                else if (m.x >=0 && m.x <= 100 &&
                    m.y >= H / 2 - 100 && m.y <= H / 2) {
                    gameState = INTRO2;
                }
                else if (m.x >= 0 && m.x <= 100 &&
                    m.y >= H - 200 && m.y <= H) {
                    gameState = MENU0;
                }
            }
            else if (gameState == INTRO2_2 && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= W - 60 && m.x <= W - 10 && m.y >= 20 && m.y <= 70) {
                    gameState = MENU2;
                }
               /* else if (m.x >= W - 100 && m.x <= W &&
                    m.y >= H / 2 - 100 && m.y <= H / 2) {
                    gameState = INTRO2_2;
                }*/
                else if (m.x >=0 && m.x <= 100 &&
                    m.y >= H / 2 - 100 && m.y <= H / 2) {
                    PlayBGM2(_T("bh.mp3"));
                    gameState = INTRO2_1;
                }
                else if (m.x >= 0 && m.x <= 100 &&
                    m.y >= H - 200 && m.y <= H) {
                    gameState = MENU0;
                }
            }
            else if (gameState == PLAYING1 && m.uMsg == WM_LBUTTONDOWN) {
                if (GetTickCount() - attackCD > ATTACK_COOLDOWN) {
                    AttackFire(player.x, player.y, m.x, m.y);
                    attackCD = GetTickCount();
                }
            }
            else if (gameState == WIN1 && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= btnX && m.x <= btnX + BTN_W &&
                    m.y >= btnY && m.y <= btnY + BTN_H) {
                    gameState = MENU1;
                    PlayBGM(_T("b1.mp3"));
                }
                else if (m.x >= btnx && m.x <= btnx + BTN_W &&
                    m.y >= btny && m.y <= btny + BTN_H) {
                    gameState = PLAYING1;
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
                else if (m.x >= 0 && m.x <= 100 &&
                    m.y >= H - 200 && m.y <= H) {
                    gameState = MENU0;
                }
            }
            else if (gameState == LOSE1 && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= btnX && m.x <= btnX + BTN_W &&
                    m.y >= btnY && m.y <= btnY + BTN_H) {
                    gameState = MENU1;
                    PlayBGM(_T("b1.mp3"));

                }
                else if (m.x >= btnx && m.x <= btnx + BTN_W &&
                    m.y >= btny && m.y <= btny + BTN_H) {
                    gameState = PLAYING1;
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
                else if (m.x >= 0 && m.x <= 100 &&
                    m.y >= H - 200 && m.y <= H) {
                    gameState = MENU0;
                }
            }
            else if (gameState == WIN2 && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= btnX && m.x <= btnX + BTN_W &&
                    m.y >= btnY && m.y <= btnY + BTN_H) {
                    gameState = MENU2;
                    PlayBGM(_T("b1.mp3"));
                }
                else if (m.x >= btnx && m.x <= btnx + BTN_W &&
                    m.y >= btny && m.y <= btny + BTN_H) {
                    gameState = PLAYING2;
                    
                }
                else if (m.x >= 0 && m.x <= 100 &&
                    m.y >= H - 200 && m.y <= H) {
                    gameState = MENU0;
                }
            }
            else if (gameState == LOSE2 && m.uMsg == WM_LBUTTONDOWN) {
                if (m.x >= btnX && m.x <= btnX + BTN_W &&
                    m.y >= btnY && m.y <= btnY + BTN_H) {
                    gameState = MENU2;
                    PlayBGM(_T("b1.mp3"));

                }
                else if (m.x >= btnx && m.x <= btnx + BTN_W &&
                    m.y >= btny && m.y <= btny + BTN_H) {
                    gameState = PLAYING2;
                    resetGame();
                
                }
                else if (m.x >= 0 && m.x <= 100 &&
                    m.y >= H - 200 && m.y <= H) {
                    gameState = MENU0;
                }
            }

            if (gameState == PLAYING1 && m.uMsg == WM_RBUTTONDOWN) {
                LayLm(m.x, m.y);
            }

        }
        if (gameState == MENU0) {
            drawMenu1();
        }
        else if (gameState == MENU1) {
            drawMenu();
        }
        else if (gameState == INTRO1) {
            drawIntro();
        }
        else if (gameState == INTRO2) {
            drawIntro2();
        }
        else if (gameState == INTRO2_1) {
            drawIntro2_1();
        }
        else if (gameState == INTRO2_2) {
            drawIntro2_2();
        }
        else if (gameState == MENU2) {
            drawMenu2();
        }
        else if (gameState == PLAYING1) {
            if (GetTickCount() - spawnTime > 1000) {
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
                gameState = LOSE1;
                StopBGM();          // 专门停止背景音乐
                PlayLoseMusic(_T("lose.mp3"));
            }

            if (!boss.isAlive && boss.bossSpawned) {
                gameState = WIN1;
                StopBGM();
                PlayWinMusic(_T("win.mp3"));
                continue;
            }

            //DrawAllBgTiles();

            bkDraw();
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
        else if (gameState == WIN1) {
            drawWin();
        }
        else if (gameState == LOSE1) {
            drawLose();
        }
        else if (gameState == PLAYING2) {
            drawEvery();
            update();
            if (p1.hp <= 0) {
                gameState = LOSE2;
                StopBGM();          // 专门停止背景音乐
                PlayLoseMusic(_T("lose.mp3"));
            }

            if (p2.hp<=0 ) {
                gameState = WIN2;
                StopBGM();
                PlayWinMusic(_T("win.mp3"));
                continue;
            }
        }
        else if (gameState == WIN2) {
            drawWin2();
        }
        else if (gameState == LOSE2) {
            drawlose2();
        }


        FlushBatchDraw();
        Sleep(20);
    }

    closegraph();
    return 0;
}