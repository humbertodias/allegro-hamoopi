# Project
TARGET       := HAMOOPI
BUILD_DIR    := build
PLATFORM     := $(shell uname -s)-$(shell uname -m)

# Options
BUILD_TYPE   := Debug
SDL2         := ON
CMAKE_FLAGS  := -DUSE_SDL2=$(SDL2) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

.PHONY: build clean zip

build: clean
	cmake -B $(BUILD_DIR) $(CMAKE_FLAGS)
	cmake --build $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TARGET).exe *.o *.so

zip:
	zip -r $(TARGET)-$(PLATFORM).zip data LICENSE README.md SETUP.ini $(TARGET) $(TARGET).exe