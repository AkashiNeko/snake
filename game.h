#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

//颜色
#define MENU_COLOR		0x0e	//菜单颜色
#define TIP_COLOR		0x06	//提示颜色
#define SEL_COLOR		0x3f	//菜单选中
#define HEAD_COLOR		0x03	//蛇头颜色
#define HEAD_EAT		0x0a	//吃食物时蛇头颜色
#define SNK_COLOR		0x0b	//蛇身颜色
#define FOOD_COLOR		0x06	//食物颜色
#define MAP_FRA			0xf1	//地图边框
#define SCORE			0x0a	//地图边框

//蛇身和食物
#define BODY "●"
#define FOOD "★"

//全局变量
extern HANDLE h;
extern int size;
extern int speed;

//蛇的方向
enum { up,down,left,right };

/******************** 自定义数据类型 ********************/

//蛇（双向链表）
typedef struct snakeNode
{
	short x;
	short y;
	struct snakeNode* pri;
	struct snakeNode* nex;
}snakeNode, * link;

//蛇头
typedef struct snake
{
	short x;	//x坐标
	short y;	//y坐标
	int dir;	//方向
}snake;

//食物
typedef struct food
{
	short x;	//x坐标
	short y;	//y坐标
	int score;	//食物加分
	int exist;	//是否存在
}food;

/******************** game.c 函数定义 ********************/

//开始目录
int start_menu();

//设置菜单
void setting();

//设置窗口尺寸
void window_size(int cols, int lines);

//进入游戏
int play(map);

//玩家输入（控制蛇的方向）
int player_input(int dir);

//生成食物
food add_food(link p, short map[20][20]);

/******************** disp.c 函数定义 ********************/

//设置打印坐标
void setrd(int x, int y);

//设置打印颜色
void setcl(int color);

//在指定位置以指定颜色打印
void disp(int color, int x, int y, char* str);

//打印开始菜单
void print_start_menu();

//打印开始菜单选项
void print_start_menu_options(int select);

//打印设置菜单选项
void print_setting_options(int select);

//设置菜单提示1
void print_setting_tip1();

//设置菜单提示2
void print_setting_tip2();

//打印地图边框
void print_map_frame();

//打印分数
void print_score(int score);

//打印整条蛇
void print_total_snake(link p);

//打印节点
void print_node(snake node, int color, char* text);

//打印食物
void print_food(food fd);

//打印小提示
void subtips(int i);

//打印游戏提示
void print_game_tips();

/******************** snake.c 函数定义 ********************/

//初始化蛇
void init_snake(snake, link*, link*, short[20][20]);

//下一个坐标（根据蛇头的坐标和方向）
void next_coor(snake* node);

//上一个坐标（根据蛇头的坐标和方向）
void prior_coor(snake* node);

//移动
int move(snake* pS, link* pHead, link* pEnd, food* fd, short map[20][20], int* score);

//释放整条蛇的链表占用的内存
void free_total_snake(link p);

#endif