/*
 * 2048是一款简单而又富有挑战性的数字益智游戏。其规则简单，但策略性强，玩家需要通过合并相同数字的方块，
 * 最终组合成数字2048以达到胜利。
 * 
 * 基础功能:
 * 1. 随机数产生函数: 在初始化和每次操作后，在空区域产生2或4的随机数。
 * 2. 上下左右移动操作: 移动数字朝指定方向并合并相同数字。(合并时不仅限于相邻相同数字的合并，而是向特定方向合并直到边界)
 * 3. 判断游戏状态: 达到2048时判断游戏胜利，无法移动时判断游戏失败。(在每次移动后立即判断游戏是否结束)
 * 
 * 进阶功能:
 * 1. 返回上一步操作: 实现撤销上一步操作的功能。
 * 2. 保存游戏进度: 将当前游戏状态保存到文件中，以便后续加载。
 * 3. 加载历史游戏: 从文件中读取已保存的游戏状态，恢复游戏进度。
 */
#include <stdio.h>  // 包含标准输入输出库
#include <stdlib.h>  // 包含标准库
#include <time.h>  // 包含时间库，用于生成随机数

#define SIZE 4  // 定义游戏板的大小为4x4

int board[SIZE][SIZE];  // 定义游戏板
int previous_board[SIZE][SIZE];  // 定义上一步的游戏板，用于撤销操作
int score = 0;  // 当前分数
int previous_score = 0;  // 上一步的分数，用于撤销操作

// 添加随机数2或4到空位置
void add_random_tile() {
    int empty_tiles[SIZE * SIZE][2];  // 定义一个数组存储所有空位置的坐标
    int empty_count = 0;  // 记录空位置的数量
    for (int i = 0; i < SIZE; i++) {  // 遍历游戏板的每一行
        for (int j = 0; j < SIZE; j++) {  // 遍历游戏板的每一列
            if (board[i][j] == 0) {  // 如果当前位置为空
                empty_tiles[empty_count][0] = i;  // 记录空位置的行坐标
                empty_tiles[empty_count][1] = j;  // 记录空位置的列坐标
                empty_count++;  // 增加空位置的数量
            }
        }
    }
    if (empty_count > 0) {  // 如果有空位置
        int random_index = rand() % empty_count;  // 随机选择一个空位置的索引
        int random_value = (rand() % 2 + 1) * 2;  // 随机生成2或4
        board[empty_tiles[random_index][0]][empty_tiles[random_index][1]] = random_value;  // 在随机选择的空位置添加随机数
    }
}

// 初始化游戏板
void init_board() {
    srand(time(NULL));  // 使用当前时间作为随机数种子
    for (int i = 0; i < SIZE; i++) {  // 遍历游戏板的每一行
        for (int j = 0; j < SIZE; j++) {  // 遍历游戏板的每一列
            board[i][j] = 0;  // 将游戏板的每个位置初始化为0
        }
    }
    add_random_tile();  // 添加一个随机数到游戏板
    add_random_tile();  // 再添加一个随机数到游戏板
}

// 保存当前状态
void save_state() {
    for (int i = 0; i < SIZE; i++) {  // 遍历游戏板的每一行
        for (int j = 0; j < SIZE; j++) {  // 遍历游戏板的每一列
            previous_board[i][j] = board[i][j];  // 保存当前游戏板的状态到previous_board
        }
    }
    previous_score = score;  // 保存当前分数到previous_score
}

// 撤销上一步操作
void undo() {
    for (int i = 0; i < SIZE; i++) {  // 遍历游戏板的每一行
        for (int j = 0; j < SIZE; j++) {  // 遍历游戏板的每一列
            board[i][j] = previous_board[i][j];  // 恢复上一步的游戏板状态
        }
    }
    score = previous_score;  // 恢复上一步的分数
}

// 保存游戏进度到文件
void save_game(const char *filename) {
    FILE *file = fopen(filename, "wb");  // 以二进制写模式打开文件
    if (file != NULL) {  // 如果文件成功打开
        fwrite(board, sizeof(int), SIZE * SIZE, file);  // 将游戏板写入文件
        fwrite(&score, sizeof(int), 1, file);  // 将分数写入文件
        fclose(file);  // 关闭文件
    }
}

// 从文件加载游戏进度
void load_game(const char *filename) {
    FILE *file = fopen(filename, "rb");// 以二进制读模式打开文件
    if (file != NULL) {                //如果文件成功打开
        fread(board, sizeof(int), SIZE * SIZE, file);//从文件读取游戏板
        fread(&score, sizeof(int), 1, file);         //从文件读取分数
        fclose(file);                                //关闭文件
    }
}

// 判断游戏是否结束
int is_game_over() {
    for (int i = 0; i < SIZE; i++) {  // 遍历每一行
        for (int j = 0; j < SIZE; j++) {  // 遍历每一列
            if (board[i][j] == 2048) {  // 如果有一个方块的值为2048
                return 1;  // 游戏胜利
            }
            if (board[i][j] == 0) {  // 如果有一个方块为空
                return 0;  // 游戏未结束
            }
            if (i > 0 && board[i][j] == board[i - 1][j]) {  // 如果当前方块与上方方块相同
                return 0;  // 游戏未结束
            }
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) {  // 如果当前方块与下方方块相同
                return 0;  // 游戏未结束
            }
            if (j > 0 && board[i][j] == board[i][j - 1]) {  // 如果当前方块与左方方块相同
                return 0;  // 游戏未结束
            }
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) {  // 如果当前方块与右方方块相同
                return 0;  // 游戏未结束
            }
        }
    }
    return -1;  // 游戏失败
}

// 向左移动并合并
void move_left() {
    save_state();  // 保存当前状态以便撤销
    for (int i = 0; i < SIZE; i++) {  // 遍历每一行
        int target = 0;  // 目标位置初始化为第一列
        for (int j = 1; j < SIZE; j++) {  // 从第二列开始遍历每一列
            if (board[i][j] != 0) {  // 如果当前元素不为空
                int k = j;  // 记录当前元素的位置
                while (k > target && board[i][k - 1] == 0) {  // 如果左方位置为空
                    board[i][k - 1] = board[i][k];  // 将当前元素移动到左方的空位置
                    board[i][k] = 0;  // 将当前元素位置清空
                    k--;  // 更新当前元素的位置
                }
                if (k > target && board[i][k - 1] == board[i][k]) {  // 如果左方的元素与当前元素相同
                    board[i][k - 1] *= 2;  // 合并两个相同的元素
                    score += board[i][k - 1];  // 更新分数
                    board[i][k] = 0;  // 将当前元素位置清空
                    target = k;  // 更新目标位置，防止重复合并
                }
            }
        }
    }
    add_random_tile();  // 在空位置添加一个随机数
}

// 向右移动并合并
void move_right() {
    save_state();  // 保存当前状态以便撤销
    for (int i = 0; i < SIZE; i++) {  // 遍历每一行
        int target = SIZE - 1;  // 目标位置初始化为最后一列
        for (int j = SIZE - 2; j >= 0; j--) {  // 从倒数第二列开始遍历每一列
            if (board[i][j] != 0) {  // 如果当前元素不为空
                int k = j;  // 记录当前元素的位置
                while (k < target && board[i][k + 1] == 0) {  // 如果右方位置为空
                    board[i][k + 1] = board[i][k];  // 将当前元素移动到右方的空位置
                    board[i][k] = 0;  // 将当前元素位置清空
                    k++;  // 更新当前元素的位置
                }
                if (k < target && board[i][k + 1] == board[i][k]) {  // 如果右方的元素与当前元素相同
                    board[i][k + 1] *= 2;  // 合并两个相同的元素
                    score += board[i][k + 1];  // 更新分数
                    board[i][k] = 0;  // 将当前元素位置清空
                    target = k;  // 更新目标位置，防止重复合并
                }
            }
        }
    }
    add_random_tile();  // 在空位置添加一个随机数
}

// 向上移动并合并
void move_up() {
    save_state();  // 保存当前状态以便撤销
    for (int j = 0; j < SIZE; j++) {  // 遍历每一列
        int target = 0;  // 目标位置初始化为第一行
        for (int i = 1; i < SIZE; i++) {  // 从第二行开始遍历每一行
            if (board[i][j] != 0) {  // 如果当前元素不为空
                int k = i;  // 记录当前元素的位置
                while (k > target && board[k - 1][j] == 0) {  // 如果上方位置为空
                    board[k - 1][j] = board[k][j];  // 将当前元素移动到上方的空位置
                    board[k][j] = 0;  // 将当前元素位置清空
                    k--;  // 更新当前元素的位置
                }
                if (k > target && board[k - 1][j] == board[k][j]) {  // 如果上方的元素与当前元素相同
                    board[k - 1][j] *= 2;  // 合并两个相同的元素
                    score += board[k - 1][j];  // 更新分数
                    board[k][j] = 0;  // 将当前元素位置清空
                    target = k;  // 更新目标位置，防止重复合并
                }
            }
        }
    }
    add_random_tile();  // 在空位置添加一个随机数
}

// 向下移动并合并
void move_down() {
    save_state();  // 保存当前状态以便撤销
    for (int j = 0; j < SIZE; j++) {  // 遍历每一列
        int target = SIZE - 1;  // 目标位置初始化为最后一行
        for (int i = SIZE - 2; i >= 0; i--) {  // 从倒数第二行开始遍历每一行
            if (board[i][j] != 0) {  // 如果当前元素不为空
                int k = i;  // 记录当前元素的位置
                while (k < target && board[k + 1][j] == 0) {  // 如果下方位置为空
                    board[k + 1][j] = board[k][j];  // 将当前元素移动到下方的空位置
                    board[k][j] = 0;  // 将当前元素位置清空
                    k++;  // 更新当前元素的位置
                }
                if (k < target && board[k + 1][j] == board[k][j]) {  // 如果下方的元素与当前元素相同
                    board[k + 1][j] *= 2;  // 合并两个相同的元素
                    score += board[k + 1][j];  // 更新分数
                    board[k][j] = 0;  // 将当前元素位置清空
                    target = k;  // 更新目标位置，防止重复合并
                }
            }
        }
    }
    add_random_tile();  // 在空位置添加一个随机数
}

// 打印游戏板
void print_board() {
    printf("Score: %d\n", score);  // 打印当前分数
    for (int i = 0; i < SIZE; i++) {  // 遍历每一行
        for (int j = 0; j < SIZE; j++) {  // 遍历每一列
            printf("%4d", board[i][j]);  // 打印当前方块的值，宽度为4
        }
        printf("\n");  // 换行
    }
}

int main() {
    char choice;  // 定义一个字符变量用于存储用户输入的命令
    init_board();  // 初始化游戏板

    printf("\n\n");
    printf("\t\t________________________________________________\n");
    printf("\t\t||===================操作说明==================||\n");
    printf("\t\t||================1.w为向上移动================||\n");
    printf("\t\t||================2.a为向左移动================||\n");
    printf("\t\t||================3.s为向下移动================||\n");
    printf("\t\t||================4.d为向右移动================||\n");
    printf("\t\t||================5.u为撤销上一步操作===========||\n");
    printf("\t\t||================6.b为退出游戏================||\n");
    printf("\t\t||================7.p为存档====================||\n");
    printf("\t\t||================8.l加载游戏进度===============||\n");
    printf("\t\t________________________________________________\n");
    
    while (1) {  // 无限循环，直到游戏结束
        print_board();  // 打印当前游戏板和分数
        if (is_game_over() == 1) {  // 检查游戏是否胜利
            printf("太dio辣!膜拜膜拜佬，游戏成功！\n");  // 如果胜利，打印胜利信息
            break;  // 退出循环
        } else if (is_game_over() == -1) {  // 检查游戏是否失败
            printf("很可惜，游戏失败，继续努力吧!\n");  // 如果失败，打印失败信息
            break;  // 退出循环
        }
        
        printf("请输入你的行动:\n");//其4实这一步提示不知道有什么必要哈（真正的游戏都是直接操作），放在这里是为了显得scanf没那么孤单……
        scanf(" %c", &choice);  // 读取用户输入的指令
        switch (choice) {  // 根据用户输入执行相应操作
            case 'w':  // 如果输入'w'
                move_up();  // 向上移动
                break;  
            case 'a':  // 如果输入'a'
                move_left();  // 向左移动
                break; 
            case 's':  // 如果输入's'
                move_down();  // 向下移动
                break;  
            case 'd':  // 如果输入'd'
                move_right();  // 向右移动
                break;  
            case 'u':  // 如果输入'u'
                undo();  // 撤销上一步操作
                break;  
            case 'b':  // 如果输入'b'
                return 0;  // 退出程序
            case 'p':  // 如果输入'p'
                save_game("savefile.dat");  // 保存游戏进度到文件
                break; 
            case 'l':  // 如果输入'l'
                load_game("savefile.dat");  // 从文件加载游戏进度
                break; 
            default:  // 如果输入无效
                printf("请输入正确操作符号，不要点错咯.\n");  // 提示用户输入无效
        }
    }
    return 0;  // 返回0，表示程序正常结束
}
