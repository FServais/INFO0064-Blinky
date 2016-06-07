#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "simulation.h"
#include "track.h"

void displayResults(int error, Point *p, Point *TD, long double T1, long double T2);

void printPoint (FILE* output, Point *p);
void printTimes (FILE* output, long double T1, long double T2);

double computeError(Point *p, Point *TD);

int main()
{
   long double T1; // in second
   long double T2; // in second

   const long double e = 7.0;    /* distance between the captor and the origin in [cm] */
   const long double v = 0.0340; /* Velocity of son = 340 [m/2] */
                                 /* Velocity of the signal in [cm/(10^(-6)s)] */

   fprintf(stdout, "\nParameters:\n");
   fprintf(stdout, "\ndistance between receivers and Transmitter = %Le [cm]\n", e);
   fprintf(stdout, "\nspeed of the signal = %Le [cm/(10^-6)s]\n", v);

   fprintf(stdout, "\nStarting simulation\n");

   long double dx = 250.0, dy = 250.0, dz = 250.0;

   long double xMin = -500.0, yMin = -500.0, zMin = -500.0;
   long double xMax = +500.0, yMax = +500.0, zMax = +500.0;

   for (long double z = zMin; z <= zMax; z += dz)
   {
       for (long double y = yMin; y <= yMax; y += dy)
       {
           for (long double x = xMin; x <= xMax; x += dx)
           {
               Point p_test;

               p_test.x = x;
               p_test.y = y;
               p_test.z = z;

               simulate(&p_test, &T1, &T2, 0.0);

               Point p_approx;
               p_approx.x = +0.0;
               p_approx.y = -1.0;
               p_approx.z =  0.0;

               int error = track(T1, T2, &p_approx);

               displayResults(error, &p_approx, &p_test, T1, T2);
           }
       }
   }

   fprintf(stdout, "\nEnd of simulation\n");

   return EXIT_SUCCESS;
}

void displayResults(int error, Point *p, Point *TD, long double T1, long double T2)
{
   FILE* output = stderr;

   if (error != 0)
   {
      fprintf(stderr, "\n\n !!! ERROR !!! \n");
      output = stderr;
   }
   else
   {
      fprintf(stdout, "\n\n Results of the simulation: \n");
      output = stdout;
   }

   fprintf(output, "\nTracking Device is at position:\n");
   printPoint(output, TD);

   fprintf(output, "\nMeasured ellapsed times:\n");
   printTimes(output, T1, T2);

   fprintf(output, "\nTrack function return code: %d \n", error);

   fprintf(output, "\nThe point computed by the function is:\n");
   printPoint(output, p);

   fprintf(output, "\nThe error is %lf [cm]\n", computeError(p, TD));

   fprintf(output, "\n\n");

   return;
}

double computeError(Point *p, Point *TD)
{
   return sqrt(pow(p->x - TD->x, 2) + pow(p->y - TD->y, 2));
}

void printPoint (FILE* output, Point *p)
{
   if (p == NULL)
      return;

   fprintf(output, "\n");
   fprintf(output, "P.x = %lf [cm]\n", (double) p->x);
   fprintf(output, "P.y = %lf [cm]\n", (double) p->y);
   fprintf(output, "P.z = %lf [cm]\n", (double) p->z);

}

void printTimes(FILE* output, long double T1, long double T2)
{
   if ((T1 < 0) || (T2 < 0))
      return;

   fprintf(output, "T1 = %lf (10^-6)s\n", (double) T1);
   fprintf(output, "T2 = %lf (10^-6)s\n", (double) T2);
}

