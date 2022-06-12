#include "game.h"

HANDLE h;

void setrd(int x, int y)
{
	//设置打印坐标
	COORD rd = { x,y };
	SetConsoleCursorPosition(h, rd);
}//setrd 

void setcl(int color)
{
	//设置打印颜色
	SetConsoleTextAttribute(h, color);
}//setcl 

void disp(int color, int x, int y, char* str)
{
	//在指定位置以指定颜色打印
	COORD rd = { x,y };
	SetConsoleCursorPosition(h, rd);
	SetConsoleTextAttribute(h, color);
	printf("%s", str);
}//disp 

void print_start_menu()
{
	//打印开始菜单
	disp(MENU_COLOR, 2, 2, "==== 贪吃蛇 ====");
	disp(TIP_COLOR, 3, 10, "[↑][↓] 移动");
	disp(TIP_COLOR, 3, 12, "[Enter] 选择");
}//print_start_menu 

void print_start_menu_options(int select)
{
	//打印开始菜单选项
	
	//选项1
	setrd(5, 4);
	if (select == 0) setcl(SEL_COLOR);
	else setcl(MENU_COLOR);
	printf(" 1. 开始 ");
	//选项2
	setrd(5, 6);
	if (select == 1) setcl(SEL_COLOR);
	else setcl(MENU_COLOR);
	printf(" 2. 设置 ");
	//选项3
	setrd(5, 8);
	if (select == 2) setcl(SEL_COLOR);
	else setcl(MENU_COLOR);
	printf(" 3. 退出 ");
	setrd(0, 0);
}//print_start_menu_options

void print_setting_options(int select)
{
	//打印设置菜单选项
	setrd(3, 4);
	if (select == 0) setcl(SEL_COLOR);
	else setcl(MENU_COLOR);
	printf("地图大小");

	setrd(12, 4);
	if (select == 3) setcl(0x1b);
	else setcl(0x0a);
	printf("%2d", size);

	setrd(3, 6);
	if (select == 1) setcl(SEL_COLOR);
	else setcl(MENU_COLOR);
	printf("蛇的速度");

	setrd(12, 6);
	if (select == 4) setcl(0x1b);
	else setcl(0x0a);
	printf("%2d", speed);

	setrd(3, 8);
	if (select == 2) setcl(SEL_COLOR);
	else setcl(MENU_COLOR);
	printf("返回菜单");

	setrd(0, 0);
}//print_setting_options

void print_setting_tip1()
{
	//设置菜单提示1
	setcl(TIP_COLOR);
	setrd(2, 10);
	printf("[↑][↓]  增/减");
	setrd(2, 12);
	printf("[←]      确定 ");
	setrd(2, 14);
	printf("[Enter]   确定 ");
}//print_setting_tip1

void print_setting_tip2()
{
	//设置菜单提示2
	setcl(TIP_COLOR);
	setrd(2, 10);
	printf("[↑][↓]  移动  ");
	setrd(2, 12);
	printf("[→]      选择 ");
	setrd(2, 14);
	printf("[Enter]   选择  ");
}//print_setting_tip2

void print_map_frame()
{
	//打印地图边框
	int i;
	setcl(MAP_FRA);
	//上边界（包含角）
	setrd(2, 1);
	for (i = 0; i < size + 2; i++)
	{
		printf("　");
	}
	//下边界（包含角）
	setrd(2, size + 2);
	for (i = 0; i < size + 2; i++)
	{
		printf("　");
	}
	//左右边界（不含角）
	for (i = 2; i < size + 2; i++)
	{
		setrd(2, i);
		printf("　");
		setrd(4 + size * 2, i);
		printf("　");
	}
	setcl(SCORE);
	setrd(9 + size * 2, 14);
	printf("Scores:  0  ");
}//print_map_frame 

void print_score(int s)
{
	//打印分数
	setcl(SCORE);
	setrd(16 + size * 2, 14);
	printf("%3d", s);
}//print_score

void print_total_snake(link p)
{
	//打印整条蛇
	//蛇头（HEAD_COLOR）
	disp(HEAD_COLOR, 4 + p->x * 2, 2 + p->y, BODY);
	p = p->nex;
	while (p != NULL)
	{
		//蛇身（SNK_COLOR）
		disp(SNK_COLOR, 4 + p->x * 2, 2 + p->y, BODY);
		p = p->nex;
	}
}//print_total_snake 

void print_node(snake node, int color, char* text)
{
	//打印节点
	disp(color, 4 + node.x * 2, 2 + node.y, text);
	setrd(0, 0);
}//print_node

void print_food(food fd)
{
	//打印食物
	disp(FOOD_COLOR, 4 + fd.x * 2, 2 + fd.y, FOOD);
	setrd(0, 0);
}//print_food

void subtips(int i)
{
	//打印小提示
	setrd(4, size + 4);
	setcl(TIP_COLOR);
	switch (i)
	{
	case up:
		printf("向上移动           ");
		break;
	case down:
		printf("向下移动           ");
		break;
	case left:
		printf("向左移动           ");
		break;
	case right:
		printf("向右移动           ");
		break;
	case 4:
		printf("                   ");
		break;
	case 5:
		printf("游戏开始           ");
		break;
	case 6:
		printf("游戏继续           ");
		break;
	case 7:
		printf("按下[Ｐ]开始游戏   ");
		break;
	case 8:
		printf("按下[Ｐ]继续游戏   ");
		break;
	case 9:
		printf("游戏结束           ");
		break;
	}
	setrd(0, 0);
}//subtips

void print_game_tips()
{
	//打印游戏提示
	setcl(MENU_COLOR);
	setrd(12 + size * 2, 2);
	printf("[Ｗ]");
	setrd(8 + size * 2, 4);
	printf("[Ａ][Ｓ][Ｄ]");
	setrd(8 + size * 2, 6);
	printf("或方向键移动");
	setrd(9 + size * 2, 8);
	printf("[Ｒ]  重开");
	setrd(9 + size * 2, 10);
	printf("[Ｅ]  退出");
	setrd(9 + size * 2, 12);
	printf("[Ｐ]  暂停");
}//print_game_tips