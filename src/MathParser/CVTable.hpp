//
// Created by qnbhd on 28.11.2019.
//

#pragma once
#include <map>

class CVTable
{
private:

    static std::map<std::string, double> consts_;

    static std::map<std::string, double> variables_;

public:

    static bool ConstIsExists (const std::string& key)
    {
        return consts_.count(key) > 0;
    }

    static bool VarIsExists (const std::string& key)
    {
        return variables_.count(key) > 0;
    }

    static double getConst (const std::string& key)
    {
        //return (consts_.count(key) == 0) ? 0 :
        if (!ConstIsExists(key))
           throw std::runtime_error("[ERROR] CONST DOESN'T EXIST");
        return consts_[key];
    }

    static double getVariable (const std::string& key)
    {
        if (!VarIsExists(key))
            throw std::runtime_error("[ERROR] VARIABLE DOESN'T EXIST");
        return variables_[key];

    }

    static void setVariable (const std::string& key, double value)
    {
        /// VARS MUSTN'T BE NAMED AS CONSTS
        if (!ConstIsExists(key))
        {
            variables_[key] = value;
        }
    }

    static void removeVariable (const std::string& key)
    {
        variables_.erase(key);
    }


};

