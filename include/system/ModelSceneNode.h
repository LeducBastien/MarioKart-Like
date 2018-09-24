#ifndef __MODELSCENENODE_H_INCLUDED__
#define __MODELSCENENODE_H_INCLUDED__

#include <SDL.h>
#include <GL/glew.h>

#include "SceneNode.h"
#include "Log.h"
#include "Program.h"

namespace id
{

class ModelMesh;

class ModelSceneNode
: public SceneNode
{
public:
	ModelSceneNode(ModelSceneNode const&) = delete;
	ModelSceneNode(ModelSceneNode&&) = delete;

	~ModelSceneNode();

	auto operator=(ModelSceneNode const&) -> ModelSceneNode& = delete;
	auto operator=(ModelSceneNode&&) -> ModelSceneNode& = delete;

	static auto create(SceneManager*,SceneNode*) -> ModelSceneNode*;
	void setMesh(std::string const&, std::string const&);
	void updateGUIWindow();

	void updateBuffer();
	
	virtual void draw();
	virtual void updateWorld();
	void mouseEvent();

	void ParseDirectory();

	virtual void saveData(std::string const&);
	virtual void loadData();
	void loadColors();
	
	std::vector<std::string> getModels() const& {return models;}

	unsigned int getSelectedModel () const {return selected_model;}
	unsigned int getSelectedTexture() const {return selected_texture;}

	void setSelectedModel(int state) {selected_model += state;}
	void setSelectedTexture(int state) {selected_texture += state;}

	std::vector<std::string> getModelTab() const& {return models;}
	std::vector<std::string> getTextureTab() const& {return textures;}

	void SwitchColor(float R, float G, float B, float A);

	private:
	ModelSceneNode();

	static unsigned int selected_model;
        static unsigned int selected_texture;

	unsigned int current_model = 0;
	unsigned int current_texture = 0;
        
	std::vector<std::string> models;
	std::vector<std::string> textures;
	
	const char** stringTexturePtr;
	const char** stringModelPtr;
	ModelMesh* mesh;

	bool changing_model = false;
	std::string vec4;
	id::log::Log log;

	float R;
	float G;
	float B;
	float A;

	Shader* shader;
	Program* prg;

	bool colors_mode = false;
};

}
#endif
