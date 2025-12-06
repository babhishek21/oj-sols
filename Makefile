# ==========================================
#    Root-Aware Competitive Programming Makefile (for macOS & Linux)
# ==========================================

# 1. SPECIAL TARGETS
# ------------------
# MAKEFLAGS += --no-builtin-rules
# .SUFFIXES:

# PRESERVE only .bin files.
# This prevents Make from deleting them after the bridge rule runs.
.PRECIOUS: %.bin

# 2. CONFIGURATION
# ----------------

REPO_ROOT := $(shell git rev-parse --show-toplevel)
HEADER_SRC = /usr/local/include/bits/stdc++.h
PCH_FILE = $(REPO_ROOT)/stdc++.h.gch

CXX = g++
JAVAC = javac

# PCH Logic (Mac/Clang only)
IS_CLANG := $(shell $(CXX) --version 2>/dev/null | grep -i clang)
IS_OVERRIDE := $(filter command line,$(origin CXXFLAGS))
PCH_FLAG =
PCH_DEPENDENCY =

ifdef IS_CLANG
	ifndef IS_OVERRIDE
		ifneq ("$(wildcard $(HEADER_SRC))","")
			PCH_FLAG = -include-pch $(PCH_FILE)
			PCH_DEPENDENCY = $(PCH_FILE)
		endif
	endif
endif

# 3. RULES
# --------

# --- Conditional Rule Cancellation ---
# ONLY disable built-in rules if CP_MODE is set (i.e., called via 'mymake')

# [WARNING] Indent only using spaces in the following block!
ifdef CP_MODE
    # prevent direct compilation of .cpp -> .o -> .bin
    %: %.cpp
    %.o: %.cpp

    # prevent direct compilation of .java -> .class -> .bin
    %: %.java
    %.class: %.java
endif

# --- Bridge Rule ---
# 'mymake ProblemA' -> builds 'ProblemA.bin'
%: %.bin
	@:

# --- Explicit Rules ---

# Explicit C++ -> .bin
cpp.%.bin: %.cpp $(PCH_DEPENDENCY)
	@echo "[C++] Building $*.bin..."
	$(CXX) $(CXXFLAGS) $(PCH_FLAG) $< -o $*.bin

# Explicit Java -> .bin (Wrapper)
java.%.bin: %.java
	@echo "[Java] Building $*.bin..."
	$(JAVAC) $<
	@echo '#!/bin/bash' > $*.bin
	@echo 'java -cp . $* "$$@"' >> $*.bin
	@chmod +x $*.bin

# --- Smart Defaults ---

# Smart Default (C++)
%.bin: %.cpp $(PCH_DEPENDENCY)
	@echo "[Auto] C++ -> $*.bin..."
	$(CXX) $(CXXFLAGS) $(PCH_FLAG) $< -o $@

# Smart Default (Java)
%.bin: %.java
	@echo "[Auto] Java -> $*.bin..."
	$(JAVAC) $<
	@echo '#!/bin/bash' > $@
	@echo 'java -cp . $* "$$@"' >> $@
	@chmod +x $@

# --- Initialization ---

# PCH Generation
$(PCH_FILE):
	@echo "[Init] Generating PCH..."
	$(CXX) -x c++-header $(HEADER_SRC) -o $(PCH_FILE)

.PHONY: clean
clean:
	rm -f *.bin *.class *.dSYM $(PCH_FILE)
