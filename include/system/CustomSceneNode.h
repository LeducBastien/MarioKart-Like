#ifndef __CUSTOMSCENENODE_H_INCLUDED__
#define __CUSTOMSCENENODE_H_INCLUDED__

#include <vector>

#include "SceneNode.h"

namespace id
{

class Mesh;
class ManualMesh;

class CustomSceneNode
: public SceneNode
{
public:
	CustomSceneNode(CustomSceneNode const&) = delete;
	CustomSceneNode(CustomSceneNode&&) = delete;
	virtual ~CustomSceneNode();

	auto operator=(CustomSceneNode const&) -> CustomSceneNode& = delete;
	auto operator=(CustomSceneNode&&) -> CustomSceneNode& = delete;

	static auto create(SceneManager*,SceneNode*) -> CustomSceneNode*;

	auto createManualMesh() -> ManualMesh*;
	void setMesh(std::vector<GLfloat>);

	void updateBuffer();

	virtual void updateGUIWindow();
	virtual void draw();
	virtual void updateWorld();

private:
	CustomSceneNode();

	ManualMesh* mesh;

	

};

}

#endif
