# CC toolchain info
"This file contains the cc toolchain config info"
#
# cc_common is something intrinstic to bazel

# NEW
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

# toolchain/cc_toolchain_config.bzl:
# NEW
load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature",
    "flag_group",
    "flag_set",
    "tool_path",
)

all_link_actions = [
    # NEW
    ACTION_NAMES.cpp_link_executable,
    ACTION_NAMES.cpp_link_dynamic_library,
    ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

all_compile_actions = [
    # NEW
    ACTION_NAMES.c_compile,
    ACTION_NAMES.cpp_compile,
]

def _impl(ctx):
    tool_paths = [
        tool_path(name = "gcc", path = "/usr/bin/mpicxx"),
        tool_path(name = "ld", path = "/usr/bin/ld"),
        tool_path(name = "ar", path = "/usr/bin/gcc-ar-9"),
        tool_path(name = "cpp", path = "/bin/false"),
        tool_path(name = "gcov", path = "/bin/false"),
        tool_path(name = "nm", path = "/usr/bin/gcc-nm-9"),
        tool_path(name = "objdump", path = "/bin/false"),
        tool_path(name = "strip", path = "/bin/false"),
    ]

    # Features allow us to specify linker flags for libraries
    features = [
        # NEW
        feature(
            name = "openmpi_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_link_actions,
                    flag_groups = ([
                        flag_group(
                            flags = [
                                "-lstdc++",
                                "-lm",
                                "-pthread",
                                "-L/usr/lib/x86_64-linux-gnu/openmpi/lib",
                                "-lmpi",
                            ],
                        ),
                    ]),
                ),
                flag_set(
                    actions = all_compile_actions,
                    flag_groups = ([
                        flag_group(
                            flags = [
                                "-pthread",
                                "-I/usr/lib/x86_64-linux-gnu/openmpi/include/openmpi",
                                "-I/usr/lib/x86_64-linux-gnu/openmpi/include",
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
            "/usr/lib/gcc/x86_64-linux-gnu/9/include",
            "/usr/include",
            "/usr/lib/x86_64-linux-gnu/openmpi/include/openmpi",
            "/usr/lib/x86_64-linux-gnu/openmpi/include",
        ],
        features = features,
        toolchain_identifier = "local",
        host_system_name = "local",
        target_system_name = "local",
        target_cpu = "k8",
        target_libc = "unknown",
        compiler = "gcc",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths,
    )

linux_x86_64_toolchain_config = rule(
    implementation = _impl,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)
