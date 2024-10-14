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
#define LEN 50    // 定义学号和姓名的最大字符数

// 定义学生结构体
typedef struct {
    char id[LEN];          //工兵学号
    char name[LEN];        //工兵名字
    int age;               //工兵年龄
    char class_name[LEN];  //工兵班级
    float score[3];        //工兵各科成绩
} Student;

Student students[MAX_STUDENT];  // 学生数组
int current_student = 0;        // 初始工兵鼠数量

// 声明函数
void menu();                  // 声明函数显示菜单
void attention();                  //声明使用帮助函数
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
                    help();      //查看使用的注意事项
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
    getchar();//防止控制台窗口立即关闭，确保操作者可以看到程序的输出结果
    return 0;
}
//显示菜单哈
void menu() {
    printf("\n\n\n");
    printf("\t\t_______________________________________________________________\n");
    printf("\t\t||              *****************************                ||\n");
    printf("\t\t||                     学生信息管理系统                       ||\n");
    printf("\t\t||              *****************************                ||\n");
    printf("\t\t||                                                           ||\n");
    printf("\t\t||=======================1.注意事项===========================||\n");
    printf("\t\t||=======================2.显示所有工兵=======================||\n");
    printf("\t\t||=======================3.添加新兵蛋子=======================||\n");
    printf("\t\t||=======================4.删除工兵===========================||\n");
    printf("\t\t||=======================5.修改工兵信息=======================||\n");
    printf("\t\t||=======================6.查询工兵===========================||\n");
    printf("\t\t||=======================7.排序工兵数据=======================||\n");
    printf("\t\t||=======================8.保存工兵数据=======================||\n");
    printf("\t\t||=======================9.清屏==============================||\n");
    printf("\t\t||                                                           ||\n");
    printf("\t\t_______________________________________________________________\n");
}
//显示需要注意的事项
void attention(){
    printf("\n---欢迎来到广东工业大学的工兵信息管理系统！为帮助每一位鼠鼠更快地了解使用我们的系统，请认真阅读下面的信息---\n");
    printf("\n--------------------------------------------注意事项:-----------------------------------------------\n");
    printf("\n---------------------------------1.初次使用时请先增加工兵的信息！-------------------------------------\n");
    printf("\n---------------------------------2.修改或增加工兵的信息后记得保存哟^^---------------------------------\n");
    printf("\n---------------------------------3.若数据有误，请先修改再保存^^--------------------------------------\n");
    printf("\n---------------------------------4.请确保输入的学号唯一且有效。--------------------------------------\n");
    printf("\n---------------------------------5.在删除或修改学生的信息时，请确保输入正确的学号。--------------------\n");
    printf("\n---------------------------------6.使用保存数据功能时，确保文件路径正确且有写入权限。------------------\n");
    getchar();//防止控制台窗口立即关闭，确保操作者可以看到程序的输出结果
}
//加载文件数据
void load_data() {
    FILE* file = fopen("students.data", "rb");  // 以二进制读方式打开名为students.data的文件
    if (file == NULL) {       //判断是否打开文件失败
        printf("好可惜，文件打开失败...\n");
        return;
    }
    fread(&current_student, sizeof(int), 1, file);  // 从文件中读取工兵数量
    fread(students, sizeof(Student), current_student, file);  // 从文件中读取工兵的相关数据
    fclose(file);  // 关闭文件
}
//保存数据至文件
void save_data() {
    FILE* file = fopen("students.data", "wb");  // 以二进制写方式打开文件
    if (file == NULL) {                 //判断是否打开文件失败
        printf("好可惜，文件打开失败...\n");
        return;
    fwrite(&current_student, sizeof(int), 1, file);  // 向文件中写入工兵数量
    fwrite(students, sizeof(Student), current_student, file);  // 向文件中写入工兵相关数据
    printf("保存成功！！！")；  //显示提示信息
    fclose(file);  // 关闭文件
    getchar();     //防止控制台窗口立即关闭，确保操作者可以看到程序的输出结果
}
//显示所有工兵鼠的信息
void display_students() {  
    int i;    //定义循环变量
    if (current_student == 0)//若当前工兵鼠数量为0
    {
        printf("现在暂无任何鼠鼠的信息呢……")；
    }
    else
        {
            for (i = 0; i < current_student; i++) {  // 遍历数组
                printf("学号：%d,姓名：%s,年龄：%d, 班级：%s,高数成绩:%.2f,大英成绩:%.2f,大物成绩:%.2f\n", students[i].id, students[i].name, students[i].age, students[i].class_name,students[i].score[0],students[i].score[1],students[i].score[2]);  // 输出信息
            }
        }
    
    getchar();//防止控制台窗口立即关闭，确保操作者可以看到程序的输出结果
}
//添加新兵蛋子
void add_student() {  
    int j,m,i = current_student,new_stu = 0;    //定义循环变量
    if (current_student >= MAX_STUDENT) {  // 检查鼠鼠数量是否已满
        printf("学生已满员！\n");           // 提示信息
        return;
    }
    printf("请输入你想增加的鼠鼠数量：\n");  //提示新增的鼠鼠数量
    scanf("%d",&new_stu);   
    if (new_stu>0) {
        do{
            m = 1;//控制循环
            while (m)
                {
                    m = 0;
                    printf("请输入第%d位新鼠的学号：\n",i + 1);//提示输入学号
                    scanf("%d",&students[i].id);
                    for (j = 0;j < i;j++){                   //遍历学生数组找到相应的学号
                        if(strcmp(students[i].id,students[j].id)==0){
                            printf("该学号已存在！请重新输入!\n");
                            m = 1;//重新进入循环输入学号
                            break;
                        }
                    }
                }
                printf("请输入第%d位工兵鼠的名字\n",i + 1);//提示输入新的名字
                scanf("%s",students[i].name);
                printf("请输入第%d位工兵鼠的年龄\n",i + 1);//提示输入新的年龄
                scanf("%d",&students[i].age);
                printf("请输入第%d位工兵鼠的班级\n",i + 1);//提示输入新的班级
                scanf("%s",students[i].class_name);
                printf("请输入第%d位工兵鼠的高数成绩\n",i + 1);//提示输入新的高数成绩
                scanf("%f",&students[i].score[0]);
                printf("请输入第%d位工兵鼠的大英成绩\n",i + 1);//提示输入新的大英成绩
                scanf("%f",&students[i].score[1]);
                printf("请输入第%d位工兵鼠的大物成绩\n",i + 1);//提示输入新的大物成绩
                scanf("%f",&students[i].score[2]);
                i++;
        }while (i < current_student + new_stu);//若原鼠数量仍小于更新后的鼠鼠数量，则继续循环
    }
    current_student += new_stu;//更新现有鼠鼠数量
    printf("成功添加一枚鼠鼠！！！");
    getcahr();//防止控制台窗口立即关闭，确保操作者可以看到程序的输出结果
}
//删除工兵鼠的信息 
void delete_student() {  
    int id;    // 要删除的学号
    int i,j;   //定义循环变量
    printf("输入要删除的学生学号：\n");        //  提示信息
    scanf("%d", &id);                        // 获取要删除的学号
    for (i = 0; i < current_student; i++) {  // 遍历数组
        if (students[i].id == id) {          // 找到匹配的鼠
            for (int j = i; j < current_student - 1; j++) {
                students[j] = students[j + 1];  // 移动后面的数据向前推进
            }
            current_student--;            // 鼠鼠数量减一
            printf("该学生已被删除！\n");  // 提示信息
            return;
        }
    }
    printf("没有该学生的信息！\n");        //输入不存在的学号时提示信息
    getchar();
}
//修改工兵鼠的信息
void modify_student() {  
    int i,m;
    char Name[LEN];
    printf("请输入要修改信息的鼠鼠的姓名：\n");//输入要修改信息的工兵鼠的姓名
    scanf("%s",Name);
    while (1){
        m = 0;
        for (i = 0;i < n;i++){    //遍历数组找到相应的鼠鼠
            if(strcmp(students[i].name,Name) == 0){
                m = 1;
                int n;
                printf("\n\n\n")        //找到相应的鼠鼠则提示下面的信息
                printf("\t\t_____________________________________________________________\n");
                printf("\t\t||====================请选择要修改的信息=====================||\n");
                printf("\t\t||====================1.修改学号============================||\n");
                printf("\t\t||====================2.修改年龄============================||\n");
                printf("\t\t||====================3.修改班别============================||\n");
                printf("\t\t||====================4.修改高数成绩========================||\n");
                printf("\t\t||====================5.修改大英成绩========================||\n");
                printf("\t\t||====================6.修改大物成绩========================||\n");
                printf("\t\t_____________________________________________________________\n");
                printf("请输入你的选择:\n");  //操作者选择要修改的数据
                scanf("%d",n);
                switcn (n){     //根据选择进入相应板块
                    case 1:
                        printf("请输入新的学号:\n");           //输入新的学号
                        scanf("%s",students[i].id);
                        break;
                    case 2:
                        printf("请输入新的年龄:\n");           //输入新的年龄
                        scanf("%d",students[i].age);
                        break;
                    case 3:
                        printf("请输入新的班级:\n");           //输入新的班级
                        scanf("%s",students[i].class_name);
                        break;
                    case 4:
                        printf("请输入新的高数成绩:\n");        //输入新的高数成绩
                        scanf("%.2f",students[i].score[0]);
                        break;
                    case 5:
                        printf("请输入新的大英成绩:\n");        //输入新的大英成绩
                        scanf("%.2f",students[i].score[2]);
                        break;
                    case 6:
                        printf("请输入新的大物成绩:\n");        //数据如新的大物成绩
                        scanf("%.2f",students[i].score[2]);
                        break;
                    default:
                        printf("请在1-6中选择！！！");          //若选择其他数字，则输出提示信息
                }
                if (n > 0 && n < 7){       //选择在范围内，修改成功
                    printf("修改成功！")；
                }
                break;
            }
        }
        if (m == 0){
            printf("没有找到该鼠，请重新输入姓名:\n");   //查无此鼠
            scanf("%s",Name);
        }
    }
    getchar();         //防止控制台窗口立即关闭，确保操作者可以看到程序的输出结果
}
//查找某位鼠
void search_student() { 
    int i,ch,m,n;
    char arr[LEN];//用来存放操作者输入的信息
    printf("\n\n\n");   //显示选择界面
    printf("\t\t_________________________________________________________\n");
    printf("\t\t||======================================================||\n");
    printf("\t\t||==================1.根据学号查询=======================||\n");
    printf("\t\t||==================2.根据姓名查询=======================||\n");
    printf("\t\t||==================3.根据高数成绩查询===================||\n");
    printf("\t\t||==================4.根据大英成绩查询===================||\n");
    printf("\t\t||==================5.根据大物成绩查询===================||\n");
    printf("\t\t_________________________________________________________\n");
    while (1){
        m = 0;//控制是否找到鼠鼠
        printf("请输入你的选择：\n");
        scanf("%d",&ch);
        switch (ch)  //根据选择进入相应板块
            {
                case 1:          //根据学号查询
                    printf("请输入需要查找的工兵鼠的学号：\n");
                    scanf("%s",arr);
                    for (i = 0;i < current_student;i++){     //遍历循环查找
                        if (strcmp(students[i].id,arr) == 0){   //若找到相应学号
                            m = 1;
                            printf("\t学号\t姓名\t年龄\t班级\t高数成绩\t大英成绩\t大物成绩\n");
                            printf("\t%s\t%s\t%d\t%s\t%.2f\t%.2f\t%.2f\n",students[i].id,students[i].name,students[i].age,students[i].class_name,students[i].score[0],students[i].score[1],students[i].score[2]);//输出信息
                        }
                    }
                    break;
                case 2:               //根据姓名查询
                    printf("请输入需要查询的工兵鼠的姓名：\n");
                    scanf("%s",arr);
                    for (i = 0;i < current_student;i++){    //遍历数组
                        if(strcmp(students[i].name,arr) == 0){   //若找到相应名字
                            m = 1;
                            printf("\t学号\t姓名\t年龄\t班级\t高数成绩\t大英成绩\t大物成绩\n");
                            printf("\t%s\t%s\t%d\t%s\t%.2f\t%.2f\t%.2f\n",students[i].id,students[i].name,students[i].age,students[i].class_name,students[i].score[0],students[i].score[1],students[i].score[2]);//输出信息
                        }
                    }
                    break;
                case 3:               //根据高数成绩查询
                    printf("请输入需要查询的工兵鼠的高数成绩：\n");
                    scanf("%.2f",arr);
                    for (i = 0;i < current_student;i++){     //遍历数组
                        if(strcmp(students[i].score[0],arr) == 0){  //找到相应成绩
                            m = 1;
                            printf("\t学号\t姓名\t年龄\t班级\t高数成绩\t大英成绩\t大物成绩\n");
                            printf("\t%s\t%s\t%d\t%s\t%.2f\t%.2f\t%.2f\n",students[i].id,students[i].name,students[i].age,students[i].class_name,students[i].score[0],students[i].score[1],students[i].score[2]);//输出信息
                        }
                    }
                    break;
                case 4:               //根据大英成绩查询
                    printf("请输入需要查询的工兵鼠的大英成绩：\n");
                    scanf("%.2f",arr);
                    for (i = 0;i < current_student;i++){    //遍历数组
                        if(strcmp(students[i].score[0],arr) == 0){   //找到相应成绩
                            m = 1;
                            printf("\t学号\t姓名\t年龄\t班级\t高数成绩\t大英成绩\t大物成绩\n");
                            printf("\t%s\t%s\t%d\t%s\t%.2f\t%.2f\t%.2f\n",students[i].id,students[i].name,students[i].age,students[i].class_name,students[i].score[0],students[i].score[1],students[i].score[2]);//输出信息
                        }
                    }
                    break;
                case 5:             //根据大物成绩查询
                    printf("请输入需要查询的工兵鼠的大物成绩：\n");
                    scanf("%.2f",arr);
                    for (i = 0;i < current_student;i++){        //遍历数组
                        if(strcmp(students[i].score[2],arr) == 0){     //找到相应成绩
                            m = 1;
                            printf("\t学号\t姓名\t年龄\t班级\t高数成绩\t大英成绩\t大物成绩\n");
                            printf("\t%s\t%s\t%d\t%s\t%.2f\t%.2f\t%.2f\n",students[i].id,students[i].name,students[i].age,students[i].class_name,students[i].score[0],students[i].score[1],students[i].score[2]);//输出信息
                        }
                    }
                    break;
                default:    //选择不再范围内
                    {
                        printf("请在1-5内进行选择！");
                    }
                    break;
            }
            if (m == 0){   //没能根据信息找到对应鼠鼠
                printf("查无此鼠！请重新输入");
            }
            
    }
    getchar();
}
//排序工兵信息
void sort_students() {  
    int i,j,m = 0;  // 工兵数量临时变量
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
    printf("\n\n\n");
    printf("\t\t||______________________________________________________________||\n");
    printf("\t\t||========================选择你要排序的信息======================||\n");
    printf("\t\t||========================1.按学号排序===========================||\n");
    printf("\t\t||========================2.按高数成绩排序=======================||\n");
    printf("\t\t||========================3.按大英成绩排序=======================||\n");
    printf("\t\t||========================4.按大物成绩排序=======================||\n");
    printf("\t\t||========================5.按年龄排序===========================||\n");
    printf("\t\t||______________________________________________________________||\n");
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

        case 2:  // 按高数成绩排序
            for (i = 0; i < m; i++) {
                for (j = i + 1; j < m; j++) {
                    if (students[i].score[0]> students[j].score[0]) {//后一个高数成绩比前一个大
                        //交换数据
                        temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            break;
        case 3:  //按大英成绩排序
            for (i = 0; i < m; i++) {
                for (j = i + 1; j < m; j++) {
                    if (students[i].score[1]> students[j].score[1]) {//后一个大英成绩比前一个大
                        //交换数据
                        temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            break;
        case 4:   //按大物成绩排序
            for (i = 0; i < m; i++) {
                for (j = i + 1; j < m; j++) {
                    if (students[i].score[2]> students[j].score[2]) {//后一个大物成绩比前一个大
                        //交换数据
                        temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            break;
        case 5:  // 按年龄排序
            for (i = 0; i < m; i++) {
                for (j = i + 1; j < m; j++) {
                    if (students[i].age > students[j].age) {//后一个年龄比前一个大
                        //交换数据
                        temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            break;
    }
    printf("学号\t姓名\t班级\t高数成绩\t大英成绩\t大物成绩\t年龄\n");  // 显示排序结果
    for (i = 0; i < m; i++) {                //遍历数组显示排序结果
        printf("%d\t%s\t%s\t%.2f\t%d\n", students[i].id, students[i].name, students[i].class_name, students[i].score[0],students[i].score[1],students[i].score[2], students[i].age);
    }
    getchar();//防止控制台窗口立即关闭，确保操作者可以看到程序的输出结果
}

void clear() {
    system("cls");  // 清屏
}
