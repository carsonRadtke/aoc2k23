#ifndef AOC_H
#define AOC_H

#include <cstdlib>
#include <iostream>
#include <string>

[[noreturn]] inline void aoc_exit_error( const std::string & error )
{
  std::cerr << error << std::endl;
  exit( EXIT_FAILURE );
}

#endif /* AOC_H */