objdir := obj
bindir := bin
srcs := $(wildcard src/*.c) $(wildcard src/*/*.c)
objs := $(patsubst %.c,$(objdir)/%.o,$(notdir $(srcs)))
deps := $(objs:%.o=%.d)
target := geosmith

VPATH := $(sort $(dir $(srcs))) # search in all source directories
CPPFLAGS = -MT $@ -MMD -MP -MF $(@:%.o=%.d) # generate dependency target files
CFLAGS = -Wall -Werror -std=c99 -Iinclude
LDLIBS := -lm

# detect platform for linking libs
ifeq ($(OS),Windows_NT)
	LDLIBS += -lglfw3 -lopengl32
else
	LDLIBS += -lglfw -lGL -ldl
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
	$(RM) -r obj bin

.PHONY: echo_%
echo_%:
	@echo $($*)

-include $(deps)