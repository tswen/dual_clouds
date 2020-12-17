set(COMPONENT_ADD_INCLUDEDIRS .)

set(COMPONENT_SRCS "CJSON.c" "linkkit_solo.c")

set(COMPONENT_REQUIRES "esp-ali-smartliving" "json" )

register_component()
