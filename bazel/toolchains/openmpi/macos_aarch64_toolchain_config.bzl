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
    "variable_with_value",
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

BREW_OPENMPI_BIN_PATH = "/opt/homebrew/bin"
BREW_OPENMPI_INCLUDE_PATH = "/opt/homebrew/Cellar/open-mpi/5.0.8/include"
BREW_OPENMPI_LIB_PATH = "/opt/homebrew/Cellar/open-mpi/5.0.8/lib"
CLANG_SDK_INCLUDE_PATH = "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk"
CLANG_LIB_PATH = "/Library/Developer/CommandLineTools/usr/lib/clang/17/include"

def _impl(ctx):
    tool_paths = [
        tool_path(name = "gcc", path = BREW_OPENMPI_BIN_PATH + "/mpicxx"),
        tool_path(name = "ld", path = "/usr/bin/ld"),
        tool_path(name = "ar", path = "/usr/bin/ar"),
        tool_path(name = "cpp", path = "/bin/false"),
        tool_path(name = "gcov", path = "/bin/false"),
        tool_path(name = "nm", path = "/bin/false"),
        tool_path(name = "objdump", path = "/bin/false"),
        tool_path(name = "strip", path = "/bin/false"),
    ]

    # Features allow us to specify linker flags for libraries
    openmpi_feature = feature(
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
                            "-L" + BREW_OPENMPI_LIB_PATH,
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
                            "-I" + BREW_OPENMPI_INCLUDE_PATH,
                        ],
                    ),
                ]),
            ),
        ],
    )

    # Features allow us to specify linker flags for libraries
    ar_flags_feature = feature(
        name = "archiver_flags",
        enabled = True,
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

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        cxx_builtin_include_directories = [
            "/usr/include",
            BREW_OPENMPI_INCLUDE_PATH,
            BREW_OPENMPI_LIB_PATH,
            CLANG_SDK_INCLUDE_PATH,
            CLANG_LIB_PATH,
        ],
        features = [openmpi_feature, ar_flags_feature],
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

macos_aarch64_mpi_toolchain_config = rule(
    implementation = _impl,
    attrs = {"ar_flags": attr.string(default = "rcsD")},
    provides = [CcToolchainConfigInfo],
)
