#include <cstdint>

#include <format>
#include <fstream>
#include <sstream>
#include <string>

#include "aoc.hpp"

static std::vector<std::uint64_t> s_line_to_numbers( const std::string & line )
{
  std::vector<std::uint64_t> numbers;
  std::stringstream linestream( line );
  std::string buffer;
  linestream >> buffer; // ignore label
  while ( !linestream.eof() )
  {
    linestream >> buffer;
    numbers.emplace_back( std::atoi( buffer.c_str() ) );
  }
  return numbers;
}

static bool s_is_perfect_square( std::uint64_t x )
{
  auto sqrt = static_cast<std::uint64_t>( std::sqrt( x ) );
  return sqrt * sqrt == x;
}

static std::uint64_t s_name_of_day( const std::string & input_file )
{
  auto fs = std::ifstream( input_file );
  if ( !fs.is_open() )
    aoc_exit_error( "could not open input file" );
  std::string time_line;
  std::string distance_line;
  std::getline( fs, time_line );
  std::getline( fs, distance_line );
  fs.close();
  auto times = s_line_to_numbers( time_line );
  auto distances = s_line_to_numbers( distance_line );

  std::uint64_t rv = 1;
  for ( auto time_it = times.begin(), dist_it = distances.begin();
        time_it != times.end() && dist_it != distances.end();
        ++time_it, ++dist_it )
  {
    auto T = static_cast<double>( *time_it );
    auto D = static_cast<double>( *dist_it );
    auto lo_double = ( T - std::sqrt( T * T - 4 * D ) ) / 2.;
    auto hi_double = ( T + std::sqrt( T * T - 4 * D ) ) / 2.;
    std::uint64_t lo = static_cast<decltype( lo )>( std::ceil( lo_double ) );
    std::uint64_t hi = static_cast<decltype( lo )>( std::floor( hi_double ) );
    if ( s_is_perfect_square( ( *time_it ) * ( *time_it ) - 4 * ( *dist_it ) ) )
    {
      hi--;
      lo++;
    }
    rv *= ( hi - lo ) + 1;
  }
  std::cout << rv << std::endl;

  return EXIT_SUCCESS;
}

int main( int argc, const char * argv[] )
{
  if ( argc != 2 )
    aoc_exit_error( "missing input file" );
  return s_name_of_day( argv[1] );
}
