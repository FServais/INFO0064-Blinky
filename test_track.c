#include <stdlib.h>
#include <stdio.h>

#include "track.h"

void printPoint(Point* p);
void printTimes(int T1, int T2);

int main()
{
   int T1 = 0;
   int T2 = 0;

   printTimes(T1, T2);

   Point p;

   track(T1, T2, &p);

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
   if (T1 < 0) || (T2 < 0)
      return;

   fprintf(stdout, "\n");
   fprintf(stdout, "T1 = %d\n", T1);
   fprintf(stdout, "T2 = %d\n", T2);
}

