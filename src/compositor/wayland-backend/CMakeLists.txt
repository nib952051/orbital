
find_package(Qt5Core)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

set(SOURCES wayland-backend.cpp)

add_library(wayland-backend SHARED ${SOURCES})
qt5_use_modules(wayland-backend Core)
install(TARGETS wayland-backend DESTINATION lib/orbital/compositor/backends)
