#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <iostream>
#include <list>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

class ConfigurationOption
{
public:
    ConfigurationOption(
        const std::string& path);

    const std::string& getPath() const;

    virtual void initializeValue(
        const boost::property_tree::ptree& propertyTree)=0;

private:
    std::string path;
};

template <typename T>
class BasicConfigurationOption : public ConfigurationOption
{
public:
    BasicConfigurationOption(
        const std::string& path,
        const T& defaultValue) :
        ConfigurationOption(path),
        value(defaultValue)
    {
    }

    const T& getValue() const
    {
        return value;
    }

    void initializeValue(
        const boost::property_tree::ptree& propertyTree) override
    {
        value = propertyTree.get<T>(getPath(), value);

        std::cout
            << "Configuration option \""
            << getPath()
            << "\" set to \""
            << value
            << "\""
            << std::endl;
    }

private:
    T value;
};

class Configuration
{
public:
    static void initialize(
        const std::string& fileName);

    static bool getAudioEnabled();

    static int getAudioFrequency();

    static int getFrameRate();

    static const std::string& getPaletteFileName();

    static const std::string& getRomFileName();

    static int getRenderScale();

    static bool getScanlinesEnabled();

    static bool getVsyncEnabled();

    static int getScreenWidth();

    static int getScreenHeight();

    static int getVisibleTileColumns();

private:
    static BasicConfigurationOption<bool> audioEnabled;

    static BasicConfigurationOption<int> audioFrequency;

    static BasicConfigurationOption<int> frameRate;

    static BasicConfigurationOption<std::string> paletteFileName;

    static BasicConfigurationOption<int> renderScale;

    static BasicConfigurationOption<std::string> romFileName;

    static BasicConfigurationOption<bool> scanlinesEnabled;

    static BasicConfigurationOption<bool> vsyncEnabled;

    static BasicConfigurationOption<int> screenWidth;

    static BasicConfigurationOption<int> screenHeight;

    static std::list<ConfigurationOption*> configurationOptions;
};

#endif
