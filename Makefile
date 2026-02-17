# Makefile for Employee Efficiency Tracker with ImGui Modern UI

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -fPIC
LDFLAGS = -lglfw3 -lopengl32 -lgdi32 -lws2_32

# ImGui paths
IMGUI_DIR = imgui
IMGUI_IMPL_DIR = $(IMGUI_DIR)/backends

# Include directories
INCLUDES = -I. -I$(IMGUI_DIR) -I$(IMGUI_IMPL_DIR)

# Source files
SRCDIR = src
SOURCES = \
    $(SRCDIR)/main.cpp \
    $(SRCDIR)/Employee.cpp \
    $(SRCDIR)/Task.cpp \
    $(SRCDIR)/Citizen.cpp \
    $(SRCDIR)/OTPManager.cpp \
    $(SRCDIR)/Feedback.cpp \
    $(SRCDIR)/Department.cpp \
    $(SRCDIR)/EfficiencyCalculator.cpp \
    $(SRCDIR)/Database.cpp \
    $(SRCDIR)/Admin.cpp \
    $(SRCDIR)/Utils.cpp \
    $(SRCDIR)/ImGuiManager.cpp \
    $(SRCDIR)/ImGuiAdmin.cpp \
    $(IMGUI_DIR)/imgui.cpp \
    $(IMGUI_DIR)/imgui_demo.cpp \
    $(IMGUI_DIR)/imgui_draw.cpp \
    $(IMGUI_DIR)/imgui_tables.cpp \
    $(IMGUI_DIR)/imgui_widgets.cpp \
    $(IMGUI_IMPL_DIR)/imgui_impl_glfw.cpp \
    $(IMGUI_IMPL_DIR)/imgui_impl_opengl3.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Target
TARGET = efficiency_tracker.exe

# Default target
all: check-imgui $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)
	@echo "✓ Build successful! Modern UI executable: $(TARGET)"

# Compile each source file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	@echo "✓ Compiled: $<"

# Check if ImGui is available
check-imgui:
	@if [ ! -d "$(IMGUI_DIR)" ]; then \
		echo "⚠️  ImGui directory not found. Run 'make setup-imgui' first"; \
		exit 1; \
	fi

# Download and setup ImGui
setup-imgui:
	@echo "📥 Downloading ImGui..."
	@if [ ! -d "$(IMGUI_DIR)" ]; then \
		mkdir -p $(IMGUI_DIR); \
		curl -L -o /tmp/imgui.zip https://github.com/ocornut/imgui/archive/refs/tags/v1.89.7.zip; \
		unzip /tmp/imgui.zip -d /tmp; \
		cp -r /tmp/imgui-1.89.7/* $(IMGUI_DIR)/; \
		rm -rf /tmp/imgui.zip /tmp/imgui-1.89.7; \
		echo "✓ ImGui setup complete"; \
	else \
		echo "ℹ️  ImGui already exists"; \
	fi

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Cleaned up build artifacts"

# Full clean including ImGui
clean-all: clean
	rm -rf $(IMGUI_DIR)
	@echo "✓ Full cleanup complete (ImGui removed)"

# Run the application
run: $(TARGET)
	./$(TARGET)

# Build with verbose output
verbose: CXXFLAGS += -v
verbose: clean $(TARGET)

# Help
help:
	@echo "=================================="
	@echo "Employee Efficiency Tracker - Makefile"
	@echo "Modern UI Edition (ImGui + OpenGL)"
	@echo "=================================="
	@echo "Available targets:"
	@echo "  all           - Build the project (default)"
	@echo "  check-imgui   - Verify ImGui is present"
	@echo "  setup-imgui   - Download and setup ImGui"
	@echo "  clean         - Remove build artifacts"
	@echo "  clean-all     - Remove all including ImGui"
	@echo "  run           - Build and run the application"
	@echo "  verbose       - Build with verbose output"
	@echo "  help          - Display this help message"
	@echo "=================================="

.PHONY: all check-imgui setup-imgui clean clean-all run verbose help
