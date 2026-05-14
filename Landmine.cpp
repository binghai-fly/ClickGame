#include"head.h"

Landmine lm[MAX_LANDMINE];
IMAGE lmImg;
Boom boom[MAX_BOOM];
IMAGE bmImg;


void lmInit() {
    // Ensure correct file extension and size
    loadimage(&lmImg, _T("picture/tile_0148.png"), 24, 24);
	loadimage(&bmImg, _T("picture/boom.png"), 24, 24);
	for (int i = 0; i < MAX_LANDMINE; i++) {
		lm[i].isAlive = false;
        lm[i].img = lmImg;
		lm[i].w = 24;
		lm[i].h = 24;
		boom[i].h = 24;
		boom[i].w = 24;
		boom[i].isAlive = false;
        boom[i].img = bmImg;
	}
	
}

void LayLm(int x, int y) {
	if (player.coins >= 3) {
		for (int i = 0; i < MAX_LANDMINE; i++) {
			if (lm[i].isAlive) continue;
			else {
                lm[i].x = x - lm[i].w / 2;
				lm[i].y = y - lm[i].h / 2;
				// show explosion immediately at placement
				boom[i].x = x - boom[i].w / 2;
				boom[i].y = y - boom[i].h / 2;
                lm[i].isAlive = true; // mark placed mine as active so it will be drawn
				player.coins -= 3;
				break;
			}
			
		}
	}
}

void lmDraw() {
	for (int i = 0; i < MAX_LANDMINE; i++) {
		if (lm[i].isAlive) {
			DrawTransparentImage(lm[i].x, lm[i].y, &lm[i].img);
		}
	}
	for (int i = 0; i < MAX_BOOM; i++) {
		if (boom[i].isAlive) {
			DrawTransparentImage(boom[i].x, boom[i].y, &boom[i].img);
			if (GetTickCount() - boom[i].startTime > 200) { // œ‘ æ 200ms
				boom[i].isAlive = false;
			}
		}
	}
	
	
}