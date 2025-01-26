# CC toolchain info
"This file contains the cc toolchain config info"
#
# cc_common is something intrinstic to bazel

# toolchain/cc_toolchain_config.bzl:
# NEW
load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature",
    "flag_group",
    "flag_set",
    "tool_path",
)

# NEW
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

all_link_actions = [
    # NEW
    ACTION_NAMES.cpp_link_executable,
    ACTION_NAMES.cpp_link_dynamic_library,
    ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

BREW_LLVM_PATH = "/opt/homebrew/opt/llvm@15"

def _impl(ctx):
    tool_paths = [
        # NEW
        tool_path(
            name = "gcc",
            path = BREW_LLVM_PATH + "/bin/clang-15",
        ),
        tool_path(
            name = "ld",
            path = "/usr/bin/ld",
        ),
        tool_path(
            name = "ar",
            path = BREW_LLVM_PATH + "/bin/llvm-ar",
        ),
        tool_path(
            name = "cpp",
            path = "/bin/false",
        ),
        tool_path(
            name = "gcov",
            path = "/bin/false",
        ),
        tool_path(
            name = "nm",
            path = "/bin/false",
        ),
        tool_path(
            name = "objdump",
            path = "/bin/false",
        ),
        tool_path(
            name = "strip",
            path = "/bin/false",
        ),
    ]

    # Features allow us to specify linker flags for libraries
    features = [
        # NEW
        feature(
            name = "default_linker_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_link_actions,
                    flag_groups = ([
                        flag_group(
                            flags = [
                                "-lstdc++",
                                "-lm",
                                "-L" + BREW_LLVM_PATH + "/lib",
                            ],
                        ),
                    ]),
                ),
            ],
        ),
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        cxx_builtin_include_directories = [
            # NEW
            BREW_LLVM_PATH + "/include",
            "/usr/include",
        ],
        features = features,
        toolchain_identifier = "local",
        host_system_name = "local",
        target_system_name = "local",
        target_cpu = "k8",
        target_libc = "unknown",
        compiler = "clang",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths,
    )

clang15_toolchain_config = rule(
    implementation = _impl,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)
