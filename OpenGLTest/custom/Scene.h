#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"
#include "../custom/GameObject.h"
#include "../custom/Background.h"
#include "../custom/FrameBuffer.h"

#include <memory>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <algorithm>
#include <functional>
#include <random>
#include "Chunk.h"
#include "Character.h"
#include "Ghost.h"
#include "Profiler.h"
#include "Bullet.h"
#include "objloader.h"

struct pair_hash {
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2>& p) const {
		auto h1 = std::hash<T1>{}(p.first);
		auto h2 = std::hash<T2>{}(p.second);

		// Mainly for demonstration purposes, i.e. works but is overly simple
		// In the real world, use sth. like boost.hash_combine
		return h1 ^ h2;
	}
};


	struct VecPosition
	{
		float x;
		float y;
		float z;
		//float w;
	
	};
	
	struct VecColor
	{
		float r;
		float g;
		float b;
		float a;
	};
	
	struct VecTexCoord
	{
		float x;
		float y;
	};
	
	
	struct Vertex
	{
		VecPosition position;
		VecColor color;
		VecTexCoord texCoord;
		float texID;
	};

	class Scene 
	{
	public:
		Scene();
		~Scene();

		void OnUpdate(GLFWwindow* window, float deltaTime);
		void OnRender(GLFWwindow* window);
		std::array<Vertex, 4> CreateObject(const std::shared_ptr <GameObject>& GameObjectsArray);
		std::array<Vertex, 4> CreateObject(const std::shared_ptr <Character>& GameObjectsArray);
		void FillVBO(const std::vector<std::shared_ptr <GameObject>>& GameObjectsArray, std::vector<std::array<Vertex, 4>>& arr);
		void FillVBO(const std::shared_ptr<GameObject>& character, std::vector<std::array<Vertex, 4>>& arr);
		void FillVBO(const std::shared_ptr<Character>& character, std::vector<std::array<Vertex, 4>>& arr);
		void FillVBO(const std::shared_ptr<Chunk>& character, std::vector<std::array<Vertex, 4>>& arr);
		void GenerateChunk();
		void GeneratePath(std::shared_ptr<Chunk> chunk);
		void SpawnGhost(int x, int y);
		void SpawnBullet();

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		
		
		// 7/7/2021 section
		//void GenerateChunk();
		
	private:
		static double xpos; // cursor position
		static double ypos;

		static glm::mat4 m_Proj, m_View;
		static glm::mat4 m_VP;

		TextureData RD1TXData, grassTXData, dirtTXData, /*RustyBarTXData, FloorTXData, BGImageTXData, netTXData, blackVeilTXData, FogBlocksTXData, BGBlocksTXData, RustyPipeTXData, metalSupBlocksTXData,*/ FluxTXData, 
			ghostTXData, mouseCursorTXData, bulletTXData, HelmieTXData;
		//GameObject * RustyBar, * Floor, *BGImage,* net, * mouseCursor, * blackVeil;

		std::shared_ptr <GameObject>  mouseCursor/*, blackVeil*/;
		std::shared_ptr <Character>  RD1;
		//std::shared_ptr <GameObject> RustyBar, Floor, RustyPipe;

		double starttime, endtime, delta;
		/*
		std::vector<std::shared_ptr <GameObject>> FogBlocks;
		std::vector<std::shared_ptr <GameObject>> BGBlocks;
		std::vector<std::shared_ptr <GameObject>> netBlocks;
		std::vector<std::shared_ptr <GameObject>> metalSupBlocks;
		std::vector<std::shared_ptr <GameObject>> floorAndSeilingBlocks;
		*/
		std::vector<std::shared_ptr <Ghost>> ghosts;
		std::vector<std::shared_ptr <Bullet>> bullets;
		//std::vector<std::shared_ptr <GameObject>> GameObjectsArray;

		//std::vector<std::shared_ptr <GameObject>> collideObjs;
		std::unique_ptr <Shader> m_Shader;
		std::unique_ptr <Shader> m_ShaderFB;

		std::vector<std::array<Vertex, 4>> vertices;
		std::vector<unsigned int> indices;

		std::unordered_map<std::pair<int, int>, std::shared_ptr <Chunk>, pair_hash> chunks;

		//std::unique_ptr <IndexBuffer> m_IndexBuffer;
		//std::unique_ptr <Shader> m_Shader_Instances;
		//std::unique_ptr <Shader> m_Shader_Instances_net;
		//std::unique_ptr <FrameBuffer> FramebufferBlack;

		// 7/7/2021 section

		//std::vector<std::pair <int, std::pair<int, std::shared_ptr <GameObject> > > > chunks;

		//std::vector<std::shared_ptr <GameObject>> chunks;
		//std::map<int, std::map<int, std::vector<int>>> m; <std::shared_ptr <GameObject> > > dirtPaths;

		// 3D section
		static float verticalAngle;
		static float horizontalAngle;
		static float mouseSpeed;

		static glm::vec3 position;
		static glm::vec3 direction;
		static glm::vec3 right;
		static glm::vec3 up;
		static bool perspective_mode;

		std::vector<glm::vec3> verticesCube;
		std::vector<glm::vec2> uvsCube;
		std::vector<glm::vec3> normalsCube;
	};