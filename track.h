#ifndef TRACK_H
#define TRACK_H

/**
 *
 *                      y ^
 *                        |
 * _______|_______________|____>__________|_________
 *        |               |    x          |
 *        |<------------->|<------------->|
 *        |       e       |       e       |
 *        C1              T               C2
 *
 */

typedef struct Point Point;
struct Point {
  double x;
  double y;
  double z;
};

/**
 * Track()
 *
 * @brief: compute the point where the Tracker device is situated from ellapsed
 *         times.
 *
 * @param: T1 - The time ellapsed between the moment the transmitter T sent
 *              the signal and the moment the right sensor C1 received the
 *              signal back. Given in 10^(-6) second.
 * @param: T2 - The time ellapsed between the moment the transmitter T sent
 *              the signal and the moment the left  sensor C2 received the
 *              signal back. Given in 10^(-6) second.
 * @param: p  - The point to fill with (x, y) answer. At the end of the
 *              function, p.x and p.y contain the coordinate of the tracking
 *              device.
 *
 * @return: 0 if no error occurs
 *          an error code in case of failure.
 */
int track (const long double T1, const long double T2, Point* p);

#endif

