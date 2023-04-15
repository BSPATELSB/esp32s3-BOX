cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/examples/common_components/protocol_examples_common)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

add_compile_options(-fdiagnostics-color=always)

# The following line can be removed after LVGL update to v8.3.5.
add_compile_options(-Wno-format)

project(image_display)
