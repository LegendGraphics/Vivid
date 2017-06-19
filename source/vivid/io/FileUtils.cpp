#include "vivid/io/FileUtils.h"
#include <fstream>

namespace te
{
    void FileUtils::streamFromBinaryFile(const String& filename, char*& data, int& size)
    {
        // Reading size of file
        FILE * file = fopen(filename.c_str(), "rb");
        if (file == NULL) return;
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        fclose(file);
        // Reading data to array of chars
        file = fopen(filename.c_str(), "rb");
        data = (char *)malloc(sizeof(char)*size);
        int ii = fread(data, sizeof(char), size, file);
        fclose(file);
    }

    int FileUtils::getFileLength(std::ifstream& file)
    {
        if (!file.good()) return 0;

        unsigned long pos = file.tellg();
        file.seekg(0, std::ios::end);
        unsigned long len = file.tellg();
        file.seekg(std::ios::beg);

        return len;
    }

    int FileUtils::loadShader(const String& filename, char*& data, int& size)
    {
        std::ifstream file;
        file.open(filename, std::ios::in); // opens as ASCII!
        if (!file) return -1;

        unsigned long len = getFileLength(file);

        if (len == 0) return -2;   // Error: Empty File 

        data = new char[len + 1];
        if (data == 0) return -3;   // can't reserve memory

                                            // len isn't always strlen cause some characters are stripped in ascii read...
                                            // it is important to 0-terminate the real length later, len is just max possible value... 
        data[len] = 0;

        unsigned int i = 0;
        while (file.good())
        {
            data[i] = file.get();       // get character from file.
            if (!file.eof())
                i++;
        }

        data[i] = 0;  // 0-terminate it at the correct position

        file.close();

        return 0; // No Error
    }

}
