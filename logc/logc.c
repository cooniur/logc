//
//  logc.c
//  logc
//
//  Created by Tongliang Liu on 10/11/13.
//  Copyright (c) 2013 cooniur. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "logc.h"

#define LOGC_LVL_INFO_STR				"[Info]"
#define LOGC_LVL_WARNING_STR			"{Warning}"
#define LOGC_LVL_ERROR_STR				"<Error>"
#define LOGC_TIME_FORMAT_STR			"%c %Z"
#define LOGC_TIME_FORMAT_STR_LENGTH		(255)
#define LOGC_MESSAGE_FORMAT				"[%s]%s: %s\n"

// Defines the logc settings struc
struct __logc_settings_t__
{
	char *lvl_info_str;
	char *lvl_warning_str;
	char *lvl_error_str;
	char *lvl_time_format_str;
};

// Defines the logc object
struct __logc_t__
{
	char *log_file;
	FILE *fp;
	struct __logc_settings_t__ *settings;
};

void __logc_strcpy(char **dest, const char *src)
{
	if (dest == NULL || src == NULL)
		return;
	
	if (*dest != NULL)
		free(*dest);

	size_t len = strlen(src);
	*dest = (char*)calloc(len+1, sizeof(char));
	strcpy(*dest, src);
}

char* __logc_get_current_time(logc_t log)
{
	time_t rawtime;
	time(&rawtime);
	struct tm * timeinfo = localtime(&rawtime);
	char* timestr = (char*)calloc(LOGC_TIME_FORMAT_STR_LENGTH, sizeof(char));
	strftime(timestr, LOGC_TIME_FORMAT_STR_LENGTH, log->settings->lvl_time_format_str, timeinfo);
	return timestr;
}

char* __logc_get_lvl_str(logc_t log, logc_level_t level)
{
	switch (level)
	{
		case LOGC_LVL_ERROR:
			return log->settings->lvl_error_str;
			
		case LOGC_LVL_WARNING:
			return log->settings->lvl_warning_str;
			
		case LOGC_LVL_INFO:
		default:
			return log->settings->lvl_info_str;
	}
}

void __logc_settings_init(logc_t log)
{
	if (log == NULL)
		return;
	
	log->settings = (struct __logc_settings_t__*)calloc(1, sizeof(struct __logc_settings_t__));
	__logc_strcpy(&log->settings->lvl_info_str, LOGC_LVL_INFO_STR);
	__logc_strcpy(&log->settings->lvl_warning_str, LOGC_LVL_WARNING_STR);
	__logc_strcpy(&log->settings->lvl_error_str, LOGC_LVL_ERROR_STR);
	__logc_strcpy(&log->settings->lvl_time_format_str, LOGC_TIME_FORMAT_STR);
}

void __logc_settings_free(logc_t log)
{
	if (log == NULL || log->settings == NULL)
		return;
	
	free(log->settings->lvl_error_str);
	free(log->settings->lvl_info_str);
	free(log->settings->lvl_warning_str);
	free(log->settings->lvl_time_format_str);
	log->settings->lvl_error_str = log->settings->lvl_info_str
		= log->settings->lvl_warning_str = log->settings->lvl_time_format_str = NULL;

	free(log->settings);
	log->settings = NULL;
}

void logc_settings_set_lvl_text(logc_t log, logc_level_t lvl, const char* text)
{
	switch (lvl) {
		case LOGC_LVL_ERROR:
			__logc_strcpy(&log->settings->lvl_error_str, text);
			break;
		
		case LOGC_LVL_WARNING:
			__logc_strcpy(&log->settings->lvl_warning_str, text);
			break;
			
		case LOGC_LVL_INFO:
		default:
			__logc_strcpy(&log->settings->lvl_info_str, text);
			break;
	}
}

logc_t logc_init(const char* log_file)
{
	logc_t log = (logc_t)calloc(1, sizeof(struct __logc_t__));
	
	__logc_settings_init(log);
	
	__logc_strcpy(&log->log_file, log_file);
	log->fp = fopen(log->log_file, "a");
	
	return log;
}

void logc_add(logc_t log, logc_level_t level, const char* message)
{
	if (log == NULL || log->fp == NULL)
		return;
	
	char *lvl = __logc_get_lvl_str(log, level);
	char *time = __logc_get_current_time(log);
	
	fprintf(log->fp, LOGC_MESSAGE_FORMAT, time, lvl, message);
	fflush(log->fp);

	free(time);
}

void logc_free(logc_t* log)
{
	if (log == NULL || *log == NULL)
		return;
	
	fclose((*log)->fp);
	free((*log)->log_file);
	__logc_settings_free(*log);
	free(*log);
	*log = NULL;
}
