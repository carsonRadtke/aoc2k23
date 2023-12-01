#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

[[noreturn]] void s_exit_error(const std::string & error)
{
  std::cerr << error << std::endl;
  exit(EXIT_FAILURE);
}

static std::int64_t s_calibration_value(const std::string & line)
{
  char first = '\0';
  char last = '\0';
  for (auto c : line)
  {
    if (std::isdigit(c))
    {
      if (first == '\0')
      {
        first = c;
      }
      last = c;
    }
  }
  if (first == '\0' || last == '\0') 
  {
    s_exit_error("did not find any digits");
  }
  
  return 10 * (first - '0') + (last - '0');
}

static int s_trebuchet(const std::string & input_file)
{
  auto fs = std::ifstream(input_file);
  if (!fs.is_open()) s_exit_error("could not open input file");

  std::int64_t calibration_value = 0;
  while (!fs.eof())
  {
    std::string line;
    fs >> line;
    calibration_value += s_calibration_value(line);
  }
  std::cout << calibration_value << std::endl;

  return EXIT_SUCCESS;
}

int main(int argc, const char * argv[])
{
  if (argc != 2) s_exit_error("missing input file");
  return s_trebuchet(argv[1]);
}
