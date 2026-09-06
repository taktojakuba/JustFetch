#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <cstdlib>

#include "modules/hostname.h"
#include "modules/osname.h"
#include "modules/kernel.h"
#include "modules/shell.h"
#include "modules/wm.h"
#include "modules/term.h"
#include "modules/uptime.h"
#include "modules/packages.h"

using namespace std;

string get_color_code()
{
  const char* colorfgbg = getenv("COLORFGBG");
  if (colorfgbg)
  {
    string cfbg(colorfgbg);
    size_t last_sep = cfbg.find_last_of(";");
    if (last_sep != string::npos)
    {
      string bg = cfbg.substr(last_sep + 1);
      if (bg == "0" || bg == "1" || bg == "2" || bg == "3" || bg == "4")
        return "\033[1;37m"; // dark background -> white/bright
      else
        return "\033[1;30m"; // light background -> black/bright
    }
  }

  const char* colorerm = getenv("COLORTERM");
  if (colorerm && string(colorerm) == "truecolor")
    return "\033[38;2;180;200;255m"; // soft pastel blue for truecolor

  const char* term_env = getenv("TERM");
  if (term_env)
  {
    string term(term_env);
    if (term.find("256color") != string::npos)
      return "\033[38;5;117m"; // muted pastel (256-color)
    if (term.find("color") != string::npos)
      return "\033[1;36m"; // basic 8-color bright cyan
  }

  return "\033[1;37m"; // default bright
}

int main(int argc, char* argv[])
{
  array<string, 8> info = {
    "Host: " + get_hostname(),
    "OS: " + get_osname(),
    "Kernel: " + get_kernel(),
    "Shell: " + get_shell(),
    "Term: " + get_term(),
    "WM: " + get_wm(),
    "Uptime: " + get_uptime(),
    "Packages: " + get_packages()
  };

  const string color = get_color_code();
  const string reset = "\033[0m";

  if (argc < 2)
  {
    for (int i = 0; i < info.size(); i++)
    {
      cout << info[i] << endl;
    }
    return 0;
  }

  ifstream file(argv[1]);
  string line;
  size_t i = 0;
  while (getline(file, line))
  {
    cout << color << line << reset;
    if (i < info.size())
    {
      cout << "  " << info[i];
    }
    cout << endl;
    ++i;
  }
  return 0;
}
