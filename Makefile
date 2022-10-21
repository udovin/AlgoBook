# Recursive find by pattern
find = $(foreach file, $(wildcard $1/*), $(filter $2, $(file)) $(call find, $(file), $2))

SOURCE_TESTS := $(call find, tests, %.cpp)
BINARY_TESTS := $(patsubst tests/%.cpp, tests/%, $(SOURCE_TESTS))

tests: $(BINARY_TESTS)

tests/%: tests/%.cpp
	@echo "[CC] '$<'"
	@g++ --std=c++17 -Isource -o "$@" "$<"
	@echo "[TS] '$<'"
	@./$@
	@rm -f "$@"
