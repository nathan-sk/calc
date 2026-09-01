#include <string_view>

#ifndef COMMANDS_H
#define COMMANDS_H

enum Command{ command, notCommand, quit };
Command doCommand( std::string_view input );

#endif
