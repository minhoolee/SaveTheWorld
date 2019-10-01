filegroup(
  name = "srcs",
  srcs = glob([
    "src/**/*.cpp"
  ]),
)
cc_library(
  name = "save-the-world-lib",
  srcs = glob(["**/*.cpp"]),
  hdrs = glob(["**/*.hpp"]),
  visibility = ["//:__pkg__"],
)
