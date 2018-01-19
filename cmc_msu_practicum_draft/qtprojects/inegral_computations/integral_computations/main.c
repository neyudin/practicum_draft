#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double (* func_t) (double);

double f1 (double x) {
    return log(x); //7
    //return exp(-x) + 3.0; //3
    //return 3.0 * (0.5/(x + 1.0) + 1.0); //2
    //return pow(2.0, x) + 1.0; //1
    //return exp(x) + 2.0; //4
}

double f2 (double x) {
    return -2.0 * x + 14.0; //7
    //return 2.0 * x - 2.0; //3
    //return 2.5 * x - 9.5; //2
    //return pow(x, 5.0); //1
    //return -1.0/x; //4
}

double f3 (double x) {
    return 1.0/(2.0 - x) + 6.0; //7
    //return 1.0/x; //3
    //return 5.0/x; //2
    //return (1.0 - x)/3.0; //1
    //return -2.0 * (x + 1)/3.0; //4
}

double root_finder (func_t f, func_t g, double a, double b, double eps1) { //method: chords
    double fg_a = 0.0, fg_b = 0.0, root = (a + b)/2.0;
    /*printf("fg((a+b)/2) = %.9lf\n", f((a + b)/2) - g((a + b)/2));*/printf("their delta == %.9lf\n", fabs(f((a + b)/2) - g((a + b)/2) - (f(a) + f(b) - g(a) - g(b))/2));
    /*printf("mid = %.9lf\n", (f(a) + f(b) - g(a) - g(b))/2);*/
    if ((g(a) + f(b) - f(a) - g(b)) * (f(root) - g(root) - (f(a) + f(b) - g(a) - g(b))/2.0) < -eps1) {
        while (fabs((f(root) - g(root)) * (f(root + eps1) - g(root + eps1))) > eps1) { //right: root is near b
            fg_a = f(a) - g(a);
            printf("step l->r: ");
            fg_b = f(b) - g(b);
            root = (fg_b * a - fg_a * b)/(fg_b - fg_a);
            a = root;printf("their delta == %.9lf\n", fabs(f((a + b)/2) - g((a + b)/2) - (f(a) + f(b) - g(a) - g(b))/2));
        }
    } else {
        while (fabs((f(root - eps1) - g(root - eps1)) * (f(root) - g(root))) > eps1) { //left: root is near a
            fg_a = f(a) - g(a);
            printf("step r->l: ");
            fg_b = f(b) - g(b);
            root = (fg_b * a - fg_a * b)/(fg_b - fg_a);
            b = root;printf("their delta == %.9lf\n", fabs(f((a + b)/2) - g((a + b)/2) - (f(a) + f(b) - g(a) - g(b))/2));
        }
    }
    return root;
}

double integral (func_t f, double a, double b, double eps2) { //method: trapezoid
    printf("integral\n");
    double result = 5 * eps2, height, answer = 0;
    long long i, n = 8;
    double suc;
    while (fabs(result - answer)/3 > eps2) {
        n <<= 1;
        printf("step with n == %lld\n", n);
        height = (b - a)/n;
        for (i = 0, suc = 0; i < n + 1; ++i) {
            suc += height * fabs(f(a + i * height)) * (((i == 0) || (i == n)) ? 0.5 : 1);
        }
        answer = result;
        result = suc;
    }
    return result;
}

double f12 (double x) {
    return f1(x) - f2(x);//-0.371824 [-5; -0.01] EPS1_6 ; (4)
    //[1; 2] ; (1)
    //[4.2; 5.8] ; (2)
    //[2.2; 3.0] ; (3)
    //[5.8; 6.6] ; (7)
}

double f23 (double x) {
    return f2(x) - f3(x);//-1.822888 [-3; -1] EPS1_6 ; (4)
    //[-1; 0.9] ; (1)
    //[3.8; 4;8] ; (2)
    //[1.0; 1.8] ; (3)
    //[3.8; 4.6] ; (7)
}

double f13 (double x) {
    return f1(x) - f3(x);//-4.026754 [-5; -3] EPS1_6 ; (4)
    //[-4; -2.3] ; (1)
    //[1.0; 2.0] ; (2)
    //[0.1; 0.6] ; (3)
    //[2.1; 2.6] ; (7)
}

int main(void) {
    double eps1 = 0.000001, eps2 = 0.000001, x1, x2, x3, result;
        x1 = root_finder(f1, f2, 5.8, 6.6, eps1);
        printf("x1 = %.9lf\n", x1);
        x2 = root_finder(f2, f3, 3.8, 4.6, eps1);
        printf("x2 = %.9lf\n", x2);
        x3 = root_finder(f1, f3, 2.1, 2.6, eps1);
        printf("x3 = %.9lf\n", x3);
    if ((x1 - x2 >= eps1) || ((x1 - x2 <= eps1) && (x1 - x2 >= -eps1))) {
        if ((x3 - x1 >= eps1) || ((x3 - x1 <= eps1) && (x3 - x1 >= -eps1))) {
            result = integral(f23, x2, x1, eps2) + integral(f13, x1, x3, eps2);
        }
        if ((x2 - x3 >= eps1) || ((x2 - x3 <= eps1) && (x2 - x3 >= -eps1))) {
            result = integral(f13, x3, x2, eps2) + integral(f12, x2, x1, eps2);
        } else {
            result = integral(f23, x2, x3, eps2) + integral(f12, x3, x1, eps2);
        }
    } else {
        if ((x3 - x2 >= eps1) || ((x3 - x2 <= eps1) && (x3 - x2 >= -eps1))) {
            result = integral(f12, x1, x2, eps2) + integral(f13, x2, x3, eps2);
        }
        if ((x1 - x3 >= eps1) || ((x1 - x3 <= eps1) && (x1 - x3 >= -eps1))) {
            result = integral(f13, x3, x1, eps2) + integral(f23, x1, x3, eps2);
        } else {
            result = integral(f12, x1, x3, eps2) + integral(f23, x3, x2, eps2);
        }
    }
    printf("square of non-linear triangle = %.9lf\n", result);
    return 0;
}
