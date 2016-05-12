#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "simulation.h"
#include "track.h"

double distance(Point_s *a, Point_s *b);

int simulate (Point_s *p, long double *T1, long double *T2)
{
  const double c1 =  0.05; // [m] distance from sensor 1 to sender
  const double c2 = -0.05; // [m] distance from sensor 2 to sender

  const double v = 343.0; //[m/s] approximate velocity of the ultrason in air
  const double epsilon = 0; // the time it takes to the tracking device to send back

  Point_s o;
  o.x = 0.0;
  o.y = 0.0;
  o.z = 0.0;

  double dt1 = 0.0;
  double dt2 = 0.0;

  // for C1:
  /* time ellapse to go from senders to the point */
  double dt = distance(&o, p) / v;
  dt1 += dt;
  dt2 += dt;

  /* Time taken by the T.D. to respond */
  dt1 += epsilon;
  dt2 += epsilon;

  /* time ellapse to go from the T.D. to the sensors */
  Point_s C1, C2;
  C1.x = c1;
  C1.y = 0;
  C1.z = 0;

  C2.x = c2;
  C2.y = 0;
  C2.z = 0;

  dt1 += distance(p, &C1) / v;
  dt2 += distance(p, &C2) / v;

  // end of simulation  
  *T1 = dt1;
  *T2 = dt2;

  return 0;
}

double distance(Point_s *a, Point_s *b)
{
   if (a == NULL || b == NULL)
      return -1;

   return sqrt(pow(b->x - a->x,2) + pow(b->y - a->y, 2) + pow(b->z - a->z, 2));
}

void printPoint_s(Point_s *p)
{
   if (p == NULL)
      return;

   fprintf(stdout, "\n");
   fprintf(stdout, "P.x = %lf\n", p->x);
   fprintf(stdout, "P.y = %lf\n", p->y);
   fprintf(stdout, "P.z = %lf\n", p->z);
}


