#include "game.h"

void init_snake(snake node, link* pHead, link* pEnd, short map[20][20])
{
	//初始化蛇（创建一条长度为3的蛇）
	link s = NULL;
	//蛇头
	s = (link)malloc(sizeof(snakeNode));
	if (s == NULL) exit(1);
	s->x = node.x; s->y = node.y;
	map[node.x][node.y] = 1;
	s->pri = NULL;
	*pHead = s;
	//蛇身（中间）
	s = (link)malloc(sizeof(snakeNode));
	if (s == NULL) exit(1);
	s->pri = *pHead;
	(*pHead)->nex = s;
	prior_coor(&node);
	s->x = node.x; s->y = node.y;
	map[node.x][node.y] = 1;
	//蛇尾
	s = (link)malloc(sizeof(snakeNode));
	if (s == NULL) exit(1);
	s->pri = (*pHead)->nex;
	(s->pri)->nex = s;
	prior_coor(&node);
	s->x = node.x; s->y = node.y;
	map[node.x][node.y] = 0;
	s->nex = NULL;
	*pEnd = s;
}//init_snake

void next_coor(snake* node)
{
	//寻找下一个坐标（根据蛇头的坐标和方向）
	switch (node->dir)
	{
	case up: node->y--;
		break;
	case down: node->y++;
		break;
	case left: node->x--;
		break;
	case right: node->x++;
		break;
	}
}//next_coor

void prior_coor(snake* node)
{
	//寻找上一个坐标（根据蛇头的坐标和方向）
	switch (node->dir)
	{
	case up: node->y++;
		break;
	case down: node->y--;
		break;
	case left: node->x++;
		break;
	case right: node->x--;
		break;
	}
}//prior_coor

int move(snake* pS, link* pHead, link* pEnd, food* fd, short map[20][20], int* score)
{
	//移动
	snake snake_end;
	snake origin = *pS;
	next_coor(pS);
	if (map[pS->x][pS->y] == 1)
	{
		print_node(*pS, 0x0c, "●");
		return 0;
	}
	if (pS->x < 0 || pS->y < 0 || pS->x >= size || pS->y >= size)
	{
		print_node(*pS, 0xcc, "  ");
		return 0;
	}
	//插入新的蛇头
	link s = (link)malloc(sizeof(snakeNode));
	if (s == NULL) exit(1);
	s->x = pS->x; s->y = pS->y;
	(*pHead)->pri = s;
	s->nex = *pHead;
	*pHead = s;
	//打印蛇头后的一节身体
	print_node(origin, SNK_COLOR, BODY);
	map[pS->x][pS->y] = 1;
	//删除尾部
	if (s->x == fd->x && s->y == fd->y)
	{
		//碰到食物
		//只插头不删尾
		*score += fd->score;
		print_score(*score);
		print_node(*pS, HEAD_EAT, BODY);
		fd->exist = 0;
		return 1;
	}
	snake_end.x = (*pEnd)->x;
	snake_end.y = (*pEnd)->y;
	//清除蛇尾
	print_node(snake_end, 0x0f, "　");
	//打印蛇头
	print_node(*pS, HEAD_COLOR, BODY);
	*pEnd = (*pEnd)->pri;
	free((*pEnd)->nex);
	(*pEnd)->nex = NULL;
	map[(*pEnd)->x][(*pEnd)->y] = 0;
	return 1;
}//move

void free_total_snake(link p)
{
	//释放整条蛇的链表占用的内存
	while (p->nex != NULL)
	{
		//跳到下一个节点
		p = p->nex;
		//释放上一个节点
		free(p->pri);
	}
	//释放最后一节
	free(p);
}//free_total_snake