/*! \file ch_log.h
 *
 * \brief Functions to handle log level in Soniclib driver.
 *
 * You should not need to edit this file. Doing so will reduce your ability
 * to benefit from future enhancements and releases from Chirp.
 *
 */

/*
 Copyright 2016-2023, InvenSense, Inc.  All rights reserved.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED.
*/
#ifndef CH_LOG_H_
#define CH_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define CH_LOG_LEVEL_TRACE   0
#define CH_LOG_LEVEL_DEBUG   1
#define CH_LOG_LEVEL_INFO    2
#define CH_LOG_LEVEL_WARNING 3
#define CH_LOG_LEVEL_ERROR   4
#define CH_LOG_LEVEL_APP     5
#define CH_LOG_LEVEL_DISABLE 6

#ifndef CH_LOG_MODULE_LEVEL
#define CH_LOG_MODULE_LEVEL CH_LOG_LEVEL_ERROR
#endif

#ifndef CH_LOG_BUFFER_SIZE
/* Size of the internal buffer to save messages before printing */
#define CH_LOG_BUFFER_SIZE (200)
#endif

#define IS_CH_LOG_USED              (CH_LOG_MODULE_LEVEL < CH_LOG_LEVEL_DISABLE)
#define IS_CH_LOG_LEVEL_USED(level) (level >= CH_LOG_MODULE_LEVEL)

#if (CH_LOG_MODULE_LEVEL <= CH_LOG_LEVEL_TRACE)
#define CH_LOG_TRACE(...)       ch_log_prefix_printf('T', CH_LOG_MODULE_NAME, __func__, __VA_ARGS__)
#define CH_LOG_TRACE_START(...) ch_log_prefix_start('T', CH_LOG_MODULE_NAME, __func__, __VA_ARGS__)
#define CH_LOG_TRACE_MSG(...)   ch_log_msg(__VA_ARGS__)
#define CH_LOG_TRACE_END()      ch_log_end()
#else
#define CH_LOG_TRACE(...)
#define CH_LOG_TRACE_START(...)
#define CH_LOG_TRACE_MSG(...)
#define CH_LOG_TRACE_END()
#endif

#if (CH_LOG_MODULE_LEVEL <= CH_LOG_LEVEL_DEBUG)
#define CH_LOG_DEBUG(...)       ch_log_prefix_printf('D', CH_LOG_MODULE_NAME, __func__, __VA_ARGS__)
#define CH_LOG_DEBUG_START(...) ch_log_prefix_start('D', CH_LOG_MODULE_NAME, __func__, __VA_ARGS__)
#define CH_LOG_DEBUG_MSG(...)   ch_log_msg(__VA_ARGS__)
#define CH_LOG_DEBUG_END()      ch_log_end()
#else
#define CH_LOG_DEBUG(...)
#define CH_LOG_DEBUG_START(...)
#define CH_LOG_DEBUG_MSG(...)
#define CH_LOG_DEBUG_END()
#endif

#if (CH_LOG_MODULE_LEVEL <= CH_LOG_LEVEL_INFO)
#define CH_LOG_INFO(...)       ch_log_prefix_printf('I', CH_LOG_MODULE_NAME, __func__, __VA_ARGS__)
#define CH_LOG_INFO_START(...) ch_log_prefix_start('I', CH_LOG_MODULE_NAME, __func__, __VA_ARGS__)
#define CH_LOG_INFO_MSG(...)   ch_log_msg(__VA_ARGS__)
#define CH_LOG_INFO_END()      ch_log_end()
#else
#define CH_LOG_INFO(...)
#define CH_LOG_INFO_START(...)
#define CH_LOG_INFO_MSG(...)
#define CH_LOG_INFO_END()
#endif

#if (CH_LOG_MODULE_LEVEL <= CH_LOG_LEVEL_WARNING)
#define CH_LOG_WARN(...)       ch_log_prefix_printf('W', CH_LOG_MODULE_NAME, __func__, __VA_ARGS__)
#define CH_LOG_WARN_START(...) ch_log_prefix_start('W', CH_LOG_MODULE_NAME, __func__, __VA_ARGS__)
#define CH_LOG_WARN_MSG(...)   ch_log_msg(__VA_ARGS__)
#define CH_LOG_WARN_END()      ch_log_end()
#else
#define CH_LOG_WARN(...)
#define CH_LOG_WARN_START(...)
#define CH_LOG_WARN_MSG(...)
#define CH_LOG_WARN_END()
#endif

#if (CH_LOG_MODULE_LEVEL <= CH_LOG_LEVEL_ERROR)
#define CH_LOG_ERR(...)       ch_log_prefix_printf('E', CH_LOG_MODULE_NAME, __func__, __VA_ARGS__)
#define CH_LOG_ERR_START(...) ch_log_prefix_start('E', CH_LOG_MODULE_NAME, __func__, __VA_ARGS__)
#define CH_LOG_ERR_MSG(...)   ch_log_msg(__VA_ARGS__)
#define CH_LOG_ERR_END()      ch_log_end()
#else
#define CH_LOG_ERR(...)
#define CH_LOG_ERR_START(...)
#define CH_LOG_ERR_MSG(...)
#define CH_LOG_ERR_END()
#endif

#if (CH_LOG_MODULE_LEVEL <= CH_LOG_LEVEL_APP)
#define CH_LOG_APP(...)       ch_log_printf_eol(__VA_ARGS__)
#define CH_LOG_APP_START(...) ch_log_start(__VA_ARGS__)
#define CH_LOG_APP_MSG(...)   ch_log_msg(__VA_ARGS__)
#define CH_LOG_APP_END()      ch_log_end()
#else
#define CH_LOG_APP(...)
#define CH_LOG_APP_START(...)
#define CH_LOG_APP_MSG(...)
#define CH_LOG_APP_END()
#endif

void ch_log_printf(const char *format, ...);
void ch_log_printf_eol(const char *format, ...);
void ch_log_prefix_printf(const char level, const char *name, const char *func_name, const char *format, ...);
void ch_log_prefix_start(const char level, const char *name, const char *func_name, const char *format, ...);
void ch_log_start(const char *format, ...);
void ch_log_msg(const char *format, ...);
void ch_log_end(void);

#ifdef __cplusplus
}
#endif

#endif /* CH_LOG_H_ */
