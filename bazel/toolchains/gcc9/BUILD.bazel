load(":linux_x86_64_toolchain_config.bzl", "linux_x86_64_toolchain_config")

package(default_visibility = ["//visibility:public"])

filegroup(name = "empty")

linux_x86_64_toolchain_config(name = "linux_x86_64_toolchain_config")

cc_toolchain(
    name = "linux_x86_64",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
    toolchain_config = ":linux_x86_64_toolchain_config",
    toolchain_identifier = "k8-gcc-toolchain",
)

toolchain(
    name = "gcc9_toolchain_for_linux_x86_64",
    exec_compatible_with = [
        "@platforms//cpu:x86_64",
        "@platforms//os:linux",
    ],
    target_compatible_with = [
        "@platforms//cpu:x86_64",
        "@platforms//os:linux",
    ],
    toolchain = ":linux_x86_64",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
)
