/*
 *工兵信息管理系统（学生信息管理系统）
 *
 *此学生信息管理系统是一个用C语言编写的程序，用于有效管理窝工或其他教育机构中学生数据。
 *该系统主要有以下功能：
 *1.查询所有工兵鼠信息：系统能够显示所有鼠鼠的基本信息，如学号、姓名、年龄、班级等。
 *2.添加工兵信息：操作者可以水灵灵地添加新的工兵信息。
 *3.删除工兵信息：操作者可以删除工兵信息（剔除鼠籍！）。
 *4.修改工兵信息：操作者可以修改已有的工兵信息。
 *5.保存鼠据到文件：操作者可以将当前鼠鼠的信息保存到文件中，方便后续加载。
 *6.加载鼠据：从文件中加载数据。
 *7.条件查询工兵信息：操作者可以根据特定的条件（如姓名、年龄、成绩等）查询学生信息，或者修改已有的学生数据。
 *8.条件排序工兵信息：系统能够根据指定的条件（如成绩、年龄等）对学生信息进行排序。
 *
 *该系统可以有效地管理和优化窝工的教育资源，提高教学质量和管理水平（^^）
 */
#include <stdio.h>   // 标准输入输出库
#include <stdlib.h>  // 标准库
#include <string.h>  // 字符串处理库

#define MAX_STUDENT 1000  // 定义最大工兵鼠数量
#define NAME_LENGTH 50    // 定义最长名字长度

// 定义学生结构体
typedef struct {
    int id;
    char name[NAME_LENGTH];
    int age;
    char class_name[NAME_LENGTH]; 
    float score;
} Student;

Student students[MAX_STUDENT];  // 学生数组
int current_student = 0;        // 工兵鼠数量
int i, j;                       // 循环变量

// 声明函数
void menu();                  // 声明函数显示菜单
void help();                  //声明使用帮助函数
void load_data();             // 声明加载数据函数
void save_data();             // 声明保存数据函数
void display_students();      // 声明显示所有工兵信息函数
void add_student();           // 声明添加工兵信息函数
void delete_student();        // 声明删除工兵信息函数
void modify_student();        // 声明修改工兵信息函数
void search_student();        // 声明查询工兵信息函数
void sort_students();         // 声明排序工兵信息函数
void clear();                 // 声明函数用于清屏

// 主函数
int main() {
    load_data();  // 加载数据
    menu();       // 显示菜单页面
    int n;        // 功能选择变量
    printf("请选择功能(1-9):\n");  // 显示提示信息
    scanf("%d", &n);  // 输入选择
    while (n) {
        if (n >= 1 && n <= 9) {  // 根据选择调用函数
            switch (n) {
                case 1:
                    help();      //召唤使用帮助
                    break;
                case 2:
                    display_students();  //显示工兵鼠信息
                    break;
                case 3:
                    add_student();       //添加新的工兵鼠
                    break;
                case 4:
                    delete_student();    //删除某位鼠，剔除鼠籍
                    break;
                case 5:
                    modify_student()；   //修改工兵的信息
                    break；
                case 6:
                    search_student();    //查询某位工兵的信息
                    break;
                case 7:
                    sort_student();      //将工兵鼠的某个信息进行相关排序
                    break;
                case 8:
                    save_data();         //保存工兵数据
                    break;
                case 9:
                    clear();             //进行清屏处理
                    break;
                // 其他case语句
                default:
                    printf("无效选择，请重新输入。\n");
                    break;
            }
        } else {
            printf("无效选择，请重新输入。\n");
        }
        printf("请选择功能(1-9):\n");  // 显示提示信息
        scanf("%d", &n);  // 输入选择
    }
    return 0;
}
//显示菜单哈
void menu() {
    printf("\n\n");
    printf("\t\t_____________________________________________________________\n");
    printf("\t\t||              *****************************                ||\n");
    printf("\t\t||                     学生信息管理系统                       ||\n");
    printf("\t\t||              *****************************                ||\n");
    printf("\t\t||                                                           ||\n");
    printf("\t\t||=======================1.使用帮助===========================||\n");
    printf("\t\t||=======================2.显示所有工兵=======================||\n");
    printf("\t\t||=======================3.添加新兵蛋子=======================||\n");
    printf("\t\t||=======================4.删除工兵===========================||\n");
    printf("\t\t||=======================5.修改工兵信息=======================||\n");
    printf("\t\t||=======================6.查询工兵===========================||\n");
    printf("\t\t||=======================7.排序工兵数据=======================||\n");
    printf("\t\t||=======================8.保存工兵数据=======================||\n");
    printf("\t\t||=======================9.清屏==============================||\n");
    printf("\t\t||                                                           ||\n");
    printf("\t\t||___________________________________________________________||\n");
}
void help(){
    printf("欢迎来到广东工业大学的工兵信息管理系统！为帮助每一位鼠鼠更快地了解使用我们的系统，请认真阅读下面的信息。");
    printf("                                            注意事项：                                          ");
    printf("1.初次使用时请先增加工兵的信息！\n");
    printf("2.修改或增加工兵的信息后记得保存哟^^\n");
    printf("3.若数据有误，请先修改再保存^^\n");
    
}
//加载文件数据
void load_data() {
    FILE* file = fopen("students.data", "r");  // 以只读方式打开名为students.data的文件
    if (file == NULL) {
        printf("好可惜，文件打开失败...\n");
        return;
    }
    fread(&current_student, sizeof(int), 1, file);  // 从文件中读取工兵数量
    fread(students, sizeof(Student), current_student, file);  // 从文件中读取工兵的相关数据
    fclose(file);  // 关闭文件
}
//保存数据至文件
void save_data() {
    FILE* file = fopen("students.data", "w");  // 以只写方式打开文件
    fwrite(&current_student, sizeof(int), 1, file);  // 向文件中写入工兵数量
    fwrite(students, sizeof(Student), current_student, file);  // 向文件中写入工兵相关数据
    fclose(file);  // 关闭文件
}
//显示所有工兵鼠的信息
void display_students() {  
    for (i = 0; i < current_student; i++) {  // 遍历数组
        printf("学号：%d, 姓名：%s，年龄：%d, 班级：%s\n", students[i].id, students[i].name, students[i].age, students[i].class_name);  // 输出信息
    }
}
//添加新兵蛋子
void add_student() {  
    if (current_student >= MAX_STUDENT) {  // 检查鼠鼠数量是否已满
        printf("学生已满员！\n");  // 提示信息
        return;
    }
    printf("输入学号(id):\n");  // 输入学号
    scanf("%d", &students[current_student].id);  // 获取学号
    printf("输入姓名(name):\n");  // 输入姓名
    scanf("%s", students[current_student].name);  // 获取姓名
    printf("请输入年龄(age):");  // 输入年龄
    scanf("%d", &students[current_student].age);  // 获取年龄
    printf("输入班级(class_name):\n");  // 输入班级
    scanf("%s", students[current_student].class_name);  // 获取班级
    current_student++;  // 学生数量加一
}
//删除工兵鼠的信息
void delete_student() {  
    int id;  // 要删除的学号
    printf("输入要删除的学生学号：\n");  // 输入要删除的学号
    scanf("%d", &id);  // 获取要删除的学号
    for (i = 0; i < current_student; i++) {  // 遍历数组
        if (students[i].id == id) {  // 找到匹配的鼠
            for (int j = i; j < current_student - 1; j++) {
                students[j] = students[j + 1];  // 移动后面的数据向前推进
            }
            current_student--;  // 鼠鼠数量减一
            printf("该学生已被删除！\n");  // 提示信息
            return;
        }
    }
    printf("没有该学生的信息！\n");  // 输入不存在的学号时提示信息
}
//修改工兵鼠的信息
void modify_student() {  
    int id;  // 要修改的鼠鼠的学号
    printf("请输入你要修改的学生学号：\n");  // 输入要修改的学号
    scanf("%d", &id);  // 获取学号
    for (i = 0; i < current_student; i++) {  // 遍历学生数组
        if (students[i].id == id) {  // 找到匹配的鼠鼠
            printf("输入新的姓名：\n");
            scanf("%s", students[i].name);
            printf("输入新的年龄：\n");
            scanf("%d", &students[i].age);
            printf("输入新的班级：\n");
            scanf("%s", students[i].class_name);
            printf("该学生的信息已被更新。\n");
            return;
        }
    }
    printf("没有找到该学生的信息。\n");
}
//查找某位鼠
void search_student() {  
    char name[NAME_LENGTH];  // 输入要查找的姓名
    printf("请输入您要查询的学生姓名：\n");  // 输入姓名
    scanf("%s", name);  // 获取姓名
    for (i = 0; i < current_student; i++) {  // 遍历学生数组
        if (strcmp(students[i].name, name) == 0) {  // 比较找到对应的工兵
            printf("学号：%d，姓名：%s，年龄：%d, 班级：%s\n", students[i].id, students[i].name, students[i].age, students[i].class_name);  // 输出相关兵王的信息
            return;
        }
    }
    printf("没有找到该学生的信息。\n");
}
//排序工兵信息
void sort_students() {  
    int m = 0;  // 工兵数量临时变量
    FILE* file;  // 文件指针
    if ((file = fopen("students.data", "r")) == NULL) {  // 以只读方式打开文件
        printf("文件打开失败!\n");
        return;
    }
    while (!feof(file)) {  // 文件未结束
        if (fread(&students[m], sizeof(Student), 1, file) == 1) {  // 读取工兵数据
            m++;
        }
    }
    fclose(file);  // 关闭文件
    Student temp;  // 临时变量用于交换
    int ch;  // 排序选择变量
    printf("1.学号排序，2：成绩排序，3，年龄排序\n");  // 显示排序选项
    printf("请选择显示形式：");
    scanf("%d", &ch);  // 获取选择
    switch (ch) {
        case 1:  // 按学号排序
            for (i = 0; i < m; i++) {
                for (j = i + 1; j < m; j++) {
                    if (students[i].id > students[j].id) {
                        temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            break;

        case 2:  // 按成绩排序
            for (i = 0; i < m; i++) {
                for (j = i + 1; j < m; j++) {
                    if (students[i].score > students[j].score) {
                        temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            break;
        case 3:  // 按年龄排序
            for (i = 0; i < m; i++) {
                for (j = i + 1; j < m; j++) {
                    if (students[i].age > students[j].age) {
                        temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            break;
    }
    printf("学号\t姓名\t班级\t成绩\t年龄\n");  // 显示排序结果
    for (i = 0; i < m; i++) {
        printf("%d\t%s\t%s\t%.2f\t%d\n", students[i].id, students[i].name, students[i].class_name, students[i].score, students[i].age);
    }
}

void clear() {
    system("cls");  // 清屏
}
