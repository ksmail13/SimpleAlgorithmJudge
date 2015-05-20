#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

/*void BaseLogMessage(FILE *fp, ...)
{
    va_list vargs;
    fprintf(fp, "[%s(%d)-%s]", __FILE__, __LINE__, __FUNCTION__);
    fprintf(fp, vargs);
    fputc('\n', fp);
}*/

#define BaseLogMessage(target, message, ...) fprintf(target, ("[%s(%d)-%s]" message), __FILE__, __LINE__, __PRETTY_FUNCTION__, ## __VA_ARGS__)


#define InformMessage(...) BaseLogMessage(stdout, __VA_ARGS__);

#define ErrorMessage(msg, ...) BaseLogMessage(stderr, __VA_ARGS__ );

#endif
