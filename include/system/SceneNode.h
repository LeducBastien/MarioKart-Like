#ifndef __SCENENODE_H_INCLUDED__
#define __SCENENODE_H_INCLUDED__

#include <memory>
#include <vector>
#include <SDL.h>
#include <GL/glew.h>
#include <string>

#include "maths/Matrix.h"

namespace id
{
	class Driver;
	class SceneManager;

	class SceneNode
	{
	public:
		SceneNode(SceneNode const&) = delete;
		SceneNode(SceneNode&&) = delete;
		virtual ~SceneNode();
		
		auto operator=(SceneNode const&) -> SceneNode& = delete;
		auto operator=(SceneNode&&) -> SceneNode = delete;

		maths::Matrix4 getWorld() const& {return this->world;}

		virtual void setShader(std::string const& name);

		static SceneNode* create(SceneManager*, SceneNode*);

		std::vector<SceneNode*>& getChildren() {return children;}

		void addChild(SceneNode*);

		virtual void displaySaveWindow();
		virtual void displayLoadWindow();
		virtual void saveData(std::string const&);
		virtual void loadData();

	        virtual void collectFiles();


		virtual void draw();
		virtual void event();
		virtual void keyboardEvent();
		virtual void updateGUIWindow();
		virtual void updateWorld();
		virtual void bindBufferAndVertexArrays();
		virtual void unbindBufferAndVertexArrays();

	protected:
		SceneNode();

		Driver* driver;
		SceneManager* scenemgr;
		SceneNode* parent;
		std::vector<SceneNode*> children;

		GLuint prg_id;
		std::string shader_name;

		GLint world_loc;
		maths::Matrix4 world;

		float angle = 0.f;

		std::string textbuf = "no_name";
		bool save_win = false;
		bool load_win = false;

		static bool is_typing_text;

		std::vector<const char*> file_list;
        	int selected_file = 0;


	};
	
}

#endif
