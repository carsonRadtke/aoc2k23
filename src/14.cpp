#include <assert.h>

#include <fstream>
#include <string>

#include "aoc.hpp"

#define ROUND_ROCK 'O'
#define CUBE_ROCK '#'
#define EMPTY '.'

class PRD
{
public:
  enum TiltDir
  {
    TiltNorth,
    TiltSouth,
    TiltWest,
    TiltEast,
  };

  void add_row( const std::string & row ) { m_rows.emplace_back( row ); }

  void tilt( const TiltDir & dir )
  {
    assert( dir == TiltNorth );
    for ( int i = 1; i < m_rows.size(); i++ )
    {
      for ( int j = 0; j < m_rows[i].size(); j++ )
      {
        if ( m_rows[i][j] == ROUND_ROCK )
        {
          int tmp_i = i - 1;
          while ( m_rows[tmp_i][j] == EMPTY )
          {
            m_rows[tmp_i + 1][j] = EMPTY;
            m_rows[tmp_i][j] = ROUND_ROCK;
            if ( tmp_i == 0 )
              break;
            tmp_i--;
          }
        }
      }
    }
  }

  size_t load() const
  {
    size_t rv = 0;
    int i = m_rows.size();
    ;
    for ( auto row : m_rows )
    {
      int load = row.size();
      for ( auto ch : row )
      {
        if ( ch != ROUND_ROCK )
          load--;
      }
      rv += load * i;
      i--;
    }
    return rv;
  }

  void dump() const
  {
    for ( auto row : m_rows )
    {
      std::cout << row << "\n";
    }
  }

private:
  std::vector<std::string> m_rows;
};

static int s_name_of_day( const std::string & input_file )
{
  auto fs = std::ifstream( input_file );
  if ( !fs.is_open() )
    aoc_exit_error( "could not open input file" );

  PRD prd;
  while ( !fs.eof() )
  {
    std::string line;
    fs >> line;
    if ( line.size() > 0 )
      prd.add_row( line );
  }
  fs.close();

  prd.tilt( PRD::TiltNorth );
  std::cout << prd.load() << std::endl;

  return EXIT_SUCCESS;
}

int main( int argc, const char * argv[] )
{
  if ( argc != 2 )
    aoc_exit_error( "missing input file" );
  return s_name_of_day( argv[1] );
}
