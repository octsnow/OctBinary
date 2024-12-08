encode = $(subst $() ,*,$(1))
decode = $(subst *,$() ,$(1))
quotes = $(addprefix ",$(addsuffix ",$(1)))
includes = $(addprefix -I,$(1))

RM = cmd.exe /C del

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.obj,$(SRCS))
INC_DIR = includes C:\glut\freeglut-3.2.1\install\include

INC_DIR := $(call includes,$(INC_DIR))

TARGET = lib\oct_binary

CXXFLAGS = /EHsc /std:c++20 /c

.SUFFIXES:.obj .cpp

.PHONY: release build
release: $(OBJS)
	lib $(OBJS) /OUT:$(TARGET).lib

$(OBJ_DIR)/%.obj: $(SRC_DIR)/%.cpp
	cl $(CXXFLAGS) $< /Fo$@ $(INC_DIR)

clean:
	-$(RM) $(subst /,\,$(OBJS)) $(subst /,\,$(TARGET).lib) $(subst /,\,$(TARGET)_d.lib)
