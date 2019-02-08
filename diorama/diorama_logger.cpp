#include "diorama_logger.h"

#include <iostream>

using namespace std;

void logf(int log_level, char * log, char*... r)
{
	printf(log, r);
}
