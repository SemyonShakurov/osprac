#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void reverse(char* str, size_t sz);

int main()
{
    int parent[2], child[2], result;
    size_t size;
    char resstring[14];

    if (pipe(parent) < 0) {
        printf("Невозможно создать pipe отца\n\r");
        exit(-1);
    }

    if (pipe(child) < 0) {
        printf("Невозможно создать pipe ребёнка\n\r");
        exit(-1);
    }

    result = fork();

    if (result < 0) {
        printf("Неудачный fork\n\r");
        exit(-1);
    } else if (result > 0) {
        close(parent[0]);
        close(child[1]);
        size = write(parent[1], "Hello, world!", 14);
        if (size != 14) {
            printf("Can\'t write all string\n\r");
            exit(-1);
        }
        close(parent[1]);

        size = read(child[0], resstring, 14);
        if (size != 14) {
            printf("Can\'t read from child\n\r");
            exit(-1);
        }

        close(child[0]);
        printf("Отец прочитал с ребёнка: %s\n\rОтец закончил.\n\r", resstring);
    } else {
        close(parent[1]);
        close(child[0]);
        size = read(parent[0], resstring, 14);
        if (size < 0) {
            printf("Can\'t get from parent\n\r");
            exit(-1);
        }
        printf("Ребёнок получил с отца: %s\n\r", resstring);
        size = write(child[1], resstring, 14);
        close(child[1]);
        close(parent[0]);
        printf("Ребёнок вышел\n\r");
    }
    return 0;
}
