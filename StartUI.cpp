#include "head.h"
MOUSEMSG m;
IMAGE menuBg;
IMAGE startBtnImg;
IMAGE gameIntro;
IMAGE heart_full;
IMAGE heart_empty;
IMAGE coin_icon;
IMAGE num_imgs[10];
IMAGE overBg;
IMAGE loseBg;
IMAGE bk1;
IMAGE bk2;
int btnX, btnY;
const int BTN_W = 180;
const int BTN_H = 50;
int btnx, btny;
int closeBtnX ;
int closeBtnY ;
TCHAR num[20];
int numm;

void initMenu() {
    safeLoadImage(&menuBg, _T("picture/stbk.png"), W, H);
    safeLoadImage(&overBg, _T("picture/over.png"), W, H);
    safeLoadImage(&loseBg, _T("picture/lose.png"), W, H);
    safeLoadImage(&bk1, _T("picture/bk1.png"), W, H);
    safeLoadImage(&bk2, _T("picture/bk2.png"), W, H);
    safeLoadImage(&gameIntro, _T("picture/gameIntro.png"), 500, H + 20);
    safeLoadImage(&heart_full, _T("picture/tile_0044.png"), 24, 24);
    safeLoadImage(&heart_empty, _T("picture/tile_0046.png"), 24, 24);
    safeLoadImage(&coin_icon, _T("picture/tile_0151.png"), 24, 24);
    for (int i = 0; i < 10; i++) {
        TCHAR path[50];
        wsprintf(path, _T("picture/tile_016%d.png"), i);
        safeLoadImage(&num_imgs[i], path, 24, 24);
    }
    
    btnX = W / 2 - BTN_W / 2;
    btnY = H / 2 + 100;
    btnx = btnX;
    btny = btnY + 80;
    
    // 启动时在主菜单播放背景音乐
    PlayBGM(_T("startbgm.mp3"));
}

void drawMenu1() {
    if (isValidImage(&bk1))
    putimage(0, 0, &bk1);
    else {
        setfillcolor(RGB(30, 30, 60));
        solidrectangle(0, 0, W, H);
    }

    drawButton(btnX, btnY,btd,bt);
    drawButton(btnx, btny,btd,bt);

    setbkmode(TRANSPARENT);
    setcolor(WHITE);
    settextstyle(30, 0, _T("隶书"));
    outtextxy(btnX + 50, btnY + 4, _T("转避"));
    outtextxy(btnx + 20, btny + 4, _T("拳皇苍穹"));
}

void drawMenu() {
 
    putimage(0, 0, &menuBg);
    drawHome();

    drawButton(btnX, btnY, btgn, btdgn);
    drawButton(btnx, btny, btgn, btdgn);
   
    setbkmode(TRANSPARENT);
    setcolor(RGB(125,125,125));
    settextstyle(30, 0, _T("隶书"));
    outtextxy(btnX + 20, btnY + 4, _T("开始游戏"));
    outtextxy(btnx + 20, btny + 4, _T("游戏介绍"));
}

void drawIntro() {
    putimage(0, 0, &menuBg);
    drawHome();

    DrawTransparentImage(220, 0, &gameIntro);
    closeBtnX = btnX + 300;
    closeBtnY = btny;

    drawButton(closeBtnX, closeBtnY, btgn, btdgn);

    setbkmode(TRANSPARENT);
    setcolor(RGB(125, 125, 125));
    settextstyle(30, 0, _T("隶书"));
    outtextxy(closeBtnX + 50, closeBtnY + 4, _T("关闭"));
}

void bkDraw() {
    putimage(0, 0, &bk2);
}
// 新增函数：画血量和金币
void DrawUI() {

    // 左上角：3颗爱心
    IMAGE* curImg = NULL;
    for (int i = 0; i < 3; i++) {
        int x = 10 + i * 30;
        if (i < player.hp) {
            curImg = &heart_full;
            if (curImg == NULL) return;

            DrawTransparentImage(x, 10, curImg);
        }
        else {
            curImg=&heart_empty;
            if (curImg == NULL) return;
            DrawTransparentImage(x, 10, curImg);

        }
    }
    // 右上角：金币图标 + 数字图片
    curImg = &coin_icon;
    if (curImg == NULL) return;

    DrawTransparentImage(W-130, 10, curImg);

    
    
    // 绘制金币数字（图片）
    int n = player.coins;
    if (n == 0) {
        curImg = &num_imgs[0];
        if (curImg == NULL) return;

        DrawTransparentImage(W-70, 10, curImg);

       
    }
    else {
        int x = W - 70;
        while (n > 0) {
            int d = n % 10;
            curImg = &num_imgs[d];
            DrawTransparentImage(x, 10, curImg);

            x -= 25;
            n /= 10;
        }
    }

    //总击败个数
    setbkmode(TRANSPARENT);
    setcolor(RED);
    settextstyle(18, 0, _T("隶书"));
    outtextxy(W/2-140, 12, _T("总击败怪兽数："));
    int nn = monstersKilledCount;
    if (nn == 0) {
        curImg = &num_imgs[0];
        DrawTransparentImage(W/2, 10, curImg);


    }
    else {
        int x = W /2;
        while (nn > 0) {
            int d = nn % 10;
            curImg = &num_imgs[d];
            if (curImg == NULL) return;

            DrawTransparentImage(x, 10, curImg);

            x -= 25;
            nn /= 10;
        }
    }

}

void drawWin() {
    putimage(0, 0, &overBg);
    drawHome();

    drawButton(btnX, btnY, btgn, btdgn);
    drawButton(btnx, btny, btgn, btdgn);

    setbkmode(TRANSPARENT);
    setcolor(RGB(125, 125, 125));
    settextstyle(30, 0, _T("隶书"));
    outtextxy(btnX + 20, btnY + 4, _T("返回菜单"));
    outtextxy(btnx + 20, btny + 4, _T("重新游戏"));
}

void drawLose() {
    putimage(0, 0, &loseBg);
    drawHome();

    drawButton(btnX, btnY, btgn, btdgn);
    drawButton(btnx, btny, btgn, btdgn);

    setbkmode(TRANSPARENT);
    setcolor(RGB(125, 125, 125));
    settextstyle(30, 0, _T("隶书"));
    outtextxy(btnX + 20, btnY + 4, _T("返回菜单"));
    outtextxy(btnx + 20, btny + 4, _T("重新游戏"));
}