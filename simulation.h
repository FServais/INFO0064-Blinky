#ifndef SIM_H
#define SIM_H

// Define a point with double instead of int as in track.h
typedef struct Point_s Point_s;

struct Point_s
{
  double x;
  double y;
  double z;
};

int simulate (Point_s *p, long double *T1, long double *T2);

void printPoint_s(Point_s *p);

#endif

