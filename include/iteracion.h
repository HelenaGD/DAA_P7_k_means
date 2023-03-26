#pragma once

#include <iostream>
#include <vector>

using namespace std;

struct Iteracion {
  string Identificador_;
  int m_;
  int k_;
  int ejecuciones_;
  double sse_;
  double tiempo_;
};