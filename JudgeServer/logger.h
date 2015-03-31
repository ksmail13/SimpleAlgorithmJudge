#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define BaseLogMessage(target, ...) fprintf(target, "[%s(%d)-%s] ", __FILE__, __LINE__, __FUNCTION__); fprintf(target, __VA_ARGS__); fputc('\n', target)

#define InformMessage(...) BaseLogMessage(stdout, __VA_ARGS__);

#define ErrorMessage(msg, ...) BaseLogMessage(stderr, __VA_ARGS__ );

#endif
