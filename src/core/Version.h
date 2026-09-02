#pragma once

#include <cstdint>
#include <string_view>

namespace LogosRobotics::Core
{

class Version
{
public:

    static constexpr std::string_view Name    = "Logos Robotics SDK";

    static constexpr std::uint16_t Major = 0;
    static constexpr std::uint16_t Minor = 1;
    static constexpr std::uint16_t Patch = 0;

    static constexpr std::uint32_t Build = 1;

    static constexpr std::string_view Status  = "Alpha";
    static constexpr std::string_view Author  = "Prele Prelević";
    static constexpr std::string_view License = "MIT";
};

}