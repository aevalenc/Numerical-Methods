cc_library(
    name = "functions",
    hdrs = ["functions.h"],
    visibility = ["//Newtons-Method/src:__pkg__"],
)

cc_library(
    name = "newtons_method",
    srcs = ["newtons_method.cpp"],
    hdrs = ["newtons_method.h"],
    visibility = ["//Newtons-Method/test:__pkg__"],
    deps = [
        "//Newtons-Method/src:functions",
    ],
)
