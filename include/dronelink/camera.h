#pragma once

#include <functional>
#include <vector>
#include <string>
#include <cmath>

namespace dronelink {

class CameraImpl;

class Camera
{
public:
    explicit Camera(CameraImpl *impl);
    ~Camera();

    enum class Result {
        SUCCESS = 0,
        IN_PROGRESS,
        DENIED,
        ERROR,
        TIMEOUT,
        WRONG_ARGUMENT,
        UNKNOWN
    };

    static const char *result_str(Result);

    typedef std::function<void(Result)> result_callback_t;

    /**
     * Note that shutter and ISO must be either both set to auto or both to a value (not-auto).
     *
     * Values left at NAN, won't have any effect.
     */
    struct Settings {
        enum class Mode {
            UNKNOWN,
            PHOTO,
            VIDEO
        } mode {Mode::UNKNOWN};

        double aperture_value {NAN};

        double shutter_speed_s {NAN};

        double iso_sensitivity {NAN};

        double white_balance_temperature_k {NAN};
        bool white_balance_locked {false};

        double exposure_value {NAN};
        enum class ExposureMode {
            UNKNOWN,
            FULL_AUTO,
            FULL_MANUAL,
            APERTURE_PRIORITY,
            SHUTTER_PRIORITY
        } exposure_mode {ExposureMode::FULL_AUTO};
    };

    struct Status {
        bool video_on;
        bool photo_interval_on;

        enum class StorageStatus {
            NOT_AVAILABLE,
            UNFORMATTED,
            FORMATTED
        } storage_status;
        float used_storage_mib;
        float available_storage_mib;
        float total_storage_mib;
    };


    Result set_settings(const Settings &settings);
    Result get_settings(Settings &settings);

    void set_settings_async(const Settings &settings, result_callback_t callback);

    typedef std::function<void(Result, const Settings &)> get_settings_callback_t;
    void get_settings_async(get_settings_callback_t callback);

    typedef std::function<void(Result, const Status &)> get_status_callback_t;
    void get_status_async(get_status_callback_t callback);

    Result take_photo();

    Result start_photo_interval(double interval_s);
    Result stop_photo_interval();

    Result start_video();
    Result stop_video();

    void take_photo_async(result_callback_t callback);

    void start_photo_interval_async(double interval_s, result_callback_t callback);
    void stop_photo_interval_async(result_callback_t callback);

    void start_video_async(result_callback_t callback);
    void stop_video_async(result_callback_t callback);

    struct MediaInfo {
        MediaInfo()
        {
        }
        ~MediaInfo()
        {
            path.clear();
        }

        std::string path {};
        float size_mib = 0.0f;
    };

    typedef std::function<void(Result, std::vector<MediaInfo> &)> get_media_infos_callback_t;
    void get_media_infos_async(get_media_infos_callback_t callback);

    typedef std::function<void(Result, long unsigned bytes, long unsigned bytes_total)>
    get_media_callback_t;
    void get_media_async(const std::string &local_path,
                         const std::string &url,
                         get_media_callback_t callback);

    // Non-copyable
    Camera(const Camera &) = delete;
    const Camera &operator=(const Camera &) = delete;

private:
    // Underlying implementation, set at instantiation
    CameraImpl *_impl;
};

} // namespace dronelink
