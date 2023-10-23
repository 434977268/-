#include "Tetris.h"
#include "Block.h"
#include <conio.h>
#define MAX_LEVEL 5
//const int SPEED_NORMAL = 500;//ms

const int SPEED_NORMAL[MAX_LEVEL] = {500,300,150,100,80};//ms

const int SPEED_QUICK = 30;//ms

using namespace std;
Tetris::Tetris(int rows, int cols, int left, int top, int blockSize)
{
	this->rows = rows;
	this->cols = cols;
	this->leftMargin = left;
	this->topMargin = top;
	this->blockSize = blockSize;
	this->score = 0;
	this->lineCount = 0;
	this->level = 1;
	for (int i = 0; i < rows; i++)
	{
		vector<int> mapRow;
		for (int j = 0; j < cols; j++)
		{
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}
}

void Tetris::Init()
{
	srand(time(NULL));
	delay = SPEED_NORMAL[0];
	//创建游戏窗口
	initgraph(938, 896);
	//加载背景图片
	loadimage(&imgBg, "res/bg2.png");

	//初始化游戏区中的数据
	char data[20][10];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			map[i][j] = 0;
		}
	}
}

void Tetris::Play()
{
	Init();

	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;



	int timer = 0;
	while (true) {
		//接收用户输入
		KeyEvent();
		timer += GetDelay();//计算延时总时间
		//延时大于30时重新渲染一次
		if (timer > delay) {
			timer = 0;
			Drop();
			update = true;

		}
		if (update) {
			update = false;
			//渲染游戏画面
			UpdataWindow();
			//更新游戏数据
			ClearLine();
		}
	}
}

void Tetris::moveLeftRight(int offset)
{
	bakBlock = *curBlock;
	curBlock->moveLeftRight(offset);

	if (!curBlock->blockInMap(map)) {
		*curBlock = bakBlock;
	}

}

void Tetris::KeyEvent()
{
	unsigned char ch = 0;

	bool rotate = false;
	INT dx = 0;
	if (_kbhit()) {
		ch = _getch();
	}
	//按下方向键会自动返回两个字符 
	//向上 依次返回 224 72
	//向下 依次返回 224 80
	//向左 依次返回 224 75
	//向右 依次返回 224 77

	if (ch == 224) {
		ch = _getch();

		switch (ch)
		{
		case 72: rotate = true;
			break;
		case 80: delay = SPEED_QUICK;
			break;
		case 75: dx = -1;
			break;
		case 77: dx = 1;
			break;
		}

	}

	if (rotate) {
		this->Rotate();
		rotate = true;
	}

	if (dx != 0) {
		moveLeftRight(dx);
		update = true;
	}


}

void Tetris::UpdataWindow()
{
	putimage(0, 0, &imgBg);//绘制背景图片
	IMAGE** imgs = Block::getImage();
	BeginBatchDraw();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j] == 0)
				continue;
			int x = j * blockSize + leftMargin;
			int y = i * blockSize + topMargin;

			putimage(x, y, imgs[map[i][j] - 1]);
		}
	}


	curBlock->Draw(leftMargin, topMargin);
	nextBlock->Draw(689, 150);

	DrawScore();



	EndBatchDraw();

	/*Block block;
	block.Draw(263,163);*/
}

int Tetris::GetDelay()
{
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();
	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}
}

void Tetris::Drop()
{
	bakBlock = *curBlock;
	curBlock->Drop();

	if (!curBlock->blockInMap(map)) {
		bakBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;
	}

	delay = SPEED_NORMAL[level-1];
}

void Tetris::ClearLine()
{
	int lines = 0;
	int k = rows - 1;
	for (int i = rows - 1; i >= 0; i--)
	{
		int count = 0;
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j]) {
				count++;
			}
			map[k][j] = map[i][j];
		}

		if (count < cols) {
			k--;
		}
		else {
			lines++;
		}

	}

	if (lines > 0) {

		int addScore[4] = { 10,30,60,80 };
		score += addScore[lines - 1];
		mciSendString("play res/xiaochu1.mp3", 0, 0, 0);
		update = true;

		level = (score + 99) / 100;
	}
}

void Tetris::Rotate()
{
	if (curBlock->GetBlockType() == 7)
		return;
	bakBlock = *curBlock;
	curBlock->Rotate();
	if (!curBlock->blockInMap(map)) {
		*curBlock = bakBlock;
	}
}

void Tetris::DrawScore()
{
	char scoreText[32];
	sprintf_s(scoreText, sizeof(scoreText), "%d", score);

	setcolor(RGB(179, 179, 179));

	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 60;
	f.lfWidth = 30;
	f.lfQuality = ANTIALIASED_QUALITY;
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI Black"));
	settextstyle(&f);
	setbkmode(TRANSPARENT);
	outtextxy(670, 727, scoreText);


	sprintf_s(scoreText, sizeof(scoreText), "%d", lineCount);
	settextstyle(&f);
	int xPos = 224 - f.lfWidth * strlen(scoreText);
	outtextxy(xPos, 817, scoreText);


	sprintf_s(scoreText, sizeof(scoreText), "%d", level);
	outtextxy(224 - 30, 727, scoreText);

}
