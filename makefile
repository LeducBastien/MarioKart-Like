TARGET = out

SRC = main.cpp \
	system/System.cpp \
	GUI/GUI.cpp \
	system/Tools.cpp \
	system/Game.cpp \
	system/PollEvent.cpp \
	system/Device.cpp \
	system/Driver.cpp \
	system/Window.cpp \
	mesh/Shader.cpp \
	system/Program.cpp \
	system/SceneManager.cpp \
	system/SceneNode.cpp \
	system/CameraSceneNode.cpp \
	system/TriangleSceneNode.cpp \
	system/ModelSceneNode.cpp \
	system/CustomSceneNode.cpp \
	mesh/Mesh.cpp \
	mesh/ManualMesh.cpp \
	mesh/ModelMesh.cpp \
	GUI/imgui.cpp \
	GUI/imgui_demo.cpp \
	GUI/imgui_draw.cpp \
	GUI/ImGuiImpl.cpp \
	maths/Matrix.cpp \
	maths/tools.cpp \
	system/Log.cpp \
	system/JSONParser.cpp \


LIBS = SDL2 SDL2_image GL GLEW

BIN_DIR = bin/
OBJ_DIR = obj/
SRC_DIR = src/
INC_DIR = include/system/ include/GUI/ include/ include/mesh/  /usr/include/SDL2/ 

OBJ = $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRC))
DEPENDENCIES = $(OBJ:.o=.d)
ARBO = $(sort $(dir $(DEPENDENCIES) $(OBJ_DIR)))
INCLUDES = $(addprefix -I,$(INC_DIR))
LIBRARIES = $(addprefix -l,$(LIBS))
CXXFLAGS = -MMD -W -Wall -Werror -g3
LDFLAGS = -W -Wall -Werror -g3
CXX = g++ -std=c++14

.PHONY: all clean fclean re release debug 

release: CXXFLAGS += -O3
release: LDFLAGS += -O3
release: all

debug: CXXFLAGS += -O0 -g3
debug: LDFLAGS += -O0 -g3
debug: all

all: $(TARGET)

$(TARGET): $(BIN_DIR)$(TARGET) | $(ARBO)

$(BIN_DIR)$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LIBRARIES)

$(OBJ): | $(ARBO)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(ARBO):
	mkdir -p $(ARBO)

-include $(DEPENDENCIES)

clean:
	$(RM) $(OBJ)
	$(RM) $(DEPENDENCIES)
	$(RM) -r $(ARBO)
	$(RM) .*.swp

fclean: clean
	$(RM) $(TARGET)

re: fclean all

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INCLUDES)
