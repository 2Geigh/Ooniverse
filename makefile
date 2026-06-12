CC := gcc
CFLAGS := -Wall -Wextra -O2 -Iinclude

# Adjusted rpath to relative path matching project layout
LDFLAGS := -Llib -Wl,-rpath,@loader_path/lib
LDLIBS := -lglfw.3 -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL

SRCDIR := src
OBJDIR := build
TARGET := Ooniverse

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all clean dirs FORCE

# Chaining clean before the target forces a rebuild
all: clean
	$(MAKE) $(TARGET)

dirs:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -rf $(OBJDIR) $(TARGET)