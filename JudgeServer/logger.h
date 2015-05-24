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

#define BaseLogMessage(target, message, ...)


#define InformMessage(message, ...) fprintf(stdout, "[%s(%4d)] " message "\n", __PRETTY_FUNCTION__, __LINE__, ## __VA_ARGS__)

#define ErrorMessage(message, ...) fprintf(stderr, "[%s(%4d)] " message "\n", __PRETTY_FUNCTION__, __LINE__, ## __VA_ARGS__)

#endif
