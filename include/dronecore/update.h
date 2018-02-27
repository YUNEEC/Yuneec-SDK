#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include "plugin_base.h"

namespace dronecore {

class UpdateImpl;
class Device;

class Update : public PluginBase
{
public:
    explicit Update(Device *device);
    ~Update();

    enum class UpdateInstruction : unsigned {
        UNKNOWN = 0,
        INSTALLED_VERSION_UNKNOWN = 1,
        LATEST_VERSION_UNKNOWN = 2,
        UP_TO_DATE = 3,
        MINOR_FIRMWARE_UPDATE_AVAILABLE = 4,
        MAJOR_FIRMWARE_UPDATE_AVAILABLE = 5,
        MANDATORY_FIRMWARE_UPDATE_AVAILABLE = 6,
        UNKNOWN_ERROR = 7,
        UPDATE_PROCESS_ONGOING = 8,
        CHECK_INSTALLED_VERSION_TIMEOUT = 9,
        CHECK_LATEST_VERSION_TIMEOUT = 10
    };

    // 16 chars + terminating 0
    static const unsigned GIT_HASH_STR_LEN = 17;

    struct AutopilotVersion {
        int flight_sw_major;
        int flight_sw_minor;
        int flight_sw_patch;
        int flight_sw_vendor_major;
        int flight_sw_vendor_minor;
        int flight_sw_vendor_patch;
        char flight_sw_git_hash[GIT_HASH_STR_LEN];
        int os_sw_major;
        int os_sw_minor;
        int os_sw_patch;
        char os_sw_git_hash[GIT_HASH_STR_LEN];
        uint16_t vendor_id;
        uint16_t product_id;
    };

    class Version
    {
    public:
        int major;
        int minor;
        int patch;
    };

    class CameraVersion : public Version
    {
    public:
        std::string region;
        std::string model;
    };

    struct GimbalVersion {
        int major;
        int minor;
        int patch;
        std::string model;
    };

    struct DatapilotVersion {
        int major;
        int minor;
        int patch;
    };

    struct UpdaterAppVersion {
        int major;
        int minor;
        int patch;
    };

    struct ST16SVersion {
        int major;
        int minor;
        int patch;
    };

    enum class UpdateState {
        Idle,
        ConnectingToVehicle,
        ConnectingToUpdateServer,
        VehicleNotFound,
        UpdateServerNotFound,
        Downloading,
        Uploading,
        Rebooting,
        Flashing,
        Verifying,
        Finished,
        Error,
        Cancelled,
        DownloadingTimeout,
        UploadingTimeout,
        BatteryTooLow,
        SDCardNotInserted
    };

    enum class Component {
        None,
        Autopilot,
        Camera,
        Gimbal,
        Datapilot,
        UpdaterApp,
        Firmware,
        Apps,
        ST16S
    };

    typedef std::function<void(int progress, UpdateState status, Component component)>
    update_callback_t;
    typedef std::function<void(Component component,
                               UpdateInstruction instruction,
                               std::string latest_version,
                               std::string installed_version)> version_callback_t;

    void enable();
    void disable();

    void do_firmware_update(update_callback_t callback);
    void do_app_update(update_callback_t callback, Update::version_callback_t version_callback,
                       bool check_version_only);
    void set_app_version(const std::string &datapilot_version_text,
                         const std::string &updaterapp_version_text,
                         const std::string &st16s_version_text);
    void do_version_check(version_callback_t callback, bool delete_installed);

    // Autopilot
    UpdateInstruction check_autopilot_version();
    Update::AutopilotVersion get_autopilot_version();

    // Camera
    UpdateInstruction check_camera_version();
    Update::CameraVersion get_camera_version();

    // Gimbal
    UpdateInstruction check_gimbal_version();
    Update::GimbalVersion get_gimbal_version();

    // Non-copyable
    Update(const Update &) = delete;
    const Update &operator=(const Update &) = delete;

private:
    // Underlying implementation, set at instantiation
    UpdateImpl *_impl;
};

} // namespace dronecore
