# SynTHBloK Stereo Phaser by NoiZee ToyZ: a VCV Rack 2 plugin.  make / make dist / make install  (RACK_DIR = your Rack SDK)
RACK_DIR ?= ../..
SOURCES += src/plugin.cpp src/SynTHBloKStereo.cpp
DISTRIBUTABLES += res LICENSE.txt
# Windows: put winpthread inside plugin.dll (new MSYS2 compilers otherwise need a newer libwinpthread than Rack 2.6 ships)
ifeq ($(OS),Windows_NT)
LDFLAGS += -Wl,-Bstatic -lwinpthread -Wl,-Bdynamic
endif
include $(RACK_DIR)/plugin.mk
