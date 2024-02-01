CXX := g++

TARGET := build/avl_tree

SRCDIR := src
INCDIR := include
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CXXFLAGS := -g -Wall -I$(INCDIR) -std=c++11

LFLAGS :=

ifeq ($(OS),Windows_NT)
    MKDIR_P = if not exist "$(subst /,\,$1)" mkdir "$(subst /,\,$1)"
    RM = del /Q /F
    RMDIR = if exist "$(subst /,\,$1)" rmdir /S /Q "$(subst /,\,$1)"
    FixPath = $(subst /,\,$1)
else
    MKDIR_P = mkdir -p $1
    RM = rm -f $1
    RMDIR = rm -rf $1
    FixPath = $1
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDES)
	@$(call MKDIR_P,$(OBJDIR))
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	@$(call MKDIR_P,$(BUILDDIR))
	$(CXX) $^ -o $(TARGET) $(LFLAGS)

all: $(TARGET)

clean:
	@echo " Cleaning..."
	@$(call RMDIR,$(BUILDDIR))

.PHONY: clean
