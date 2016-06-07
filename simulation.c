#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <float.h>

#include "simulation.h"

int simulate (const Point *p, long double *T1, long double *T2, const long double eps)
{

  if (p->y <= 0)
  {
     *T1 = LDBL_MAX;
     *T2 = LDBL_MAX;
     return -1;
  }

  const long double e = 7.0; /* distance between the captor and the origin in [cm] */
  const long double v = 0.034000; /* Velocity of the signal in [cm/(10^-6)s] */

  *T1 = 0.00;
  *T2 = 0.00;

  Point origine, c1, c2;

  origine.x = 0.0;
  origine.y = 0.0;
  origine.z = 0.0;

  c1.x = -e;
  c1.y = 0.0;
  c1.z = 0.0;

  c2.x = e;
  c2.y = 0.0;
  c2.z = 0.0;

  long double t0 = distance(&origine, p) / v;

  *T1 += t0;
  *T2 += t0;

  long double t1 = distance(&c1, p) / v;

  *T1 += t1;

  long double t2 = distance(&c2, p) / v;

  *T2 += t2;

  // end of simulation. Adding negligeable error

  *T1 += eps;
  *T2 += eps;

  return 0;
}

long double distance(const Point *a, const Point *b)
{
   if (a == NULL || b == NULL)
      return -1;

   return sqrt(pow(b->x - a->x,2) + pow(b->y - a->y, 2) + pow(b->z - a->z, 2));
}

