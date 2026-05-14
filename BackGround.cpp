#include "head.h"

BackgroundTile bgTiles[MAX_BG_TILES];

void BGLoad() {
	// 只加载一张背景图，节省内存
	bgTiles[0].x = 0;
	bgTiles[0].y = 0;
	bgTiles[0].w = W;
	bgTiles[0].h = H;
	loadimage(&bgTiles[0].img, _T("picture/bk2.png"), W, H);
}

void DrawAllBgTiles() {
	// 只绘制一张背景图，大幅提升性能
	putimage(bgTiles[0].x, bgTiles[0].y, &bgTiles[0].img);
}


