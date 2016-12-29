#pragma once

#include <vector>
#include "action.h"
#include "info.h"
#include "logging.h"
#include "offboard.h"
#include "telemetry.h"
#include "camera.h"
#include "gimbal.h"
#include "mission.h"
#include "mission_item.h"


namespace dronelink {

class DeviceImpl;
class PluginImplBase;
class ActionImpl;
class InfoImpl;
class LoggingImpl;
class OffboardImpl;
class TelemetryImpl;
class CameraImpl;
class GimbalImpl;
class MissionImpl;


class DevicePluginContainer
{
public:
    explicit DevicePluginContainer(DeviceImpl *impl);
    virtual ~DevicePluginContainer();

    Action &action() { return _action; }
    Info &info() { return _info; }
    Logging &logging() { return _logging; }
    Offboard &offboard() { return _offboard; }
    Telemetry &telemetry() { return _telemetry; }
    Camera &camera() { return _camera; }
    Gimbal &gimbal() { return _gimbal; }
    Mission &mission() { return _mission; }


    // Non-copyable
    DevicePluginContainer(const DevicePluginContainer &) = delete;
    const DevicePluginContainer &operator=(const DevicePluginContainer &) = delete;

protected:
    virtual void init_plugins();
    virtual void deinit_plugins();

    DeviceImpl *_impl;

    ActionImpl *_action_impl;
    Action _action;
    InfoImpl *_info_impl;
    Info _info;
    LoggingImpl *_logging_impl;
    Logging _logging;
    OffboardImpl *_offboard_impl;
    Offboard _offboard;
    TelemetryImpl *_telemetry_impl;
    Telemetry _telemetry;
    CameraImpl *_camera_impl;
    Camera _camera;
    GimbalImpl *_gimbal_impl;
    Gimbal _gimbal;
    MissionImpl *_mission_impl;
    Mission _mission;


    std::vector<PluginImplBase *> _plugin_impl_list;
};

} // namespace dronelink
