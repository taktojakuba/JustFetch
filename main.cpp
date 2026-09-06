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

string get_color_code(bool ascii)
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
        return ascii ? "\033[1;37m" : "\033[1;33m";
      else
        return ascii ? "\033[1;30m" : "\033[1;34m";
    }
  }

  const char* colorerm = getenv("COLORTERM");
  if (colorerm && string(colorerm) == "truecolor")
    return ascii ? "\033[38;2;180;200;255m" : "\033[38;2;255;190;150m";

  const char* term_env = getenv("TERM");
  if (term_env)
  {
    string term(term_env);
    if (term.find("256color") != string::npos)
      return ascii ? "\033[38;5;117m" : "\033[38;5;173m";
    if (term.find("color") != string::npos)
      return ascii ? "\033[1;36m" : "\033[1;35m";
  }

  return ascii ? "\033[1;37m" : "\033[1;33m";
}

int main(int argc, char* argv[])
{
  const string color = get_color_code(true);
  const string label_color = get_color_code(false);
  const string reset = "\033[0m";

  array<string, 8> labels = {
    "Host", "OS", "Kernel", "Shell", "Term", "WM", "Uptime", "Packages"
  };
  array<string, 8> values = {
    get_hostname(),
    get_osname(),
    get_kernel(),
    get_shell(),
    get_term(),
    get_wm(),
    get_uptime(),
    get_packages()
  };

  if (argc < 2)
  {
    for (int i = 0; i < labels.size(); i++)
    {
      cout << label_color << labels[i] << reset << ": " << values[i] << endl;
    }
    return 0;
  }

  ifstream file(argv[1]);
  string line;
  size_t i = 0;
  while (getline(file, line))
  {
    cout << color << line << reset;
    if (i < values.size())
    {
      cout << "  " << label_color << labels[i] << reset << ": " << values[i];
    }
    cout << endl;
    ++i;
  }
  return 0;
}
