#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

double formula1(double a) {
    return cos(a) + sin(a) + cos(3 * a) + sin(3 * a);
}

double formula2(double a) {
    return 2 * sqrt(2) * cos(a) * sin(M_PI / 4 + 2 * a);
}

int main() {
    printf("Enter a: ");

    double a;
    if (scanf_s("%lf", &a) != 1) {
        printf("invalid input, must be floating point number\n");
        return 1;
    }

    printf("\n");

    printf(" a = %lf\n", a);
    printf("z1 = %lf\n", formula1(a));
    printf("z2 = %lf\n", formula2(a));
}
