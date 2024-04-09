#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct {
    char* arr;
    size_t size;
    size_t capacity;
    size_t cursorPosition;
}DynamicArray;
DynamicArray initDynamicArray(size_t initialCapacity) {
    DynamicArray dynamicArray;
    dynamicArray.arr = (char*)malloc(initialCapacity * sizeof(char));
    dynamicArray.size = 0;
    dynamicArray.cursorPosition = 0;
    dynamicArray.capacity = initialCapacity;
    return dynamicArray;
}
void pushElement(DynamicArray* dynamicArray, char element) {
    if (dynamicArray->size == dynamicArray->capacity) {
        dynamicArray->capacity *= 2;
        dynamicArray->arr = (char*)realloc(dynamicArray->arr, dynamicArray->capacity * sizeof(char));
    }
    dynamicArray->arr[dynamicArray->cursorPosition] = element;
    dynamicArray->cursorPosition++;
    dynamicArray->size++;
}
void printDynamicArray(const DynamicArray* dynamicArray) {
    printf(" \n");
    for (size_t i = 0; i < dynamicArray->size; ++i) {
        printf("%c", dynamicArray->arr[i]);
    }
    printf(" \n");
}
void popElement(DynamicArray* dynamicArray) {
    if (dynamicArray->size > 0) {
        dynamicArray->size--;
        dynamicArray->cursorPosition--;
        putchar(' ');  // Print a space to clear the character on the console
        putchar('\b'); // Move the cursor back again
    }
}
void freeDynamicArray(DynamicArray* dynamicArray) {
    free(dynamicArray->arr);
    dynamicArray->arr = NULL;
    dynamicArray->size = 0;
    dynamicArray->capacity = 0;
    dynamicArray->cursorPosition=0;
}
void moveCursorLeft(DynamicArray* dynamicArray) {
    if (dynamicArray->cursorPosition > 0) {
        dynamicArray->cursorPosition--;
        putchar('\b');
    }
}

void moveCursorRight(DynamicArray* dynamicArray) {
    if (dynamicArray->cursorPosition < dynamicArray->size) {
        putchar(dynamicArray->arr[dynamicArray->cursorPosition]);
        dynamicArray->cursorPosition++;
    }
}
void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);

}
void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

void clrscr()
{
    system("cls");
}
int main()
{
    DynamicArray myArray = initDynamicArray(5);
    size_t *cur=myArray.cursorPosition;
    int flag=0;
    int size=1;
    char ch='b';
    clrscr();
    gotoxy(20,0);
    printf("Line Editor\n");
    gotoxy(0,1+size);
    do
    {
        ch=getch();
        if (ch == 0 || ch == 224 || ch==-32)
        {
            ch = getch();
                switch (ch) {
                    case 75: //left arrow
                        moveCursorLeft(&myArray);
                        break;
                    case 77: //Right arrow
                        moveCursorRight(&myArray);
                        break;
                    case 71:  //Home go to the first element of array
                        putchar('\r');
                        break;
                    case 79:  //End go to the last element of array
                        gotoxy(myArray.size+1,2);
                        break;
                    case 83:  // ASCII value for Delete remove all the array
                        if (myArray.cursorPosition > 0){
                            for(int d=0;d<myArray.capacity;d++)
                            {
                                moveCursorLeft(&myArray);
                                myArray.cursorPosition++;
                                popElement(&myArray);
                            }
                        }
                    break;
                }

        }
        else{
        switch(ch)
        {
            default:
                pushElement(&myArray, ch);
                putchar(ch);
                size++;
            break;   //Enter
            case 13:
               printDynamicArray(&myArray);;
               getch();
            break;
            case 8:  // ASCII value for Backspace
                if (myArray.cursorPosition > 0)
                    {
                        moveCursorLeft(&myArray);
                        myArray.cursorPosition++;
                        popElement(&myArray);
                    }
                break;
            case 27:  // ASCII value for Escape
                flag=1;
            break;
        }
    }
    }
    while(flag==0);
    freeDynamicArray(&myArray);
    return 0;
}
