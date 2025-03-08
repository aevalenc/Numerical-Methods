load("@bazel_skylib//rules:common_settings.bzl", "bool_flag")

bool_flag(
    name = "print_debug_info_flag",
    build_setting_default = False,
)

config_setting(
    name = "print_debug_info",
    flag_values = {
        ":print_debug_info_flag": "True",
    },
)
