BINARY = a.out
SRC_DIR = src
OBJ_DIR = .obj

CPP_FILES := $(shell find -L $(SRC_DIR) -name '*.cpp')
HEADERS := $(shell find -L $(SRC_DIR) -name '*.hpp')
OBJECTS := $(subst $(SRC_DIR),$(OBJ_DIR),$(CPP_FILES:.cpp=.o))

CXX = clang++
CXXFLAGS = -Wall -std=c++1y -fconstexpr-steps=100000000 -fconstexpr-depth=1000 \
					 -ftemplate-depth=400 `pkg-config --cflags Magick++` -Qunused-arguments
LDFLAGS = `pkg-config --libs Magick++`

.PHONY: all clean

all: $(BINARY)

clean:
	@$(info Cleaning up)
	@rm -f $(BINARY) -rf $(OBJ_DIR)

%.o: $(CPP_FILES) $(HEADERS)
	@$(info Building object $@)
	@mkdir -p $(dir $@);
	@$(CXX) $(CXXFLAGS) -c $(subst $(OBJ_DIR),$(SRC_DIR),$(@:.o=.cpp)) -o $@

$(BINARY): $(OBJECTS)
	@$(info Linking executable $@)
	@$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

%:
	@
