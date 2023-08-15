#define BLANK   ' '
#define DFL_SYMODE  'O'

//边界定义
#define TOP_ROW 5
#define BOT_ROW 20
#define LEFT_EDGE   10
#define RIGHT_EDGE  70
#define X_INIT      10      //起始行
#define Y_INIT      10      //起始列
#define TICKS_PER_SEC   50      //速度

#define X_TTM   4
#define Y_TTM   3

//定义乒乓
struct ppball
{
    int y_pos , x_pos,
    y_ttm,x_ttm,        //两个方向移动的间隔
    y_ttg,x_ttg,        //两个方向的当前值
    y_dir,x_dir;

    char symbol;
} theball;

int bounce_or_lose(struct ppball *bp);
int set_ticker(int n_msecs);
