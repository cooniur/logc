//
//  main.c
//  logc
//
//  Created by Tongliang Liu on 10/11/13.
//  Copyright (c) 2013 cooniur. All rights reserved.
//

#include <stdio.h>
#include "logc.h"

int main(int argc, const char * argv[])
{
	logc_t log = logc_init("/Users/cooniur/Desktop/log.txt");
	printf("%X\n", (unsigned int)(void*)log);

	logc_add(log, LOGC_LVL_INFO, "This is an information message with default level text.");
	logc_add(log, LOGC_LVL_ERROR, "This is an error message with default level text.");
	logc_add(log, LOGC_LVL_WARNING, "This is a warning message with default level text.");
	
	logc_settings_set_lvl_text(log, LOGC_LVL_INFO, "Custom Info");
	logc_settings_set_lvl_text(log, LOGC_LVL_ERROR, "Custom Error");
	logc_settings_set_lvl_text(log, LOGC_LVL_WARNING, "Custom Warning");
	
	logc_add(log, LOGC_LVL_INFO, "This is an information message with custom level text.");
	logc_add(log, LOGC_LVL_ERROR, "This is an error message with custom level text.");
	logc_add(log, LOGC_LVL_WARNING, "This is a warning message with custom level text.");
	
	logc_free(&log);
	
	printf("%X\n", (unsigned int)(void*)log);

    return 0;
}

