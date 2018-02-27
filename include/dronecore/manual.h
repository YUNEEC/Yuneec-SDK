#pragma once

#include "plugin_base.h"

namespace dronecore {

class ManualImpl;
class Device;

class Manual : public PluginBase
{
public:
    explicit Manual(Device *device);
    ~Manual();

    void set_channels(float throttle_norm,
                      float roll_norm,
                      float pitch_norm,
                      float yaw_norm,
                      float gimbal_angle_norm);
    void send_channel_value();

    // Non-copyable
    Manual(const Manual &) = delete;
    const Manual &operator=(const Manual &) = delete;

private:
    // Underlying implementation, set at instantiation
    ManualImpl *_impl;
};

} // namespace dronecore
