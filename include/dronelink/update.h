#pragma once

#include <cstdint>
#include <functional>

namespace dronelink {

class UpdateImpl;

class Update
{
public:
    explicit Update(UpdateImpl *impl);
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
        UPDATE_PROCESS_ONGOING = 8
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

    struct CameraVersion {
        int major;
        int minor;
        int patch;
        std::string region;
        std::string model;
    };

    struct GimbalVersion {
        int major;
        int minor;
        int patch;
        std::string model;
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
        Cancelled
    };

    enum class Component {
        None,
        Autopilot,
        Camera,
        Gimbal
    };

    typedef std::function<void(int progress, UpdateState status, Component component)> update_callback_t;

    void do_firmware_update(update_callback_t callback, bool force_update);

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

} // namespace dronelink
