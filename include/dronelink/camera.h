#pragma once

#include <functional>
#include <vector>
#include <string>
#include <cstdint>

#define CAMERA_HTTP

namespace dronelink {

class CameraImpl;

class Camera
{
public:
    explicit Camera(CameraImpl *impl);
    ~Camera();

    enum class Result {
        SUCCESS = 0,
        DENIED,
        ERROR,
        TIMEOUT,
        WRONG_ARGUMENT,
        UNKNOWN
    };

    static const char *result_str(Result);

    typedef std::function<void(Result)> result_callback_t;

    struct Settings {
        double aperture_value;
        double shutter_speed_s;
        double iso_sensitivity;
        double white_space_balance_temperature_k;

        bool aperture_auto;
        bool shutter_auto;
        bool iso_auto;
        bool white_space_auto;
        enum class Mode {
            UNKNOWN,
            VIDEO,
            PHOTO
        } mode;
    };

    struct Status {
        bool video_on;
        bool photo_interval_on;
    };

    /**
     * Note that shutter and ISO must be either both set to auto or both to a value (not-auto).
     */

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

    struct Media {
        std::string url;
        float size_mib;
    };

    const std::string &get_media_http_index_url();
    bool extract_media_from_http_index(const std::string &http_index, std::vector<Media> &files);

    // Non-copyable
    Camera(const Camera &) = delete;
    const Camera &operator=(const Camera &) = delete;

private:
    // Underlying implementation, set at instantiation
    CameraImpl *_impl;
};

} // namespace dronelink
