cc_binary(
  name = "save-the-world-main",
  deps = [
    "//src:save-the-world-lib",
  ],
  linkopts = [
    "-L/usr/local/lib",
    "-lsfml-graphics",
    "-lsfml-window",
    "-lsfml-system",
    "-lsfml-network",
    "-lsfml-audio",
    "-lpthread"
  ],
  data = glob([
    "Textures/*.png",
    "Fonts/*.ttf"
  ]),
  srcs = ["main.cpp"],
)
