#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "track.h"
#include "simulation.h"

void printPoint(Point* p);
void printTimes(long double T1, long double T2);

int main()
{
   long double T1; // in second
   long double T2; // in second

   const long double e = 1; /* distance between the captor and the origin in [m] */
   const long double v = 3; /* Velocity of the signal in [m/s] */

   fprintf(stdout, "\ne = %Le\n", e);
   fprintf(stdout, "v = %Le\n", v);

   Point p_test;
   p_test.x = 1.0;
   p_test.y = 1.0;
   p_test.z = 0.0;

   fprintf(stdout, "\nT.D. is at position:\n");
   printPoint(&p_test);
   fprintf(stdout, "\n");

   simulate(&p_test, &T1, &T2, 0);

   printTimes(T1, T2);

   Point p_approx;
   p_approx.x = 0;
   p_approx.y = 0;
   p_approx.z = 0;

   fprintf(stderr, "\ntrack return %d\n", track(T1, T2, &p_approx));

   fprintf(stdout, "\nThe point computed by the function is:");

   printPoint(&p_approx);

   return EXIT_SUCCESS;
}

void printPoint(Point* p)
{
   if (p == NULL)
      return;

   fprintf(stdout, "\n");
   fprintf(stdout, "P.x = %Le\n", p->x);
   fprintf(stdout, "P.y = %Le\n", p->y);
   fprintf(stdout, "P.z = %Le\n", p->z);
}

void printTimes(long double T1, long double T2)
{
   if ((T1 < 0) || (T2 < 0))
      return;

   fprintf(stdout, "T1 = %Le s\n", T1);
   fprintf(stdout, "T2 = %Le s\n", T2);
}

