#include"head.h"
// Define some image globals referenced across modules
IMAGE start;
IMAGE wini2;
IMAGE losei2;
IMAGE dd;
IMAGE al;
IMAGE ar;
IMAGE bs;
IMAGE bSt;
IMAGE cross;
IMAGE home;
IMAGE mds;
IMAGE bkk;
IMAGE bt;
IMAGE btd;
IMAGE btyw;
IMAGE btdyw;
IMAGE btgn;
IMAGE btdgn;

bool isValidImage(IMAGE* img) {
    return img != nullptr && GetImageBuffer(img) != nullptr;
}


void safeLoadImage(IMAGE* img, const TCHAR* filename, int width, int height) {
    if (img == nullptr) return;
    DWORD attr = GetFileAttributes(filename);
    if (attr == INVALID_FILE_ATTRIBUTES) {
        // Log missing file but still attempt to load so easyx can provide placeholder
        TCHAR buf[512];
        wsprintf(buf, _T("Missing image: %s"), filename);
     /*   Log(buf);*/
    }
    loadimage(img, filename, width, height);
}

void drawAttackCd(int x, int y, int cd, int maxCd, const TCHAR* name) {
    int w = 120;
    int h = 12;

    setfillcolor(RGB(50, 50, 50));
    solidrectangle(x, y, x + w, y + h);

    int rw = (maxCd - cd) * w / maxCd;
    if (cd > 0) {
        setfillcolor(RGB(100, 100, 255));
    }
    else {
        setfillcolor(RGB(0, 255, 0));
    }
    solidrectangle(x, y, x + rw, y + h);

    setlinecolor(RGB(255, 215, 0));
    setlinestyle(PS_SOLID, 1);
    rectangle(x, y, x + w, y + h);

    settextcolor(WHITE);
    settextstyle(16, 0, _T("黑体"));
    if (cd > 0) {
        TCHAR cdText[50];
        _stprintf_s(cdText, _T("%s CD: %.1f"), name, cd / 60.0f);
        outtextxy(x, y - 20, cdText);
    }
    else {
        TCHAR cdText[50];
        _stprintf_s(cdText, _T("%s 就绪"), name);
        outtextxy(x + 10, y - 20, cdText);
    }
}

void Imageinit() {
    srand(time(NULL));

    // 获取当前工作目录并显示提示（调试用）
    TCHAR currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentPath);



    // 加载图片（使用 safeLoadImage，如果文件名或后缀错误会用占位图替代并提示）
    safeLoadImage(&bg, _T("picture1/bk1.jpg"), W,H);
    safeLoadImage(&start, _T("picture1/start.png"), W, H);
    safeLoadImage(&losei2, _T("picture1/lose.png"), W, H);
    safeLoadImage(&wini2, _T("picture1/win.png"), W, H);
    safeLoadImage(&wini2, _T("picture1/win.png"), W, H);
    safeLoadImage(&dd, _T("picture1/dd.png"), W, H);
    safeLoadImage(&mds, _T("picture1/mds.png"), W, H);
    safeLoadImage(&bkk, _T("picture1/bk2.png"), W, H);

    safeLoadImage(&al, _T("picture1/arrowLeft.png"), 100, 100);
    safeLoadImage(&ar, _T("picture1/arrowRight.png"), 100, 100);
    safeLoadImage(&bs, _T("picture1/buttonSelect.png"), 100, 100);
    safeLoadImage(&bSt, _T("picture1/buttonStart.png"), 100, 100);
    safeLoadImage(&cross, _T("picture1/cross.png"), 50, 50);
    safeLoadImage(&home, _T("picture1/home.png"), 50, 50);
    safeLoadImage(&bt, _T("picture/bt.png"),160,50);
    safeLoadImage(&btd, _T("picture/btd.png"), 160, 50);
    safeLoadImage(&btyw, _T("picture/btyw.png"), 160, 50);
    safeLoadImage(&btdyw, _T("picture/btdyw.png"), 160, 50);
    safeLoadImage(&btgn, _T("picture/btgn.png"), 160, 50);
    safeLoadImage(&btdgn, _T("picture/btdgn.png"), 160, 50);


    safeLoadImage(&shield[0], _T("picture1/shield.png"), ROLE_SIZE, ROLE_SIZE);
    safeLoadImage(&shield[1], _T("picture1/shield2.png"), ROLE_SIZE, ROLE_SIZE);
    safeLoadImage(&dragon, _T("picture1/dragon.png"), 100, 60);
    safeLoadImage(&snake, _T("picture1/snake.png"), 100, 60);

    safeLoadImage(&p1_run[0], _T("picture1/run1.png"), ROLE_SIZE, ROLE_SIZE);
    safeLoadImage(&p1_run[1], _T("picture1/run2.png"), ROLE_SIZE, ROLE_SIZE);
    safeLoadImage(&p1_run[2], _T("picture1/run3.png"), ROLE_SIZE, ROLE_SIZE);
    safeLoadImage(&p1_attack[0], _T("picture1/attack1.png"), ROLE_SIZE, ROLE_SIZE);
    safeLoadImage(&p1_attack[1], _T("picture1/attack2.png"), ROLE_SIZE, ROLE_SIZE);
    safeLoadImage(&p1_attack[2], _T("picture1/attack3.png"), ROLE_SIZE, ROLE_SIZE);
    safeLoadImage(&p1_attack[3], _T("picture1/attack4.png"), ROLE_SIZE, ROLE_SIZE);
    safeLoadImage(&p1_jump, _T("picture1/jump.png"), ROLE_SIZE, ROLE_SIZE);

    safeLoadImage(&p2_stand[0], _T("picture1/p2_1.png"), ROLE_SIZE1, ROLE_SIZE1);
    safeLoadImage(&p2_stand[1], _T("picture1/p2_2.png"), ROLE_SIZE1, ROLE_SIZE1);
    safeLoadImage(&p2_stand[2], _T("picture1/p2_3.png"), ROLE_SIZE1, ROLE_SIZE1);
    safeLoadImage(&p2_jump[0], _T("picture1/p2_jump1.png"), ROLE_SIZE1, ROLE_SIZE1);
    safeLoadImage(&p2_jump[1], _T("picture1/p2_jump2.png"), ROLE_SIZE1, ROLE_SIZE1);
    safeLoadImage(&p2_jump[2], _T("picture1/p2_jump1.png"), ROLE_SIZE1, ROLE_SIZE1);
    safeLoadImage(&p2_attack[0], _T("picture1/p2a1.png"), ROLE_SIZE1, ROLE_SIZE1);
    safeLoadImage(&p2_attack[1], _T("picture1/p2a2.png"), ROLE_SIZE1, ROLE_SIZE1);
    safeLoadImage(&p2_attack[2], _T("picture1/p2a3.png"), ROLE_SIZE1, ROLE_SIZE1);

    resetGame();
}

void drawFlip(IMAGE* img, int x, int y, int size, bool flip) {

    if (img == nullptr) return;
    HDC hdc = GetImageHDC(NULL);
    HDC imdc = GetImageHDC(img);
    if (hdc == NULL || imdc == NULL) return;

    BLENDFUNCTION bf;
    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.SourceConstantAlpha = 255;
    bf.AlphaFormat = AC_SRC_ALPHA;

    if (!flip) {
        AlphaBlend(hdc, x, y, size, size,
            imdc, 0, 0, img->getwidth(), img->getheight(), bf);
    }
    else {

        IMAGE tmp(size, size);
        HDC tdc = GetImageHDC(&tmp);
        if (tdc == NULL) return;

        StretchBlt(tdc, 0, 0, size, size,
            imdc, img->getwidth() - 1, 0, -img->getwidth(), img->getheight(), SRCCOPY);

        AlphaBlend(hdc, x, y, size, size, tdc, 0, 0, size, size, bf);
    }
}

void drawHp(int x, int y, int w, int h, int hp, int maxHp, COLORREF color) {
    setfillcolor(RGB(50, 50, 50));
    solidrectangle(x, y, x + w, y + h);

    int rw = hp * w / maxHp;
    setfillcolor(color);
    solidrectangle(x, y, x + rw, y + h);

    setlinecolor(RGB(255, 215, 0));
    setlinestyle(PS_SOLID, 2);
    rectangle(x, y, x + w, y + h);
}

void drawEvery() {
    if (isValidImage(&bg)) {
        putimage(0, 0, &bg);
    }
    else {
        setfillcolor(RGB(30, 30, 50));
        solidrectangle(0, 0, W, H);
    }

    drawHp(50, 30, 400, 30, p1.hp, p1.maxHp, RGB(0, 255, 0));
    drawHp(W - 450, 30, 400, 30, p2.hp, p2.maxHp, RGB(255, 0, 0));

    settextcolor(WHITE);
    setbkmode(TRANSPARENT);
    settextstyle(24, 0, _T("黑体"));
    outtextxy(60, 65, _T("海波东"));
    outtextxy(W - 170, 65, _T("美杜莎"));

    if (!(gameState == LOSE2 || gameState == WIN2)) {
        drawAttackCd(50, 110, p1.attackCd, 60, _T("攻击"));
        drawAttackCd(W - 170, 110, p2.attackCd, 60, _T("攻击"));
        drawAttackCd(50, 150, p1.ultimateCd, 180, _T("大招(玄冰龙翔)"));
        drawAttackCd(W - 170, 150, p2.ultimateCd, 180, _T("大招(蛇)"));
        // 绘制防御CD
        drawAttackCd(50, 190, p1.defendCd, 60, _T("防御(S)"));
        drawAttackCd(W - 170, 190, p2.defendCd, 60, _T("防御"));
    }

    if (p1Ultimate.active && isValidImage(&dragon)) {
        drawFlip(&dragon, p1Ultimate.x, p1Ultimate.y, 100, p1Ultimate.vx < 0);
    }
    if (p2Ultimate.active && isValidImage(&snake)) {
        drawFlip(&snake, p2Ultimate.x, p2Ultimate.y, 100, p2Ultimate.vx < 0);
    }


    // 绘制P1
    static int runFrame1 = 0;
    runFrame1 = (runFrame1 + 1) % 12;
    // 绘制优先级: 攻击 > 跳跃 > 跑动
    if (p1.isAttack && isValidImage(&p1_attack[0])) {
        int frame = p1.attackTimer / 5; // attackTimer范围约为0..19，分成4帧
        if (frame > 3) frame = 3;
        drawFlip(&p1_attack[frame], p1.x, p1.y, ROLE_SIZE, p1.face == -1);
    }
    else if (!p1.isOnGround && isValidImage(&p1_jump)) {
        drawFlip(&p1_jump, p1.x, p1.y, ROLE_SIZE, p1.face == -1);
    }
    else if (p1.isDefending) {
        //int sx = p1.face == -1 ? p1.x + ROLE_SIZE - 40 : p1.x - 40;
        if (isValidImage(&shield[0])) {
            drawFlip(&shield[0], p1.x, p1.y, ROLE_SIZE, p1.face == 1);
        }
    }
    else {
        int idx = (std::min)(runFrame1 / 4, 2);
        drawFlip(&p1_run[idx], p1.x, p1.y, ROLE_SIZE, p1.face == -1);
    }

    // 绘制P2
    static int runFrame2 = 0;
    runFrame2 = (runFrame2 + 1) % 12;
    // 绘制优先级: 攻击 > 跳跃 > 跑动
    if (p2.isAttack && isValidImage(&p2_attack[0])) {
        int frame = p2.attackTimer / 5; // attackTimer范围约为0..19，分成4帧
        if (frame > 3) frame = 3;
        drawFlip(&p2_attack[frame], p2.x, p2.y, ROLE_SIZE1, p2.face == 1);
    }
    else if (!p2.isOnGround && isValidImage(&p2_jump[0])) {
        drawFlip(&p2_jump[runFrame2 / 3], p2.x, p2.y, ROLE_SIZE1, p2.face == 1);
    }
    else if (p2.isDefending) {
        //int sx = p1.face == -1 ? p1.x + ROLE_SIZE - 40 : p1.x - 40;
        if (isValidImage(&shield[1])) {
            drawFlip(&shield[1], p2.x, p2.y, ROLE_SIZE, p2.face == 1);
        }
    }
    else {
        int idx = (std::min)(runFrame2 / 4, 2);
        drawFlip(&p2_stand[idx], p2.x, p2.y, ROLE_SIZE1, p2.face == 1);
    }

}

void drawMenu2() {

    putimage(0, 0, &start);
    drawHome();
    
    drawButton(btnX, btnY, btyw, btdyw);
    drawButton(btnx, btny, btyw, btdyw);


    setbkmode(TRANSPARENT);
    setcolor(RED);
    settextstyle(30, 0, _T("隶书"));
    outtextxy(btnX + 20, btnY + 4, _T("开始游戏"));
    outtextxy(btnx + 20, btny + 4, _T("游戏介绍"));
}


void drawWin2() {
  
    putimage(0, 0, &wini2);
    drawHome();

    drawButton(btnX, btnY, btyw, btdyw);
    drawButton(btnx, btny, btyw, btdyw);
    setbkmode(TRANSPARENT);
    setcolor(RED);
    settextstyle(30, 0, _T("隶书"));
    outtextxy(btnX + 20, btnY + 4, _T("返回菜单"));
    outtextxy(btnx + 20, btny + 4, _T("重新游戏"));
}

void drawlose2() {
   
    putimage(0, 0, &losei2);
    drawHome();
    drawButton(btnX, btnY, btyw, btdyw);
    drawButton(btnx, btny, btyw, btdyw);
    setbkmode(TRANSPARENT);
    setcolor(RED);
    settextstyle(30, 0, _T("隶书"));
    outtextxy(btnX + 20, btnY + 4, _T("返回菜单"));
    outtextxy(btnx + 20, btny + 4, _T("重新游戏"));
}

void drawIntro2() {
    putimage(0, 0, &bkk);
    drawCross();
    drawHome();

    bool inBtn = (m.x >= W-100 && m.x <= W &&
        m.y >= H/2-100 && m.y <= H/2);
    if (inBtn) {
        drawRight();
    }
}

void drawCross() {
    DrawTransparentImage(W - 60, 20,&cross);
}

void drawRight() {
    DrawTransparentImage(W - 100, H / 2 - 100, &ar);
}

void drawLeft() {
    DrawTransparentImage(0, H / 2 - 100, &al);
}

void drawIntro2_1() {
    putimage(0, 0, &dd);
    drawCross();
    drawHome();

    bool inBtn = (m.x >= W - 100 && m.x <= W &&
        m.y >= H / 2 - 100 && m.y <= H / 2);
    if (inBtn) {
        drawRight();
    }

    bool inBtn1 = (m.x >= 0 && m.x <=100  &&
        m.y >= H / 2 - 100 && m.y <= H / 2);
    if (inBtn1) {
        drawLeft();
    }
}

void drawIntro2_2() {
    putimage(0, 0, &mds);
    drawCross();
    drawHome();

    bool inBtn1 = (m.x >= 0 && m.x <= 100 &&
        m.y >= H / 2 - 100 && m.y <= H / 2);
    if (inBtn1) {
        drawLeft();
    }
}

void drawHome() {
    DrawTransparentImage(0, H-70, &home);
}

void drawButton(int btx, int bty ,IMAGE imgbt,IMAGE imgbtd) {

    DrawTransparentImage(btx, bty,&imgbt);
    bool inBtn = (m.x >= btx && m.x <= btx + 160 &&
        m.y >= bty && m.y <= bty + 50);

    if (inBtn)
    {
            DrawTransparentImage(btx, bty, &imgbtd);      
    }
    else
    {
        DrawTransparentImage(btx, bty, &imgbt);
    }

}
