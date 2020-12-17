#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := esp-dual-clouds

ESP_DUAL_CLOUDS_VER := $(shell git rev-parse --short HEAD)

CFLAGS += -DESP_DUAL_CLOUDS_COMMIT_ID=\"$(ESP_DUAL_CLOUDS_VER)\"


ifeq ($(ESP_DUAL_CLOUDS_DIR), )
export ESP_DUAL_CLOUDS_DIR := $(realpath ../../)
endif

EXTRA_COMPONENT_DIRS += $(realpath ../../)/components/
EXTRA_COMPONENT_DIRS += $(realpath .)/components/

ifneq (,$(wildcard $(IDF_PATH)/components/esp8266/*))
export IDF_TARGET = esp8266
else
ifndef IDF_TARGET
export IDF_TARGET := esp32
endif
endif

SDKCONFIG_DEFAULTS ?= $(realpath .)/default_configs/$(IDF_TARGET)/sdkconfig.defaults

include $(IDF_PATH)/make/project.mk
