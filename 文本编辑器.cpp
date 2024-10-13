/*
 * 文本编辑器
 * 
 * 该文本编辑器使用栈来实现基本的文本输入、删除、撤销和重做功能。
 * 
 * 基础功能：
 * 1. 使用两个栈储存信息，一个存储文本内容，另一个存储操作记录。
 * 2. 支持以下操作：
 *    - 插入字符：在当前光标位置插入一个字符。
 *    - 删除字符：删除当前光标位置的字符。
 *    - 撤销：撤销最近的一次操作。
 * 3.模拟文本编辑和撤销操作
 * 4.测试
 * 
 * 进阶功能：
 * 1. 支持多种编辑操作，例如复制、粘贴。
 * 2. 支持重做（redo）功能，允许用户恢复最近撤销的操作。
 * 3. 添加错误处理，例如操作非法的情况（如删除空文本时的操作）。
 * 
 * 示例操作序列：
 * 1. 插入字符 'a'
 * 2. 插入字符 'b'
 * 3. 插入字符 'c'
 * 4. 删除字符
 * 5. 撤销
 * 6. 撤销
 * 
 * 预期输出：
 * 结果字符串：ab
 *
 * 好了淦就完了！奥里给========>
 */
#include <stdio.h>   // 标准输入输出库
#include <stdlib.h>  // 标准库
#include <string.h>  // 字符串操作库

#define MAX_SIZE 100  // 定义栈的最大容量

// 定义栈结构
typedef struct {
    char data[MAX_SIZE];  // 存储栈数据的数组
    int top;              // 栈顶指针
} Stack;

char clipboard[MAX_SIZE];  // 定义剪贴板缓冲区

void menu();                                      //声明函数用于显示菜单
void initStack(Stack *stack);                     //声明函数用于初始化栈
int isEmpty(Stack *stack);                        //声明函数用于判断栈是否为空
int isFull(Stack *stack);                         //声明函数用于判断栈是否已经满了
void push(Stack *stack, char ch);                 //声明函数用于插入字符
char pop(Stack *stack);                           //声明函数用于删除字符
void copy_to_clipboard(Stack *stack);             //声明函数用于复制栈中的内容到剪切板
void paste_from_clipboard(Stack *stack);          //声明函数用于从剪切板中粘贴内容到栈
char peek(Stack *stack);                          //声明函数用于查看栈顶元素
void display(Stack*stack);                        //显示栈内容
void initEditor(TextEditor *editor);              //声明函数用于初始化文本编辑器
void insert_Char(TextEditor *editor, char ch);     //声明函数用于插入字符
void delete_Char(TextEditor *editor);              //声明函数用于删除字符
void undo(TextEditor *editor);                    //声明函数用于撤销最近一次操作
void redo(TextEditor *editor);                    //声明函数用于重做操作
void print_Text(TextEditor *editor);               //声明函数用于打印文本内容

// 初始化栈
void initStack(Stack *stack) {
    if (stack == NULL) {
        fprintf(stderr, "Error: Stack pointer is NULL.\n");
        exit(EXIT_FAILURE);
    }
    stack->top = -1;  // 栈顶指针初始化为-1，表示空栈
}

// 判断栈是否为空
int isEmpty(Stack *stack) {
    return stack->top == -1;  // 如果栈顶指针为-1，则栈为空
}

// 判断栈是否已满
int isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;  // 如果栈顶指针等于最大容量减1，则栈已满
}

// 入栈
void push(Stack *stack, char ch) {
    if (isFull(stack)) {
        fprintf(stderr, "Error: Stack is full. Cannot push '%c'.\n", ch);//栈满时输出提示信息
        return '\0';  // 返回空字符表示错误
    }
    stack->data[++stack->top] = ch;  // 插入字符到栈顶
}

// 出栈
char pop(Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Error: Stack is empty. Cannot pop.\n");//栈为空时输出提示信息
        return '\0';  // 返回空字符表示错误
    }
    return stack->data[stack->top--];  // 返回栈顶字符并更新栈顶指针
}

// 复制栈中的内容到剪贴板
void copy_to_clipboard(Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Error: Stack is empty. Cannot copy.\n");
        return;
    }
    strncpy(clipboard, stack->data, stack->top + 1);
    clipboard[stack->top + 1] = '\0';  // 添加字符串结束符
}

// 从剪贴板粘贴内容到栈
void paste_from_clipboard(Stack *stack) {
    for (int i = 0; clipboard[i] != '\0'; i++) {
        push(stack, clipboard[i]);
    }
}

// 查看栈顶元素
char peek(Stack *stack) {
    if (!isEmpty(stack)) {  // 如果栈不为空
        return stack->data[stack->top];  // 返回栈顶元素
    }
    return '\0';  // 如果栈为空，返回空字符
}

//显示栈中内容
void display(Stack* stack) {
    if (isEmpty(stack)) {           //检查栈是否为空
        printf("Stack is empty.\n");//提示栈为空
        return;
    }
    printf("Stack contents: ");
    for (int i = 0; i <= stack->top; i++) {  //遍历栈中数据，打印栈中内容
        printf("%c ", stack->data[i]);
    }
    printf("\n");
}

// 定义文本编辑器结构
typedef struct {
    Stack text;        // 存储文本内容的栈
    Stack operations;  // 存储操作记录的栈
    Stack redoStack;   // 存储重做操作的栈
} TextEditor;

// 初始化文本编辑器
void initEditor(TextEditor *editor) {
    initStack(&editor->text);        // 初始化文本内容栈
    initStack(&editor->operations);  // 初始化操作记录栈
    initStack(&editor->redoStack);   // 初始化重做操作栈
}

// 插入字符
void insert_Char(TextEditor *editor, char ch) {
    push(&editor->text, ch);         // 将字符压入文本内容栈
    push(&editor->operations, 'I');  // 将插入操作记录压入操作记录栈
    push(&editor->redoStack, '\0');  // 清空重做操作栈
}

// 删除字符
void delete_Char(TextEditor *editor) {
    if (!isEmpty(&editor->text)) {  // 如果文本内容栈不为空
        char deleted_Char = pop(&editor->text);  // 弹出栈顶字符
        push(&editor->operations, 'D');         // 将删除操作记录压入操作记录栈
        push(&editor->redoStack, deleted_Char);  // 将删除的字符压入重做操作栈
    }
}

// 撤销操作
void undo(TextEditor *editor) {
    if (!isEmpty(&editor->operations)) {  // 如果操作记录栈不为空
        char last_Op = pop(&editor->operations);  // 弹出最近的操作记录
        if (last_Op == 'I') {  // 如果最近的操作是插入
            char undone_Char = pop(&editor->text);  // 弹出文本内容栈顶字符
            push(&editor->redoStack, undone_Char);  // 将撤销的字符压入重做操作栈
        } else if (last_Op == 'D') {  // 如果最近的操作是删除
            char redo_Char = pop(&editor->redoStack);  // 弹出重做操作栈顶字符
            push(&editor->text, redo_Char);            // 将字符重新压入文本内容栈
        }
    }
}

// 重做操作
void redo(TextEditor *editor) {
    if (!isEmpty(&editor->redoStack)) {  // 如果重做操作栈不为空
        char redo_Char = pop(&editor->redoStack);  // 弹出重做操作栈顶字符
        if (redo_Char != '\0') {  // 如果字符不为空
            push(&editor->text, redo_Char);         // 将字符压入文本内容栈
            push(&editor->operations, 'I');        // 将插入操作记录压入操作记录栈
        }
    }
}

// 打印文本内容
void print_Text(TextEditor *editor) {
    for (int i = 0; i <= editor->text.top; i++) // 遍历文本内容栈
    {  
        printf("%c", editor->text.data[i]);  // 打印每个字符
    }
    printf("\n");  // 换行
}

// 测试文本编辑器功能
void testEditor() {
    TextEditor editor;  // 定义文本编辑器实例
    initEditor(&editor);  // 初始化文本编辑器

    // 示例1
    printf("Example 1:\n");   //示例1
    insert_Char(&editor, 'a'); //插入字符'a'
    insert_Char(&editor, 'b'); //插入字符'b'
    insert_Char(&editor, 'c'); //插入字符'c'
    print_Text(&editor);  // 预期输出: abc
    delete_Char(&editor); // 撤销近一次操作 
    print_Text(&editor);  // 预期输出: ab
    undo(&editor);       // 重做，撤销撤销操作
    print_Text(&editor);  // 预期输出: abc
    undo(&editor);       //重做
    print_Text(&editor);  // 预期输出: ab

    // 清空编辑器
    initEditor(&editor);

    // 示例2
    printf("Example 2:\n");   //示例2
    insert_Char(&editor, 'x'); //插入字符'x'
    insert_Char(&editor, 'y'); //插入字符'y'
    insert_Char(&editor, 'z'); //插入字符'z'
    print_Text(&editor);  // 预期输出: xyz
    delete_Char(&editor); //撤销近一次操作
    delete_Char(&editor); //再次撤销
    print_Text(&editor);  // 预期输出: x
    undo(&editor);       //重做
    print_Text(&editor);  // 预期输出: xy
    undo(&editor);       //重做
    print_Text(&editor);  // 预期输出: xyz

    // 清空编辑器
    initEditor(&editor);

    // 示例3
    printf("Example 3:\n");   //示例3
    insert_Char(&editor, '1'); //插入字符'1'
    insert_Char(&editor, '2'); //插入字符'2'
    insert_Char(&editor, '3'); //插入字符'3'
    print_Text(&editor);  // 预期输出: 123
    delete_Char(&editor); //撤销近一次操作
    delete_Char(&editor); //再次撤销
    delete_Char(&editor); //又双叒叕撤销
    print_Text(&editor);  // 预期输出: (空)
    undo(&editor);       //重做，返回上一步
    print_Text(&editor);  // 预期输出: 1
    undo(&editor);       //再次返回上一步
    print_Text(&editor);  // 预期输出: 12
    undo(&editor);       //又双叒叕返回上一步
    print_Text(&editor);  // 预期输出: 123
}

// 主函数
int main() {
    testEditor();  // 测试文本编辑器功能
    Stack editor;  //定义文本编辑器实例
    initStack(&textStack);  //初始化文本编辑器
    
    int choice;             //定义用户选择的变量
    char ch;                //定义用户储存的变量

    //无限循环直到用户选择退出
    while (1){
        printf("\t\t________________________________________________\n");
        printf("\t\t===============文本编辑器操作指引================\n");
        printf("\t\t===============1.插入===========================\n");
        printf("\t\t===============2.删除===========================\n");
        printf("\t\t===============3.撤销===========================\n");
        printf("\t\t===============4.打印文本=======================\n");
        printf("\t\t===============5.复制内容至剪贴板================\n");
        printf("\t\t===============6.从剪贴板粘贴内容================\n");
        printf("\t\t===============7.正常退出=======================\n");
        printf("\t\t________________________________________________\n");
        scanf("%d", &choice);//读取用户的选择

        switch (choice) {    //根据用户选择执行相应操作
            case 1:          //选择插入
                printf("请输入一个要插入的字符: ");
                scanf(" %c", &ch);//读取用户输入的字符
                insert_Char(&editor, ch);//插入字符到文本编辑器中
                break;
            case 2:          //选择删除字符
                delete_Char(&editor);//删除文本编辑器中的字符
                break;
            case 3:            //选择撤销
                undo(&editor); //撤销上一步操作
                break;
            case 4:            //选择打印文本
                print_Text(&editor);//打印当前文本内容
                break;
            case 5:            //选择复制内容至剪贴板
                copy_to_clipboard(&editor.textStack);//复制文本内容到剪贴板
                break;
            case 6:            //选择从剪贴板粘贴内容
                paste_from_clipboard(&editor.textStack);//从剪贴板粘贴内容
                break;
            case 7:            //选择退出
                exit(0);       //退出程序
            default:           //如果输入无效
                printf("我不懂你想让我干什么.\n");   //明示用户输入无效
        }
    }
    return 0;  // 返回0，表示程序正常结束
}
