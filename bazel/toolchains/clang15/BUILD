load(":macos_toolchain_config.bzl", "clang15_toolchain_config")

package(default_visibility = ["//visibility:public"])

filegroup(name = "empty")

clang15_toolchain_config(name = "clang15_toolchain_config")

cc_toolchain(
    name = "osx_aarch64_clang15_toolchain",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
    toolchain_config = ":clang15_toolchain_config",
    toolchain_identifier = "k8-clang-toolchain",
)

toolchain(
    name = "clang15_toolchain_for_osx_aarch64",
    exec_compatible_with = [
        "@platforms//cpu:aarch64",
        "@platforms//os:osx",
    ],
    target_compatible_with = [
        "@platforms//cpu:aarch64",
        "@platforms//os:osx",
    ],
    toolchain = ":osx_aarch64_clang15_toolchain",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
)
