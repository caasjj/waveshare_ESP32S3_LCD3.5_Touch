file(GLOB LIB_SOURCES "lib/*.c")

idf_component_register(
    SRCS "main.c" ${LIB_SOURCES}
    INCLUDE_DIRS "." "lib"
)