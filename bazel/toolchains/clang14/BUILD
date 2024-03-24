load(":clang14_toolchain_config.bzl", "clang14_toolchain_config")

cc_toolchain_suite(
    name = "clang14_suite",
    toolchains = {
        "k8": ":k8_clang14_toolchain",
    },
)

clang14_toolchain_config(name = "k8_clang14_toolchain_config")

cc_toolchain(
    name = "k8_clang14_toolchain",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
    toolchain_config = ":k8_clang14_toolchain_config",
    toolchain_identifier = "k8-clang-toolchain",
)
