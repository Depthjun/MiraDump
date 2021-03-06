#include <iostream>
#include <optional>
#include <tuple>
#include <string>
#include "ConfigReader.h"
#include "Process.h"
#include "Scanner.h"
#include "Exporter.h"
#include <unordered_map>

void Terminate() {
}

int main()
{
    std::string configFileName = "config.toml";
    std::optional<std::string> gameName = ConfigReader::ReadGameName(configFileName);
    if (!gameName) {
        std::cout << "Something went wrong. Make sure if you have config.toml and specified the name of a game." << std::endl;
        Terminate();
        return 1;
    }
    
    std::vector<SigProfile> configs = ConfigReader::ReadProfile(configFileName);
    std::vector<std::tuple<std::string, uintptr_t, std::string>> resultInfo {};
    std::unordered_map<std::string, std::vector<std::byte>> modules;
    for (SigProfile& config : configs)
    {
        Process prc = Process::GetProcess(*gameName, config.module);
        if (auto e = prc.GetError(); e && e->find("module") == std::string::npos) {
            std::cout << *e;
            Terminate();
            return 1;
        } else if (e->find("module") != std::string::npos) {
            std::cout << *e;
            resultInfo.emplace_back(std::make_tuple(config.name, 0, "Invalid module name: " + config.module));
            continue;
        }

        if (modules.count(prc.moduleName) == 0) {
            std::vector<std::byte> buffer(prc.moduleBaseSize);
            ReadProcessMemory(prc.hProcess, static_cast<LPCVOID>(prc.moduleBaseAddress), buffer.data(), buffer.size(), NULL);
            modules.emplace(prc.moduleName, buffer);
        }

        std::optional<uintptr_t> result = Scanner::Scan(prc, config, modules.at(prc.moduleName));

        if (!result) {
            std::cerr << "Couldn't find signature: " << config.name << std::endl;
            resultInfo.emplace_back(std::make_tuple(config.name, 0, "Invalid signature: " + config.signatureString));
            continue;
        }
        std::cout << config.name << ": " << "<" << config.module << ">" << " + 0x" << std::hex << *result << std::endl;
        resultInfo.emplace_back(std::make_tuple(config.name, *result, config.module));
    }

    std::string dir = ConfigReader::ReadExportDir(configFileName);
    if (!dir.empty()) {
        std::cout << "\nOffsets.hpp will be created at: " << dir << std::endl;
    } else {
        std::cout << "GameOffsets.hpp will be created at current directory." << std::endl;
        std::cout << "(You probably didn't specify existing directory.)" << std::endl;
    }

    std::string exptDir = dir + "Offsets.hpp";
    Exporter exp(exptDir, resultInfo);
    exp.WriteDown();
    std::cout << "\nMiraDump has successfully finished its work:)" << std::endl;
    Terminate();
    return 0;
}