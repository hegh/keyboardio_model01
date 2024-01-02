# This stub makefile for a Kaleidoscope plugin pulls in 
# all targets from the Kaleidoscope-Plugin library

UNAME_S := $(shell uname -s)
PACKAGE_DIR ?= $(HOME)/src/keyboardio/arduino-1.8.9
ARDUINO_INSTALLED_ENV=$(shell ls -dt $(PACKAGE_DIR)/hardware/keyboardio/avr 2>/dev/null |head -n 1)

ifneq ("$(wildcard $(ARDUINO_INSTALLED_ENV)/boards.txt)","")
BOARD_HARDWARE_PATH = $(ARDUINO_INSTALLED_ENV)
KALEIDOSCOPE_PLUGIN_MAKEFILE_DIR ?= build-tools/makefiles/
KALEIDOSCOPE_BUILDER_DIR ?= $(ARDUINO_INSTALLED_ENV)/libraries/Kaleidoscope/bin/
endif

include $(BOARD_HARDWARE_PATH)/$(KALEIDOSCOPE_PLUGIN_MAKEFILE_DIR)/rules.mk
