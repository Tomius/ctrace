BINARY = a.out
SRC_DIR = src
OBJ_DIR = .obj

CPP_FILES := $(shell find -L $(SRC_DIR) -name '*.cpp')
HEADERS := $(shell find -L $(SRC_DIR) -name '*.hpp')
OBJECTS := $(subst $(SRC_DIR),$(OBJ_DIR),$(CPP_FILES:.cpp=.o))

CXX = clang++
CXXFLAGS = -Wall -std=c++1y -fconstexpr-steps=1000000000 -fconstexpr-depth=1000 \
					 `pkg-config --cflags Magick++` -Qunused-arguments
LDFLAGS = `pkg-config --libs Magick++`

.PHONY: all me a sandwich clean

all: $(BINARY)

# make me a sandwich -j4
me: $(BINARY)
a: $(BINARY)
sandwich: $(BINARY)

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
