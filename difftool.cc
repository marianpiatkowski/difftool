#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <array>
#include <cassert>

/** \brief Mimic git difftool outside of git.
 *
 *  \author Marian Piatkowski
 */

int main(int argc, char** argv)
{
  if(argc < 3)
  {
    std::cerr << "Usage: difftool [OPTION]... FILES" << std::endl;
    return 1;
  }
  // invoke diff with brief info
  std::string system_command = "diff -q";
  for(int i=1; i<argc; i++)
  {
    system_command.append(" ");
    system_command.append(argv[i]);
  }
  // write output of diff to temp file in order to examine its content afterwards
  system_command.append(" > temp.out");
  std::system(system_command.c_str());
  std::ifstream infile("temp.out");
  std::string buffer;
  if(infile.is_open())
  {
    while(std::getline(infile, buffer))
    {
      std::cout << buffer << std::endl;
      std::istringstream iss(buffer);
      // check if line begins with 'Files'
      std::string first_sub;
      iss >> first_sub;
      if(first_sub == "Files")
      {
        std::string file1, file2;
        iss >> file1;
        iss >> file2; iss >> file2;
        // test invocation with opendiff
        std::array<char,100> answer;
        std::cout << "Launch 'opendiff' [Y/n]? ";
        std::fgets(&answer[0], answer.size(), stdin);
        if(answer[0] == 'y' or answer[0] == 'Y' or answer[0] == '\n')
        {
          std::ostringstream diff_ext_cmd;
          diff_ext_cmd << "opendiff " << file1 << " " << file2;
          std::system(diff_ext_cmd.str().c_str());
        }
      }
    }
    infile.close();
  }
  // delete temp file at the end
  std::system("rm temp.out");
  return 0;
}
