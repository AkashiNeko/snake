//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
//
//    date:   2022-6-5
//    author: Akashi (氟氟)
//    github: https://github.com/AkashiNeko/snake
//    QQ:     1006554341
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#include "game.h"
int size = 20;
int speed = 5;
void game()
{
	int state = 1, ret;
	window_size(22 + size * 2, size + 7);
	do
	{
		//打印地图边框
		print_map_frame();
		//打印游戏提示
		print_game_tips();
		//玩家操作
		ret = play();
		if (ret == 0)
			return;
		setcl(0x0f);
		system("cls");
	} while (state);
}
int main()
{
	srand((unsigned int)time(NULL));
	int select;
	
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	system("@chcp 936");
	system("cls");
	system("@title 贪吃蛇 - By AkashiNeko");
	while (1)
	{
		select = start_menu();
		switch (select)
		{
		case 0:
			game();
			break;
		case 1:
			setting();
			break;
		case 2:
			setcl(0x0f);
			system("cls");
			return 0;
		default:
			exit(114514);
		}
	}
	return 0;
}