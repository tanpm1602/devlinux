# ===== Project =====
TARGET := spws

# ===== Toolchain & Flags =====
CC      := gcc
CSTD    := -std=c11
WARN    := -Wall -Wextra -Wpedantic
OPT     := -O2
DEFS    := -D_POSIX_C_SOURCE=200809L
INCS    := -Iinc -Ihal/inc
CFLAGS  := $(CSTD) $(WARN) $(OPT) $(DEFS) $(INCS)
LDFLAGS := 
LDLIBS  := 

# Bật debug: make DEBUG=1
ifeq ($(DEBUG),1)
  CFLAGS += -g -DDEBUG
endif

# ===== Sources & Objects =====
SRC := \
  $(wildcard src/*.c) \
  $(wildcard hal/src/*.c)

# Ví dụ sẽ tạo: build/src/main.o, build/hal/src/hal_leds.o, ...
OBJ  := $(patsubst %.c,build/%.o,$(SRC))
DEPS := $(OBJ:.o=.d)

# ===== Top-level Targets =====
.PHONY: all clean run debug release print

all: build/$(TARGET)

build/$(TARGET): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)

# ===== Compile .c -> .o (tự sinh dependency .d) =====
build/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# ===== Helpers =====
run: build/$(TARGET)
	./build/$(TARGET)

debug:
	@$(MAKE) all DEBUG=1

release:
	@$(MAKE) clean
	@$(MAKE) all DEBUG=0

print:
	@echo "SRC  = $(SRC)"
	@echo "OBJ  = $(OBJ)"
	@echo "DEPS = $(DEPS)"

clean:
	rm -rf build

# Include dependency để tự rebuild khi .h thay đổi
-include $(DEPS)
