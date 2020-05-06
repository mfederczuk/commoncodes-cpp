# C/C++ Makefile Template for applications and libraries.
# Copyright (C) 2019 Michael Federczuk
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# === user definitions ======================================================= #

SOFTWARE = lib

TARGET = commoncodes++

SRC_MAIN = src/main
SRC_TEST = src/test
BIN = bin
INC = include/$(TARGET)

TEST = ./test --valgrind

CCFLAGS  = -Iinclude -std=c17   -Wall -Wextra
CXXFLAGS = -Iinclude -std=c++17 -Wall -Wextra

# === colors ================================================================= #

# reset:     0
# bold:      1
# italic:    3
# underline: 4
# black:    30  |  bright black:   90
# red:      31  |  bright red:     91
# yellow:   33  |  bright yellow:  93
# green:    32  |  bright green:   92
# cyan:     36  |  bright cyan:    96
# blue:     34  |  bright blue:    94
# magenta:  35  |  bright magenta: 95
# white:    37  |  bright white:   97
_ascii_esc = $(shell printf '\033[$(1)m')

reset_fx        := $(call _ascii_esc,0)
error_fx        := $(call _ascii_esc,91;1)
warning_fx      := $(call _ascii_esc,33)
object_build_fx := $(call _ascii_esc,34)
target_build_fx := $(call _ascii_esc,34;1)
test_build_fx   := $(call _ascii_esc,35;1)
install_fx      := $(call _ascii_esc,32)
uninstall_fx    := $(call _ascii_esc,91)
clean_fx        := $(call _ascii_esc,91)

# === preconditions ========================================================== #

-include _debug.mk

ifndef SOFTWARE
 $(error $(error_fx)SOFTWARE is not defined$(reset_fx))
endif
override SOFTWARE := $(strip $(SOFTWARE))
ifeq "$(SOFTWARE),$(TARGET),$(SRC),$(SRC_MAIN),$(SRC_TEST),$(BIN),$(INC),$(LINKS),$(LINK_DIRS),$(TEST),$(CCFLAGS),$(CXXFLAGS)" \
     "exe|lib,,,src/main,src/test,bin,include/$(TARGET),,,,-Iinclude -std=c17   -Wall -Wextra,-Iinclude -std=c++17 -Wall -Wextra"
 $(error $(error_fx)Makefile is not configured$(reset_fx))
endif
ifneq "$(SOFTWARE)" "exe"
 ifneq "$(SOFTWARE)" "lib"
  $(error $(error_fx)Software type ("$(SOFTWARE)") is unknown$(reset_fx))
 endif
endif

ifndef TARGET
 $(error $(error_fx)TARGET is not defined$(reset_fx))
endif
override TARGET := $(strip $(TARGET))

ifdef SRC_MAIN
 ifndef SRC_TEST
  $(error $(error_fx)SRC_MAIN is defined but SRC_TEST is not defined. \
          If you don't want to use tests, \
          consider using SRC instead of SRC_MAIN$(reset_fx))
 endif
 override SRC_TEST := $(strip $(SRC_TEST))

 ifeq "$(SRC_MAIN)" "$(SRC_TEST)"
  $(error $(error_fx)SRC_MAIN and SRC_TEST are equal. \
          If you don't want to use tests, \
          consider using just SRC instead of SRC_MAIN and SRC_TEST$(reset_fx))
 endif
 override SRC_MAIN := $(strip $(SRC_MAIN))

 ifdef SRC
  $(warning $(warning_fx)SRC is ignored if SRC_MAIN is defined. \
            Consider removing it$(reset_fx))
 endif
else
 ifndef SRC
  $(error $(error_fx)Neither SRC nor SRC_MAIN are defined$(reset_fx))
 endif
 override SRC_MAIN := $(strip $(SRC))

 ifdef SRC_TEST
  $(warning $(warning_fx)SRC_TEST is ignored if SRC_MAIN is not defined and \
            SRC is defined. \
            Consider removing it$(reset_fx))
 endif
 override SRC_TEST := /dev/null
endif

ifndef BIN
 $(error $(error_fx)BIN is not defined$(reset_fx))
endif
override BIN := $(strip $(BIN))

ifneq "$(SOFTWARE)" "exe"
 ifndef INC
  $(error $(error_fx)INC is not defined$(reset_fx))
 endif
 override INC := $(strip $(INC))
endif

# warnings/errors about LINKS and LINK_DIRS
ifeq "$(SOFTWARE)" "exe"
 ifdef LINK_DIRS
  ifndef LINKS
   $(warning $(warning_fx)LINK_DIRS is defined, but LINKS isn't. \
             Specifying link directories without links doesn't do anything. \
             Consider either removing LINK_DIRS or defining LINKS$(reset_fx))
  endif
 endif
else
 ifdef LINKS
  $(warning $(warning_fx)LINKS is defined, but is ignored when building a \
            library. Consider removing LINKS$(reset_fx))
 endif
 ifdef LINK_DIRS
  $(warning $(warning_fx)LINK_DIRS is defined, but is ignored when building a \
            library. Consider removing LINK_DIRS$(reset_fx))
 endif
endif

ifndef TEST
 $(error $(error_fx)TEST is not defined. \
         If you don't have any tests, define it as ':'$(reset_fx))
endif
override TEST := $(strip $(TEST))

# === variables ============================================================== #

SHELL = /bin/sh
prefix      = /usr/local
exec_prefix = $(prefix)
bindir      = $(exec_prefix)/bin
includedir  = $(prefix)/include
libdir      = $(exec_prefix)/lib

# normally, shared object files also have the .o extension, to hold them apart
# we're going to use .so (which literally stands for shared object).
# it's important that these two variables are different
shared_object_ext = so
static_object_ext = o

# better not change those
shared_lib_prefix = lib
static_lib_prefix = lib
shared_lib_suffix = .so
static_lib_suffix = .a

# *nix executables usually don't have a suffix, if you want you can change that
exe_prefix =
exe_suffix =

test_prefix = $(exe_prefix)
test_suffix = _test$(exe_suffix)

# in case these are not defined for some reason
CC      ?= cc
CXX     ?= c++
AR      ?= ar
INSTALL ?= install

# === custom functions ======================================================= #

override _eq = $(and $(findstring $(1),$(2)),$(findstring $(2),$(1)))

override _test_target = $(word 1,$(subst :, ,$(1)))
override _test_source = $(word 2,$(subst :, ,$(1)))

override _color_pipe = sed -E s/'.*'/'$(1)\0$(reset_fx)'/g

# === constants ============================================================== #

override LINK_FLAGS := $(addprefix -L,$(LINK_DIRS)) $(addprefix -l,$(LINKS))

override _find_c_files   = $(foreach \
		__file, \
		$(shell find '$(1)' \
				-type f \
				-name '*.[ci]' \
		), \
		$(__file:$(1)/%=%) \
)
override _find_cxx_files = $(foreach \
		__file, \
		$(shell find '$(1)' \
				-type f \
				'(' \
						-name '*.C'   -o \
						-name '*.cc'  -o \
						-name '*.cp'  -o \
						-name '*.ii'  -o \
						-name '*.c++' -o \
						-name '*.cpp' -o \
						-name '*.CPP' -o \
						-name '*.cxx'    \
				')' \
		), \
		$(__file:$(1)/%=%) \
)

override C_SOURCES   := $(call _find_c_files,$(SRC_MAIN))
override CXX_SOURCES := $(call _find_cxx_files,$(SRC_MAIN))

# checking if source files were found
ifeq "$(C_SOURCES)$(CXX_SOURCES)" ""
 $(error $(error_fx)No source files found$(reset_fx))
endif

override TEST_C_SOURCES   := $(call _find_c_files,$(SRC_TEST))
override TEST_CXX_SOURCES := $(call _find_cxx_files,$(SRC_TEST))

# shared objects
override SHARED_C_OBJECTS   := $(foreach __source_file,$(C_SOURCES), \
	$(BIN)/$(__source_file).$(shared_object_ext) \
)
override SHARED_CXX_OBJECTS := $(foreach __source_file,$(CXX_SOURCES), \
	$(BIN)/$(__source_file).$(shared_object_ext) \
)
override SHARED_OBJECTS     := $(SHARED_C_OBJECTS) $(SHARED_CXX_OBJECTS)

# static objects
override STATIC_C_OBJECTS   := $(foreach __source_file,$(C_SOURCES), \
	$(BIN)/$(__source_file).$(static_object_ext) \
)
override STATIC_CXX_OBJECTS := $(foreach __source_file,$(CXX_SOURCES), \
	$(BIN)/$(__source_file).$(static_object_ext) \
)
override STATIC_OBJECTS     := $(STATIC_C_OBJECTS) $(STATIC_CXX_OBJECTS)

# targets
override SHARED_LIB_TARGET := $(shared_lib_prefix)$(TARGET)$(shared_lib_suffix)
override STATIC_LIB_TARGET := $(static_lib_prefix)$(TARGET)$(static_lib_suffix)
override EXE_TARGET        := $(exe_prefix)$(TARGET)$(exe_suffix)

override C_TESTS   := $(foreach __source_file,$(TEST_C_SOURCES), \
	$(test_prefix)$(basename $(notdir $(__source_file)))$(test_suffix):$(__source_file) \
)
override CXX_TESTS := $(foreach __source_file,$(TEST_CXX_SOURCES), \
	$(test_prefix)$(basename $(notdir $(__source_file)))$(test_suffix):$(__source_file) \
)

override TEST_C_TARGETS   := $(foreach __test,$(C_TESTS), \
	$(call _test_target,$(__test)) \
)
override TEST_CXX_TARGETS := $(foreach __test,$(CXX_TESTS), \
	$(call _test_target,$(__test)) \
)
override TEST_TARGETS     := $(TEST_C_TARGETS) $(TEST_CXX_TARGETS)

# === default rule =========================================================== #

ifeq "$(SOFTWARE)" "exe"
 all: $(EXE_TARGET)
 .PHONY: all
else
 all: targets
 .PHONY: all
endif

# === universe rule ========================================================== #

ifeq "$(SOFTWARE)" "exe"
 ifneq "$(SRC_TEST)" "/dev/null"
  _universe: $(EXE_TARGET) tests
  .PHONY: _universe
 else
  _universe: $(EXE_TARGET)
  .PHONY: _universe
 endif
else
 ifneq "$(SRC_TEST)" "/dev/null"
  _universe: targets tests
  .PHONY: _universe
 else
  _universe: targets
  .PHONY: _universe
 endif
endif

# === building object files ================================================== #

ifeq "$(SOFTWARE)" "exe"
 objects: $(STATIC_OBJECTS)
 $(STATIC_C_OBJECTS):   $(BIN)/%.$(static_object_ext): $(SRC_MAIN)/%
	@mkdir -p '$(dir $@)'
	$(info $(object_build_fx)Building file '$@'...$(reset_fx))
	@$(CC)  $(CCFLAGS) -c '$<' -o '$@'
 $(STATIC_CXX_OBJECTS): $(BIN)/%.$(static_object_ext): $(SRC_MAIN)/%
	@mkdir -p '$(dir $@)'
	$(info $(object_build_fx)Building file '$@'...$(reset_fx))
	@$(CXX) $(CXXFLAGS) -c '$<' -o '$@'
 .PHONY: objects
else
 objects: objects/shared objects/static
 objects/shared: $(SHARED_OBJECTS)
 objects/static: $(STATIC_OBJECTS)
 $(SHARED_C_OBJECTS):   $(BIN)/%.$(shared_object_ext): $(SRC_MAIN)/%
	@mkdir -p '$(dir $@)'
	$(info $(object_build_fx)Building file '$@'...$(reset_fx))
	@$(CC)  $(CCFLAGS) -c '$<' -o '$@' -fPIC
 $(SHARED_CXX_OBJECTS): $(BIN)/%.$(shared_object_ext): $(SRC_MAIN)/%
	@mkdir -p '$(dir $@)'
	$(info $(object_build_fx)Building file '$@'...$(reset_fx))
	@$(CXX) $(CXXFLAGS) -c '$<' -o '$@' -fPIC
 $(STATIC_C_OBJECTS):   $(BIN)/%.$(static_object_ext): $(SRC_MAIN)/%
	@mkdir -p '$(dir $@)'
	$(info $(object_build_fx)Building file '$@'...$(reset_fx))
	@$(CC)  $(CCFLAGS) -c '$<' -o '$@'
 $(STATIC_CXX_OBJECTS): $(BIN)/%.$(static_object_ext): $(SRC_MAIN)/%
	@mkdir -p '$(dir $@)'
	$(info $(object_build_fx)Building file '$@'...$(reset_fx))
	@$(CXX) $(CXXFLAGS) -c '$<' -o '$@'
 .PHONY: objects objects/shared objects/static
endif

# === building targets ======================================================= #

ifeq "$(SOFTWARE)" "exe"
 $(EXE_TARGET): $(STATIC_OBJECTS)
	$(info $(target_build_fx)Building target '$@'...$(reset_fx))
  ifeq "$(CXX_SOURCES)" ""
	@$(CC)  $(CCFLAGS)  $^ -o '$@' $(LINK_FLAGS)
  else
	@$(CXX) $(CXXFLAGS) $^ -o '$@' $(LINK_FLAGS)
  endif
else
 targets: $(SHARED_LIB_TARGET) $(STATIC_LIB_TARGET)
 $(SHARED_LIB_TARGET): $(SHARED_OBJECTS)
	$(info $(target_build_fx)Building target '$@'...$(reset_fx))
  ifeq "$(CXX_SOURCES)" ""
	@$(CC)  $(CCFLAGS)  $^ -o '$@' -shared
  else
	@$(CXX) $(CXXFLAGS) $^ -o '$@' -shared
  endif
 $(STATIC_LIB_TARGET): $(STATIC_OBJECTS)
	$(info $(target_build_fx)Building target '$@'...$(reset_fx))
	@$(AR) rs '$@' $^ 2>/dev/null
 .PHONY: targets
endif

# === testing ================================================================ #

ifneq "$(SRC_TEST)" "/dev/null"
 override _find_test_source = $(foreach __test,$(C_TESTS) $(CXX_TESTS), \
	$(if \
		$(call _eq,$(1),$(call _test_target,$(__test))), \
		$(call _test_source,$(__test)) \
	) \
 )

 ifeq "$(SOFTWARE)" "exe"
  tests: $(TEST_TARGETS)
  .SECONDEXPANSION:
  $(TEST_C_TARGETS): %:   $(SRC_TEST)/$$(strip $$(call _find_test_source,%))
	$(info $(test_build_fx)Building test '$@'...$(reset_fx))
	@$(CC)  $(CCFLAGS)  '$<' -o '$@'
  .SECONDEXPANSION:
  $(TEST_CXX_TARGETS): %: $(SRC_TEST)/$$(strip $$(call _find_test_source,%))
	$(info $(test_build_fx)Building test '$@'...$(reset_fx))
	@$(CXX) $(CXXFLAGS) '$<' -o '$@'
  test: $(TEST_TARGETS)
	@$(TEST) $(addprefix ./,$^)
  .PHONY: tests test
 else
  tests: $(TEST_TARGETS)
  .SECONDEXPANSION:
  $(TEST_C_TARGETS): %:   $(STATIC_OBJECTS) \
                          $(SRC_TEST)/$$(strip $$(call _find_test_source,%))
	$(info $(test_build_fx)Building test '$@'...$(reset_fx))
	@$(CC)  $(CCFLAGS)  $^ -o '$@'
  .SECONDEXPANSION:
  $(TEST_CXX_TARGETS): %: $(STATIC_OBJECTS) \
                          $(SRC_TEST)/$$(strip $$(call _find_test_source,%))
	$(info $(test_build_fx)Building test '$@'...$(reset_fx))
	@$(CXX) $(CXXFLAGS) $^ -o '$@'
  test: $(TEST_TARGETS)
	@$(TEST) $(addprefix ./,$^)
  .PHONY: tests test
 endif
endif

# === installing ============================================================= #

ifeq "$(SOFTWARE)" "exe"
 install: $(EXE_TARGET)
	$(info $(install_fx)Installing target '$@' to '$(DESTDIR)$(bindir)'...$(reset_fx))
	@$(INSTALL) -m755 '$@' '$(DESTDIR)$(bindir)'
 .PHONY: install
else
 install: install/targets install/headers
 install/targets: install/$(SHARED_LIB_TARGET) install/$(STATIC_LIB_TARGET)
 install/$(SHARED_LIB_TARGET) install/$(STATIC_LIB_TARGET): install/%: %
	$(info $(install_fx)Installing target '$(@:install/%=%)' to '$(DESTDIR)$(libdir)'...$(reset_fx))
	@$(INSTALL) -m644 '$(@:install/%=%)' '$(DESTDIR)$(libdir)'
 install/headers:
	$(info $(install_fx)Installing headers to '$(DESTDIR)$(includedir)'...$(reset_fx))
	@cp -r '$(INC)' '$(DESTDIR)$(includedir)'
 .PHONY: install install/targets \
         install/$(SHARED_LIB_TARGET) install/$(STATIC_LIB_TARGET) \
         install/headers
endif

# === uninstalling =========================================================== #

ifeq "$(SOFTWARE)" "exe"
 uninstall:
	@rm -f '$(DESTDIR)$(bindir)/$(EXE_TARGET)' | \
		sed -E s/'(.*)'/'$(uninstall_fx)\1$(reset_fx)'/g
 .PHONY: uninstall
else
 uninstall: uninstall/targets uninstall/headers
 uninstall/targets: uninstall/$(SHARED_LIB_TARGET) uninstall/$(STATIC_LIB_TARGET)
 uninstall/$(SHARED_LIB_TARGET) uninstall/$(STATIC_LIB_TARGET): %:
	@rm -fv '$(DESTDIR)$(libdir)/$(@:uninstall/%=%)' | \
		$(call _color_pipe,$(uninstall_fx))
 uninstall/headers:
	@rm -rfv '$(DESTDIR)$(includedir)/$(notdir $(INC))' | \
		$(call _color_pipe,$(uninstall_fx))
 .PHONY: uninstall uninstall/targets \
         uninstall/$(SHARED_LIB_TARGET) uninstall/$(STATIC_LIB_TARGET) \
         uninstall/headers
endif

# === cleaning =============================================================== #

override _clean_empty_dir = if [ -d '$(1)' ]; then \
	find '$(BIN)' -depth -type d -exec rm -dfv '{}' ';' 2>/dev/null \
		| $(call _color_pipe,$(clean_fx)) ; \
fi

override CLEANING_STATIC_OBJECTS := $(addprefix clean/,$(STATIC_OBJECTS))
override CLEANING_SHARED_OBJECTS := $(addprefix clean/,$(SHARED_OBJECTS))
override CLEANING_OBJECTS        := $(CLEANING_SHARED_OBJECTS) \
                                    $(CLEANING_STATIC_OBJECTS)

override CLEANING_TEST_TARGETS := $(addprefix clean/,$(TEST_TARGETS))

ifeq "$(SOFTWARE)" "exe"
 ifneq "$(SRC_TEST)" "/dev/null"
  clean: clean/objects clean/$(EXE_TARGET) clean/tests
  .PHONY: clean
 else
  clean: clean/objects clean/$(EXE_TARGET)
  .PHONY: clean
 endif

 clean/objects: $(CLEANING_STATIC_OBJECTS)
 $(CLEANING_STATIC_OBJECTS): %:
	@rm -fv '$(@:clean/%=%)' | $(call _color_pipe,$(clean_fx))
	@$(call _clean_empty_dir,$(BIN))
 .PHONY: clean/objects $(CLEANING_STATIC_OBJECTS)

 clean/$(EXE_TARGET):
	@rm -fv '$@' | $(call _color_pipe,$(clean_fx))
 .PHONY: clean/$(EXE_TARGET)

 ifneq "$(SRC_TEST)" "/dev/null"
  clean/tests: $(CLEANING_TEST_TARGETS)
  $(CLEANING_TEST_TARGETS): %:
	@rm -fv '$(@:clean/%=%)' | $(call _color_pipe,$(clean_fx))
  .PHONY: clean/tests $(CLEANING_TEST_TARGETS)
 endif
else
 ifneq "$(SRC_TEST)" "/dev/null"
  clean: clean/objects clean/targets clean/tests
  .PHONY: clean
 else
  clean: clean/objects clean/targets
  .PHONY: clean
 endif

 clean/objects: clean/objects/shared clean/objects/static
 clean/objects/shared: $(CLEANING_SHARED_OBJECTS)
 clean/objects/static: $(CLEANING_STATIC_OBJECTS)
 $(CLEANING_OBJECTS): %:
	@rm -fv '$(@:clean/%=%)' | $(call _color_pipe,$(clean_fx))
	@$(call _clean_empty_dir,$(BIN))
 .PHONY: clean/objects \
         clean/objects/shared clean/objects/static \
         $(CLEANING_OBJECTS)

 clean/targets: clean/$(SHARED_LIB_TARGET) clean/$(STATIC_LIB_TARGET)
 clean/$(SHARED_LIB_TARGET) clean/$(STATIC_LIB_TARGET): %:
	@rm -fv '$(@:clean/%=%)' | $(call _color_pipe,$(clean_fx))
 .PHONY: clean/targets clean/$(SHARED_LIB_TARGET) clean/$(STATIC_LIB_TARGET)

 ifneq "$(SRC_TEST)" "/dev/null"
  clean/tests: $(CLEANING_TEST_TARGETS)
  $(CLEANING_TEST_TARGETS): %:
	@rm -fv '$(@:clean/%=%)' | $(call _color_pipe,$(clean_fx))
  .PHONY: clean/tests $(CLEANING_TEST_TARGETS)
 endif
endif

# === version ================================================================ #

_version:
	@echo 2.1.0
.PHONY: _version

# = other.mk ================================================================= #

-include other.mk
