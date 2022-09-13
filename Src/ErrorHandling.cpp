#include "ErrorHandling.h"

#include <cstdlib>
#include <iostream>

//-----------------------------------------------------------------------------

void ErrorHandling::ExitWithErrorMessage(const char* errorMessage) {
  std::cout << errorMessage << std::endl;
  exit(1);
}

//-----------------------------------------------------------------------------
