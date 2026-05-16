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
int btnX, btnY;
const int BTN_W = 180;
const int BTN_H = 50;
int btnx, btny;
int closeBtnX ;
int closeBtnY ;
TCHAR num[20];
int numm;

void initMenu() {
    loadimage(&menuBg, _T("picture/stbk.png"), W, H);
    loadimage(&overBg, _T("picture/over.png"), W, H);
    loadimage(&loseBg, _T("picture/lose.png"), W, H);
    //loadimage(&startBtnImg, _T("bt.png"), BTN_W, BTN_H);
    loadimage(&gameIntro, _T("picture/gameIntro.png"), 500, H+20 );
    loadimage(&heart_full, _T("picture/tile_0044.png"), 24, 24);
    loadimage(&heart_empty, _T("picture/tile_0046.png"), 24, 24);
    loadimage(&coin_icon, _T("picture/tile_0151.png"), 24, 24);
    for (int i = 0; i < 10; i++) {
        TCHAR path[50];
        wsprintf(path, _T("picture/tile_016%d.png"), i);
        loadimage(&num_imgs[i], path, 24, 24);
    }
    btnX = W / 2 - BTN_W / 2;
    btnY = H / 2 + 100;
    btnx = btnX;
    btny = btnY + 80;
    
}

void drawMenu() {
 
    putimage(0, 0, &menuBg);
    
    /*putimage(btnX, btnY, &startBtnImg);*/
       // 默认颜色
    COLORREF btnColor = RGB(255, 128, 0);
    // 悬浮颜色
    COLORREF hoverColor = RGB(255, 165, 50);
    // 点击颜色
    COLORREF clickColor = RGB(200, 80, 0);
   
    bool inBtn = (m.x >= btnX && m.x <= btnX + BTN_W &&
        m.y >= btnY && m.y <= btnY + BTN_H);
    bool inBtn1 = (m.x >= btnx && m.x <= btnx + BTN_W &&
        m.y >= btny && m.y <= btny + BTN_H);

    if (inBtn)
    {
        if (m.uMsg == WM_LBUTTONDOWN)
            setfillcolor(clickColor);   // 按下变深
        else
            setfillcolor(hoverColor);   // 悬浮变浅
    }
    else
    {
        setfillcolor(btnColor);         // 离开恢复原色
    }
    solidrectangle(btnX, btnY, btnX + BTN_W, BTN_H + btnY);
    if (inBtn1)
    {
        if (m.uMsg == WM_LBUTTONDOWN)
            setfillcolor(clickColor);   // 按下变深
        else
            setfillcolor(hoverColor);   // 悬浮变浅
    }
    else
    {
        setfillcolor(btnColor);         // 离开恢复原色
    }

    
    solidrectangle(btnx, btny, btnx + BTN_W, BTN_H + btny);
    setbkmode(TRANSPARENT);
    setcolor(WHITE);
    settextstyle(30, 0, _T("隶书"));
    outtextxy(btnX + 30, btnY + 7, _T("开始游戏"));
    outtextxy(btnx + 30, btny + 7, _T("游戏介绍"));
}

void drawIntro() {
    putimage(0, 0, &menuBg);
    //putimage(200, 0, &gameIntro);
    int w = gameIntro.getwidth();
    int h = gameIntro.getheight();

    HDC dstDC = GetImageHDC(NULL);
    HDC srcDC = GetImageHDC(&gameIntro);

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    AlphaBlend(dstDC, 220,0 , w , h ,
        srcDC, 0, 0, w, h, blend);
    closeBtnX = btnX + 300;
    closeBtnY = btny;
    COLORREF btnColor = RGB(255, 128, 0);
    // 悬浮颜色
    COLORREF hoverColor = RGB(255, 165, 50);
    // 点击颜色
    COLORREF clickColor = RGB(200, 80, 0);

    bool inBtn3 = (m.x >= closeBtnX && m.x <= closeBtnX + BTN_W &&
        m.y >= closeBtnY && m.y <= closeBtnY + BTN_H);

    if (inBtn3)
    {
        if (m.uMsg == WM_LBUTTONDOWN)
            setfillcolor(clickColor);   // 按下变深
        else
            setfillcolor(hoverColor);   // 悬浮变浅
    }
    else
    {
        setfillcolor(btnColor);         // 离开恢复原色
    }
    solidrectangle(closeBtnX, closeBtnY, closeBtnX + BTN_W, closeBtnY + BTN_H);
    setbkmode(TRANSPARENT);
    setcolor(WHITE);
    settextstyle(30, 0, _T("黑体"));
    outtextxy(closeBtnX + 60, closeBtnY + 7, _T("关闭"));
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

            int w = curImg->getwidth();
            int h = curImg->getheight();

            HDC dstDC = GetImageHDC(NULL);
            HDC srcDC = GetImageHDC(curImg);

            BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
            AlphaBlend(dstDC, x, 10, w , h ,
                srcDC, 0, 0, w, h, blend);
        }
        else {
            curImg=&heart_empty;
            if (curImg == NULL) return;

            int w = curImg->getwidth();
            int h = curImg->getheight();

            HDC dstDC = GetImageHDC(NULL);
            HDC srcDC = GetImageHDC(curImg);

            BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
            AlphaBlend(dstDC, x, 10, w, h,
                srcDC, 0, 0, w, h, blend);
        }
    }
    // 右上角：金币图标 + 数字图片
    curImg = &coin_icon;
    if (curImg == NULL) return;

    int w = curImg->getwidth();
    int h = curImg->getheight();

    HDC dstDC = GetImageHDC(NULL);
    HDC srcDC = GetImageHDC(curImg);

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    AlphaBlend(dstDC, W-130, 10, w, h,
        srcDC, 0, 0, w, h, blend);
    
    
    // 绘制金币数字（图片）
    int n = player.coins;
    if (n == 0) {
        curImg = &num_imgs[0];
        if (curImg == NULL) return;

        int w = curImg->getwidth();
        int h = curImg->getheight();

        HDC dstDC = GetImageHDC(NULL);
        HDC srcDC = GetImageHDC(curImg);

        BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
        AlphaBlend(dstDC, W-70, 10, w, h,
            srcDC, 0, 0, w, h, blend);
       
    }
    else {
        int x = W - 70;
        while (n > 0) {
            int d = n % 10;
            curImg = &num_imgs[d];
            if (curImg == NULL) return;

            int w = curImg->getwidth();
            int h = curImg->getheight();

            HDC dstDC = GetImageHDC(NULL);
            HDC srcDC = GetImageHDC(curImg);

            BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
            AlphaBlend(dstDC, x, 10, w, h,
                srcDC, 0, 0, w, h, blend);
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
        if (curImg == NULL) return;

        int w = curImg->getwidth();
        int h = curImg->getheight();

        HDC dstDC = GetImageHDC(NULL);
        HDC srcDC = GetImageHDC(curImg);

        BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
        AlphaBlend(dstDC, W /2, 10, w, h,
            srcDC, 0, 0, w, h, blend);

    }
    else {
        int x = W /2;
        while (nn > 0) {
            int d = nn % 10;
            curImg = &num_imgs[d];
            if (curImg == NULL) return;

            int w = curImg->getwidth();
            int h = curImg->getheight();

            HDC dstDC = GetImageHDC(NULL);
            HDC srcDC = GetImageHDC(curImg);

            BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
            AlphaBlend(dstDC, x, 10, w, h,
                srcDC, 0, 0, w, h, blend);
            x -= 25;
            nn /= 10;
        }
    }

}

void drawWin() {
    putimage(0, 0, &overBg);
    COLORREF btnColor = RGB(255, 128, 0);
    // 悬浮颜色
    COLORREF hoverColor = RGB(255, 165, 50);
    // 点击颜色
    COLORREF clickColor = RGB(200, 80, 0);

    bool inBtn = (m.x >= btnX && m.x <= btnX + BTN_W &&
        m.y >= btnY && m.y <= btnY + BTN_H);
    bool inBtn1 = (m.x >= btnx && m.x <= btnx + BTN_W &&
        m.y >= btny && m.y <= btny + BTN_H);

    if (inBtn)
    {
        if (m.uMsg == WM_LBUTTONDOWN)
            setfillcolor(clickColor);   // 按下变深
        else
            setfillcolor(hoverColor);   // 悬浮变浅
    }
    else
    {
        setfillcolor(btnColor);         // 离开恢复原色
    }
    solidrectangle(btnX, btnY, btnX + BTN_W, BTN_H + btnY);
    if (inBtn1)
    {
        if (m.uMsg == WM_LBUTTONDOWN)
            setfillcolor(clickColor);   // 按下变深
        else
            setfillcolor(hoverColor);   // 悬浮变浅
    }
    else
    {
        setfillcolor(btnColor);         // 离开恢复原色
    }


    solidrectangle(btnx, btny, btnx + BTN_W, BTN_H + btny);
    setbkmode(TRANSPARENT);
    setcolor(WHITE);
    settextstyle(30, 0, _T("隶书"));
    outtextxy(btnX + 30, btnY + 7, _T("返回菜单"));
    outtextxy(btnx + 30, btny + 7, _T("重新游戏"));
}

void drawLose() {
    putimage(0, 0, &loseBg);
    COLORREF btnColor = RGB(255, 128, 0);
    // 悬浮颜色
    COLORREF hoverColor = RGB(255, 165, 50);
    // 点击颜色
    COLORREF clickColor = RGB(200, 80, 0);

    bool inBtn = (m.x >= btnX && m.x <= btnX + BTN_W &&
        m.y >= btnY && m.y <= btnY + BTN_H);
    bool inBtn1 = (m.x >= btnx && m.x <= btnx + BTN_W &&
        m.y >= btny && m.y <= btny + BTN_H);

    if (inBtn)
    {
        if (m.uMsg == WM_LBUTTONDOWN)
            setfillcolor(clickColor);   // 按下变深
        else
            setfillcolor(hoverColor);   // 悬浮变浅
    }
    else
    {
        setfillcolor(btnColor);         // 离开恢复原色
    }
    solidrectangle(btnX, btnY, btnX + BTN_W, BTN_H + btnY);
    if (inBtn1)
    {
        if (m.uMsg == WM_LBUTTONDOWN)
            setfillcolor(clickColor);   // 按下变深
        else
            setfillcolor(hoverColor);   // 悬浮变浅
    }
    else
    {
        setfillcolor(btnColor);         // 离开恢复原色
    }


    solidrectangle(btnx, btny, btnx + BTN_W, BTN_H + btny);
    setbkmode(TRANSPARENT);
    setcolor(WHITE);
    settextstyle(30, 0, _T("隶书"));
    outtextxy(btnX + 30, btnY + 7, _T("返回菜单"));
    outtextxy(btnx + 30, btny + 7, _T("重新游戏"));
}