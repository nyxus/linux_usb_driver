#include "gcv-usb-app.hpp"
#include "Config.h"


#include <iostream>

int main(int argc, const char* argv[])
{
	  if (argc < 2) {
    // report version
    std::cout << argv[0] << " Version " << VERSION_MAJOR << "."
              << VERSION_MINOR << "." 
              << VERSION_PATCH << std::endl;
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }
	gcv::foo();
    return 0;
}
