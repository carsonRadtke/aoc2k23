#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "aoc.hpp"

static std::string s_get_number( const std::vector<std::string> & s, std::int64_t i,
                                 std::int64_t j )
{
  const char * ptr = s[i].c_str() + j;
  const char * end = ptr;
  while ( *end && std::isdigit( *end ) )
    end++;
  return std::string( ptr, end - ptr );
}

static std::int64_t s_start_of_number( const std::vector<std::string> & s, std::int64_t i, std::int64_t j )
{
  std::int64_t rv = j;
  while ( rv > 0 && std::isdigit( s[i][rv-1] ) )
  {
    rv--;
  }
  return rv;
}

static std::int64_t s_i = 0;
static std::pair<std::int64_t, std::int64_t>
s_find_gear_ratio( const std::vector<std::string> & s, std::int64_t i, std::int64_t j )
{
  std::int64_t count = 0;
  std::int64_t a, b;
  if ( j - 1 >= 0 && std::isdigit( s[i][j - 1] ) )
  {
    std::int64_t start = s_start_of_number( s, i, j - 1 );
    auto num = s_get_number( s, i, start );
    switch (count++)
    {
      case 0: a = std::atoi(num.c_str()); break;
      case 1: b = std::atoi(num.c_str()); break;
      default: return { 0, 0 };
    }
  }
  if ( j + 1 < s[i].size() && std::isdigit( s[i][j + 1] ) )
  {
    auto num = s_get_number( s, i, j + 1 );
    switch (count++)
    {
      case 0: a = std::atoi(num.c_str()); break;
      case 1: b = std::atoi(num.c_str()); break;
      default: return { 0, 0 };
    }
  }
  for ( std::int64_t x = -1; x <= 1; x++ )
  {
    if ( i - 1 >= 0 && j + x >= 0 && j + x < s[i - 1].size() &&
         std::isdigit( s[i - 1][j + x] ) )
    {
      std::int64_t start = s_start_of_number( s, i - 1, j + x );
      auto num = s_get_number( s, i - 1, start );
      switch (count++)
      {
        case 0: a = std::atoi(num.c_str()); break;
        case 1: b = std::atoi(num.c_str()); break;
        default: return { 0, 0 };
      }
      while (j+x < s[i-1].size() && std::isdigit(s[i-1][j+x])) x++;
    }
  }
  for ( std::int64_t x = -1; x <= 1; x++ )
  {
    if ( i + 1 < s.size() && j + x >= 0 && j + x < s[i + 1].size() &&
         std::isdigit( s[i + 1][j + x] ) )
    {
      std::int64_t start = s_start_of_number( s, i + 1, j + x );
      auto num = s_get_number( s, i + 1, start );
      switch (count++)
      {
        case 0: a = std::atoi(num.c_str()); break;
        case 1: b = std::atoi(num.c_str()); break;
        default: return { 0, 0 };
      }
      while (j+x < s[i+1].size() && std::isdigit(s[i+1][j+x])) x++;
    }
  }
  if ( count == 2 )
  {
    std::cout << a << " | " << b << "\n";
    return { a, b };
  }
  return { 0, 0 };
}

static std::int64_t s_gear_ratios( const std::string & input_file )
{
  auto fs = std::ifstream( input_file );
  if ( !fs.is_open() )
    aoc_exit_error( "could not open input file" );
  std::vector<std::string> lines;
  std::int64_t part_no_sum = 0;
  while ( !fs.eof() )
  {
    std::string buffer;
    fs >> buffer;
    lines.emplace_back( buffer );
  }
  for ( std::int64_t i = 0; i < lines.size(); i++ )
  {
    auto line = lines[i];
    for ( std::int64_t j = 0; j < line.size(); j++ )
    {
      if ( line[j] == '*' )
      {
        std::cout << ++s_i << "\n";
        auto [rat1, rat2] = s_find_gear_ratio( lines, i, j );
        part_no_sum += rat1 * rat2;
      }
    }
  }
  std::cout << part_no_sum << std::endl;
  fs.close();

  return EXIT_SUCCESS;
}

int main( int argc, const char * argv[] )
{
  if ( argc != 2 )
    aoc_exit_error( "missing input file" );
  return s_gear_ratios( argv[1] );
}
