#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "simulation.h"

#include "track.h"

int simulate (Point *p, long double *T1, long double *T2, long double eps)
{

  const long double e = 1; /* distance between the captor and the origin in [m] */
  const long double v = 3; /* Velocity of the signal in [m/s] */

  *T1 = 0.00;
  *T2 = 0.00;

  Point tmp;

  tmp.x = 0.00;
  tmp.y = 0.00;
  tmp.z = 0.00;

  long double t0 = distance(&tmp, p) / v;

  *T1 += t0;
  *T2 += t0;

  tmp.x = e;

  long double t1 = distance(&tmp, p) / v;

  *T1 += t1;

  tmp.x = -e;

  long double t2 = distance(&tmp, p) / v;

  *T2 += t2;

  *T1 += eps;
  *T2 += eps;

  return 0;
}

long double distance(Point *a, Point *b)
{
   if (a == NULL || b == NULL)
      return -1;

   return sqrt(pow(b->x - a->x,2) + pow(b->y - a->y, 2) + pow(b->z - a->z, 2));
}

void printPoint_s(Point *p)
{
   if (p == NULL)
      return;

   fprintf(stdout, "\n");
   fprintf(stdout, "P.x = %Le\n", p->x);
   fprintf(stdout, "P.y = %Le\n", p->y);
   fprintf(stdout, "P.z = %Le\n", p->z);
}


