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

// 插入字符到栈
void push(Stack *stack, char ch) {
    if (isFull(stack)) {
        fprintf(stderr, "Error: Stack is full. Cannot push '%c'.\n", ch);
        return;
    }
    stack->data[++stack->top] = ch;  // 插入字符到栈顶
}

// 从栈中删除字符
char pop(Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Error: Stack is empty. Cannot pop.\n");
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
void insertChar(TextEditor *editor, char ch) {
    push(&editor->text, ch);         // 将字符压入文本内容栈
    push(&editor->operations, 'I');  // 将插入操作记录压入操作记录栈
    push(&editor->redoStack, '\0');  // 清空重做操作栈
}

// 删除字符
void deleteChar(TextEditor *editor) {
    if (!isEmpty(&editor->text)) {  // 如果文本内容栈不为空
        char deletedChar = pop(&editor->text);  // 弹出栈顶字符
        push(&editor->operations, 'D');         // 将删除操作记录压入操作记录栈
        push(&editor->redoStack, deletedChar);  // 将删除的字符压入重做操作栈
    }
}

// 撤销操作
void undo(TextEditor *editor) {
    if (!isEmpty(&editor->operations)) {  // 如果操作记录栈不为空
        char lastOp = pop(&editor->operations);  // 弹出最近的操作记录
        if (lastOp == 'I') {  // 如果最近的操作是插入
            char undoneChar = pop(&editor->text);  // 弹出文本内容栈顶字符
            push(&editor->redoStack, undoneChar);  // 将撤销的字符压入重做操作栈
        } else if (lastOp == 'D') {  // 如果最近的操作是删除
            char redoChar = pop(&editor->redoStack);  // 弹出重做操作栈顶字符
            push(&editor->text, redoChar);            // 将字符重新压入文本内容栈
        }
    }
}

// 重做操作
void redo(TextEditor *editor) {
    if (!isEmpty(&editor->redoStack)) {  // 如果重做操作栈不为空
        char redoChar = pop(&editor->redoStack);  // 弹出重做操作栈顶字符
        if (redoChar != '\0') {  // 如果字符不为空
            push(&editor->text, redoChar);         // 将字符压入文本内容栈
            push(&editor->operations, 'I');        // 将插入操作记录压入操作记录栈
        }
    }
}

// 打印文本内容
void printText(TextEditor *editor) {
    for (int i = 0; i <= editor->text.top; i++) 
    {  // 遍历文本内容栈
        printf("%c", editor->text.data[i]);  // 打印每个字符
    }
    printf("\n");  // 换行
}

// 测试文本编辑器功能
void testEditor() {
    TextEditor editor;  // 定义文本编辑器实例
    initEditor(&editor);  // 初始化文本编辑器

    insertChar(&editor, 'a');  // 插入字符'a'
    insertChar(&editor, 'b');  // 插入字符'b'
    insertChar(&editor, 'c');  // 插入字符'c'
    deleteChar(&editor);       // 删除字符
    undo(&editor);             // 撤销操作
    undo(&editor);             // 撤销操作

    printText(&editor);  // 打印文本内容，预期输出: "ab"
}

// 主函数
int main() {
    testEditor();  // 测试文本编辑器功能

    Stack textStack;
    initStack(&textStack);

    push(&textStack, 'a');
    push(&textStack, 'b');
    push(&textStack, 'c');
    copy_to_clipboard(&textStack);  // 复制栈中的内容
    pop(&textStack);
    pop(&textStack);
    paste_from_clipboard(&textStack);  // 从剪贴板粘贴内容

    return 0;  // 返回0，表示程序正常结束
}