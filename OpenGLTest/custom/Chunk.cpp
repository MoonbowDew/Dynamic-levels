#include "Chunk.h"

Chunk::Chunk(glm::vec3 SpawnPoint, TextureData TXData, float TXNumber, float r, float g, float b, float alpha) :
	GameObject(SpawnPoint, TXData, TXNumber, r, g, b, alpha)// :
	//m_x(GameObject::BottomLeft.x), m_y(GameObject::BottomLeft.y) // inits with garbage
{
	//GameObject::GameObject(SpawnPoint, TXData, TXNumber);
	m_pathStartPoint = 0;
	m_pathElementCoords.reserve(50);
	std::cout << "Derived Chunk Object is created" << std::endl;
}

//void Chunk::GeneratePath(TextureData dirtTXData)
//{
//
//}



std::vector<std::shared_ptr<GameObject>> Chunk::GetpathElementCoords()
{
	return m_pathElementCoords;
}

void Chunk::AddpathElementCoords(std::shared_ptr<GameObject> coords)
{
	m_pathElementCoords.push_back(coords);
}