/*
更新:添加player越界检测
更新:将检测移动到int mov(char c)


*/



/*错误列表:
    main:
        0-未知
        1-无错误
        2-正常退出
        3-player越界
    mov(int):
        0-错误
        1-无错误
    mov(char):
        0-错误
        1-无错误
        3-越界




----------------------------------------*/


#include<iostream>
using namespace std;

 char egg;

 short map0_height = 8;//高
 short map0_width = 7;//宽

//地图,map[宽][高]
//1为方块，0为空格,2为人
 short int map0[8][7] = 
{
{1,1,1,1,1,1,1},    //1
{1,0,0,1,0,0,1},    //2
{1,0,0,0,0,0,1},    //3
{1,1,1,0,1,1,1},    //4
{1,1,0,0,0,1,1},    //5
{1,0,0,0,0,0,1},    //6
{0,0,0,1,0,0,0},    //7
{0,0,1,1,1,0,0}    //8
};
//地图宽度、高度

//地图打印函数
//检测到错误直接退出
int printf_map0()
{
        int loop1 = 0;//高
        int loop2 = 0;//宽
        for(loop1 = 0;loop1 < map0_height;loop1 ++)    //遍历行(高)
        {
            cout <<"\t";
            for(loop2 = 0;loop2 < map0_width;loop2 ++)    //遍历列(宽)
            {
                switch (map0[loop1][loop2])//判断并打印
            {
            case 0:
                cout << " ";
                break;
            case 1:
                cout << "■";
                break;
            case 2:
                cout <<"♦";
                break;
            //错误接收
            default:
                cout << "✘";
                cerr << "\n地图错误:含有未知类型的值\n";
                return 0;
            };
            //一列结束换行
            if((map0_width - 1) == loop2)
            {
                cout << "\n";
            }
            }
        }
        return 1;
}


//玩家类
class player
{
    public:
        //构造函数
        player(int x1,int y1,short int id = 2)//也没写检测🌚
        {
            x = x1;//横坐标
            y = y1;//纵坐标
            map0[y][x] = id;//类型
        }
        int x;
        int y;
        char name[10];    //名字(刚好三个汉字)
        
        int ex(short int *a,short int* b)    //交换函数(本来应该是私有的)
        {
            short int temp = *a;
            *a = *b;
            *b = temp;
            return 1;
        }
        //没检测，会溢出😂
        int mov(int a)    //底层移动
        {
            //入参检查
            if((a < 0||a >4))
            {
                return 0;
            }
            //移动方式
            //1:上↑,2右→;3:下↓;4:左←;
            switch(a)
            {
                case 1://上↑
                    ex(&map0[y][x],&map0[y-1][x]);
                    y--;
                    break;
                
                case 2://右→
                    ex(&map0[y][x],&map0[y][x+1]);
                    x++;
                    break;
                
                case 3://下↓
                    ex(&map0[y][x],&map0[y+1][x]);
                    y++;
                    break;
                
                case 4://左←
                    ex(&map0[y][x],&map0[y][x-1]);
                    x--;
                    break;
                
                default://未知错误接收
                    cerr << "error:未知错误";
                    return 0;
            }
            return 1;
        }
        int mov(char a)    //字符移动wdsa
        {
            if(*"a" == a)    //左
            {
                if(x - 1 < 0)    //检测
                {
                    return 3;
                }
                return mov(4);
            }
            if(*"d" == a)    //右
            {
                if(x + 1 > map0_width - 1)    //检测
                {
                    return 3;
                }
                return mov(2);
            }
            
            if(*"w" == a)    //上
            {
                if(y - 1 < 0)    //检测
                {
                    return 3;
                }
                return mov(1);
            }
            
            if(*"s" == a)    //下
            {
                if(y + 1 > map0_height - 1)    //检测
                {
                    return 3;
                }
                return mov(3);
            }
            
            return 0;    //错误
        }
};

void hello()
{
    cout << "欢迎来到这里。\n帮助:\nw↑d→s↓a←\n按c退出\n";
}

int main()
{
    /*char a[16]={232,128,129,229,184,136,230,152,175,230,178,153,233,155,149};
    cout << "Hello,World!" << a << "\n";
    cin  >> a[9] >> a[10] >> a[11] >> a[12] >> a[13] >> a[14];
    cout << a << "\n";*/
    hello();
    char c;
    player me = player(3,3);
    printf_map0();
    for(;;)
    {
        cin >> c;
        if(*"c" == c || *"C" == c)
        {
            return 2;
        }
        if(me.mov(c) == 3)
        {
            goto error3;
        };
        printf_map0();
    }
    error3:cout << "越界\n";
    return 3;
}
    