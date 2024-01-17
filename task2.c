#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int divide(int a, int b) {
    return a / b;
}

int multiply(int a, int b) {
    return a * b;
}

int subtract(int a, int b) {
    return a - b;
}

typedef int (*func_t)(int, int);

struct operation_t {
    char operation;
    func_t func;
};

int main() {
    struct operation_t operations[] = {
            {
                    .operation = '+',
                    .func = add
            },
            {
                    .operation = '/',
                    .func = divide
            },
            {
                    .operation = '*',
                    .func = multiply
            },
            {
                    .operation = '-',
                    .func = subtract
            },
    };

    int a = 10;
    int b = 2;
    for (int i = 0; i < sizeof operations / sizeof(struct operation_t); i++) {
        struct operation_t op = operations[i];
        int res = op.func(a, b);
        printf("%d %c %d = %d\n", a, op.operation, b, res);
    }
}
