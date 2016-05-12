#include <stdlib.h>
#include <math.h>

#include "track.h"

/**
 * pow2()
 * @param: x
 * @return: x^2
 */
double pow2 (double x);

/**
 * root2()
 * @param: x
 * @return: sqrt(x)
 */
double root2 (double x);

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
  if (p == NULL)
     return -1;

  if (T1 <= 0)
     return -2;

  if (T2 <= 0)
     return -3;

  const long double velocity = 343;/* [m/s] */

  T1 = T1 * velocity;
  T2 = T2 * velocity;

  const long double e = 0.05;//[m] /* TODO: measure the real value in cm */

  const long double m = pow2(e) - pow2(T1);
  const long double n = pow2(e) - pow2(T2);
  const long double a = (n / pow2(T2)) - (m / pow2(T1));
  const long double b = - e * ((n / pow2(T2)) + (m / pow2(T1)));
  const long double c = (pow2(n) / (4 * pow2(T2))) - (pow2(m) / (4 * pow2(T1)));
  const long double delta = pow2(b) - 4 * a * c;

  p->x = -b + root2(delta) / (2 * a);
  p->y = root2((m * pow2(p->x) + m * e * p->x + pow2(m) / 4) / pow2(T1));
/*
  p->x = 2;
  p->y = 3;
*/
  return 0;
}

double root2 (double x)
{
   return sqrt(x);
}

double pow2 (double x)
{
   return pow(x, 2);
}

