#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/sem.h>

int increment(int semid, struct sembuf* buf) {
    buf->sem_op = 1;
    buf->sem_flg = 0;
    buf->sem_num = 0;

    return semop(semid, buf, 1);
}

int decrement(int semid, struct sembuf* buf) {
    buf->sem_op = -1;
    buf->sem_flg = 0;
    buf->sem_num = 0;

    return semop(semid, buf, 1);
}

int main()
{
    int parent[2], result;
    size_t size = 0;
    key_t key;
    char pathname[] = "05-3.c";
    struct sembuf buffer;

    int semid;
    char resstring[14];

    if (pipe(parent) < 0) {
        printf("Невозможно создать pipe отца\n\r");
        exit(-1);
    }

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Ключ не сгенерирован.\n");
        exit(-1);
    }

    if ((semid = semget(key, 1, 0666)) < 0) {
        printf("Семафор не найден, повторяю: \n");
        if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
            printf("Не могу получить Semid\n");
            exit(-1);
        }
        printf("Успешно создан!\n");
    }

    result = fork();

    if (result < 0) {
        printf("Неудачный fork\n\r");
        exit(-1);
    }

    else if (result > 0) {
        int N;
        printf("Введите N: \n");
        scanf("%d", &N);
        if (N < 2) {
            printf("N должен быть больше или равен 2.\n");
            exit(-1);
        }

        for (size_t i = 0; i < N; i++)
        {
            if (write(parent[1], "Hello, world!", 14) != 14) {
                printf("Can\'t write all string\n\r");
                exit(-1);
            }

            printf("Пара №%d, Отец отправил рёбенку месседж.\n\r", i + 1);

            increment(semid, &buffer);
            decrement(semid, &buffer);
            size = read(parent[0], resstring, 14);

            if (size != 14) {
                printf("Can\'t read from child\n\r");
                exit(-1);
            }

            printf("Отец прочитал с ребёнка: %s\n\r", resstring);
        }
        close(parent[0]);
    }
    else {
        int counter = 0;
        while(1){
            decrement(semid, &buffer);
            size = read(parent[0], resstring, 14);

            if (size < 0) {
                close(parent[1]);
                close(parent[0]);

                printf("Всё тип топ, все покинули чат-чат\n");
                return 0;
            }

            printf("Пара №%d, Ребёнок получил с отца: %s\n\r", ++counter, resstring);

            if (write(parent[1], "Hi, my parent", 14) != 14) {
                printf("Невозможно написать всю строку.\n");
                exit(-1);
            }
            increment(semid, &buffer);
        }
    }
    return 0;
}
