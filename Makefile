objdir := obj
bindir := bin
srcs := $(wildcard src/*.c) $(wildcard src/*/*.c)
objs := $(patsubst %.c,$(objdir)/%.o,$(notdir $(srcs)))
deps := $(objs:%.o=%.d)
target := geosmith

VPATH := $(sort $(dir $(srcs))) # search in all source directories
CPPFLAGS = -MT $@ -MMD -MP -MF $(@:%.o=%.d) # generate dependency target files
CFLAGS := -Wall -Werror -std=c99 -Iinclude -Ilib/glfw/include
LDLIBS := -lm -Llib/glfw/build/src -lglfw3
CC := gcc

# platform-specific configuration
ifeq ($(OS),Windows_NT)
	LDLIBS += -lopengl32 -lgdi32
	RM := del /q
else
	LDLIBS += -lGL -ldl
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