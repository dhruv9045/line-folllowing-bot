#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

int P, I, D;

int PID(int err, int lastErr) {
  int kP, kI, kD;
  if (err > 3) {
    kP = 20;
    kI = kD = 0;
  } else {
    kP = 10;
    kI = kD = 0;
  }
  P = kP * err;
  I += err;
  D = kD * (err - lastErr);
  return abs(P + (kI * I) + D);
}

#undef kP
#undef kI
#undef kD

#endif
