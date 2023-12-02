#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "aoc.hpp"

static std::vector<std::string> s_english_numbers = {
    "zero", "one", "two",   "three", "four",
    "five", "six", "seven", "eight", "nine" };

int8_t s_english_number( const char * ptr )
{
  int8_t rv = 0;
  for ( auto word : s_english_numbers )
  {
    if ( std::strncmp( word.data(), ptr, word.length() ) == 0 )
      return rv;
    rv++;
  }
  return -1;
}

int8_t s_get_last_digit( const std::string & line )
{
  const char * data = line.data();
  const char * ptr = data + line.size() - 1;
  while ( ptr >= data )
  {
    if ( std::isdigit( *ptr ) )
      return *ptr - '0';
    int8_t english_number = s_english_number( ptr );
    if ( english_number >= 0 )
      return english_number;
    ptr--;
  }
  return -1;
}

int8_t s_get_first_digit( const std::string & line )
{
  const char * data = line.data();
  const char * ptr = data;
  while ( *ptr )
  {
    if ( std::isdigit( *ptr ) )
      return *ptr - '0';
    int8_t english_number = s_english_number( ptr );
    if ( english_number >= 0 )
      return english_number;
    ptr++;
  }
  return -1;
}

static std::int64_t s_calibration_value( const std::string & line )
{
  int8_t first = s_get_first_digit( line );
  int8_t last = s_get_last_digit( line );
  if ( first == '\0' || last == '\0' )
  {
    aoc_exit_error( "did not find any digits" );
  }

  return 10 * first + last;
}

static int s_trebuchet( const std::string & input_file )
{
  auto fs = std::ifstream( input_file );
  if ( !fs.is_open() )
    aoc_exit_error( "could not open input file" );

  std::int64_t calibration_value = 0;
  while ( !fs.eof() )
  {
    std::string line;
    fs >> line;
    calibration_value += s_calibration_value( line );
  }
  fs.close();
  std::cout << calibration_value << std::endl;

  return EXIT_SUCCESS;
}

int main( int argc, const char * argv[] )
{
  if ( argc != 2 )
    aoc_exit_error( "missing input file" );
  return s_trebuchet( argv[1] );
}
