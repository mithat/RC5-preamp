# Project config
ARDUINO_LIBS = RC5
BOARD_TAG = uno
MONITOR_PORT = /dev/ttyACM0
MONITOR_CMD = screen-wrap

# "Platform" config
ARDUINO_QUIET = true
ARDUINO_SKETCHBOOK = $(HOME)/Arduino
ARDUINO_DIR = $(HOME)/.opt/arduino
ARDMK_DIR = $(HOME)/Build/Arduino-Makefile
AVR_TOOLS_DIR = /usr

# Include parent Makefile from <https://github.com/sudar/Arduino-Makefile>
include $(HOME)/Build/Arduino-Makefile/Arduino.mk
