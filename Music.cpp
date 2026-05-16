#include"head.h"

// 播放背景音乐（独立别名：bgm）
void PlayBGM(const TCHAR* name)
{
    mciSendString(_T("close bgm"), NULL, 0, NULL);
    TCHAR path[128], cmd[256];
    wsprintf(path, _T("sound/%s"), name);
    wsprintf(cmd, _T("open %s alias bgm"), path);
    mciSendString(cmd, NULL, 0, NULL);
    mciSendString(_T("play bgm repeat"), NULL, 0, NULL);
}

// 停止背景音乐
void StopBGM()
{
    mciSendString(_T("stop bgm"), NULL, 0, NULL);
    mciSendString(_T("close bgm"), NULL, 0, NULL);
}

// 播放胜利音乐（独立别名：win_music）
void PlayWinMusic(const TCHAR* name)
{
    mciSendString(_T("close win_music"), NULL, 0, NULL);
    TCHAR path[128], cmd[256];
    wsprintf(path, _T("sound/%s"), name);
    wsprintf(cmd, _T("open %s alias win_music"), path);
    mciSendString(cmd, NULL, 0, NULL);
    mciSendString(_T("play win_music"), NULL, 0, NULL);
}

// 播放失败音乐（独立别名：lose_music）
void PlayLoseMusic(const TCHAR* name)
{
    mciSendString(_T("close lose_music"), NULL, 0, NULL);
    TCHAR path[128], cmd[256];
    wsprintf(path, _T("sound/%s"), name);
    wsprintf(cmd, _T("open %s alias lose_music"), path);
    mciSendString(cmd, NULL, 0, NULL);
    mciSendString(_T("play lose_music"), NULL, 0, NULL);
}

// 播放地雷爆炸音效（独立别名：mine_sound）
void PlayMineExplode(const TCHAR* name)
{
    mciSendString(_T("close mine_sound"), NULL, 0, NULL);
    TCHAR path[128], cmd[256];
    wsprintf(path, _T("sound/%s"), name);
    wsprintf(cmd, _T("open %s alias mine_sound"), path);
    mciSendString(cmd, NULL, 0, NULL);
    mciSendString(_T("play mine_sound"), NULL, 0, NULL);
}

// 播放WAV子弹音效（不变）
//void PlayWAV(const TCHAR* name)
//{
//    TCHAR path[128];
//    wsprintf(path, _T("sound/%s"), name);
//    PlaySound(path, NULL, SND_ASYNC | SND_NOSTOP);
//}