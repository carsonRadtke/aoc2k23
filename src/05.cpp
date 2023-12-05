#include <cstdint>
#include <fstream>
#include <limits>
#include <map>
#include <sstream>
#include <string>

#include "aoc.hpp"

class SomeMap
{
public:
  SomeMap( std::ifstream & fs )
  {
    std::string line;
    std::getline( fs, line ); // ignore map description
    do
    {
      std::getline( fs, line );
      if ( line.size() == 0 )
        return;
      std::stringstream linestream( line );

      std::string buffer;
      linestream >> buffer;
      auto dest = std::atoi( buffer.c_str() );
      linestream >> buffer;
      auto source = std::atoi( buffer.c_str() );
      linestream >> buffer;
      auto range = std::atoi( buffer.c_str() );
      this->add_entry( dest, source, range );
    } while ( !fs.eof() && line.size() > 0 );
  }

  std::uint64_t operator()( std::uint64_t x ) const
  {
    std::uint64_t rv = x;
    for ( auto [dest, source, range] : m_entries )
    {
      if ( x - source <= range && x - source >= 0 )
      {
        rv = x - source + dest;
        break;
      }
    }
    return rv;
  }

  void add_entry( std::uint64_t dest, std::uint64_t source,
                  std::uint64_t range )
  {
    m_entries
        .emplace_back<std::tuple<std::uint64_t, std::uint64_t, std::uint64_t>>(
            { dest, source, range } );
  }

private:
  std::vector<std::tuple<std::uint64_t, std::uint64_t, std::uint64_t>>
      m_entries;
};

static void s_read_seeds( std::ifstream & fs,
                          std::vector<std::uint64_t> & seeds )
{
  std::string line;
  std::getline( fs, line );
  std::stringstream linestream( line );

  std::string buffer;
  linestream >> buffer; // ignore 'seeds:'
  while ( !linestream.eof() )
  {
    linestream >> buffer;
    seeds.emplace_back( std::atoi( buffer.c_str() ) );
  }
  std::getline( fs, line ); // skip empty line
}

static std::uint64_t s_name_of_day( const std::string & input_file )
{
  auto fs = std::ifstream( input_file );
  if ( !fs.is_open() )
    aoc_exit_error( "could not open input file" );

  std::vector<std::uint64_t> seeds;
  s_read_seeds( fs, seeds );
  SomeMap seed2soil( fs );
  SomeMap soil2fert( fs );
  SomeMap fert2water( fs );
  SomeMap water2light( fs );
  SomeMap light2temp( fs );
  SomeMap temp2humidity( fs );
  SomeMap humidity2loc( fs );

  std::uint64_t min = std::numeric_limits<std::uint64_t>::max();
  for ( auto seed : seeds )
  {
    min = std::min( min,
                    humidity2loc( temp2humidity( light2temp( water2light(
                        fert2water( soil2fert( seed2soil( seed ) ) ) ) ) ) ) );
  }
  std::cout << min << "\n";

  fs.close();

  return EXIT_SUCCESS;
}

int main( int argc, const char * argv[] )
{
  if ( argc != 2 )
    aoc_exit_error( "missing input file" );
  return s_name_of_day( argv[1] );
}
