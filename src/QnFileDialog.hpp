//
// Created by qnbhd on 11.12.2019.
//

#pragma once

#include <vector>
#include <string>
#include <stdexcept>

#include <algorithm>

class QnFileDialog {
public:
#if !defined(__APPLE__)
    static std::string FileDialog(const std::vector<std::pair<std::string, std::string>> &filetypes, bool save) {
#define FILE_DIALOG_MAX_BUFFER 1024
#if defined(_WIN32)
        OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    char tmp[FILE_DIALOG_MAX_BUFFER];
    ofn.lpstrFile = tmp;
    ZeroMemory(tmp, FILE_DIALOG_MAX_BUFFER);
    ofn.nMaxFile = FILE_DIALOG_MAX_BUFFER;
    ofn.nFilterIndex = 1;

    std::string filter;

    if (!save && filetypes.size() > 1) {
        filter.append("Supported file types (");
        for (size_t i = 0; i < filetypes.size(); ++i) {
            filter.append("*.");
            filter.append(filetypes[i].first);
            if (i + 1 < filetypes.size())
                filter.append(";");
        }
        filter.append(")");
        filter.push_back('\0');
        for (size_t i = 0; i < filetypes.size(); ++i) {
            filter.append("*.");
            filter.append(filetypes[i].first);
            if (i + 1 < filetypes.size())
                filter.append(";");
        }
        filter.push_back('\0');
    }
    for (auto pair: filetypes) {
        filter.append(pair.second);
        filter.append(" (*.");
        filter.append(pair.first);
        filter.append(")");
        filter.push_back('\0');
        filter.append("*.");
        filter.append(pair.first);
        filter.push_back('\0');
    }
    filter.push_back('\0');
    ofn.lpstrFilter = filter.data();

    if (save) {
        ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
        if (GetSaveFileNameA(&ofn) == FALSE)
            return "";
    } else {
        ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        if (GetOpenFileNameA(&ofn) == FALSE)
            return "";
    }
    return std::string(ofn.lpstrFile);
#else
        char buffer[FILE_DIALOG_MAX_BUFFER];
        std::string cmd = "/usr/bin/zenity --file-selection ";
        if (save)
            cmd += "--save ";
        cmd += "--file-filter=\"";
        for (const auto& pair: filetypes)
            cmd += "\"*." + pair.first +  "\" ";
        cmd += "\"";
        FILE *output = popen(cmd.c_str(), "r");
        if (output == nullptr)
            throw std::runtime_error("popen() failed -- could not launch zenity!");
        while (fgets(buffer, FILE_DIALOG_MAX_BUFFER, output) != NULL)
            ;
        pclose(output);
        std::string result(buffer);
        result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
        return result;
#endif
    }
#endif
};