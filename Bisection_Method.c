#include <stdio.h>
#include <math.h>

#define MAX_DEGREE 100

// Function to evaluate the polynomial at a given x
double evaluate(double x, double coeffs[], int degree)
{
    double result = 0.0;
    for (int i = 0; i <= degree; i++)
    {
        result += coeffs[i] * pow(x, degree - i);
    }
    return result;
}

// Bisection Method implementation with return value only
double bisection(double a, double b, double coeffs[], int degree, double EPSILON)
{
    double c = a;
    int iteration = 1;
    double prev_c = c;

    printf("\n%-10s %-15s %-15s %-15s %-15s %-15s\n", "Iter", "a", "b", "c", "f(c)", "Error");
    printf("-------------------------------------------------------------------------------\n");

    while ((b - a) >= EPSILON)
    {
        c = (a + b) / 2;
        double fc = evaluate(c, coeffs, degree);
        double error = fabs(c - prev_c);

        printf("%-10d %-15.6lf %-15.6lf %-15.6lf %-15.6lf %-15.6lf\n",
               iteration, a, b, c, fc, error);

        if (fc == 0.0) // Exact root found
            break;

        if (evaluate(a, coeffs, degree) * fc < 0)
            b = c;
        else
            a = c;

        prev_c = c;
        iteration++;
    }

    return c;
}

int main()
{
    int degree;
    double coeffs[MAX_DEGREE];

    printf("Enter the degree of the polynomial: ");
    scanf("%d", &degree);

    for (int i = 0; i <= degree; i++)
    {
        printf("Coefficient of x^%d: ", degree - i);
        scanf("%lf", &coeffs[i]);
    }

    double a, b;
    while (1)
    {
        printf("Enter the interval [a, b] (a < b):\n");
        printf("a: ");
        scanf("%lf", &a);
        printf("b: ");
        scanf("%lf", &b);

        if (evaluate(a, coeffs, degree) * evaluate(b, coeffs, degree) < 0)
        {
            break;
        }
        else
        {
            printf("Invalid interval! f(a) * f(b) >= 0. Try again.\n");
        }
    }

    double EPSILON;
    printf("Enter the tolerance value: ");
    scanf("%lf", &EPSILON);

    double root = bisection(a, b, coeffs, degree, EPSILON);

    printf("Approximate root found: %.10lf\n", root);

    return 0;
}
