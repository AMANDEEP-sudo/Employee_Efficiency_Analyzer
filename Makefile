CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = efficiency_tracker
SRCDIR = src
BINDIR = bin

# Automatically find all source files
SOURCES = $(SRCDIR)/main.cpp \
          $(SRCDIR)/Employee.cpp \
          $(SRCDIR)/Task.cpp \
          $(SRCDIR)/Citizen.cpp \
          $(SRCDIR)/OTPManager.cpp \
          $(SRCDIR)/Feedback.cpp \
          $(SRCDIR)/Department.cpp \
          $(SRCDIR)/EfficiencyCalculator.cpp \
          $(SRCDIR)/Database.cpp \
          $(SRCDIR)/Admin.cpp \
          $(SRCDIR)/Utils.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✓ Build successful! Executable: $(TARGET)"

# Compile each source file to object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "✓ Compiled: $<"

# Clean up build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Cleaned up build artifacts"

# Run the application
run: $(TARGET)
	./$(TARGET)

# Help target
help:
	@echo "=================================="
	@echo "Employee Efficiency Tracker - Makefile"
	@echo "=================================="
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  run     - Build and run the application"
	@echo "  help    - Display this help message"
	@echo "=================================="

.PHONY: all clean run help
