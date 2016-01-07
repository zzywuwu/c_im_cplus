#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>


typedef struct fruit_s
{
		void (*sell)(void);
}fruit;

typedef struct juice_s
{
		void (*drink)(void);
}juice;

struct foctory
{
        fruit* (*create_fruit)();
        juice* (*create_juice)();
};

void apple_sell(void)
{
        printf("i am apple,sell!\n");
}

void apple_drink(void)
{
        printf("i am apple juice,drink!\n");
}

fruit * create_apple_fruit(void)
{
        fruit *apple = malloc(sizeof(fruit));
        apple->sell = apple_sell;

        return apple;
}

juice * create_apple_juice(void)
{
        juice *apple_juice = malloc(sizeof(juice));
        apple_juice->drink = apple_drink;

        return apple_juice;
}

struct foctory * create_apple_foctory(void)
{
        struct foctory *f = malloc(sizeof(struct foctory));
        f->create_fruit = create_apple_fruit;
        f->create_juice = create_apple_juice;

        return f;
}

int main()
{
        fruit *ff;
        juice *jj;

        struct foctory *f_apple = create_apple_foctory();

        ff = f_apple->create_fruit();
        ff->sell();

        jj = f_apple->create_juice();
        jj->drink();

        return 0;
}
