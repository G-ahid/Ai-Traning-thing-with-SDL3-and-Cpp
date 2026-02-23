# Makefile - builds game, AiView and ai, places binaries in bin/
# Usage:
#   make            # build everything
#   make -j4        # build in parallel
#   make game       # build only game
#   make aiview     # build only AiView
#   make ai         # build only ai
#   make clean      # remove build/ and bin/

CXX        := g++
CXXFLAGS   := -std=c++20 -O2 -Wall -Wextra -Igame/src -Iai/src $(shell pkg-config --cflags sdl3)
SDL_LIBS   := $(shell pkg-config --libs sdl3)
AR         := ar
BUILD      := build
BIN        := bin
LIBGAME    := $(BUILD)/libgame.a

# Source lists
GAME_SRCS   := $(wildcard game/src/*.cpp) $(wildcard game/*.cpp)
AI_SRC_MAIN := ai/main.cpp
AI_SRC_LIB  := $(wildcard ai/src/*.cpp)
AIVIEW_SRC  := ai/AiView.cpp

# Object lists (object files live under build/... preserving relative paths)
GAME_OBJS    := $(patsubst %.cpp,$(BUILD)/%.o,$(GAME_SRCS))
AI_OBJS      := $(patsubst %.cpp,$(BUILD)/%.o,$(AI_SRC_MAIN) $(AI_SRC_LIB))
AI_LIB_OBJS  := $(patsubst %.cpp,$(BUILD)/%.o,$(AI_SRC_LIB))   # objects usable by AiView (no main)
AIVIEW_OBJ   := $(patsubst %.cpp,$(BUILD)/%.o,$(AIVIEW_SRC))

.PHONY: all clean game ai aiview help

all: $(BIN)/game.x86_64 $(BIN)/AiView.x86_64 $(BIN)/ai.x86_64

# -----------------------------------------------------------------------------
# Link targets (produce final binaries) — append SDL libs when linking
# -----------------------------------------------------------------------------
$(BIN)/game.x86_64: $(GAME_OBJS) | $(BIN)
	@start=$$(date +%s); \
	echo "----------------------------"; \
	printf "Linking game -> $@\n"; \
	$(CXX) $(LDFLAGS) -o $@ $(GAME_OBJS) $(SDL_LIBS); \
	end=$$(date +%s); echo "Compiled in $$((end - start))s"; \
	echo "----------------------------"

# AiView: link AiView.cpp + ai/src/*.cpp (but NOT ai/main.cpp) + libgame
$(BIN)/AiView.x86_64: $(AIVIEW_OBJ) $(AI_LIB_OBJS) $(LIBGAME) | $(BIN)
	@start=$$(date +%s); \
	echo "----------------------------"; \
	printf "Linking AiView -> $@\n"; \
	$(CXX) $(LDFLAGS) -o $@ $(AIVIEW_OBJ) $(AI_LIB_OBJS) $(LIBGAME) $(SDL_LIBS); \
	end=$$(date +%s); echo "Compiled in $$((end - start))s"; \
	echo "----------------------------"

# ai: link ai/main.cpp + ai/src/*.cpp + libgame
$(BIN)/ai.x86_64: $(AI_OBJS) $(LIBGAME) | $(BIN)
	@start=$$(date +%s); \
	echo "----------------------------"; \
	printf "Linking ai -> $@\n"; \
	$(CXX) $(LDFLAGS) -o $@ $(AI_OBJS) $(LIBGAME) $(SDL_LIBS); \
	end=$$(date +%s); echo "Compiled in $$((end - start))s"; \
	echo "----------------------------"

# -----------------------------------------------------------------------------
# Build static library from game objects
# -----------------------------------------------------------------------------
$(LIBGAME): $(GAME_OBJS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

# -----------------------------------------------------------------------------
# Generic compile rule: compile any .cpp to build/relative/path.o
# Example: build/game/src/blocks.o is built from game/src/blocks.cpp
# -----------------------------------------------------------------------------
$(BUILD)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# -----------------------------------------------------------------------------
# Support targets and helpers
# -----------------------------------------------------------------------------
$(BIN):
	@mkdir -p $(BIN)

# Convenience shortcuts
game: $(BIN)/game.x86_64
aiview: $(BIN)/AiView.x86_64
ai: $(BIN)/ai.x86_64

clean:
	@echo "Removing $(BUILD) and $(BIN)"
	@rm -rf $(BUILD) $(BIN)

help:
	@printf "Makefile targets:\n\n"
	@printf "  make           # build all\n"
	@printf "  make -jN       # parallel build (N jobs)\n"
	@printf "  make game      # build only game\n"
	@printf "  make aiview    # build only AiView\n"
	@printf "  make ai        # build only ai\n"
	@printf "  make clean     # remove compiled files\n"