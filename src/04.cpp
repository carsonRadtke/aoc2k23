#include <cstdlib>
#include <fstream>
#include <iostream>

#include "aoc.hpp"

class Card
{
public:
  Card( std::ifstream & fs ) { parse( fs ); }

  int value() const
  {
    int rv = 0;
    for ( auto num : m_numbers )
    {
      for ( auto winning : m_winning_numbers )
      {
        if ( num == winning )
        {
          if ( rv == 0 )
            rv = 1;
          else
            rv *= 2;
        }
      }
    }
    return rv;
  }

  int matches() const
  {
    int rv = 0;
    for ( auto num : m_numbers )
    {
      for ( auto winning : m_winning_numbers )
      {
        if ( num == winning )
        {
          rv++;
        }
      }
    }
    return rv;
  }

private:
  void parse( std::ifstream & fs )
  {
    m_id = parse_game_id( fs );
    std::string buffer;
    for ( int i = 0; i < 10; i++ )
    {
      fs >> buffer;
      m_winning_numbers.emplace_back( std::atoi( buffer.c_str() ) );
    }
    fs >> buffer; // ignore '|'
    for ( int i = 0; i < 25; i++ )
    {
      fs >> buffer;
      m_numbers.emplace_back( std::atoi( buffer.c_str() ) );
    }
  }

  std::int64_t parse_game_id( std::ifstream & fs ) const
  {
    std::string buffer;
    fs >> buffer; // ignore "Game"
    fs >> buffer; // number followed by ':'
    return std::atoi( buffer.substr( 0, buffer.size() - 1 ).c_str() );
  }

private:
  int m_id;
  std::vector<int> m_winning_numbers;
  std::vector<int> m_numbers;
};

static int s_scratchcards( const std::string & input_file )
{
  auto fs = std::ifstream( input_file );
  if ( !fs.is_open() )
    aoc_exit_error( "could not open input file" );
  std::vector<int> scratches( 206 );
  for ( int i = 0; i < scratches.size(); i++ )
    scratches[i] = 0;
  int id = 0;
  while ( !fs.eof() )
  {
    scratches[id]++;
    int matches = Card( fs ).matches();
    for ( int i = 0; i < matches; i++ )
    {
      scratches[id + i + 1] += scratches[id];
    }
    id++;
  }
  int total_points = 0;
  for ( auto scratch : scratches )
  {
    total_points += scratch;
  }
  std::cout << total_points << std::endl;
  fs.close();

  return EXIT_SUCCESS;
}

int main( int argc, const char * argv[] )
{
  if ( argc != 2 )
    aoc_exit_error( "missing input file" );
  return s_scratchcards( argv[1] );
}
