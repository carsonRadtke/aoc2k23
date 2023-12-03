#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "aoc.hpp"

static std::string s_get_number( const std::vector<std::string> & s, int i,
                                 int j )
{
  const char * ptr = s[i].c_str() + j;
  const char * end = ptr;
  while ( *end && std::isdigit( *end ) )
    end++;
  return std::string( ptr, end - ptr );
}

static int s_start_of_number( const std::vector<std::string> & s, int i, int j )
{
  int rv = j;
  while ( rv > 0 && std::isdigit( s[i][rv-1] ) )
  {
    rv--;
  }
  return rv;
}

static std::pair<int, int>
s_find_gear_ratio( const std::vector<std::string> & s, int i, int j )
{
  int count = 0;
  int a, b;
  if ( j - 1 >= 0 && std::isdigit( s[i][j - 1] ) )
  {
    int start = s_start_of_number( s, i, j - 1 );
    auto num = s_get_number( s, i, start );
    if ( count == 0 )
      a = std::atoi( num.c_str() );
    else
      b = std::atoi( num.c_str() );
    count++;
  }
  if ( j + 1 < s[i].size() && std::isdigit( s[i][j + 1] ) )
  {
    auto num = s_get_number( s, i, j + 1 );
    if ( count == 0 )
      a = std::atoi( num.c_str() );
    else
      b = std::atoi( num.c_str() );
    count++;
  }
  for ( int x = -1; x <= 1; x++ )
  {
    if ( i - 1 >= 0 && j + x >= 0 && j + x < s[i - 1].size() &&
         std::isdigit( s[i - 1][j + x] ) )
    {
      int start = s_start_of_number( s, i - 1, j + x );
      auto num = s_get_number( s, i - 1, start );
      if ( count == 0 )
        a = std::atoi( num.c_str() );
      else
        b = std::atoi( num.c_str() );
      count++;
      x += num.size();
    }
  }
  for ( int x = -1; x <= 1; x++ )
  {
    if ( i + 1 < s.size() && j + x >= 0 && j + x < s[i + 1].size() &&
         std::isdigit( s[i + 1][j + x] ) )
    {
      int start = s_start_of_number( s, i + 1, j + x );
      auto num = s_get_number( s, i + 1, start );
      if ( count == 0 )
        a = std::atoi( num.c_str() );
      else
        b = std::atoi( num.c_str() );
      count++;
      x += num.size();
    }
  }
  if ( count == 2 )
    return { a, b };
  return { 0, 0 };
}

static int s_gear_ratios( const std::string & input_file )
{
  auto fs = std::ifstream( input_file );
  if ( !fs.is_open() )
    aoc_exit_error( "could not open input file" );
  std::vector<std::string> lines;
  int part_no_sum = 0;
  while ( !fs.eof() )
  {
    std::string buffer;
    fs >> buffer;
    lines.emplace_back( buffer );
  }
  for ( int i = 0; i < lines.size(); i++ )
  {
    auto line = lines[i];
    for ( int j = 0; j < line.size(); j++ )
    {
      if ( line[j] == '*' )
      {
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
