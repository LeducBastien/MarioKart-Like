#include <iostream>
#include <sys/types.h>
#include <imgui.h>
#include <dirent.h>

#include "PollEvent.h"
#include "Driver.h"
#include "SceneManager.h"
#include "ModelMesh.h"
#include "JSONParser.h"
#include "ModelSceneNode.h"
#include "Shader.h"

namespace id
{
	unsigned int ModelSceneNode::selected_model = 0;
	unsigned int ModelSceneNode::selected_texture = 0;

	ModelSceneNode::ModelSceneNode()
	: SceneNode()
	{
		this->mesh = nullptr;
		R = 0;
		G = 0;
		B = 0;
		A = 1;
		stringTexturePtr = nullptr;
		stringModelPtr = nullptr;
		vec4 = "";
		
		shader =  nullptr;
		prg = nullptr;
	}

	ModelSceneNode::~ModelSceneNode()
	{
		if(this->mesh)
		{
			delete this->mesh;
			this->mesh = nullptr;
		}
	
		free(this->stringTexturePtr);
                free(this->stringModelPtr);
		
		delete shader;
		shader = nullptr;
	
		delete prg;
		prg = nullptr;
	
	}

	auto ModelSceneNode::create(SceneManager* scenemgr, SceneNode* parent) -> ModelSceneNode*
	{
		ModelSceneNode* node = new ModelSceneNode();

		node->driver = scenemgr->getDriver();
		node->scenemgr = scenemgr;
		node->parent = parent;

		node->prg_id = 0;

		node->world_loc = glGetUniformLocation(node->driver->getCurrentProgram(), "world");
                node->world = maths::Matrix4::identity;

		if (parent)
			parent->addChild(node);

                node->ParseDirectory();
		
		node->stringTexturePtr = (const char**) malloc(sizeof(char*)*node->textures.size());
		node->stringModelPtr = (const char**)malloc(sizeof(char*) * node->models.size());
	
		for(unsigned int i = 0; i < node->models.size(); ++i)
                {
                        node->stringModelPtr[i] = node->models[i].c_str();
                }

                for(unsigned int j = 0; j < node->textures.size(); ++j)
                {
                        node->stringTexturePtr[j] = node->textures[j].c_str();
                }

	        node->log.setIdentifier("ModelSceneNode");
		node->log.setOutput(id::log::BOTH);

		return node;
	}

	void ModelSceneNode::setMesh(std::string const& filename, std::string const& texture)
	{
		this->mesh = ModelMesh::create(filename, texture);

		this->textbuf = filename;

		auto mesh_coord = this->mesh->getDrawCoord();

		if (this->prg_id == 0)
			this->setShader("simple");

		this->world_loc = glGetUniformLocation(this->prg_id, "world");
                this->world = maths::Matrix4::identity;

                glBufferData(GL_ARRAY_BUFFER, mesh_coord.size() * sizeof(mesh_coord[0]), mesh_coord.data(), GL_STATIC_READ);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), nullptr);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
                glClearColor(0.5f, 0.5f, 0.5f ,1.f);

	}

	void ModelSceneNode::updateBuffer()
	{
		auto mesh_coord = this->mesh->getDrawCoord();

                glBufferData(GL_ARRAY_BUFFER, mesh_coord.size() * sizeof(mesh_coord[0]), mesh_coord.data(), GL_STATIC_READ);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), nullptr);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
                glClearColor(0.5f, 0.5f, 0.5f ,1.f);
	}

	void ModelSceneNode::updateGUIWindow()
        {
		float R_buffer = R;
		float G_buffer = G;
		float B_buffer = B;
		float A_buffer = A;
        
        ImGui::SetNextWindowSize(ImVec2(400,180), ImGuiSetCond_FirstUseEver);
        ImGui::Begin("Controls");
            ImGui::Text("Move: Use arrows to move.");
            ImGui::Text("Zoom: Foward(W) | Backward (S)");
            ImGui::Text("Rotate: clockwise(A) | Counter clockwise (D)");
        ImGui::End();
	
		ImGui::SetNextWindowSize(ImVec2(181,181), ImGuiSetCond_FirstUseEver);
                ImGui::Begin("Stat");
                ImGui::Text("Triangle Number : %d \n",mesh->getPointNumber());
		ImGui::Text("Vertex Number : %d \n",mesh->getPointNumber()*3);
		ImGui::Text("Scaling : %d \n", scenemgr->getDevice()->getEvent()->getScale());
                ImGui::Text("Children Number : %lu", children.size());
		ImGui::End();

		ImGui::SetNextWindowSize(ImVec2(400,400), ImGuiSetCond_FirstUseEver);
                ImGui::Begin("Edit Model");
		ImGui::ListBox("Select a Model", (int*)&selected_model, stringModelPtr, models.size(), 5);
                ImGui::ListBox("Select a Texture",(int*)&selected_texture, stringTexturePtr, textures.size(), 5);
                ImGui::SliderFloat("Red", &R, 0.f, 1.f);
                ImGui::SliderFloat("Green", &G, 0.f, 1.f);
                ImGui::SliderFloat("Blue", &B, 0.f, 1.f);
                ImGui::SliderFloat("Alpha", &A, 0.f, 1.f);



		bool save = ImGui::Button("Save Data", ImVec2(100,40));
                if (save)
                        this->save_win = true;

                if (this->save_win)
                        this->displaySaveWindow();

                ImGui::SameLine();

                bool load = ImGui::Button("Load data", ImVec2(100,40));
                if (load)
                        this->load_win = true;

                if (this->load_win)
                        this->displayLoadWindow();

		ImGui::SameLine();

		bool texture = ImGui::Button("Texture Shader", ImVec2(100, 40));
		if(texture)
		{
			this->prg_id = this->driver->addShader("simple");
                        this->driver->useProgram(this->prg_id, this->scenemgr);
                        this->world_loc = glGetUniformLocation(this->prg_id, "world");
			this->colors_mode = false;
		}

		ImGui::SameLine();
		bool color = ImGui::Button("Color Shader", ImVec2(100, 40));
		if(color)
		{
                        this->prg_id = this->driver->ReplaceShader("color", shader, prg);
                        this->driver->useProgram(this->prg_id, this->scenemgr);
                        this->world_loc = glGetUniformLocation(this->prg_id, "world");
			this->colors_mode = true;
		}

                ImGui::End();

		if (selected_model != this->current_model || selected_texture != this->current_texture)
		{
			delete this->mesh;
			this->setMesh(models[selected_model], textures[selected_texture]);
			this->current_model = selected_model;
			this->current_texture = selected_texture;
			this->changing_model = false;
		}
	
		if(R_buffer != R || G_buffer != G || B_buffer != B ||A_buffer != A || mesh->getMeshState() == true)
		{
			SwitchColor(R,G, B, A);
                        this->prg_id = this->driver->ReplaceShader("color", shader, prg);
                        this->driver->useProgram(this->prg_id, this->scenemgr);
                        this->world_loc = glGetUniformLocation(this->prg_id, "world");	
			if(mesh->getMeshState() == true)
			mesh->setMeshState(false);
			this->colors_mode = true;
		}


	}

	void ModelSceneNode::ParseDirectory()
	{
                DIR* repository = opendir("./assets");

                struct dirent* readRep = NULL;

                while((readRep = readdir(repository)) != 0)
                { 
                        if(readRep->d_name[strlen(readRep->d_name) - 1] == 'j')
                        if(readRep->d_name[strlen(readRep->d_name) - 2] == 'b')
			if(readRep->d_name[strlen(readRep->d_name) - 3] == 'o')
			if(readRep->d_name[strlen(readRep->d_name) - 4] == '.')
			{
                                models.push_back(readRep->d_name);
                        }
                
			if(readRep->d_name[strlen(readRep->d_name) - 1] == 'g')
			if(readRep->d_name[strlen(readRep->d_name) - 2] == 'n')
			if(readRep->d_name[strlen(readRep->d_name) - 3] == 'p')
			if(readRep->d_name[strlen(readRep->d_name) - 4] == '.')
			{
				textures.push_back(readRep->d_name);
			}

			if(readRep->d_name[strlen(readRep->d_name) - 1] == 'g')
                        if(readRep->d_name[strlen(readRep->d_name) - 2] == 'p')
                        if(readRep->d_name[strlen(readRep->d_name) - 3] == 'j')
                        if(readRep->d_name[strlen(readRep->d_name) - 4] == '.')
                        {
                                textures.push_back(readRep->d_name);
                        }

		}

                closedir(repository);
	}

	void ModelSceneNode::saveData(std::string const& filename)
        {
		core::JSONParser json;

		std::string str(this->textures[selected_texture]);
		std::string texture(str);

		core::SaveData data(this->mesh->getModel(), this->shader_name, texture, this->R, this->G, this->B, this->A, this->colors_mode);

		json.parseData(filename, data);
        }

	void ModelSceneNode::loadData()
	{
		core::JSONParser json;

		std::string path = this->file_list[this->selected_file];

		auto* data = json.readData("./assets/" + path);

		this->shader_name = data->shader_name;
		this->driver->ReplaceShader(data->shader_name, this->shader, this->prg);

		this->setMesh(data->model_name, data->texture_path);
		this->R = data->R;
		this->G = data->G;
		this->B = data->B;
		this->A = data->A;

		this->colors_mode = data->colors_mode;

		this->loadColors();

		delete data;
	}

	void ModelSceneNode::loadColors()
	{
		if (this->colors_mode)
		{
			SwitchColor(this->R, this->G, this->B, this->A);
                        this->prg_id = this->driver->ReplaceShader("color", this->shader, this->prg);
                        this->driver->useProgram(this->prg_id, this->scenemgr);
                        this->world_loc = glGetUniformLocation(this->prg_id, "world");
                        this->mesh->setMeshState(false);
		}
	}

	void ModelSceneNode::draw()
	{
		this->event();


		this->driver->useProgram(this->prg_id, this->scenemgr);

		this->bindBufferAndVertexArrays();

		this->updateBuffer();

		this->updateWorld();

		if (this->mesh)
			this->mesh->draw();

		this->unbindBufferAndVertexArrays();

		this->updateGUIWindow();

		std::vector<SceneNode*>::iterator first = this->children.begin();
                std::vector<SceneNode*>::iterator last = this->children.end();

                for (; first != last; ++first)
                        (*first)->draw();

	}

	void ModelSceneNode::updateWorld()
	{
		this->world = maths::Matrix4::identity;

                if(this->parent)
                {
                        maths::Matrix4 parent_world = this->parent->getWorld();
                        this->world = parent_world;
                }
		
		this->world = maths::Matrix4x4::scale(
                        scenemgr->getDevice()->getEvent()->getScale(),
                        scenemgr->getDevice()->getEvent()->getScale(),
                        scenemgr->getDevice()->getEvent()->getScale());

                glUniformMatrix4fv(this->world_loc, 1, GL_TRUE, this->world.val);
	}

	void ModelSceneNode::SwitchColor(float R, float G, float B, float A)
	{
		vec4 = "vec4(";
		vec4 += std::to_string(R);
		vec4 += ",";
		vec4 += std::to_string(G);
                vec4 += ",";
		vec4 += std::to_string(B);
                vec4 += ",";
		vec4 += std::to_string(A);
                vec4 += ");\n";

		std::ofstream file;
		file.open("./assets/shader/color_fs.glsl", std::ofstream::trunc);
		file << "#version 420\n\n";
		file << "in vec4         tmpColor;\n";
		file << "out vec4        outColor;\n";
		file << "void    main(void)\n";
		file << "{\n";
		file << "outColor = ";
		file << vec4;
		file << "}";
		file.close();
	}
}
