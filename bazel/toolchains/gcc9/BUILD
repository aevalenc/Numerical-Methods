load(":gcc9_toolchain_config.bzl", "gcc9_toolchain_config")

package(default_visibility = ["//visibility:public"])

cc_toolchain_suite(
    name = "gcc9_suite",
    toolchains = {
        "k8": ":k8_gcc9_toolchain",
    },
)

gcc9_toolchain_config(name = "k8_toolchain_gcc9_config")

cc_toolchain(
    name = "k8_gcc9_toolchain",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
    toolchain_config = ":k8_toolchain_gcc9_config",
    toolchain_identifier = "k8-gcc-toolchain",
)