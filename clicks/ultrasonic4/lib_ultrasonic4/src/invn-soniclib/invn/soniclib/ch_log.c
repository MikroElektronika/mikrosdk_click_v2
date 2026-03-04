/*! \file ch_log.c
 \brief Internal driver functions to log informations on console

 The user should not need to edit this file.
 */

/*
 Copyright 2016-2023, InvenSense, Inc.  All rights reserved.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED.

 */
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <invn/soniclib/ch_log.h>
#include <invn/soniclib/chirp_bsp.h>

#if defined(__GNUC__)
#define DEFINE_FCT_PRINTF_LIKE(arg_fmt_position, first_varg_position)                                                  \
	__attribute__((format(printf, arg_fmt_position, first_varg_position)))
#else
#define DEFINE_FCT_PRINTF_LIKE(arg_fmt_position, first_varg_position)
#endif

#define MODULE_NAME_LENGTH   7 /* log module name max size in char */
#define FUNC_NAME_LENGTH     30
#define HEADER_LENGTH        (1 + 1 + MODULE_NAME_LENGTH + 1 + FUNC_NAME_LENGTH + 1)
#define INDEX_LOG_MESSAGE    (HEADER_LENGTH - 1)
#define END_OF_LINE_PATTERN  "\r\n"
#define END_OF_LINE_LENGTH   2
#define MESSAGE_MINIMAL_SIZE 50

#if IS_CH_LOG_USED

#if CH_LOG_BUFFER_SIZE < (HEADER_LENGTH + MESSAGE_MINIMAL_SIZE + END_OF_LINE_LENGTH)
#error Please define a greater size for CH_LOG_BUFFER_SIZE
#endif

static char buf_msg[CH_LOG_BUFFER_SIZE];
static uint16_t buf_idx = 0;

static inline void print(void) {
	chbsp_print_str(&buf_msg[0]);
	buf_idx = 0;
}

static DEFINE_FCT_PRINTF_LIKE(1, 0) int print_to_buf(const char *format, va_list va) {
	size_t buf_max_space_available;
	int rc = 0;

	for (uint8_t retry = 2; retry > 0; --retry) {
		buf_max_space_available = sizeof(buf_msg) - buf_idx;

		rc = vsnprintf(&buf_msg[buf_idx], buf_max_space_available, format, va);
		if (rc < 0) {
			/* encoding error , string not put to buf_msg*/

		} else if ((size_t)rc > buf_max_space_available) {
			/* Buffer is full, can't append new argument
			 * Print current buffer and rollover */
			buf_msg[buf_idx] = '\0';
			print();
		} else {
			buf_idx += rc;
			break;
		}
	}
	return rc;
}

static inline void add_header(const char level, const char *name, const char *func_name) {
	size_t buf_max_space_available;
	int rc = 0;

	for (uint8_t retry = 2; retry > 0; --retry) {
		buf_max_space_available = sizeof(buf_msg) - buf_idx;
		/* Write the header :
		   - 1 letter for the criticality,
		   - 1 space,
		   - module name space complemented if less than MODULE_NAME_LENGTH,
		   - 1 space,
		   - '\0' char */
		rc = snprintf(&buf_msg[buf_idx], buf_max_space_available, "%c %-*.*s %-*.*s ", level, MODULE_NAME_LENGTH,
		              MODULE_NAME_LENGTH, name, FUNC_NAME_LENGTH, FUNC_NAME_LENGTH, func_name);
		if (rc < 0) {
			/* encoding error , string not put to buf_msg*/
		} else if ((size_t)rc > buf_max_space_available) {
			/* Buffer is full, can't append new argument
			 * Print current buffer and rollover */
			buf_msg[buf_idx] = '\0';
			print();
		} else {
			buf_idx += rc;
			break;
		}
	}
}

static inline void add_eof(void) {
	const size_t buf_idx_eof_max = (sizeof(buf_msg) - END_OF_LINE_LENGTH - sizeof('\0'));

	if (buf_idx > buf_idx_eof_max) {
		buf_idx = buf_idx_eof_max;
	}
	/* Add the carriage return */
	memcpy(&buf_msg[buf_idx], END_OF_LINE_PATTERN, sizeof(END_OF_LINE_PATTERN));
	buf_msg[sizeof(buf_msg) - 1] = '\0'; /* be sure there is at least one '\0' in buffer */
}

DEFINE_FCT_PRINTF_LIKE(1, 2) void ch_log_printf(const char *format, ...) {
	va_list va;

	va_start(va, format);
	print_to_buf(format, va);
	va_end(va);

	print();
}

DEFINE_FCT_PRINTF_LIKE(1, 2) void ch_log_printf_eol(const char *format, ...) {
	va_list va;

	va_start(va, format);
	print_to_buf(format, va);
	va_end(va);

	add_eof();

	print();
}

DEFINE_FCT_PRINTF_LIKE(4, 5)
void ch_log_prefix_printf(const char level, const char *name, const char *func_name, const char *format, ...) {
	va_list va;

	buf_idx = 0;
	add_header(level, name, func_name);

	va_start(va, format);
	/* Copy all after the header */
	print_to_buf(format, va);
	va_end(va);

	add_eof();

	print();
}

DEFINE_FCT_PRINTF_LIKE(4, 5)
void ch_log_prefix_start(const char level, const char *name, const char *func_name, const char *format, ...) {
	va_list va;

	buf_idx = 0;
	add_header(level, name, func_name);

	buf_msg[sizeof(buf_msg) - 1] = '\0'; /* be sure there is at least one '\0' in buffer */
	va_start(va, format);
	print_to_buf(format, va);
	va_end(va);
}

DEFINE_FCT_PRINTF_LIKE(1, 2) void ch_log_start(const char *format, ...) {
	va_list va;

	buf_msg[sizeof(buf_msg) - 1] = '\0'; /* be sure there is at least one '\0' in buffer */
	va_start(va, format);
	/* Copy all after the header. Save room for the \r\n at the end of the string. */
	print_to_buf(format, va);
	va_end(va);
}

DEFINE_FCT_PRINTF_LIKE(1, 2) void ch_log_msg(const char *format, ...) {
	va_list va;

	buf_msg[sizeof(buf_msg) - 1] = '\0'; /* be sure there is at least one '\0' in buffer */
	va_start(va, format);
	print_to_buf(format, va);
	va_end(va);
}

void ch_log_end(void) {
	add_eof();
	print();
}

#endif /* IS_CH_LOG_USED */