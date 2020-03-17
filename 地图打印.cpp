#include<iostream>
using namespace std;

char egg;

short map_height = 4;//高
short map_width = 7;//宽

//地图,map[宽][高]
//1为方块，0为空格,2为人
short int map[4][7] = 
{
{1,1,1,1,1,1,1},
{1,0,0,1,0,0,1},
{1,0,0,0,0,0,1},
{1,1,1,1,1,1,1},
};
//地图宽度、高度

//地图打印函数
//检测到错误直接退出
int printf_map()
{
        int loop1 = 0;//高
        int loop2 = 0;//宽
        for(loop1 = 0;loop1 < map_height;loop1 ++)    //遍历行(高)
        {
            for(loop2 = 0;loop2 < map_width;loop2 ++)    //遍历列(宽)
            {
                switch (map[loop1][loop2])//判断并打印
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
            if((map_width - 1) == loop2)
            {
                cout << "\n";
            }
            }
        }
        return 1;
};


//玩家类
class player
{
    public:
        //构造函数
        player(int x1,int y1,int id = 2)//也没写检测🌚
        {
            x = x1;//横坐标
            y = y1;//纵坐标
            map[y][x] = id;//类型
        }
        int x;
        int y;
        char name[10];    //名字(刚好三个汉字)
        
        int ex(short int *a,short int* b)    //交换函数(本来应该是私有的)
        {
            int temp = *a;
            *a = *b;
            *b = temp;
            return 1;
        }
        //没检测，会溢出😂
        int mov(int a)    //标准移动
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
                    ex(&map[y][x],&map[y-1][x]);
                    y--;
                    break;
                case 2://右→
                    ex(&map[y][x],&map[y][x+1]);
                    x++;
                    break;
                case 3://下↓
                    ex(&map[y][x],&map[y+1][x]);
                    y++;
                    break;
                case 4://左←
                    ex(&map[y][x],&map[y][x-1]);
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
                return mov(4);
            }
            if(*"d" == a)    //右
            {
                return mov(2);
                
            }
            if(*"w" == a)    //上
            {
                return mov(1);
            }
            if(*"s" == a)    //下
            {
                return mov(3);
            }
            return 0;    //错误
        }
};

void hello()
{
    cout << "欢迎来到这里。\n帮助:\nw↑d→s↓a←\n提示:内存会溢出😂\n按c退出\n";
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
    printf_map();
    for(;;)
    {
        cin >> c;
        if(*"c" == c || *"C" == c)
        {
            return 2;
        }
        me.mov(c);
        printf_map();
    }
    return 0;
}
    