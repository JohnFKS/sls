
//本程序改编自网络学习资源只供学习使用，未经作者许可，不得用于其它任何用途 

#include <stdio.h>
#include <stdlib.h>  
#include <windows.h>
#include <conio.h>
#include<graphics.h>
#include<time.h>
#include<math.h>
#pragma comment(lib,"winmm.lib")//全局变量的定义
#define NUM 10			//烟花弹个数，烟花
#define PI 3.1415925
#define High  20     //设置范围 
#define Width 40

int surprise_x,surprise_y;           //定义白色雷子 
int surprise_x0,surprise_y0;         //定义红色雷子  
int surprise_x1,surprise_y1;         //定义黄色雷子 
int surprise_x2,surprise_y2;         //定义绿色雷子  
int movedirection;        //定义方向初标志位 
int long1=4;            //定义增加的长度 

int ks,sudo,sp1,sp2;            //定义ks为进入游戏的返回值，sudo为速度，sp1和sp2为炸弹数选择变量 
int map[High][Width]={0};    
int color(int num)
//num为每一种颜色所代表的数字，范围是0~15（颜色函数）
{
	//SetConsoleTextAttribute是设置控制台窗口字体颜色和背景色的函数
	//GetStdHandle是获得输入、输出或错误的屏幕缓冲区的句柄
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),num);
	return 0;
}
//光标隐藏函数 
void HideCursor()                                          
{
CONSOLE_CURSOR_INFO cursor_info = {1, 0};
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
// 光标隐藏函数 
void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}
//初始化变量及二维数组元素函数 
void startup(){ 
	                                  //设计边框的元素值为-1 
	int i,j,k; 
	movedirection=4;                     //设置蛇头的初始方向 
	HideCursor();
	for(i=0;i<High;i++){
		map[i][0]=-1;               //每一行的第一个赋值为-1 
		map[i][Width-1]=-1;         //每一行的最后一个赋值为-1 
	}
	for(j=0;j<Width;j++){ 
		map[0][j]=-1;              //第一行全为-1 
		map[High-1][j]=-1;         //最后一行全为-1 
	}
	//设计蛇头的元素组为1
	map[High/2][Width/2]=1;       //设置蛇头位置的标志位  
	for(k=1;k<5;k++){
		map[High/2][Width/2-k]=k+1;       //设置蛇尾的标志位 
	}
	//设计食物的元素值为-2
	srand(time(NULL));                         //设计随机数种子 
    surprise_x=rand()%(High-4)+2;     //生成雷子随机的坐标位置  
    surprise_y=rand()%(Width-4)+2;
	map[surprise_x][surprise_y]=-2;      //设置雷子的标志位为-2
	if(map[surprise_x][surprise_y]>=2)                  //防止雷子出现在蛇身上 
	    {
	       surprise_x=rand()%(High-4)+2;           
	       surprise_y=rand()%(Width-4)+2;
	       map[surprise_x][surprise_y]=-2;
		}
	
	surprise_x0=rand()%(High-4)+2;     
    surprise_y0=rand()%(Width-4)+2;
	map[surprise_x0][surprise_y0]=-3; 
		 if(map[surprise_x0][surprise_y0]>=2)                      //防止雷子出现在蛇身上
	    {
	       surprise_x0=rand()%(High-4)+2;
	       surprise_y0=rand()%(Width-4)+2;
	       map[surprise_x0][surprise_y0]=-2;
		} 	
	
	surprise_x1=rand()%(High-4)+2;                   
    surprise_y1=rand()%(Width-4)+2;
	map[surprise_x1][surprise_y1]=-4;
	if(map[surprise_x1][surprise_y1]>=2)                      //防止雷子出现在蛇身上
	    {
	       surprise_x1=rand()%(High-4)+2;
	       surprise_y1=rand()%(Width-4)+2;
	       map[surprise_x1][surprise_y1]=-2;
		} 	
	
	surprise_x2=rand()%(High-4)+2;     
    surprise_y2=rand()%(Width-4)+2;
	map[surprise_x2][surprise_y2]=-5; 
	if(map[surprise_x2][surprise_y2]>=2)                      //防止雷子出现在蛇身上
	    {
	       surprise_x2=rand()%(High-4)+2;
	       surprise_y2=rand()%(Width-4)+2;
	       map[surprise_x2][surprise_y2]=-2;
		} 	
}
//初始界面 
int show(){
	char ch1,ch2;
	color(12);
	printf("                   |----------------------------------------------------------------------------------\n");    //欢迎界面 
    printf("                   |                                                                                  \n");
    printf("                   |                                                                                  \n");
	printf("                   |                            欢迎来到扫雷蛇小游戏                                  \n");
	printf("                   |游戏规则：1.通过AWSD来进行上下左右控制贪吃蛇,按k来增加速度,按L使速度初始化        \n");
	printf("                   |          2.白色:50%%增加2点生命值  50%%减少2点生命值                               \n"); 
	printf("                   |          3.红色:30%%增加4点生命值  70%%减少1点生命值                               \n");
	printf("                   |          4.黄色:40%%增加3点生命值  60%%减少2点生命值                               \n");
	printf("                   |          5.绿色:70%%增加1点生命值  30%%减少2点生命值                               \n");
	printf("                   |          6.蛇可以向自己的反方向运动，可以穿过身体                                \n"); 
	printf("                   |          7.剩余生命值负数或10则游戏结束                                                   \n");
	printf("                   |          8.按'G'来开始游戏                                                       \n");
    printf("                   |                                                                                  \n");
    printf("                   |----------------------------------------------------------------------------------\n");
    ch1=getch();
    if(ch1=='g')
	{
		system("cls");      //清空函数 
		ks=1;
	}
	color(12);printf("               !! 准备阶段，按任意键继续!!           \n"); 
	ch2=getch();
	if(ch2=='2')
	{ 
	    system("cls");
		
	}
	if(ch2=='3')
	{ 
	    system("cls");  
		
	}
	else  system("cls");            
	return ks;
} 
//贪吃蛇运动 
void movesnake(){
	int i,j,k;
	int oldhead_x,oldhead_y,newhead_x,newhead_y; 
	for(i=1;i<High-1;i++)                                                     //扫描所有二维码数组，把所有>0的元素+1 *
		for(j=1;j<Width-1;j++)
			if (map[i][j]>0)    map[i][j]++;                              //扫描到坐标上的数，意思是使扫雷蛇运动起来 ，其他物体不变 
	//数组内元素值为6时，置0，元素值为2的坐标定义为旧蛇头的位置 
	for(i=1;i<High-1;i++){                                            //i代表的y,j代表的是x 
		for(j=1;j<Width-1;j++){
			if(map[i][j]==6+long1)  map[i][j]=0;                    //重新开始继续扫描  
			if(map[i][j]==2)   {oldhead_x=i;oldhead_y=j;             //把旧的坐标赋值给oldhead ，记录蛇头位置 
			
			}          
			 
		}
	}
	//新蛇头位置与老蛇头的位置关系 
	if(movedirection==4){                                          //这里的x就是y，y就是x 
		newhead_y=oldhead_y+1;                       
		newhead_x=oldhead_x;               //向右 ，将旧蛇头的位置赋值给新蛇头 
	}
	if(movedirection==1){                 //向上 
		newhead_y=oldhead_y;
		newhead_x=oldhead_x-1;
	}
	if(movedirection==2){                //向下 
		newhead_y=oldhead_y;
		newhead_x=oldhead_x+1;
	}
	if(movedirection==3){              //向左 
		newhead_y=oldhead_y-1;
		newhead_x=oldhead_x;
	}
	//吃到食物
	if((oldhead_x==surprise_x)&&(oldhead_y==surprise_y)) 
	{
	   	int m;
		m=rand()%10;
if(m==1||m==2||m==3||m==4||m==5)
{
	srand(time(NULL));
	long1=long1+2;		
}
else
{	
	srand(time(NULL));
	long1=long1-2;	
}
	   	surprise_x=rand()%(High-4)+2;
	    surprise_y=rand()%(Width-4)+2;
	    map[surprise_x][surprise_y]=-2;
	    
		if(map[surprise_x][surprise_y]>=2)                      //防止雷子出现在蛇身上
	    {
	       surprise_x=rand()%(High-4)+2;
	       surprise_y=rand()%(Width-4)+2;
	       map[surprise_x][surprise_y]=-2;
		} 	
	}
	//吃到雷子
	 if((oldhead_x==surprise_x0)&&(oldhead_y==surprise_y0)) 
	{
			int m;
		m=rand()%10;
if(m==1||m==2||m==3)
{
	srand(time(NULL));
	long1=long1+4;
}
else
{
	srand(time(NULL));
	long1=long1-1;
}
	   	surprise_x0=rand()%(High-4)+2;
	    surprise_y0=rand()%(Width-4)+2;
	    map[surprise_x0][surprise_y0]=-3;
		
		 if(map[surprise_x0][surprise_y0]>=2)                      //防止雷子出现在蛇身上
	    {
	       surprise_x0=rand()%(High-4)+2;
	       surprise_y0=rand()%(Width-4)+2;
	       map[surprise_x0][surprise_y0]=-2;
		} 	
	 }
	//吃到炸弹1
	if((oldhead_x==surprise_x1)&&(oldhead_y==surprise_y1)) 
	{
	   int m;
		m=rand()%10;
if(m==1||m==2||m==3||m==4)
{	
	srand(time(NULL));
	    long1=long1+3;		
}
else
{
	srand(time(NULL));
	long1=long1-2;		
}
	   	surprise_x1=rand()%(High-4)+2;
	    surprise_y1=rand()%(Width-4)+2;
	    map[surprise_x1][surprise_y1]=-4; 	
		
	 	
		 if(map[surprise_x1][surprise_y1]>=2)                      //防止雷子出现在蛇身上
	    {
	       surprise_x1=rand()%(High-4)+2;
	       surprise_y1=rand()%(Width-4)+2;
	       map[surprise_x1][surprise_y1]=-2;
		} 	
	}
	//吃到炸弹2
	 if((oldhead_x==surprise_x2)&&(oldhead_y==surprise_y2)) 
	{
	   	int m;
		m=rand()%10;
if(m==1||m==2||m==3||m==3||m==4||m==5||m==6||m==7)
{		
	
	    long1=long1+1;		
}
else
{
	
	long1=long1-2;		
}
	   	surprise_x2=rand()%(High-4)+2;
	    surprise_y2=rand()%(Width-4)+2;
	    map[surprise_x2][surprise_y2]=-5; 
		if(map[surprise_x2][surprise_y2]>=2)                      //防止雷子出现在蛇身上
	    {
	       surprise_x2=rand()%(High-4)+2;
	       surprise_y2=rand()%(Width-4)+2;
	       map[surprise_x2][surprise_y2]=-2;
		} 	
	
	 }
	//判断失败,撞到墙 
   if(map[newhead_x][newhead_y]==-1){                         
   	printf("白给了兄弟\n");
   	exit(0);
	}
	//生命值为0则结束游戏 
	if(long1<0)
	{ 
	 printf("没命了\n");
	 system("pause");
	 exit(0);
	} 
	//速度
	else map[newhead_x][newhead_y]=1;
	     Sleep(300-sudo);
}
 //键盘输入判断
void keyboard()
 {
 	    char ch;
		if(kbhit())
	    {
		ch=getch();                   
		if(ch=='a') movedirection=3;               //向左 
		if(ch=='d') movedirection=4;               //向右 
		if(ch=='w') movedirection=1;               //向上 
		if(ch=='s') movedirection=2;               //向下 
		if(ch=='k') {sudo=sudo+20;}                //速度加快 
		if(ch=='l') sudo=0;                       //速递变为初始值 
		if(ch=='\033') exit(0);                   //按下esc可以退出 
		if(ch==32)  system("pause");             //按下空格键可以暂停 
		}
		if(sudo==240) 
		{
			sudo=0;
		}
}
//地图显示函数 
void mapshow(){
	int i,j;
	for(i=0;i<High;i++){
		for(j=0;j<Width;j++){
			
			if(map[i][j]==-2)       {color(7);printf("@");}                //输出雷子 
		    else if(map[i][j]==0)   {color(5);printf(" ");}                 //输出空格 
		    else if(map[i][j]>1)     printf("#");                 //输出蛇身 
			else if(map[i][j]==1)    printf("*");                //输出蛇头
			else if(map[i][j]==-3)  {color(4);printf("@"); }              //输出雷子 
			else if(map[i][j]==-4)  {color(6);printf("@"); }
			else if(map[i][j]==-5)  {color(2); printf("@"); }
			else if(map[i][j]==-1)  {color(9); printf("※"); }                       //输出城墙 
		}
		printf("\n");
	}
	printf("游戏规则：1.通过awsd来进行上下左右控制贪吃蛇，按k来增加速度,按L使速度初始化       \n");          //游戏规则 
    printf("          2.按空格键可以暂停游戏，按esc键可以退出游戏                             \n");	
	printf("          3.白色：50%%增加2点生命值  50%%减少2点生命值                              \n"); 
	printf("          4.红色：30%%增加4点生命值  70%%减少1点生命值                              \n");
	printf("          5.黄色：40%%增加3点生命值  60%%减少2点生命值                              \n");
	printf("          6.绿色：70%%增加1点生命值  30%%减少2点生命值                              \n");
	printf("          7.剩余生命值为负数则游戏结束                                            \n");
	color(4);printf("        注意：蛇身最短为4，此时其剩余生命值为0                         \n");
	color(9);printf("                                           最快时间内达到剩余生命值为10即可获胜，剩余生命值:%d\n",long1);
}

struct jet
{
	int x, y;			//烟花弹坐标
	int hx, hy;			//烟花弹最高点坐标
	bool shoot;			//烟花弹是否处于发射状态
	DWORD t1, t2, dt;	//发射时间  引爆时间  间隔时间
	IMAGE img[2];		//2张图片 一明一暗 01下标
	byte n : 1;			//C结构体 位段	//n 变量 1个位	0，1 n++ 0，1，0，1
}jet[NUM];				//烟花弹个数
//烟花
struct Fire
{
	int x, y;				//烟花的坐标
	int r;					//烟花的半径
	int max_r;				//烟花的最大半径
	int cen_x, cen_y;		//中心距左上角的距离
	int width, height;		//长宽
	int xy[240][240];		//重要，像素，矩阵
	bool draw;				//画出
	bool show;				//显示
	DWORD t1, t2, dt;		//发射时间  引爆时间  间隔时间
}fire[NUM];
void FireInit(int i)
{
	//初始化烟花弹
	jet[i].t1 = GetTickCount();	//GetTickCount()返回从操作系统启动到当前所经过的毫秒数。使用前包含windows.h。
	jet[i].shoot = false;		//未发射
	jet[i].dt = 10;				//上升时间
	jet[i].n = 0;				//初始化烟花
	fire[i].show = false;		//未引爆
	fire[i].r = 0;
	fire[i].dt = 5;				//上升时间
	fire[i].t1 = GetTickCount();
	fire[i].max_r = rand() % 50 + 100;	//100-149
	fire[i].cen_x = rand() % 30 + 80;	//中心距左上角的距离
	fire[i].cen_y = rand() % 30 + 80;	//
	fire[i].width = 240;				//宽
	fire[i].height = 240;				//长
}
void Load()
{
	//加载烟花弹
	IMAGE jetimg;
	loadimage(&jetimg, L"./fire/shoot.jpg", 200, 50);
	SetWorkingImage(&jetimg);
	for (int i = 0; i < NUM; i++)
	{
		int n = rand() % 5;			//01234
		getimage(&jet[i].img[0], n * 20, 0, 20, 50);
		getimage(&jet[i].img[1], (n + 5) * 20, 0, 20, 50);
	}
	SetWorkingImage(NULL);
	//加载烟花
	IMAGE fireimage, Fireimage;
	loadimage(&Fireimage, L"./fire/flower.jpg", 3120, 240);
	for (int i = 0; i < NUM; i++)
	{
		SetWorkingImage(&Fireimage);
		getimage(&fireimage, i * 240, 0, 240, 240);
		SetWorkingImage(&fireimage);
		for (int a = 0; a < 240; a++)
		{
			for (int b = 0; b < 240; b++)
			{
				fire[i].xy[a][b] = getpixel(a, b);
			}
		}
	}
	SetWorkingImage(NULL);
}
void ChoiceJet(DWORD& t1)
{
	DWORD t2 = GetTickCount();
	if (t2 - t1 > 100)		//烟花弹出现的时间间隔100ms
	{
		//烟花弹个数
		int i = rand() % 10;
		//不处于发射状态
		if (jet[i].shoot == false && fire[i].show == false)
		{
			//烟花弹
			jet[i].x = rand() % 1000;
			jet[i].y = rand() % 100 + 450;	//450-549
			jet[i].hx = jet[i].x;
			jet[i].hy = rand() % 300;		//0-299
			jet[i].shoot = true;			//发射状态

			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
		}
		t1 = t2;
	}
}
void Shoot()
{
	for (int i = 0; i < NUM; i++)
	{
		jet[i].t2 = GetTickCount();
		if (jet[i].t2 - jet[i].t1 >= jet[i].dt && jet[i].shoot == true)
		{
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
			if (jet[i].y >= jet[i].hy)
			{
				jet[i].n++;			//闪烁
				jet[i].y -= 5;
			}
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);

			if (jet[i].y <= jet[i].hy)
			{
				putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
				jet[i].shoot = false;
				//达到最大高度，接下来交给烟花
				//重新发射
				fire[i].x = jet[i].hx;
				fire[i].y = jet[i].hy;
				fire[i].show = true;
			}
		}
		jet[i].t1 = jet[i].t2;
	}
}
//显示烟花
void ShowFire(DWORD* pMem)
{
	int drt[16] = { 5, 5, 5, 5, 5, 10, 25, 25, 25, 25, 55, 55, 55, 55, 55, 65 };

	for (int i = 0; i < NUM; i++)
	{
		fire[i].t2 = GetTickCount();
		if (fire[i].t2 - fire[i].t1 >= fire[i].dt && fire[i].show == true)
		{
			if (fire[i].r < fire[i].max_r)
			{
				fire[i].r++;
				fire[i].dt = drt[fire[i].r / 10];
				fire[i].draw = true;
			}
			if (fire[i].r >= fire[i].max_r - 1)
			{
				fire[i].draw = false;
				FireInit(i);
			}
			fire[i].t1 = fire[i].t2;
			// 如果该号炮花可爆炸，根据当前爆炸半径画烟花，颜色值接近黑色的不输出。
			if (fire[i].draw)
			{
				for (double a = 0; a <= 6.28; a += 0.01)
				{
					int x1 = (int)(fire[i].cen_x + fire[i].r * cos(a));
					int y1 = (int)(fire[i].cen_y - fire[i].r * sin(a));
					if (x1 > 0 && x1 < fire[i].width && y1>0 && y1 < fire[i].height)
					{
						int b = fire[i].xy[x1][y1] & 0xff;
						int g = (fire[i].xy[x1][y1] >> 8) & 0xff;
						int r = (fire[i].xy[x1][y1] >> 16);
						// 烟花像素点在窗口上的坐标
						int xx = (int)(fire[i].x + fire[i].r * cos(a));
						int yy = (int)(fire[i].y - fire[i].r * sin(a));
						//较暗的像素点不输出、防止越界
						if (r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx < 1000 && yy >0 && yy < 600)
						{
							pMem[yy * 1000 + xx] = BGR(fire[i].xy[x1][y1]);
						}
						fire[i].draw = false;
					}
				}
			}
		}
	}
}
void welcome()
{
	setcolor(YELLOW);
	for (int i = 0; i < 50; i++)
	{
		int x = 600 + int(180 * sin(PI * 2 * i / 60));
		int y = 200 + int(180 * cos(PI * 2 * i / 60));
		cleardevice();
		settextstyle(i, 0, L"楷体");
		outtextxy(x - 80, y, L"牛逼兄弟，通关了");
		outtextxy(x - 10, y + 100, L"请欣赏烟花表演");
		Sleep(100);
	}
	Sleep(130);
	cleardevice();
	settextstyle(25, 0, L"楷体");
	outtextxy(10, 30, L"此版本为初稿，程序仍需完善,后期将改进成双人对抗游戏，最短时间内通关者获胜");
	Sleep(4000);
	cleardevice();
}
int fire1()
{
	//初始界面（1000，600）
	initgraph(1000, 600);
	//初始化种子
	srand((unsigned int)time(NULL));
	//音乐 晴天
	mciSendString(L"open ./fire/bk1.mp3 alias music", 0, 0, 0);	//send(发送)	string（字符串）
	mciSendString(L"play music", 0, 0, 0);
	//其它音乐类型 wav PlaySound()
	//0,0,0 音乐播放器时：播放设备，快进设备 快退 暂停
	welcome();
	DWORD t1 = GetTickCount();
	DWORD* pMem = GetImageBuffer();
	for (int i = 0; i < NUM; i++)
	{
		FireInit(i);
	}
	Load();
	BeginBatchDraw();
	while (1)
	{
		// 随机选择像素点擦除
		for (int clr = 0; clr < 200; clr++)
		{
			int px1 = rand() % 1000;
			int py1 = rand() % 600;

			// 防止越界
			if (py1 < 599)
			{
				//对显存赋值擦除像素点
				pMem[py1 * 1000 + px1] = pMem[py1 * 1000 + px1 + 1] = BLACK;
			}
		}
		ChoiceJet(t1);
		Shoot();
		ShowFire(pMem);
		FlushBatchDraw();
	}
	system("pause");
	return 0;
}





int main()
{ 
	show(); 
	startup();
	while(ks){
	gotoxy(0,0);
	mapshow(); 
	keyboard();
	movesnake();	
	if(long1>=10)
		fire1();
	}
	return 0;	
}