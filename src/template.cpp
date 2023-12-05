#include <fstream>
#include <string>

#include "aoc.hpp"

static int s_name_of_day( const std::string & input_file )
{
  auto fs = std::ifstream( input_file );
  if ( !fs.is_open() )
    aoc_exit_error( "could not open input file" );

  while ( !fs.eof() )
  {
    std::string line;
    fs >> line;
  }
  fs.close();

  return EXIT_SUCCESS;
}

int main( int argc, const char * argv[] )
{
  if ( argc != 2 )
    aoc_exit_error( "missing input file" );
  return s_name_of_day( argv[1] );
}
