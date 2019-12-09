//
// Created by qnbhd on 28.11.2019.
//

#pragma once
#include <map>

class FunctionTable final
{
private:
    static std::map<std::string, int> functions_;

public:
    static bool isExist (const std::string& fname)
    {
        return functions_.count(fname) > 0;
    }

    static int get (const std::string& fname)
    {
        if (isExist(fname))
            return functions_[fname];

        throw std::runtime_error("[ERROR] FUNCTION DOESN'T EXIST");
    }


};