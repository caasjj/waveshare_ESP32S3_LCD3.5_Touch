# List all screen subdirectories here
set(SCREEN_DIRS
    template
    # Add future screen folders here, e.g. another_screen
)

set(SCREEN_SRCS "")
set(SCREEN_INCLUDES ".")

foreach(screen ${SCREEN_DIRS})
    list(APPEND SCREEN_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/${screen}/${screen}.c)
    list(APPEND SCREEN_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/${screen})
endforeach()

idf_component_register(
    SRCS ${SCREEN_SRCS}
    INCLUDE_DIRS ${SCREEN_INCLUDES}
    REQUIRES lvgl
)