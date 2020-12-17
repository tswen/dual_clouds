set(COMPONENT_ADD_INCLUDEDIRS .)

file(GLOB_RECURSE srcs *.c)

set(COMPONENT_SRCS ${srcs})

set(COMPONENT_REQUIRES)

register_component()
