#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "track.h"

void printPoint(Point* p);
void printTimes(int T1, int T2);

int main()
{
   int T1 = 5; // in second
   int T2 = 4; // in second

   printTimes(T1, T2);

   Point p;

   p.x = 0;
   p.y = 0;

   printPoint(&p);

   track(T1, T2, &p);

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

void printTimes(int T1, int T2)
{
   if ((T1 < 0) || (T2 < 0))
      return;

   fprintf(stdout, "\n");
   fprintf(stdout, "T1 = %d s\n", T1);
   fprintf(stdout, "T2 = %d s\n", T2);
}

