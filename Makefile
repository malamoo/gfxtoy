builddir := build
bindir := bin
dirs := $(builddir) $(bindir)
srcs := $(wildcard src/*.c) $(wildcard src/*/*.c)
objs := $(patsubst %.c,$(builddir)/%.o,$(notdir $(srcs)))
deps := $(objs:%.o=%.d)
target := $(bindir)/eemoo

VPATH := $(sort $(dir $(srcs)))
CPPFLAGS = -MT $@ -MMD -MP -MF $(@:%.o=%.d)
CFLAGS = -Wall -Werror -std=c99 -Iinclude
LDLIBS := -lglfw -lGLEW -lGLU -lGL -lm

.PHONY: all
all: $(dirs) $(target)

$(target): $(objs)
	$(CC) $^ -o $@ $(LDLIBS) 

$(builddir)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(dirs):
	mkdir -p $(bindir) $(builddir)

.PHONY: clean
clean:
	$(RM) -r $(bindir) $(builddir)

.PHONY: echo_%
echo_%:
	@echo $($*)

-include $(deps)