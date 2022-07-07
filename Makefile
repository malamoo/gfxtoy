objdir := obj
bindir := bin
srcs := $(wildcard src/*.c) $(wildcard src/*/*.c)
objs := $(patsubst %.c,$(objdir)/%.o,$(notdir $(srcs)))
deps := $(objs:%.o=%.d)
target := geosmith

VPATH := $(sort $(dir $(srcs))) # search in all source directories
CPPFLAGS = -MT $@ -MMD -MP -MF $(@:%.o=%.d) # generate dependency target files
CFLAGS := -Wall -Werror -std=c99 -Iinclude
LDLIBS := -lm
CC := gcc

# platform-specific configuration
ifeq ($(OS),Windows_NT)
	CFLAGS += -Ilib/glfw/include
	LDLIBS += -Llib/glfw/build/src -lglfw3 -lopengl32 -lgdi32
	RM := del /q
else
	CFLAGS += $(shell env PKG_CONFIG_PATH=lib/glfw/build/src pkg-config --cflags glfw3)
	LDLIBS += $(shell env PKG_CONFIG_PATH=lib/glfw/build/src pkg-config --libs glfw3) -lGL -ldl
	RM := rm -r
endif

.PHONY: all
all: $(bindir)/$(target)

$(bindir)/$(target): $(objs) | $(bindir)
	$(CC) $^ -o $@ $(LDLIBS)

$(bindir):
	@mkdir bin

$(objdir)/%.o: %.c | $(objdir)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(objdir):
	@mkdir obj

.PHONY: clean
clean:
	$(RM) obj bin

.PHONY: echo_%
echo_%:
	@echo $($*)

-include $(deps)