#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "track.h"

/**
 * pow2()
 * @param: x
 * @return: x^2
 * @brief: Just an interface for pow in math library. If in future we want to
 * use another optimize formula, we would just have to change the implementation
 * of this function.
 */
long double pow2 (double x);

/**
 * root2()
 * @param: x
 * @return: sqrt(x)
 * @brief: Just an interface for sqrt in math library. If in future we want to
 * use another optimize formula, we would just have to change the implementation
 * of this function.
 */
long double root2 (double x);

/**
 * track()
 *
 * See matlab file and report.
 *
 * TODO :
 * - check if it gives the right answer
 * - check units
 * - check division, float type, etc.
 * - make tests
 */
int track (long double T1, long double T2, Point* p)
{

  fprintf(stdout, "\n***** start tracking algorithm *****\n");

  if (p == NULL)
  {
     p->x = 0;
     p->y = 0;
     p->z = 0;

     return -1;
  }

  if (T1 <= 0)
  {
     p->x = 0;
     p->y = 0;
     p->z = 0;

     return -2;
  }

  if (T2 <= 0)
  {
     p->x = 0;
     p->y = 0;
     p->z = 0;

     return -3;
  }

  const long double e = 1; /* distance between the captor and the origin in [m] */
  const long double v = 3; /* Velocity of the signal in [m/s] */

  long double d1 = T1 * v;
  long double d2 = T2 * v;

  if (d1 == d2)
  {
     p->x = 0;
     p->y = (pow2(d1) - pow2(e)) / (2 * d1);
     p->z = 0;
     return 0;
  }

  if (pow2(d2) == 0 || pow2(d1) == 0)
  {
     p->x = 0;
     p->y = 0;
     p->z = 0;
     return -4;
  }

  long double m = pow2(e) - pow2(d1);
  long double n = pow2(e) - pow2(d2);
  long double a = (n / pow2(d2)) - (m / pow2(d1));
  long double b = (-1) * e * ((n / pow2(d2)) + (m / pow2(d1)));
  long double c = (pow2(n) / (4 * pow2(d2))) - (pow2(m) / (4 * pow2(d1)));

  long double delta = pow2(b) - 4 * a * c;

  if (delta <= 0)
  {
     p->x = 0;
     p->y = 0;
     p->z = 0;
     return -5;
  }

  p->x = -b + root2(delta) / (2 * a);

  if ((((m * pow2(p->x) + m * e * p->x + (pow2(m)) / 4)) / pow2(d1)) < 0)
  {

     fprintf(stdout, "(d_1)^2 = %Le\n", pow2(d1));

     p->x = 0;
     p->y = 0;
     p->z = 0;
     return -6;
  }

  p->y = root2((m * pow2(p->x) + m * e * p->x + pow2(m) / 4) / pow2(d1));
  p->z = 0;

  return 0;

  fprintf(stdout, "\n***** end tracking algorithm *****\n");

}

long double root2 (double x)
{
   return sqrt(x);
}

long double pow2 (double x)
{
   return pow(x, 2);
}

