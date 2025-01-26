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
    "variable_with_value",
)

# NEW
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

all_link_actions = [
    # NEW
    ACTION_NAMES.cpp_link_executable,
    ACTION_NAMES.cpp_link_dynamic_library,
    ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

def _impl(ctx):
    tool_paths = [
        # NEW
        tool_path(
            name = "gcc",
            path = "/opt/homebrew/bin/aarch64-apple-darwin24-gcc-14",
        ),
        tool_path(
            name = "ld",
            path = "/usr/bin/ld",
        ),
        tool_path(
            name = "ar",
            # path = "/usr/bin/libtool",
            path = "/opt/homebrew/bin/aarch64-apple-darwin24-gcc-ar-14",
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
    ar_flags_feature = feature(
        name = "archiver_flags",
        flag_sets = [
            flag_set(
                actions = [ACTION_NAMES.cpp_link_static_library],
                flag_groups = [
                    flag_group(flags = [ctx.attr.ar_flags]),
                    flag_group(
                        flags = ["%{output_execpath}"],
                        expand_if_available = "output_execpath",
                    ),
                ],
            ),
            flag_set(
                actions = [ACTION_NAMES.cpp_link_static_library],
                flag_groups = [
                    flag_group(
                        iterate_over = "libraries_to_link",
                        flag_groups = [
                            flag_group(
                                flags = ["%{libraries_to_link.name}"],
                                expand_if_equal = variable_with_value(
                                    name = "libraries_to_link.type",
                                    value = "object_file",
                                ),
                            ),
                            flag_group(
                                flags = ["%{libraries_to_link.object_files}"],
                                iterate_over = "libraries_to_link.object_files",
                                expand_if_equal = variable_with_value(
                                    name = "libraries_to_link.type",
                                    value = "object_file_group",
                                ),
                            ),
                        ],
                        expand_if_available = "libraries_to_link",
                    ),
                ],
            ),
        ],
    )

    default_feature = feature(
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
                            ],
                        ),
                    ]),
                ),
            ],
        )

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        cxx_builtin_include_directories = [
            "/opt/homebrew/Cellar/gcc/14.2.0_1/include/c++/14",
            "/opt/homebrew/Cellar/gcc/14.2.0_1/lib/gcc/current/gcc/aarch64-apple-darwin24/14",
            "/Library/Developer/CommandLineTools/SDKs/MacOSX15.sdk/usr/include"
        ],
        features = [ar_flags_feature, default_feature],
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

gcc14_osx_aarch64_toolchain_config = rule(
    implementation = _impl,
    attrs = {
        "ar_flags": attr.string(default = "rcsD"),
    },
    provides = [CcToolchainConfigInfo],
)
