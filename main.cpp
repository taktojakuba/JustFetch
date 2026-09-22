#include <iostream>
#include <fstream>
#include <string>
#include <array>

#include "modules/hostname.h"
#include "modules/osname.h"
#include "modules/kernel.h"
#include "modules/shell.h"
#include "modules/wm.h"
#include "modules/term.h"
#include "modules/uptime.h"
#include "modules/packages.h"
using namespace std;

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
  if (argc < 2) 
  {
    for(int i = 0;i<info.size();i++){
      cout << info[i] << endl;
    }
    return 0;
  }
  //get file content lines
  ifstream file(argv[1]);
  string line;
  size_t i = 0;
  while (getline(file, line)) {
    cout << line;
    if (i < info.size()) {
        cout << "  " << info[i];
    }
    cout << endl;
    ++i;
}
  return 0;
}
