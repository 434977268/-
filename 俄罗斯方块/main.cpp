/*开发日志：
1、创建项目
2、先导入素材
3、C++开发
4、设计C++模块（设计类:Block 方块类\Tetris 游戏控制类）
5、设计各个模块的接口
6、启动游戏
*/

#include "Tetris.h"
#include "Block.h"

int main(void) {
	Tetris game (20, 10, 263, 133, 36);
	game.Play();
}