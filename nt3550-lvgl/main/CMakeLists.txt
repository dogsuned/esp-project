file(GLOB_RECURSE SOURCES *.c images/*.c)

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS ".")
