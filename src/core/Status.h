enum class Status : std::uint8_t
{
    Idle = 0,

    Ready,

    Running,

    Homing,

    Error
};