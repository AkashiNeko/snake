#define _CRT_SECURE_NO_WARNINGS

#include "game.h"

int start_menu()
{
	//开始目录
	char ch, select = 0;
	setcl(0x0f);
	system("cls");
	window_size(20, 16);
	//打印开始菜单
	print_start_menu();
	while (1)
	{
		//打印选项
		print_start_menu_options(select);
		while (1)
		{
			int brk = 0;
			if (_kbhit())
			{
				switch (ch = _getch())
				{
				case -32: //方向键
					ch = _getch();
					switch (ch)
					{
					case 72: //上
						if (select == 0)
							select = 2;
						else
							select--;
						brk = 1;
						break;
					case 80: //下
						if (select == 2)
							select = 0;
						else
							select++;
						brk = 1;
						break;
					default:
						break;
					}
					break;
				case 13: //回车
					setcl(0x0f);
					system("cls");
					return select;
				default:
					break;
				}//switch getch
			}//if kbhit
			if (brk) break;
		}//while
	}//while
}//start_menu

void setting()
{
	//设置菜单
	char ch, select = 0;
	window_size(20, 18);
	setrd(2, 2);
	setcl(MENU_COLOR);
	printf("==== 设置 ====");
	setcl(TIP_COLOR);
	setrd(2, 16);
	printf("[ESC]     返回   ");
	print_setting_tip2();
	sel:
	print_setting_options(select);
	while (1)
	{
		if (_kbhit())
		{
			switch (ch = _getch())
			{
			case -32: //方向键
				ch = _getch();
				switch (ch)
				{
				case 72: //上
					switch (select)
					{
					case 0: select = 2;
						break;
					case 1: select = 0;
						break;
					case 2: select = 1;
						break;
					case 3:
						if (size < 20)
							size++;
						break;
					case 4:
						if (speed < 10)
							speed++;
						break;
					}
					goto sel;
					break;
				case 80: //下
					switch (select)
					{
					case 0: select = 1; break;
					case 1: select = 2; break;
					case 2: select = 0; break;
					case 3:
						if (size > 10)
							size--;
						break;
					case 4:
						if (speed > 1)
							speed--;
						break;
					}
					goto sel;
					break;
				default:
					break;
					case 75:  //左
					case 77:; //右
				}
			case 13:	//回车
				switch (select)
				{
				case 2: //返回
					return;
				case 0:
					select = 3;
					print_setting_tip1();
					break;
				case 1:
					select = 4;
					print_setting_tip1();
					break;
				case 3:
					select = 0;
					print_setting_tip2();
					break;
				case 4:
					select = 1;
					print_setting_tip2();
					break;
				}
				goto sel;
				break;
			case 27: //ESC
				return;
			default:
				break;
			}
		}
	}
}//setting

void window_size(int cols, int lines)
{
	//设置窗口尺寸
	char cmd[30];
	sprintf(cmd, "mode con cols=%d lines=%d", cols, lines);
	if (cols > 13)
		system(cmd);
}//window_size

int play()
{
	//进入游戏
	int dret, ret;
	short map[20][20] = { 0 };
	link pHead, pEnd;
	food fd = { 0,0,5,0 };
	//生成随机坐标和方向
	short rx = rand() % 4 + (size / 2 - 2);
	short ry = rand() % 4 + (size / 2 - 2);
	int rd = rand() % 4;
	snake head = { rx, ry, rd };
	int pause = 1;	//暂停状态
	int first = 1;	//初次进入
	int over = 0;	//游戏状态
	int score = 0;	//分数
	//初始化蛇
	init_snake(head, &pHead, &pEnd, map);
	//打印初始的蛇
	print_total_snake(pHead);
	//游戏过程
	while (1)
	{
		if (pause == 1)
		{
			int tips = 1;
			int whl = 1;
			while (whl)
			{
				switch (player_input(head.dir))
				{
				case 'p':
					FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
					pause = 0;
					whl = 0;
					if (first)
						subtips(5);
					else
						subtips(6);
					break;
				case 'r':
					free_total_snake(pHead);
					return 1;
				case 'e':
					free_total_snake(pHead);
					return 0;
				default:
					if (tips)
					{
						if (first)
							subtips(7);
						else
							subtips(8);
						tips = 0;
					}
					break;
				}
			}
		}//if pause == 1

		//食物不存在，重新生成食物
		if (fd.exist == 0)
		{
			fd = add_food(pHead, map);
		}
		//玩家输入方向（未输入则保持原来方向）
		dret = player_input(head.dir);
		switch (dret)
		{
		case up:
		case down:
		case left:
		case right:
			if (over) break;
			subtips(dret);
			head.dir = dret;
			break;
		case 'p':
			pause = 1;
			break;
		case 'r':
			free_total_snake(pHead);
			return 1;
		case 'e':
			free_total_snake(pHead);
			return 0;
		}
		//蛇移动
		if(over == 0)
			ret = move(&head, &pHead, &pEnd, &fd, map, &score);
		if (ret == 0)
		{
			subtips(9);
			over = 1;
			ret = -1;
		}
		Sleep(1000 / speed);
		if(first) first = 0;
	}
	return 0;
}//play

int player_input(int dir)
{
	//玩家输入（控制蛇的方向）
	char ch;
	if (_kbhit())
	{
		switch (ch = _getch())
		{
		case -32: //方向键
			ch = _getch();
			switch (ch)
			{
			case 72: //上
				if(dir == left || dir == right)
					return up;
				break;
			case 80: //下
				if (dir == left || dir == right)
					return down;
				break;
			case 75: //左
				if (dir == up || dir == down)
					return left;
				break;
			case 77: //右
				if (dir == up || dir == down)
					return right;
				break;
			default:
				break;
			}
			break;
		case 'w':
		case 'W':
			if (dir == left || dir == right)
				return up;
			break;
		case 's':
		case 'S':
			if (dir == left || dir == right)
				return down;
			break;
		case 'a':
		case 'A':
			if (dir == up || dir == down)
				return left;
			break;
		case 'd':
		case 'D':
			if (dir == up || dir == down)
				return right;
			break;
		case 'r':
		case 'R':
			return 'r';
		case 'e':
		case 'E':
		case 27: //ESC
			return 'e';
		case 'p':
		case 'P':
		case 13: //回车
		case 32: //空格
			return 'p';
		default:
			break;
		}//switch getch
	}//if kbhit
	return dir;
}//player_input

food add_food(link p, short map[20][20])
{
	//生成食物
	food fd;
	do
	{
		fd.x = rand() % size;
		fd.y = rand() % size;
	} while (map[fd.x][fd.y]);
	print_food(fd);
	fd.exist = 1;
	fd.score = rand() % 3 + 4;
	return fd;
}//add_food