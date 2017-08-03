#pragma once

#include <functional>
#include <vector>
#include <map>
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
        VIDEO,
        UNKNOWN
    };

    void set_mode_async(Mode mode, const result_callback_t &callback);

    typedef std::function<void(Result, const Mode &)> get_mode_callback_t;
    void get_mode_async(const get_mode_callback_t &callback);

    Result take_photo();

    Result start_photo_interval(double interval_s);
    Result stop_photo_interval();

    Result start_video();
    Result stop_video();

    void take_photo_async(const result_callback_t &callback);

    void start_photo_interval_async(double interval_s, const result_callback_t &callback);
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
        AUTO = 0,
        INCANDESCENT = 1,
        SUNSET = 3,
        SUNNY = 4,
        CLOUDY = 5,
        FLUORESCENT = 7,
        LOCK = 99
    };

    void set_white_balance_async(WhiteBalance white_balance, const result_callback_t &callback);

    typedef std::function <void(Result, WhiteBalance white_balance)> get_white_balance_callback_t;
    void get_white_balance_async(const get_white_balance_callback_t &callback);

    enum class ColorMode {
        NEUTRAL = 0,
        ENHANCED = 1,
        NIGHT = 3,
        UNPROCESSED = 2
    };

    void set_color_mode_async(ColorMode color_mode, const result_callback_t &callback);

    typedef std::function <void(Result, ColorMode)> get_color_mode_callback_t;
    void get_color_mode_async(const get_color_mode_callback_t &callback);


    typedef std::function<void(Result, std::vector<MediaInfo> &)> get_media_infos_callback_t;
    void get_media_infos_async(const get_media_infos_callback_t &callback);

    typedef std::function<void(Result, int progress)> get_media_callback_t;
    void get_media_async(const std::string &local_path,
                         const std::string &url,
                         const get_media_callback_t &callback);

    // Non-copyable
    Camera(const Camera &) = delete;
    const Camera &operator=(const Camera &) = delete;

private:
    // Underlying implementation, set at instantiation
    CameraImpl *_impl;
};

} // namespace dronelink
