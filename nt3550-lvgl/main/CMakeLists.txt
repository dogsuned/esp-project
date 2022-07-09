file(GLOB_RECURSE SOURCES *.c images/*.c ui/*.c)

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS "." "ui/")
