#ifndef	_JVAL_H_
#define	_JVAL_H_

typedef union {
  int i;
  long l;
  float f;
  double d;
  char *s;
  char c;
} Jval;

extern Jval new_jval_i(int);
extern Jval new_jval_l(long);
extern Jval new_jval_f(float);
extern Jval new_jval_d(double);
extern Jval new_jval_s(char *);
extern Jval new_jval_c(char);

extern int jval_i(Jval);
extern long jval_l(Jval);
extern float jval_f(Jval);
extern double jval_d(Jval);
extern char *jval_s(Jval);
extern char jval_c(Jval);

#endif
