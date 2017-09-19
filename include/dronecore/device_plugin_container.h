#pragma once

#include <vector>
#include "action.h"
#include "info.h"
#include "logging.h"
#include "mission.h"
#include "mission_item.h"
#include "offboard.h"
#include "telemetry.h"
#include "calibration.h"
#include "camera.h"
#include "gimbal.h"
#include "manual.h"
#include "update.h"


namespace dronecore {

class DeviceImpl;
class PluginImplBase;
class ActionImpl;
class InfoImpl;
class LoggingImpl;
class MissionImpl;
class OffboardImpl;
class TelemetryImpl;
class CalibrationImpl;
class CameraImpl;
class GimbalImpl;
class ManualImpl;
class UpdateImpl;


/**
 * @brief The DevicePluginContainer contains all plugins for a device.
 *
 * The content of the DevicePluginContainer is auto-generated at compile time.
 * Plugins such as Action or Telemetry are included so that they can be accessed
 * using `DroneCore::device().action()...`
 */
class DevicePluginContainer
{
public:
    /**
     * @private Constructor of DevicePluginContainer called internally.
     *
     * A device inheriting from DevicePluginContainer is created internally and can be accessed
     * using `DroneCore::device()`.
     *
     * @param impl device implementation internal
     */
    explicit DevicePluginContainer(DeviceImpl *impl);

    /**
     * @private Destructor of DevicePluginContainer called internally.
     *
     * The destructor of a DevicePluginContainer does not need to be called by any consumer of the
     * API. Instead the device will be cleaned up when DroneCore is destroyed.
     */
    virtual ~DevicePluginContainer();

    /**
     * Getter for Action plugin.
     *
     * @return a reference to the action plugin instance
     */
    Action &action() { return _action; }

    /**
     * Getter for Info plugin.
     *
     * @return a reference to the info plugin instance
     */
    Info &info() { return _info; }

    /**
     * Getter for Logging plugin.
     *
     * @return a reference to the logging plugin instance
     */
    Logging &logging() { return _logging; }

    /**
     * Getter for Mission plugin.
     *
     * @return a reference to the mission plugin instance
     */
    Mission &mission() { return _mission; }

    /**
     * Getter for Offboard plugin.
     *
     * @return a reference to the offboard plugin instance
     */
    Offboard &offboard() { return _offboard; }

    /**
     * Getter for Telemetry plugin.
     *
     * @return a reference to the telemetry plugin instance
     */
    Telemetry &telemetry() { return _telemetry; }

    /**
     * Getter for Calibration plugin.
     *
     * @return a reference to the calibration plugin instance
     */
    Calibration &calibration() { return _calibration; }

    /**
     * Getter for Camera plugin.
     *
     * @return a reference to the camera plugin instance
     */
    Camera &camera() { return _camera; }

    /**
     * Getter for Gimbal plugin.
     *
     * @return a reference to the gimbal plugin instance
     */
    Gimbal &gimbal() { return _gimbal; }

    /**
     * Getter for Manual plugin.
     *
     * @return a reference to the manual plugin instance
     */
    Manual &manual() { return _manual; }

    /**
     * Getter for Update plugin.
     *
     * @return a reference to the update plugin instance
     */
    Update &update() { return _update; }



    // Non-copyable
    DevicePluginContainer(const DevicePluginContainer &) = delete;
    const DevicePluginContainer &operator=(const DevicePluginContainer &) = delete;

protected:
    /** @private. */
    virtual void init_plugins();

    /** @private. */
    virtual void deinit_plugins();

    /** @private. */
    DeviceImpl *_impl;

    /** @private */
    ActionImpl *_action_impl;
    /** @private */
    Action _action;
    /** @private */
    InfoImpl *_info_impl;
    /** @private */
    Info _info;
    /** @private */
    LoggingImpl *_logging_impl;
    /** @private */
    Logging _logging;
    /** @private */
    MissionImpl *_mission_impl;
    /** @private */
    Mission _mission;
    /** @private */
    OffboardImpl *_offboard_impl;
    /** @private */
    Offboard _offboard;
    /** @private */
    TelemetryImpl *_telemetry_impl;
    /** @private */
    Telemetry _telemetry;
    /** @private */
    CalibrationImpl *_calibration_impl;
    /** @private */
    Calibration _calibration;
    /** @private */
    CameraImpl *_camera_impl;
    /** @private */
    Camera _camera;
    /** @private */
    GimbalImpl *_gimbal_impl;
    /** @private */
    Gimbal _gimbal;
    /** @private */
    ManualImpl *_manual_impl;
    /** @private */
    Manual _manual;
    /** @private */
    UpdateImpl *_update_impl;
    /** @private */
    Update _update;


    /** @private. */
    std::vector<PluginImplBase *> _plugin_impl_list;
};

} // namespace dronecore
