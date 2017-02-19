#ifndef IO_FILE_UTILS_H
#define IO_FILE_UTILS_H

#include <string>

void streamFromBinaryFile(const std::string& filename, char*& data, int& size);

#endif // IO_FILE_UTILS_H