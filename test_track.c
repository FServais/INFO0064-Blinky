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
   p_test.x = 3.5;
   p_test.y = 4.0;
   p_test.z = 0.0;

   fprintf(stdout, "T.D. is at position:\n");
   printPoint_s(&p_test);
   fprintf(stdout, "\n");

   simulate(&p_test, &T1, &T2);

   printTimes(T1, T2);
   fprintf(stdout, "\n");

   Point p;

   p.x = 0;
   p.y = 0;

   track(T1, T2, &p);

   fprintf(stdout, "The point computed by the function is:");
   printPoint(&p);

   return EXIT_SUCCESS;
}

void printPoint(Point* p)
{
   if (p == NULL)
      return;

   fprintf(stdout, "\n");
   fprintf(stdout, "P.x = %d\n", p->x);
   fprintf(stdout, "P.y = %d\n", p->y);
}

void printTimes(long double T1, long double T2)
{
   if ((T1 < 0) || (T2 < 0))
      return;

   fprintf(stdout, "\n");
   fprintf(stdout, "T1 = %Le micros\n", T1 * pow(10,6));
   fprintf(stdout, "T2 = %Le micros\n", T2 * pow(10,6));
}

