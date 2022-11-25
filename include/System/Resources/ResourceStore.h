#pragma once

#include <concepts>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

template<class T>
concept Loadable = requires(T t, const std::string &path) {
    { t.loadFromFile(path) } -> std::convertible_to<bool>;
};

template<Loadable T>
class ResourceStore {
public:
    explicit ResourceStore(std::string _dataDir, std::string _configFile) : dataDir(std::move(_dataDir)), configFile(std::move(_configFile)) {
        std::ifstream storeConfig(dataDir + configFile);

        if (!storeConfig.good()) {
            const auto message = "Couldn't load resource store config '" + configFile + "'";
            spdlog::error(message);
            throw std::invalid_argument(message);
        }

        configData = nlohmann::json::parse(storeConfig);

        extension = configData["extension"].get<std::string>();
        loadAll = configData["loadAll"].get<bool>();

        // Load resources required before loading screen
        for (auto &resourceEntry : configData["essentialResources"]) {
            addResource(resourceEntry["name"].get<std::string>(), dataDir + resourceEntry["path"].get<std::string>());
        }

        storeConfig.close();
    }

    size_t loadResources() {
        if (!loadAll) {
            for (auto &resourceEntry : configData["resources"]) {
                addResource(resourceEntry["name"].get<std::string>(), dataDir + resourceEntry["path"].get<std::string>());
            }
        } else {
            for (const auto &dirEntry : std::filesystem::recursive_directory_iterator(dataDir)) {
                if (dirEntry.is_regular_file() && dirEntry.path().extension() == extension) {
                    const auto &path = dirEntry.path();
                    addResource(path.filename().replace_extension("").string(), path.string());
                }
            }
        }

        return resources.size();
    }

    std::shared_ptr<T> getResource(const std::string &name) const {
        if (!resources.contains(name)) {
            const auto message = "Resource '" + name + "' is not loaded";
            spdlog::error(message);
            throw std::invalid_argument(message);
        }

        return resources.find(name)->second;
    }

private:
    const std::string dataDir;
    const std::string configFile;
    std::string extension;
    bool loadAll;

    nlohmann::json configData;

    bool addResource(const std::string &name, const std::string &path) {
        if (resources.contains(name)) return false;

        auto resource = std::make_shared<T>();

        if (resource->loadFromFile(path)) {
            resources.emplace(name, std::move(resource));
            spdlog::debug("Loaded resource {} as {}", path, name);
            return true;
        } else {
            spdlog::error("Couldn't load resource {}", path);
            return false;
        }
    }

    std::unordered_map<std::string, std::shared_ptr<T>> resources;
};