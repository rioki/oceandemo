
#include "fs.h"

#include <fstream>

namespace fs
{
    std::string readfile(const std::string& file)
    {
        // TODO make this crap more efficient
        std::ifstream in(file);

        if (in.bad())
        {
            throw std::runtime_error("Failed to open " + file + " for reading.");
        }

        std::string result;
        int c = in.get();
        while (c != EOF)
        {
            result.push_back(c);
            c = in.get();
        }

        return result;
    }
}
