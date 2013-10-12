//
//  logc.h
//  logc
//
//  Created by cooniur on 10/11/13.
//  Copyright (c) 2013 cooniur. All rights reserved.
//

#ifndef logc_logc_h
#define logc_logc_h

// Defines a log file object
typedef struct __logc_t__ *logc_t;

// Defines the log level enum
typedef enum
{
	LOGC_LVL_INFO = 0,
	LOGC_LVL_WARNING,
	LOGC_LVL_ERROR
} logc_level_t;

// Initialize a log file object
logc_t logc_init(const char* log_file);

// Add a message to a log file
void logc_add(logc_t log, logc_level_t level, const char* message);

// Free the log file object, release memory used
void logc_free(logc_t* log);

// Set log level string
void logc_settings_set_lvl_text(logc_t log, logc_level_t lvl, const char* text);


#endif
