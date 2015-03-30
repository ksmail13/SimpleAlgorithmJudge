#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define BaseLogMessage(target,msg, ...) fprintf(target, "[%s(%d)-%s] ", __FILE__, __LINE__, __FUNCTION__); fprintf(target, msg, __VA_ARGS__)

#define InformMessage(msg, ...) BaseLogMessage(stdout, msg, __VA_ARGS__);

#define ErrorMessage(msg, ...) BaseLogMessage(stderr, msg, __VA_ARGS__ );

#endif
