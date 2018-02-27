#pragma once

#include <functional>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include "plugin_base.h"

namespace dronecore {

class YuneecSt16Impl;
class Device;

class YuneecSt16 : public PluginBase
{
public:
    explicit YuneecSt16(Device *device);
    ~YuneecSt16();

    enum class Result {
        SUCCESS = 0,
        BUSY,
        ALREADY_PAIRED,
        NOT_PAIRED,
        UNSUPPORTED_PLATFORM,
        UNKNOWN
    };

    enum class SwitchId {
        FLIGHT_MODE,
        OBSTACLE_AVOIDANCE,
    };

    enum class SwitchState {
        OFF,
        CENTER,
        ON
    };

    enum class ButtonId {
        POWER,
        AUX,
        CAMERA_SHUTTER,
        VIDEO_SHUTTER,
    };

    enum class ButtonState {
        NORMAL,
        PRESSED
    };

    struct GPSPosition {
        double latitude_deg;
        double longitude_deg;
        float absolute_altitude_m;
        int num_satellites;
        float pdop;
        float speed_m_s;
        float heading_deg;
    };


    static const char *result_str(Result);

    typedef std::function<void(Result)> result_callback_t;

    void check_paired_async(result_callback_t callback);
    void pair_async(result_callback_t callback);
    void unpair_async(result_callback_t callback);

    typedef std::function<void(SwitchId, SwitchState)> switch_callback_t;

    void switch_state_async(switch_callback_t callback);

    typedef std::function<void(ButtonId, ButtonState)> button_callback_t;

    void button_state_async(button_callback_t callback);

    typedef  std::function<void(GPSPosition)> gps_callback_t;

    void gps_async(gps_callback_t callback);

    // Non-copyable
    YuneecSt16(const YuneecSt16 &) = delete;
    const YuneecSt16 &operator=(const YuneecSt16 &) = delete;

private:
    // Underlying implementation, set at instantiation
    YuneecSt16Impl *_impl;
};

} // namespace dronecore
