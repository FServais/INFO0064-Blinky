#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "track.h"
#include "simulation.h"

void printPoint(Point* p);
void printTimes(long double T1, long double T2);

int main()
{
   long double T1 = -1.0; // in second
   long double T2 = -1.0; // in second

   Point_s p_test;
   p_test.x = 2.5;
   p_test.y = 1.0;
   p_test.z = 0.0;

   fprintf(stdout, "T.D. is at position:\n");
   printPoint_s(&p_test);
   fprintf(stdout, "\n");

   simulate(&p_test, &T1, &T2);

   printTimes(T1, T2);
   fprintf(stdout, "\n");

   Point p;

   p.x = -1;
   p.y = -1;

   fprintf(stderr, "track return %d\n", track(T1, T2, &p));

   fprintf(stdout, "\nThe point computed by the function is:");

   printPoint(&p);

   return EXIT_SUCCESS;
}

void printPoint(Point* p)
{
   if (p == NULL)
      return;

   fprintf(stdout, "\n");
   fprintf(stdout, "P.x = %lf\n", p->x);
   fprintf(stdout, "P.y = %lf\n", p->y);
}

void printTimes(long double T1, long double T2)
{
   if ((T1 < 0) || (T2 < 0))
      return;

   fprintf(stdout, "\n");
   fprintf(stdout, "T1 = %Le s\n", T1);
   fprintf(stdout, "T2 = %Le s\n", T2);
}

