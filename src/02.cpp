#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>

#include "aoc.hpp"

struct GameData
{
  GameData( std::ifstream & fs )
      : m_max_red( 0 ), m_max_green( 0 ), m_max_blue( 0 )
  {
    parse( fs );
  }

  bool possibly_valid() const
  {
    return m_max_red <= 12 && m_max_green <= 13 && m_max_blue <= 14;
  }

  auto id() const { return m_id; }

private:
  std::int64_t parse_game_id( std::ifstream & fs ) const
  {
    std::string buffer;
    fs >> buffer; // ignore "Game"
    fs >> buffer; // number followed by ':'
    return std::atoi( buffer.substr( 0, buffer.size() - 1 ).c_str() );
  }

  bool parse_round( std::ifstream & fs )
  {
    std::int64_t red = 0;
    std::int64_t blue = 0;
    std::int64_t green = 0;

    std::int64_t count;
    std::string buffer;
    do
    {
      fs >> buffer; // number
      count = std::atoi( buffer.c_str() );
      fs >> buffer; // color followed by ';', ',' or '\n'
      if ( buffer.starts_with( "red" ) )
        red += count;
      if ( buffer.starts_with( "green" ) )
        green += count;
      if ( buffer.starts_with( "blue" ) )
        blue += count;
    } while ( buffer.find( ',' ) != std::string::npos );

    m_max_red = std::max( red, m_max_red );
    m_max_green = std::max( green, m_max_green );
    m_max_blue = std::max( blue, m_max_blue );

    return buffer.find( ';' ) != std::string::npos;
  }

  void parse( std::ifstream & fs )
  {
    m_id = parse_game_id( fs );
    while ( parse_round( fs ) )
      ;
    std::cout << m_id << " -> "
              << "r(" << m_max_red << ") "
              << "g(" << m_max_green << ") "
              << "b(" << m_max_blue << ") "
              << "\n";
  }

  std::int64_t m_id;
  std::int64_t m_max_red;
  std::int64_t m_max_green;
  std::int64_t m_max_blue;
};

int s_cube_conundrum( const std::string & input_file )
{
  auto fs = std::ifstream( input_file );
  if ( !fs.is_open() )
    aoc_exit_error( "could not open input file" );

  std::int64_t sum_of_ids = 0;
  while ( !fs.eof() )
  {
    GameData gd( fs );
    if ( gd.possibly_valid() )
    {
      sum_of_ids += gd.id();
    }
  }
  fs.close();
  std::cout << sum_of_ids << std::endl;

  return EXIT_SUCCESS;
}

int main( int argc, const char * argv[] )
{
  if ( argc != 2 )
    aoc_exit_error( "missing input file" );
  return s_cube_conundrum( argv[1] );
}