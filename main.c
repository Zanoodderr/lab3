#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

 double f(double x)
 {
     return 4*pow(x+1, 3)-3*x-3;
 }

 double chord_method(double x1, double x2, double xi, unsigned int N, unsigned int i, double measurement_error, unsigned int var3, unsigned int debug);
 double half_division_method(double x1, double x2, double xi, unsigned int N, unsigned int i, double measurement_error, unsigned int var3, unsigned int debug);
 double Newton_method(double x1, double x2, double xi, unsigned int N, unsigned int i, double measurement_error, double delta, unsigned int var3, unsigned int debug);
 void shapka(void);

int main()
{
    double x1, x2, xi=0, measurement_error, h, delta;
    unsigned int N, n, var1, var2, var3=0, s_time1, s_time2, all_time, i=1, debug=0;


    printf("\n\t*==================================*");
    printf("\n\t|              lab3                |");
    printf("\n\t*----------------------------------*");
    printf("\n\t|        nonlinear equation        |");
    printf("\n\t*==================================*\n");

    do{
    printf("\n\tEnter the left boundary of calculating    (x1 < x2)\n  X(first)=");
    scanf("%lf", &x1);

    printf("\n\tEnter the right boundary of calculating\n  X(last)=");
    scanf("%lf", &x2);
    }while (x1 >= x2);

    if ( f(x1) * f(x2) > 0){
        printf("\n\tIf such boundaries are set, the program cannot cope with the search for roots.");
        printf("\n\tWhat would you like to do next   (press 1 to select 1. or any other key to select 2.)");
        printf("1.change search boundaries\n2.let the program to shorten the interval");
        scanf("%u", &var1);

        if (var1 == 1){

            do{
                printf("\n\tEnter the left boundary of calculating    (x1 < x2)\n  X(first)=");
                scanf("%lf", &x1);

                printf("\n\tEnter the right boundary of calculating\n  X(last)=");
                scanf("%lf", &x2);
            }while (x1 >= x2);
        }

        else {

            printf("\n\tEnter the value of step of shortening the root search interval");
            scanf("%lf", &h);

            while ((x1 * x2) < 0){
            x1 += h;
            }
        }
    }

    do{
    printf("\tEnter the maximum number of interations (N>0)\nN=");
    scanf("%u", &N);
    }while(N <= 0);

    n = N;

    printf("\n\tEnter the measurment error of calculating\n  Measurment error=");
    scanf("%lf", &measurement_error);

    do
    {
        printf("\nChoose the method of calculating:\n");
        printf("\t1. By Chords method:\n");
        printf("\t2. By Half division method:\n");
        printf("\t3. By Newton's method (tangent method):\n");
        scanf("%u", &var2);

            if (var2!=1 && var2!=2 && var2!=3)
                printf("\nYou are mistaken\n");
    }while (var2!=1 && var2!=2 && var2!=3);
    system ("cls");

        switch(var2)
         {

         case 1:
            {
                printf("\n\n\t======*Chords method*======\n");
                s_time1 = time (NULL);
                xi = chord_method(x1, x2, xi, N, i, measurement_error, var3, debug);
            } break;

         case 2:
            {
                printf("\n\n\t======*Half division method*======\n");
                s_time1 = time (NULL);
                xi = half_division_method(x1, x2, xi, N, i, measurement_error, var3, debug);
            } break;

        case 3:
            {
                printf("\n\n\t======*Newton's method (tangent method)*======\n");

                do{
                printf("\n\tEnter delta x  (0 < delta x < 1)\n");
                scanf("%lf", &delta);
                }while (delta <= 0 || delta >= 1);

                s_time1 = time (NULL);
                xi = Newton_method(x1, x2, xi, N, i, measurement_error, delta, var3, debug);
            } break;
         }

    shapka();

    if (fabs (f(xi)) <= measurement_error){
        s_time2 = time (NULL);
        all_time = (s_time2 - s_time1);
    }

    else{

        do{

            s_time2 = time (NULL);
            all_time += (s_time2 - s_time1);

            do{
                printf("\n\n\tThe number of iterations you specified has been exhausted.\n\tWhat would you like to do next:");
                printf("\n\n1. perform the same number of iterations   \n2. Perform iterations until the result \n3. Exit the program\n");
                scanf("%u", &var3);

                    if (var3!=1 && var3!=2 && var3!=3)
                    printf("\nYou are mistaken\n");

            }while (var3!=1 && var3!=2 && var3!=3);

            system ("cls");
            s_time1 = time (NULL);

            switch(var3){

            case 1:
                {
                    printf("\n\n\t======*%d intervals more*======\n", n);
                    i += n;
                    N += n;
                    debug = 1;
                    s_time1 = time (NULL);

                    if (var2 == 1) {
                        xi = chord_method(x1, x2, xi,  N, i, measurement_error, var3, debug);
                    }

                    else if (var2 == 2) {
                        xi = half_division_method(x1, x2, xi, N, i, measurement_error, var3, debug);
                    }

                    else {
                        xi = Newton_method(x1, x2, xi, N, i, measurement_error, delta, var3, debug);
                    }
                } break;

            case 2:
                {
                    printf("\n\n\t======*Until the end*======\n");
                    debug = 1;
                    s_time1 = time (NULL);

                    if (var2 == 1) {
                        xi = chord_method(x1, x2, xi,  N, i, measurement_error, var3, debug);
                    }

                    else if (var2 == 2) {
                        xi = half_division_method(x1, x2, xi, N, i, measurement_error, var3, debug);
                    }

                    else {
                        xi = Newton_method(x1, x2, xi, N, i, measurement_error, delta, var3, debug);
                    }

                    shapka();
                    s_time2 = time (NULL);
                    all_time += (s_time2 - s_time1);
                    printf("\n\n\t\tIt took %d seconds to complete\n", all_time);
                    printf("\t\tFinal answer:\n\t\tX = %.8f \n", xi);
                    return 0;

                } break;

            case 3:
                {
                    printf("\n\n\t\tIt took %d seconds to complete\n", all_time);
                    return 0;
                }
            }

            shapka();

        }while (fabs(f(xi)) > measurement_error);
    }
    printf("\n\n\t\tIt took %d seconds to complete\n", all_time);
    printf("\t\tFinal answer:\n\t\tX = %.8f \n", xi);
return 0;
}


//---------------------------------------------------------------------------------------------------------------------------------------------


double chord_method(double x1, double x2, double xi, unsigned int N, unsigned int i, double measurement_error, unsigned int var3, unsigned int debug){

    shapka ();

    if (var3 == 2) {       //Користувач вирішив не призупиняти роботу програми (див. рядки 109 - 161)
        do {

            if (debug == 0){          // debug може приймати значення 1 (див. рядки 152 і 171)
            xi = (f(x2)*x1-f(x1)*x2) / ( f(x2)-f(x1) );
            }

            if ( f(xi)*f(x1) > 0 ){
                x1 = xi;
            }

            else{
                x2 = xi;
            }

            debug = 0;

            printf("\n\t|    %d     |%.8f   |%.8f      |", i, xi, f(xi));
            i ++;

        } while (fabs(f(xi)) > measurement_error);
    }

    else {
        for (i; i < N+1; i++){

            if (debug == 0){            // debug може приймати значення 1 (див. рядки 152 і 171)
            xi = (f(x2)*x1-f(x1)*x2) / ( f(x2)-f(x1) );
            }

            if ( f(xi)*f(x1) > 0 ){
                x1 = xi;
            }

            else{
                x2 = xi;
            }

            debug = 0;

            printf("\n\t|    %d     |%.8f   |%.8f      |", i, xi, f(xi));

            if( fabs(f(xi)) <= measurement_error ){
                break;
            }
        }
    }
    return xi;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

double half_division_method(double x1, double x2, double xi, unsigned int N, unsigned int i, double measurement_error, unsigned int var3, unsigned int debug){

    shapka();

    if (var3 == 2) {       //Користувач вирішив не призупиняти роботу програми (див. рядки 109 - 161)
        do{

            if (debug == 0){                // debug може приймати значення 1 (див. рядки 152 і 171)
            xi = ((x1+x2)/2);
            }

            if ( f(xi)*f(x1) > 0 ){
                x1 = xi;
            }

            else{
                x2 = xi;
            }

            debug = 0;

            printf("\n\t|    %d     |%.8f   |%.8f      |", i, xi, f(xi));
            i ++;

        } while (fabs(f(xi)) > measurement_error);
    }

    else{

        for (i; i <= N; i++){

            if (debug == 0){
            xi = ((x1+x2)/2);
            }

            if ( f(xi)*f(x1) > 0 ){
                x1 = xi;
            }

            else{
                x2 = xi;
            }

            debug = 0;

            printf("\n\t|    %d     |  %.8f |   %.8f   |", i, xi, f(xi));

            if( fabs(f(xi)) <= measurement_error ){
                break;
            }
        }
    }
    return (xi);
}

//------------------------------------------------------------------------------------------------------------------------------------------------

double Newton_method(double x1, double x2, double xi, unsigned int N, unsigned int i, double measurement_error, double delta, unsigned int var3, unsigned int debug){
    double derivative;

    derivative = ( f(x1+delta) - f(x1) ) / delta;

    shapka();

    if (var3 == 2) {       //Користувач вирішив не призупиняти роботу програми (див. рядки 109 - 161)
        do{

            if (debug == 0){                  // debug може приймати значення 1 (див. рядки 152 і 171)
            xi = x1 - (f(x1) / derivative);
            }

            if ( f(xi)*f(x1) > 0 ){
                x1 = xi;
            }

            else{
                x2 = xi;
            }

            debug = 0;

            printf("\n\t|    %d     |  %.8f |   %.8f   |", i, xi, f(xi));
            i ++;

        } while (fabs(f(xi)) > measurement_error);
    }

    else{

        for (i=1; i <= N; i++){

            if (debug == 0){
            xi = x1 - (f(x1) / derivative);
            }

            if ( f(xi)*f(x1) > 0 ){
                x1 = xi;
            }

            else{
                x2 = xi;
            }

            debug = 0;

            printf("\n\t|    %d     |  %.8f |   %.8f   |", i, xi, f(xi));

            if (fabs(f(xi)) <= measurement_error) {
                break;
            }
        }
    }
    return xi;
}

void shapka(){

    printf ("\n\n\t================================================");
    printf ("\n\t|      N      |       X      |       F(X)      |");
    printf ("\n\t================================================\n");
}
