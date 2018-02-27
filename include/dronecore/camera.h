#pragma once

#include <functional>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include "plugin_base.h"

namespace dronecore {

class Device;
class CameraImpl;

class Camera : PluginBase
{
public:
    explicit Camera(Device *device);
    ~Camera();

    enum class Result {
        SUCCESS = 0,
        IN_PROGRESS,
        BUSY,
        DENIED,
        ERROR,
        TIMEOUT,
        WRONG_ARGUMENT,
        UNKNOWN
    };

    static const char *result_str(Result);

    typedef std::function<void(Result)> result_callback_t;

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

    typedef std::function<void(Result, const Status &)> get_status_callback_t;
    void get_status_async(const get_status_callback_t &callback);

    enum class Mode {
        PHOTO,
        PHOTO_SURVEY,
        VIDEO,
        UNKNOWN
    };

    typedef std::function<void(Result, const Mode &)> mode_callback_t;
    void set_mode_async(Mode mode, const mode_callback_t &callback);
    void get_mode_async(const mode_callback_t &callback);

    Result take_photo();

    Result start_photo_interval(float interval_s);
    Result stop_photo_interval();

    Result start_video();
    Result stop_video();

    void take_photo_async(const result_callback_t &callback);

    void start_photo_interval_async(float interval_s, const result_callback_t &callback);
    void stop_photo_interval_async(const result_callback_t &callback);

    void start_video_async(const result_callback_t &callback);
    void stop_video_async(const result_callback_t &callback);

    struct MediaInfo {
        std::string path {};
        float size_mib = 0.0f;
    };

    //struct Setting {
    //    std::string key {};
    //    std::string description {};
    //    //enum class Type {
    //    //    NONE,
    //    //    FLOAT,
    //    //    STRING
    //    //} type = Type::NONE;
    //};

    void reset_async(const result_callback_t &callback);

    void set_option_key_async(const std::string &setting_key,
                              const std::string &option_key,
                              const result_callback_t &callback);
    //bool set_option_value_float(const std::string &setting_key, float option_value);
    //bool set_option_value_int(const std::string &setting_key, int option_value);

    typedef std::function<void(Result, const std::string &)> get_option_callback_t;
    void get_option_key_async(const std::string &setting_key,
                              const get_option_callback_t &callback);
    //bool get_option_value_float(const std::string &setting_key, float &option_value);
    //bool get_option_value_int(const std::string &setting_key, int &option_value);

    //bool show_option_value_float(const std::string &setting_key, std::string &option_key,
    //        float &option_value);
    //bool show_option_value_int(const std::string &setting_key, std::string &option_key,
    //        int &option_value);

    bool get_possible_settings(std::map<std::string, std::string> &settings);
    bool get_possible_options(const std::string &setting_name, std::vector<std::string> &options);

    enum class WhiteBalance {
        AUTO,
        INCANDESCENT,
        SUNSET,
        SUNNY,
        CLOUDY,
        FLUORESCENT,
        LOCK,
        UNKNOWN
    };

    const char *white_balance_str(WhiteBalance white_balance);

    typedef std::function <void(Result, WhiteBalance white_balance)> white_balance_callback_t;
    void set_white_balance_async(WhiteBalance white_balance,
                                 const white_balance_callback_t &callback);
    void get_white_balance_async(const white_balance_callback_t &callback);

    enum class ColorMode {
        NEUTRAL,
        ENHANCED,
        NIGHT,
        UNPROCESSED,
        UNKNOWN
    };

    typedef std::function <void(Result, ColorMode)> color_mode_callback_t;
    void set_color_mode_async(ColorMode color_mode, const color_mode_callback_t &callback);
    void get_color_mode_async(const color_mode_callback_t &callback);

    enum class ExposureMode {
        AUTO,
        MANUAL,
        UNKNOWN
    };

    typedef std::function <void(Result, ExposureMode)> exposure_mode_callback_t;
    void set_exposure_mode_async(ExposureMode exposure_mode, const exposure_mode_callback_t &callback);
    void get_exposure_mode_async(const exposure_mode_callback_t &callback);

    typedef std::function <void(Result, float)> exposure_value_callback_t;
    void set_exposure_value_async(float exposure_value, const exposure_value_callback_t &callback);
    void get_exposure_value_async(const exposure_value_callback_t &callback);

    struct ShutterSpeedS {
        int numerator;
        int denominator;
    };

    typedef std::function <void(Result, ShutterSpeedS)> shutter_speed_callback_t;
    void set_shutter_speed_async(ShutterSpeedS shutter_speed, const shutter_speed_callback_t &callback);
    void get_shutter_speed_async(const shutter_speed_callback_t &callback);

    typedef std::function <void(Result, int)> iso_value_callback_t;
    void set_iso_value_async(int iso_value, const iso_value_callback_t &callback);
    void get_iso_value_async(const iso_value_callback_t &callback);

    struct Resolution {
        int width_pixels;
        int height_pixels;
    };

    typedef std::function <void(Result, Resolution)> resolution_callback_t;
    void get_resolution_async(const resolution_callback_t &callback);

    enum class PhotoFormat {
        JPG,
        JPG_AND_DNG,
        UNKNOWN
    };

    typedef std::function <void(Result, PhotoFormat)> photo_format_callback_t;
    void set_photo_format_async(PhotoFormat photo_format, const photo_format_callback_t &callback);
    void get_photo_format_async(const photo_format_callback_t &callback);

    enum class PhotoQuality {
        LOW,
        MEDIUM,
        HIGH,
        ULTRA,
        UNKNOWN
    };

    typedef std::function <void(Result, PhotoQuality)> photo_quality_callback_t;
    void set_photo_quality_async(PhotoQuality photo_quality, const photo_quality_callback_t &callback);
    void get_photo_quality_async(const photo_quality_callback_t &callback);


    enum class VideoFormat {
        H264,
        H265,
        UNKNOWN
    };

    typedef std::function <void(Result, VideoFormat)> video_format_callback_t;
    void set_video_format_async(VideoFormat video_format, const video_format_callback_t &callback);
    void get_video_format_async(const video_format_callback_t &callback);

    enum class VideoResolution {
        UHD_4096_X_2160_60FPS,
        UHD_4096_X_2160_50FPS,
        UHD_4096_X_2160_48FPS,
        UHD_4096_X_2160_30FPS,
        UHD_4096_X_2160_25FPS,
        UHD_4096_X_2160_24FPS,
        UHD_3840_X_2160_60FPS,
        UHD_3840_X_2160_50FPS,
        UHD_3840_X_2160_48FPS,
        UHD_3840_X_2160_30FPS,
        UHD_3840_X_2160_25FPS,
        UHD_3840_X_2160_24FPS,
        UHD_2720_X_1530_60FPS,
        UHD_2720_X_1530_48FPS,
        UHD_2720_X_1530_30FPS,
        UHD_2720_X_1530_24FPS,
        FHD_1920_X_1080_120FPS,
        FHD_1920_X_1080_60FPS,
        FHD_1920_X_1080_50FPS,
        FHD_1920_X_1080_48FPS,
        FHD_1920_X_1080_30FPS,
        FHD_1920_X_1080_25FPS,
        FHD_1920_X_1080_24FPS,
        HD_1280_X_720_120FPS,
        HD_1280_X_720_60FPS,
        HD_1280_X_720_48FPS,
        HD_1280_X_720_30FPS,
        HD_1280_X_720_24FPS,
        UNKNOWN
    };

    typedef std::function <void(Result, VideoResolution)> video_resolution_callback_t;
    void set_video_resolution_async(VideoResolution video_resolution,
                                    const video_resolution_callback_t &callback);
    void get_video_resolution_async(const video_resolution_callback_t &callback);

    struct Metering {
        enum class Mode {
            AVERAGE,
            CENTER,
            SPOT,
            UNKNOWN
        } mode;
        int spot_screen_width_percent; // possible values from 0-99.
        int spot_screen_height_percent; // possible values from 0-99.
    };

    typedef std::function <void(Result, Metering)> metering_callback_t;
    void set_metering_async(Metering metering, const metering_callback_t &callback);
    void get_metering_async(const metering_callback_t &callback);

    typedef std::function<void(Result, std::vector<MediaInfo> &)> get_media_infos_callback_t;
    void get_media_infos_async(const get_media_infos_callback_t &callback);

    typedef std::function<void(Result, int progress)> get_media_callback_t;
    void get_media_async(const std::string &local_path,
                         const std::string &url,
                         const get_media_callback_t &callback);

    /**
     * @brief Information about a picture just captured.
     */
    struct CaptureInfo {
        /**
         * @brief Position type.
         */
        struct Position {
            double latitude_deg; /**< @brief Latitude in degrees (range: -90 to +90) */
            double longitude_deg; /**< @brief Longitude in degrees (range: -180 to 180) */
            float absolute_altitude_m; /**< @brief Altitude AMSL (above mean sea level) in metres */
            float relative_altitude_m; /**< @brief Altitude relative to takeoff altitude in metres */
        } position; /**< @brief Position of drone/camera when image was captured. */

        /**
         * @brief Quaternion type.
         *
         * All rotations and axis systems follow the right-hand rule.
         * The Hamilton quaternion product definition is used.
         * A zero-rotation quaternion is represented by (1,0,0,0).
         * The quaternion could also be written as w + xi + yj + zk.
         *
         * For more info see: https://en.wikipedia.org/wiki/Quaternion
         */
        struct Quaternion {
            float w; /**< @brief Quaternion entry 0 also denoted as a. */
            float x; /**< @brief Quaternion entry 1 also denoted as b. */
            float y; /**< @brief Quaternion entry 2 also denoted as c. */
            float z; /**< @brief Quaternion entry 3 also denoted as d. */
        } quaternion; /**< @brief Quaternion of camera orientation. */

        uint64_t time_utc_us; /**< @brief timestamp in UTC (since UNIX epoch) in microseconds. */
        bool success; /**< @brief True if capture was successful. */
        int index; /**< @brief Zero-based index of this image since armed. */
        std::string file_url; /**< URL of image taken to download. */
    };

    /**
     * @brief Callback type for capture info updates.
     */
    typedef std::function<void(CaptureInfo)> capture_info_callback_t;

    /**
     * @brief Subscribe to capture info updates (asynchronous).
     *
     * @param callback Function to call with updates.
     */
    void capture_info_async(capture_info_callback_t callback);

    // Non-copyable
    Camera(const Camera &) = delete;
    const Camera &operator=(const Camera &) = delete;

private:
    // Underlying implementation, set at instantiation
    CameraImpl *_impl;
};

} // namespace dronecore
