#pragma once

#include "assets.h"
#include "strutils.h"

void log(int log_level, char * log);

//output the log to a file. Should be done at unhandled exceptions, closing event, etc
//TODO write this
void cleanup_output_log(char * output_location);