#include"head.h"

void Update() {
    while (PeekMouseMsg(&m, true)) {
        // 在首页（MENU0）点击可以选择进入不同的游戏
        if (gameState == MENU0 && m.uMsg == WM_LBUTTONDOWN) {
            // 不再在这里强制绘制，直接根据点击位置切换状态
            if (m.x >= btnX && m.x <= btnX + BTN_W &&
                m.y >= btnY && m.y <= btnY + BTN_H) {
                // 第一个按钮：进入游戏1的菜单
                gameState = MENU1;
            }
            else if (m.x >= btnx && m.x <= btnx + BTN_W &&
                m.y >= btny && m.y <= btny + BTN_H) {
                // 第二个按钮：进入游戏2（拳皇）的菜单
                gameState = MENU2;
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
        }
        else if (gameState == INTRO1 && m.uMsg == WM_LBUTTONDOWN) {
            if (m.x >= closeBtnX && m.x <= closeBtnX + BTN_W &&
                m.y >= closeBtnY && m.y <= closeBtnY + BTN_H) {
                gameState = MENU1; // 点击关闭返回菜单
                PlayBGM(_T("b1.mp3"));
            }
        }
        else if (gameState == MENU2 && m.uMsg == WM_LBUTTONDOWN) {
            // 菜单2：开始或游戏介绍
            if (m.x >= btnX && m.x <= btnX + BTN_W &&
                m.y >= btnY && m.y <= btnY + BTN_H) {
                // 开始拳皇游戏
                gameState = PLAYING2;
                // 初始化拳皇资源并重置状态
                Imageinit();
                resetGame();
                PlayBGM(_T("bgm.mp3"));
            }
            else if (m.x >= btnx && m.x <= btnx + BTN_W &&
                m.y >= btny && m.y <= btny + BTN_H) {
                // 暂无专门的介绍界面，直接保持在菜单2（可扩展）
                gameState = INTRO2;
            }
        }
        else if (gameState == INTRO2 && m.uMsg == WM_LBUTTONDOWN) {
            // 简单处理：返回菜单2
            if (m.x >= closeBtnX && m.x <= closeBtnX + BTN_W &&
                m.y >= closeBtnY && m.y <= closeBtnY + BTN_H) {
                gameState = MENU2;
                PlayBGM(_T("b1.mp3"));
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
    else if (gameState == MENU2) {
        drawMenu2();
    }
    else if (gameState == INTRO1) {
        drawIntro();
    }
    else if (gameState == INTRO2) {
        // 暂用 drawMenu2 作为占位的介绍显示（可替换为专门的介绍绘制）
        drawMenu2();
    }
    else if (gameState == PLAYING1) {
        // 缩短刷怪间隔，使场景中更容易同时存在多个怪物
        if (GetTickCount() - spawnTime > 1000) {
            MonsterSpawn();
            spawnTime = GetTickCount();
        }
        if (!boss.isAlive && monstersKilledCount >= 20) {
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
            //continue;
        }

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
        // 更新并绘制拳皇游戏（逻辑在 Fighter.cpp，绘制在 Draw.cpp）
        update();
        // drawEvery 在 Draw.cpp 中绘制不触发 Begin/Flush 的内容，主循环负责 Flush
        drawEvery();
    }
    else if (gameState == WIN2 || gameState == LOSE2) {
        // 直接使用拳皇的绘制逻辑（如果需要更多控制，可以调用 draw()）
        drawEvery();
    }

    FlushBatchDraw();
    Sleep(20);
}
