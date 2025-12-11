# Project
TARGET       := HAMOOPI
BUILD_DIR    := build
PLATFORM     := $(shell uname -s)-$(shell uname -m)

# Options
BUILD_TYPE   := Debug
CMAKE_FLAGS  :=

.PHONY: build clean zip

build: clean
	cmake -B $(BUILD_DIR) $(CMAKE_FLAGS)
	cmake --build $(BUILD_DIR) --config $(BUILD_TYPE)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TARGET).exe *.o *.so

zip:
	zip -r $(TARGET)-$(PLATFORM).zip data LICENSE README.md SETUP.ini $(TARGET) $(TARGET).exe