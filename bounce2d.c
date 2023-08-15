#include <curses.h>
#include <signal.h>
#include "bounce.h"
#include <sys/time.h>

/*

*/

void set_up();
void wrap_up();
void test();

int main()
{
    int c;

    set_up();

    while( (c = getchar()) != 'Q') {
        if(c == 'f' )    theball.x_ttm--;    //加快移速
        else if(c == 's')    theball.x_ttm++;    //减慢移速
        else if(c == 'F')    theball.y_ttm--;
        else if(c == 'S')    theball.y_ttm++;  
    }

    wrap_up();
}


void set_up()
{
    void ball_move(int);

    //初始化
    theball.y_pos = Y_INIT;
    theball.x_pos = X_INIT;
    theball.y_ttg = theball.y_ttm = Y_TTM;
    theball.x_ttg = theball.x_ttm = X_TTM;
    theball.y_dir = 1;
    theball.x_dir = 1;
    theball.symbol = DFL_SYMODE;

    initscr();
    noecho();
    crmode();

    signal(SIGINT,SIG_IGN);
    mvaddch(theball.y_pos,theball.x_pos,theball.symbol);
    refresh();

    signal(SIGALRM,ball_move);
    set_ticker(1000 / TICKS_PER_SEC);
}

void wrap_up()
{
    set_ticker(0);
    endwin();
}

//移动球
void ball_move(int signum)
{
    int y_cur,x_cur,moved;

    signal(SIGALRM,SIG_IGN);        //把时钟信号屏蔽掉，设置完再开启
    y_cur = theball.y_pos;
    x_cur = theball.x_pos;
    moved = 0;

    if(theball.y_ttm > 0 && theball.y_ttg-- == 1){
        theball.y_pos += theball.y_dir;     //移动
        theball.y_ttg = theball.y_ttm;      //重置
        moved = 1;
    }

    if(theball.x_ttm > 0 && theball.x_ttg-- == 1){
        theball.x_pos += theball.x_dir;     //移动
        theball.x_ttg = theball.x_ttm;      //重置
        moved = 1;
    }

    if(moved){
        mvaddch(y_cur,x_cur,BLANK);
        mvaddch(y_cur,x_cur,BLANK);
        mvaddch(theball.y_pos,theball.x_pos,theball.symbol);
        bounce_or_lose(&theball);
        move(LINES - 1, COLS - 1);
        refresh();
    }
    signal(SIGALRM,ball_move);
}

//碰到边界时的处理
int bounce_or_lose(struct ppball *bp)
{
    int return_val = 0;

    if(bp->y_pos == TOP_ROW){
        bp->y_dir = 1;
        return_val = 1;
    } else if(bp->y_pos == BOT_ROW){
        bp->y_dir = -1;
        return_val = 1;
    }

    if(bp->x_pos == LEFT_EDGE){
        bp->x_dir = 1;
        return_val = 1;
    }else if (bp->x_pos == RIGHT_EDGE)
    {
        bp->x_dir = -1;
        return_val = 1;
    }
    
    return return_val;
};


//设置定时器,输入的单位是毫秒
int set_ticker(int n_msecs){
    struct itimerval new_timeset;

    long n_sec,n_usecs;     //秒与微妙

    n_sec = n_msecs / 1000; 
    n_usecs = (n_msecs % 1000) * 1000;

    //设置定时器的结构体
    //重复间隔设置
    new_timeset.it_interval.tv_sec = n_sec;
    new_timeset.it_interval.tv_usec = n_usecs;

    //初始时间设置
    new_timeset.it_value.tv_sec = n_sec;
    new_timeset.it_value.tv_usec = n_usecs;

    //加载设置
    return setitimer(ITIMER_REAL,&new_timeset,NULL);
}

void test()
{
    printf("测试用的\n");
}


