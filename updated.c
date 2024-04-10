#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // For getch() function on Windows
#include <windows.h>

typedef struct {
    char* arr;
    size_t size;
    size_t capacity;
    size_t cursorPosition;
} DynamicArray;

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
    for (size_t i = dynamicArray->size; i > dynamicArray->cursorPosition; i--) {
        dynamicArray->arr[i] = dynamicArray->arr[i - 1];
    }
    dynamicArray->arr[dynamicArray->cursorPosition] = element;
    dynamicArray->cursorPosition++;
    dynamicArray->size++;
}

void popElement(DynamicArray* dynamicArray) {
    if (dynamicArray->cursorPosition > 0) {
        for (size_t i = dynamicArray->cursorPosition - 1; i < dynamicArray->size - 1; i++) {
            dynamicArray->arr[i] = dynamicArray->arr[i + 1];
        }
        dynamicArray->cursorPosition--;
        dynamicArray->size--;
    }
}

void moveCursorLeft(DynamicArray* dynamicArray) {
    if (dynamicArray->cursorPosition > 0) {
        dynamicArray->cursorPosition--;
    }
}

void moveCursorRight(DynamicArray* dynamicArray) {
    if (dynamicArray->cursorPosition < dynamicArray->size) {
        dynamicArray->cursorPosition++;
    }
}

void printDynamicArray(const DynamicArray* dynamicArray) {
    printf("\n");
    for (size_t i = 0; i < dynamicArray->size; ++i) {
        printf("%c", dynamicArray->arr[i]);
    }
    printf("\n");
}

void freeDynamicArray(DynamicArray* dynamicArray) {
    free(dynamicArray->arr);
    dynamicArray->arr = NULL;
    dynamicArray->size = 0;
    dynamicArray->capacity = 0;
    dynamicArray->cursorPosition = 0;
}

void clrscr() {
    system("cls");
}

void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void openFile(DynamicArray* dynamicArray, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        pushElement(dynamicArray, ch);
    }
    fclose(file);
}

void saveFile(const DynamicArray* dynamicArray, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error saving file.\n");
        return;
    }

    for (size_t i = 0; i < dynamicArray->size; ++i) {
        fputc(dynamicArray->arr[i], file);
    }
    fclose(file);
}

int main() {
    DynamicArray myArray = initDynamicArray(5);
    int flag = 0;
    char ch;
    clrscr();
    gotoxy(20, 0);
    printf("Simple Notepad\n");
    gotoxy(0, 2);

    do {
        ch = getch();

        switch (ch) {
            case 0:
            case 224:
                ch = getch();
                switch (ch) {
                    case 75: // Left arrow
                        moveCursorLeft(&myArray);
                        break;
                    case 77: // Right arrow
                        moveCursorRight(&myArray);
                        break;
                    case 83: // Delete
                        popElement(&myArray);
                        break;
                }
                break;
            case 13: // Enter
                printDynamicArray(&myArray);
                getch();
                break;
            case 8: // Backspace
                popElement(&myArray);
                break;
            case 27: // Escape
                flag = 1;
                break;
            case 'o': // Open file
                clrscr();
                gotoxy(20, 0);
                printf("Simple Notepad - Open File\n");
                gotoxy(0, 2);
                char filename[256];
                printf("Enter filename to open: ");
                scanf("%255s", filename);
                openFile(&myArray, filename);
                break;
            case 's': // Save file
                clrscr();
                gotoxy(20, 0);
                printf("Simple Notepad - Save File\n");
                gotoxy(0, 2);
                char saveFilename[256];
                printf("Enter filename to save: ");
                scanf("%255s", saveFilename);
                saveFile(&myArray, saveFilename);
                break;
            default:
                pushElement(&myArray, ch);
                break;
        }

        clrscr();
        gotoxy(20, 0);
        printf("Simple Notepad\n");
        gotoxy(0, 2);
        printDynamicArray(&myArray);
        gotoxy(1 + myArray.cursorPosition, 2); // Move cursor to the correct position
    } while (flag == 0);

    freeDynamicArray(&myArray);
    return 0;
}
