#ifndef DATATYPES_H
#define DATATYPES_H

struct Time {
  unsigned int Hour;
  unsigned int Minute;
};


enum AlertMode {
  AlertMode_Normal,
  AlertMode_Continuous
};


#endif
