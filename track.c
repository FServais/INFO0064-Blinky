#include <stdlib.h>
#include <math.h>

#include "track.h"

/**
 * pow2()
 * @param: x
 * @return: x^2
 */
float pow2 (float x);

/**
 * root2()
 * @param: x
 * @return: sqrt(x)
 */
float root2 (float x);

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
int track (int T1, int T2, Point* p)
{
  if ((p == NULL) || (T1 <= 0) || (T2 <= 0))
     return -1;

  const int velocity = 343;/* m/s */

  T1 = T1 * velocity;
  T2 = T2 * velocity;

  const float e = 0; /* TODO: measure the real value in cm */

  const float m = pow2(e) - pow2(T1);
  const float n = pow2(e) - pow2(T2);
  const float a = (n / pow2(T2)) - (m / pow2(T1));
  const float b = - e * ((n / pow2(T2)) + (m / pow2(T1)));
  const float c = (pow2(n) / (4 * pow2(T2))) - (pow2(m) / (4 * pow2(T1)));

  float delta = pow2(b) - 4 * a * c;

  p->x = -b + root2(delta) / (2 * a);
  p->y = root2((m * pow2(p->x) + m * e * p->x + pow2(m) / 4) / pow2(T1));

  return 0;
}

float root2 (float x)
{
   return sqrt(x);
}

float pow2 (float x)
{
   return pow(x, 2);
}

