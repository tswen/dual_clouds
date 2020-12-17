set(COMPONENT_ADD_INCLUDEDIRS "")

# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )

set(COMPONENT_PRIV_REQUIRES "ali_smartliving_extern" "esp-joylink" "conn_mgr" )

set(COMPONENT_SRCS ./app_main.c ./app_joylink.c ./app_ali_smartliving.c )

register_component()
