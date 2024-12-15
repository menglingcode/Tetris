//调用game，完成游戏的进行

//关于文件的说明
//block，panel涉及数据操作，为service
//bootom，game层（game层也会调用service函数）为view层
//common为储存变量用

#include <graphics.h>
#include "botton.h"
#include "cubePoint.h"
#include "block.h"
#include "panel.h"
#include <iostream>
#include "easyx.h"
#include "game.h"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")


void BGM() {
	mciSendString("open res/music.mp3", 0, 0, 0);
	mciSendString("play res/music.mp3", 0, 0, 0);
}

// 绘制页面1的函数
void dieview()
{

	settextcolor(RED);
	settextstyle(30, 0, _T("微软雅黑"));
	outtextxy(150,460,	_T("gameover"));
	outtextxy(150,500,	_T("return to menu"));
}

void startgame(panel p) {

	initgraph(500, 750, EW_SHOWCONSOLE);
	IMAGE img;
	loadimage(&img, _T("res/background.png"), 500, 750);
	putimage(0, 0, &img);

	BlockFactory* block = new BlockFactory("LongBlock");
	block->shape();
	block->setLocate(16, 1);
	//block->showblock();

	p.now_block = block;
	p.setPenal();

	int cflag = 0;

	//game g = game();

	ExMessage msg;
	while (cflag == 0) {
		BeginBatchDraw();
		if (peekmessage(&msg, EM_MOUSE)) {
			switch (msg.message) {
			case WM_LBUTTONDOWN:
				//转
				if (msg.x >= 319 && msg.x <= 332 + 60 && msg.y >= 509 && msg.y <= 509 + 60) {
					p.erasePenal();
					if (p.can_roll()) {
						p.now_block->rotate();
						p.setPenal();

					}
				}
				//左
				if (msg.x >= 248 && msg.x <= 248 + 60 && msg.y >= 562 && msg.y <= 562 + 60) {
					p.erasePenal();
					if (!p.isAttachLeft()) {
						p.now_block->move(1);
					}
					p.setPenal();

				}
				//右
				if (msg.x >= 400 && msg.x <= 400 + 60 && msg.y >= 576 && msg.y <= 576 + 60) {
					p.erasePenal();
					if (!p.isAttachRight()) {
						p.now_block->move(2);
					}
					p.setPenal();

				}

				//下
				if (msg.x >= 315 && msg.x <= 315 + 60 && msg.y >= 634 && msg.y <= 634 + 60) {
					p.erasePenal();
					if (!p.isAttachBottom()) {
						p.now_block->move(0);

						if (p.isAttachBlock()) {
							p.setPenal();
							p.erase();// 生成方块前 做整行消除判定
							
							if (p.haveblock() && p.gameOver()) {
								cleardevice();
								dieview();

								while (cflag == 0) {
									if (peekmessage(&msg, EM_MOUSE)) {
										switch (msg.message) {
										case WM_LBUTTONDOWN:
											if (msg.x >= 150 && msg.x <= 150 + 60 && msg.y >= 480 && msg.y <= 480 + 60) {
												p.viewflag = 0;
												cflag = 1;
												break;
											}
										}
									}
								}
							}
							p.createCube();
						}
						else {
							p.setPenal();
						}

					}
				}
				break;
			default:
				break;
			}
		}
		else {
			Sleep(500);
			p.erasePenal();
			if (!p.isAttachBottom()) {
				p.now_block->move(0);

				if (p.isAttachBlock()) {
					p.setPenal();
					p.erase();// 生成方块前 做整行消除判定

					if (p.haveblock() && p.gameOver()) {
						cleardevice();
						dieview();

						while (cflag == 0) {
							if (peekmessage(&msg, EM_MOUSE)) {
								switch (msg.message) {
								case WM_LBUTTONDOWN:
									if (msg.x >= 150 && msg.x <= 150 + 60 && msg.y >= 480 && msg.y <= 480 + 60) {
										p.viewflag = 0;
										cflag = 1;
										break;
									}
								}
							}
						}
					}
					p.createCube();
				}
				else {
					p.setPenal();
				}

			}
		}
		p.showscore(p.score);
		p.showpanel();
		EndBatchDraw();
	}

}



void panel::gameview(panel p) {

	initgraph(500, 750, EW_SHOWCONSOLE);
	BGM();
	ExMessage msg;

	while (true) {
		if (viewflag == 0) {
			startview();
			while (viewflag == 0) {
				if (peekmessage(&msg, EM_MOUSE)) {
					switch (msg.message) {
					case WM_LBUTTONDOWN:
						if (msg.x >= 150 && msg.x <= 150 + 30 && msg.y >= 109 && msg.y <= 109 + 40) {
							viewflag = 1;
						}
						if (msg.x >= 150 && msg.x <= 150 + 30 && msg.y >= 177 && msg.y <= 177 + 40) {
							viewflag = 2;
						}
						if (msg.x >= 150 && msg.x <= 150 + 30 && msg.y >= 247 && msg.y <= 247 + 40) {
							viewflag = 3;
						}
						if (msg.x >= 0 && msg.x <= 0 + 30 && msg.y >= 0 && msg.y <= 0 + 40) {
							viewflag = 4;
						}
						break;
					default:
						break;
					}
				}
			}
		}
		else if (viewflag == 1) {
			if (viewflag == 1) {
				startgame(p);
			}
		}
		else if (viewflag == 2) {
			settinggame();
			while (viewflag == 2) {
				if (peekmessage(&msg, EM_MOUSE)) {
					switch (msg.message) {
					case WM_LBUTTONDOWN:
						if (msg.x >= 313 && msg.x <= 313 + 30 && msg.y >= 372 && msg.y <= 372 + 40) {
							viewflag = 0;
						}
						break;
					default:
						break;
					}
				}
			}
		}
		else if (viewflag == 3) {
			exitgame();
		}
		else {
			aboutgame();
			while (viewflag == 4) {
				if (peekmessage(&msg, EM_MOUSE)) {
					switch (msg.message) {
					case WM_LBUTTONDOWN:
						if (msg.x >= 304 && msg.x <= 304 + 30 && msg.y >= 383 && msg.y <= 383 + 40) {
							viewflag = 0;
						}
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

int main()
{
	panel p = panel();
	p.gameview(p);
	
	

	/*
	initgraph(500, 750, EW_SHOWCONSOLE);
	IMAGE img;
	loadimage(&img, _T("res/background.png"), 500, 750);
	putimage(0, 0, &img);

	CubePoint p;
	p.printnum(123456);

	getchar();
	*/
}

/*
* 
* 
	游戏界面：
		消除后加分
		右上角的分数修改
		直接掉落（可选）

	开始界面：
		整合进程序

	死亡界面：
		整合进程序




*/

