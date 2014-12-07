
#include "fs.h"

#include <fstream>

namespace fs
{
    std::string readfile(const std::string& file)
    {
        // TODO make this crap more efficient
        std::ifstream in(file);

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
