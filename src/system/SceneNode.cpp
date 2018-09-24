#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <imgui.h>
#include <sys/types.h>
#include <dirent.h>

#include "Driver.h"
#include "SceneManager.h"
#include "PollEvent.h"
#include "JSONParser.h"
#include "SceneNode.h"

namespace id
{
	bool SceneNode::is_typing_text = false;

	SceneNode::SceneNode()
	{
	}

	SceneNode::~SceneNode()
	{
		this->driver = nullptr;
		this->scenemgr = nullptr;
		this->parent = nullptr;

		std::vector<SceneNode*>::iterator first = this->children.begin();
		std::vector<SceneNode*>::iterator last = this->children.end();

		for (; first != last; ++first)
		{
			delete *first;
		}

		this->children.clear();
	}

	SceneNode* SceneNode::create(SceneManager* scenemgr, SceneNode* parent)
	{
		SceneNode* node = new SceneNode();

		node->driver = scenemgr->getDriver();
		node->scenemgr = scenemgr;
		node->parent = parent;
		node->children = {};

		node->world = maths::Matrix4::identity;

		if (parent)
			parent->addChild(node);

		return node;
	}

	void SceneNode::addChild(SceneNode* node)
	{
		if(node)
			this->children.push_back(node);
	}

	void SceneNode::setShader(std::string const& name)
	{
		this->prg_id = this->driver->addShader(name);
		this->shader_name = name;
	}

	void SceneNode::displaySaveWindow()
	{
		ImGui::Begin("Save data");
			ImGui::Text("Enter filename\n");

			if (ImGui::GetWindowIsFocused() && !ImGui::IsAnyItemActive())
				ImGui::SetKeyboardFocusHere();
			ImGui::InputText("Name", &(this->textbuf[0u]), 256*sizeof(char), ImGuiInputTextFlags_AutoSelectAll );

			if (ImGui::IsItemActive())
				SceneNode::is_typing_text = true;
			else
				SceneNode::is_typing_text = false;

			bool save = ImGui::Button("Save", ImVec2(100, 30));

			if (save)
			{
				std::string str(&this->textbuf[0u]);
				std::string filename ("./assets/" + str + ".json");
				this->saveData(filename);
			}

			ImGui::SameLine();

			bool close = ImGui::Button("Close", ImVec2(100, 30));

			if (close)
				this->save_win = false;

		ImGui::End();
	}

	void SceneNode::displayLoadWindow()
	{
		this->collectFiles();

		const char** items = this->file_list.data();

	        ImGui::Begin("Load File");
                	ImGui::ListBox("Browse File", &this->selected_file, items, this->file_list.size(), 4);
        	        bool open = ImGui::Button("Open", ImVec2(100,40));
			ImGui::SameLine();
			bool cancel = ImGui::Button("Cancel", ImVec2(100,40));
	        ImGui::End();

		if (open)
		{
			this->loadData();
			this->load_win = false;
		}

		if(cancel)
			this->load_win = false;
	}

    void SceneNode::collectFiles()
    {
            this->file_list.clear();

            DIR* repository = opendir("./assets");
            struct dirent* readRep = NULL;

            while((readRep = readdir(repository)) != 0)
            {
		    std::string str(readRep->d_name);

                    if(str.rfind(".json") != std::string::npos)
                    {
                        this->file_list.push_back(readRep->d_name);
                    }
            }

	    closedir(repository);
    }


	void SceneNode::saveData(std::string const&)
	{
	}

	void SceneNode::loadData()
	{
	}

	void SceneNode::draw()
	{
		std::vector<SceneNode*>::iterator first = this->children.begin();
		std::vector<SceneNode*>::iterator last = this->children.end();

		for (; first != last; ++first)
			(*first)->draw();
	}

	void SceneNode::event()
	{
		this->keyboardEvent();
	}

	void SceneNode::keyboardEvent()
	{
		SDL_Scancode key = PollEvent::getKeyInput();

		switch(key)
		{
			case SDL_SCANCODE_BACKSPACE:
			{
				if (this->save_win && !PollEvent::isHold() && this->textbuf.size() > 0)
					this->textbuf.pop_back();

				PollEvent::setHold(true);
			}
			break;

			default: break;
		}
	}

	void SceneNode::updateGUIWindow()
	{
	}

	void SceneNode::updateWorld()
	{
	}

	void SceneNode::bindBufferAndVertexArrays()
	{
		GLuint vao = this->driver->getVAO();
                GLuint vbo = this->driver->getVBO();
                glBindVertexArray(vao);
                glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}

	void SceneNode::unbindBufferAndVertexArrays()
	{
		glBindVertexArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
