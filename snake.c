#include "game.h"

void init_snake(snake node, link* pHead, link* pEnd, short map[20][20])
{
	//��ʼ���ߣ�����һ������Ϊ3���ߣ�
	link s = NULL;
	//��ͷ
	s = (link)malloc(sizeof(snakeNode));
	if (s == NULL) exit(1);
	s->x = node.x; s->y = node.y;
	map[node.x][node.y] = 1;
	s->pri = NULL;
	*pHead = s;
	//�����м䣩
	s = (link)malloc(sizeof(snakeNode));
	if (s == NULL) exit(1);
	s->pri = *pHead;
	(*pHead)->nex = s;
	prior_coor(&node);
	s->x = node.x; s->y = node.y;
	map[node.x][node.y] = 1;
	//��β
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
	//Ѱ����һ�����꣨������ͷ������ͷ���
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
	//Ѱ����һ�����꣨������ͷ������ͷ���
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
	//�ƶ�
	snake snake_end;
	snake origin = *pS;
	next_coor(pS);
	if (map[pS->x][pS->y] == 1)
	{
		print_node(*pS, 0x0c, "��");
		return 0;
	}
	if (pS->x < 0 || pS->y < 0 || pS->x >= size || pS->y >= size)
	{
		print_node(*pS, 0xcc, "  ");
		return 0;
	}
	//�����µ���ͷ
	link s = (link)malloc(sizeof(snakeNode));
	if (s == NULL) exit(1);
	s->x = pS->x; s->y = pS->y;
	(*pHead)->pri = s;
	s->nex = *pHead;
	*pHead = s;
	//��ӡ��ͷ���һ������
	print_node(origin, SNK_COLOR, BODY);
	map[pS->x][pS->y] = 1;
	//ɾ��β��
	if (s->x == fd->x && s->y == fd->y)
	{
		//����ʳ��
		//ֻ��ͷ��ɾβ
		*score += fd->score;
		print_score(*score);
		print_node(*pS, HEAD_EAT, BODY);
		fd->exist = 0;
		return 1;
	}
	snake_end.x = (*pEnd)->x;
	snake_end.y = (*pEnd)->y;
	//�����β
	print_node(snake_end, 0x0f, "��");
	//��ӡ��ͷ
	print_node(*pS, HEAD_COLOR, BODY);
	*pEnd = (*pEnd)->pri;
	free((*pEnd)->nex);
	(*pEnd)->nex = NULL;
	map[(*pEnd)->x][(*pEnd)->y] = 0;
	return 1;
}//move

void free_total_snake(link p)
{
	//�ͷ������ߵ�����ռ�õ��ڴ�
	while (p->nex != NULL)
	{
		//������һ���ڵ�
		p = p->nex;
		//�ͷ���һ���ڵ�
		free(p->pri);
	}
	//�ͷ����һ��
	free(p);
}//free_total_snake