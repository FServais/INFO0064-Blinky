#ifndef SIM_H
#define SIM_H

#include "track.h"

int simulate (const Point *p, long double *T1, long double *T2, const long double eps);

long double distance (const Point *a, const Point *b);

#endif

