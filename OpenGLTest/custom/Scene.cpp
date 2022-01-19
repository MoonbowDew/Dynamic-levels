#pragma once


#include "Scene.h"
#include "../Renderer.h"
#include "../custom/Physics.h"
#include <array>
#include <algorithm> 

#define BATCH_RENDERING
#define MAX_TEXTURES 32
#define MAX_OBJECTS 1000


double Scene::xpos = 0.0;
double Scene::ypos = 0.0;

glm::mat4 Scene::m_Proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
glm::mat4 Scene::m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
glm::mat4 Scene::m_VP = m_Proj * m_View;

float Scene::verticalAngle = 0.0f;
float Scene::horizontalAngle = 3.14f;
float Scene::mouseSpeed = 0.005f;

glm::vec3 Scene::position = glm::vec3(10.0f, 0.975f, -2.0f);
glm::vec3 Scene::direction(
    cos(verticalAngle)* sin(horizontalAngle),
    sin(verticalAngle),
    cos(verticalAngle)* cos(horizontalAngle)
);

glm::vec3 Scene::right = glm::vec3(
    sin(horizontalAngle - 3.141592f / 2.0f),
    0.0f,
    cos(horizontalAngle - 3.141592f / 2.0f)
);

glm::vec3 Scene::up = glm::cross(right, direction);
bool Scene::perspective_mode = false;

    // 6/21/2021 section; Batch rendering

//void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods); // mode

    TextureData LoadTexture(const std::string& path)
    {
        int w, h, bits;
        unsigned int textureID;
        stbi_set_flip_vertically_on_load(1);
        auto* pixels = stbi_load(path.c_str(), &w, &h, &bits, STBI_rgb_alpha);
        if (!pixels)
            std::cerr << "Cannot load file image %s\nSTB Reason: %s\n", path, stbi_failure_reason();


        

        glGenTextures(1, &textureID);

        //GLenum err = glGetError();
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);



        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
        glBindTexture(GL_TEXTURE_2D, 0);



        if (pixels)
            stbi_image_free(pixels);

        return { textureID, w, h };
    }

    void Scene::GenerateChunk()
    {
        //for (float y = 0.0f; y < 1024.0f; y += 32.0f /*10*/) // 3 
        //{
        //    for (float x = 0.0f; x < 1024.0f; x += 32.0f /*10*/) // 2 
        //    {
                
                //metalSupBlocks.back()->SetSpriteResolution(80, 80);
        //    }
        //}
                
    }

    void Scene::SpawnGhost(int x, int y) // generate ghost
    {
        ghosts.push_back(std::make_shared<Ghost>(glm::vec3(x, y, 0), ghostTXData, 4.0f, 1.0f, 1.0f, 1.0f));
    }

    void Scene::SpawnBullet() // generate bullet
    {
        bullets.push_back(std::make_shared<Bullet>(glm::vec3(RD1->GetBottomLeft().x, RD1->GetBottomLeft().y, 0), bulletTXData, 5.0f, 1.0f, 1.0f, 1.0f));
    }

    void Scene::GeneratePath(std::shared_ptr<Chunk> chunks) // generate Dirt
    {
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr1(0, 1023); // define path starting position
        int pathStartPoint = distr1(gen);
        std::uniform_int_distribution<> distr2(1, 32); // define path's length
        int pathLength = distr2(gen);
        int rowIndex = (pathStartPoint % 32) - 1;
        if (((pathStartPoint % 32) - 1) == 0)
            rowIndex = 32;
        int columnIndex = pathStartPoint / 32;
        int FirstElementX = chunks->GetBottomLeft().x + 32 * rowIndex;
        int FirstElementY = chunks->GetBottomLeft().y + 32 * columnIndex;

        SpawnGhost(FirstElementX, FirstElementY);

        for (size_t i = 0; i < pathLength; i++)
        {
            chunks->AddpathElementCoords(std::make_shared<Dirt>(glm::vec3(FirstElementX + i * 32, FirstElementY, 0), dirtTXData, 6.0f, 1.0f, 1.0f, 1.0f));
        }

        std::cout << "generated path from Chunk" << std::endl;
        //m_pathElementCoords.push_back(std::make_pair(FirstElementX, FirstElementY)); //add starting coords
    }

    void BindTextures(std::vector<std::shared_ptr <GameObject>> GameObjectsArray)
    {
        for (int i = 0; i < GameObjectsArray.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(GameObjectsArray[i]->GetTXNumber()) + static_cast<GLenum>(1.0f));
            glBindTexture(GL_TEXTURE_2D, GameObjectsArray[i]->GetTextureID());
        }
    }

    void BindTextures(const std::shared_ptr<GameObject>& character)
    {

            glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(character->GetTXNumber()) + static_cast<GLenum>(1.0f));
            glBindTexture(GL_TEXTURE_2D, character->GetTextureID());

    }

    void Scene::FillVBO(const std::vector<std::shared_ptr <GameObject>>& GameObjectsArray, std::vector<std::array<Vertex, 4>>& arr)
    {
        for (int i = 0; i < GameObjectsArray.size(); i++) // 8 bg objs
        {
            arr.push_back(CreateObject(GameObjectsArray[i]));
        }
    }

    void Scene::FillVBO(const std::shared_ptr<GameObject>& character, std::vector<std::array<Vertex, 4>>& arr)
    {
        arr.push_back(CreateObject(character));
    }

    void Scene::FillVBO(const std::shared_ptr<Character>& character, std::vector<std::array<Vertex, 4>>& arr)
    {
        arr.push_back(CreateObject(character));
    }

    void Scene::FillVBO(const std::shared_ptr<Chunk>& character, std::vector<std::array<Vertex, 4>>& arr)
    {
        arr.push_back(CreateObject(character));
    }

    static float SmoothStep(float x)
    {
        float min = std::min(1.0f, x);
        float max = std::max(0.0f, min);

        float result = (max * max) * (3 - 2 * max);
        return result;
    }


     std::array<Vertex, 4> Scene::CreateObject(const std::shared_ptr <GameObject>& GameObjectsArray)
    {
        Vertex v1;


        //v1.position = { RDQuaterion1.x, RDQuaterion1.y, RDQuaterion1.z, RDQuaterion1.w };
        v1.position = { GameObjectsArray->GetBottomLeft().x, GameObjectsArray->GetBottomLeft().y, 0.0f };
        v1.color = { GameObjectsArray->GetColorR(), GameObjectsArray->GetColorG(), GameObjectsArray->GetColorB(), GameObjectsArray->GetAlphaChannel() };
        v1.texCoord = { 0.0f, 0.0f };
        v1.texID = { GameObjectsArray->GetTXNumber() }; // 0.0f will be reserved for no object


        Vertex v2;

        //v2.position = { RDQuaterion2.x, RDQuaterion2.y, RDQuaterion2.z, RDQuaterion2.w };
        v2.position = { GameObjectsArray->GetBottomRight().x, GameObjectsArray->GetBottomRight().y, 0.0f };
        v2.color = { GameObjectsArray->GetColorR(), GameObjectsArray->GetColorG(), GameObjectsArray->GetColorB(), GameObjectsArray->GetAlphaChannel() };
        v2.texCoord = { 1.0f, 0.0f };
        v2.texID = { GameObjectsArray->GetTXNumber() };


        Vertex v3;

        //v3.position = { RDQuaterion3.x, RDQuaterion3.y, RDQuaterion3.z, RDQuaterion3.w };
        v3.position = { GameObjectsArray->GetTopRight().x, GameObjectsArray->GetTopRight().y, 0.0f };
        v3.color = { GameObjectsArray->GetColorR(), GameObjectsArray->GetColorG(), GameObjectsArray->GetColorB(), GameObjectsArray->GetAlphaChannel() };
        v3.texCoord = { 1.0f, 1.0f };
        v3.texID = { GameObjectsArray->GetTXNumber() };

        Vertex v4;

        //v4.position = { RDQuaterion4.x, RDQuaterion4.y, RDQuaterion4.z, RDQuaterion4.w };
        v4.position = { GameObjectsArray->GetTopLeft().x, GameObjectsArray->GetTopLeft().y, 0.0f };
        v4.color = { GameObjectsArray->GetColorR(), GameObjectsArray->GetColorG(), GameObjectsArray->GetColorB(), GameObjectsArray->GetAlphaChannel() };
        v4.texCoord = { 0.0f, 1.0f };
        v4.texID = { GameObjectsArray->GetTXNumber() };


        return { v1, v2, v3, v4 };
    }

    std::array<Vertex, 4> Scene::CreateObject(const std::shared_ptr<Character>& GameObjectsArray)
    {
        Vertex v1;


        //v1.position = { RDQuaterion1.x, RDQuaterion1.y, RDQuaterion1.z, RDQuaterion1.w };
        v1.position = { GameObjectsArray->GetBottomLeft().x, GameObjectsArray->GetBottomLeft().y, 1.0f };
        v1.color = { GameObjectsArray->GetColorR(), GameObjectsArray->GetColorG(), GameObjectsArray->GetColorB(), GameObjectsArray->GetAlphaChannel() };
        v1.texCoord = { GameObjectsArray->GetTextureCoordinates().BottomLeft.x, GameObjectsArray->GetTextureCoordinates().BottomLeft.y };
        v1.texID = { GameObjectsArray->GetTXNumber() }; // 0.0f will be reserved for no object


        Vertex v2;

        //v2.position = { RDQuaterion2.x, RDQuaterion2.y, RDQuaterion2.z, RDQuaterion2.w };
        v2.position = { GameObjectsArray->GetBottomRight().x, GameObjectsArray->GetBottomRight().y, 1.0f };
        v2.color = { GameObjectsArray->GetColorR(), GameObjectsArray->GetColorG(), GameObjectsArray->GetColorB(), GameObjectsArray->GetAlphaChannel() };
        v2.texCoord = { GameObjectsArray->GetTextureCoordinates().BottomRight.x, GameObjectsArray->GetTextureCoordinates().BottomRight.y };
        v2.texID = { GameObjectsArray->GetTXNumber() };


        Vertex v3;

        //v3.position = { RDQuaterion3.x, RDQuaterion3.y, RDQuaterion3.z, RDQuaterion3.w };
        v3.position = { GameObjectsArray->GetTopRight().x, GameObjectsArray->GetTopRight().y, 1.0f };
        v3.color = { GameObjectsArray->GetColorR(), GameObjectsArray->GetColorG(), GameObjectsArray->GetColorB(), GameObjectsArray->GetAlphaChannel() };
        v3.texCoord = { GameObjectsArray->GetTextureCoordinates().TopRight.x, GameObjectsArray->GetTextureCoordinates().TopRight.y };
        v3.texID = { GameObjectsArray->GetTXNumber() };

        Vertex v4;

        //v4.position = { RDQuaterion4.x, RDQuaterion4.y, RDQuaterion4.z, RDQuaterion4.w };
        v4.position = { GameObjectsArray->GetTopLeft().x, GameObjectsArray->GetTopLeft().y, 1.0f };
        v4.color = { GameObjectsArray->GetColorR(), GameObjectsArray->GetColorG(), GameObjectsArray->GetColorB(), GameObjectsArray->GetAlphaChannel() };
        v4.texCoord = { GameObjectsArray->GetTextureCoordinates().TopLeft.x, GameObjectsArray->GetTextureCoordinates().TopLeft.y };
        v4.texID = { GameObjectsArray->GetTXNumber() };


        return { v1, v2, v3, v4 };
    }






    // section end
    Scene::Scene()
        : 

        RD1TXData(LoadTexture("res/textures/dew.png")), grassTXData(LoadTexture("res/textures/NewWorld/grass1024.png")), dirtTXData(LoadTexture("res/textures/NewWorld/dirt.png")), 
        /*RustyBarTXData(LoadTexture("res/textures/image 36_1.png")), FloorTXData(LoadTexture("res/textures/image 20.jpg")), BGImageTXData(LoadTexture("res/textures/image 70.jpg")),
        netTXData(LoadTexture("res/textures/image 37.png")), blackVeilTXData(LoadTexture("res/textures/LevelMap.png")), 
        FogBlocksTXData(LoadTexture("res/textures/FogBoxAlpha4.png")), BGBlocksTXData(LoadTexture("res/textures/image 70.jpg")), RustyPipeTXData(LoadTexture("res/textures/RustyPipe1.png")),
        metalSupBlocksTXData(LoadTexture("res/textures/MetalSupport.png")),*/ FluxTXData(LoadTexture("res/textures/flux.png")), ghostTXData(LoadTexture("res/textures/NewWorld/ghost.png")),
        mouseCursorTXData(LoadTexture("res/textures/image 348.png")), bulletTXData(LoadTexture("res/textures/NewWorld/bullet.png")), HelmieTXData(LoadTexture("res/textures/helmie.png")),

        RD1(std::make_shared<Character>(glm::vec3(1920/2, 1080/2, 0), RD1TXData, 1.0f)), // 300 500 0
        
        mouseCursor(std::make_shared<GameObject>(glm::vec3(960, 540, 0), mouseCursorTXData, 2.0f)),

        
        starttime(0), endtime(0), delta(0)
        
	{
        bool res = loadOBJ("cube.obj", verticesCube, uvsCube, normalsCube);
        //glfwSetMouseButtonCallback(window,  mouseButtonCallback ); // subscribe to mouse clicks
        //chang = 0.0e default texture size
        RD1->SetSpriteResolution(100, 100);




        //GameObjectsArray.reserve(450); // allocate 200 slots for fog elements
        vertices.reserve(MAX_OBJECTS); // allocate 450 slots for fog elements

        chunks.insert({ std::make_pair(0, 0), (std::make_shared<Chunk>(glm::vec3(0, 0, 0), grassTXData, 3.0f)) });


        //GenerateChunk();

        //GameObjectsArray.push_back(chunks[(std::make_pair(RD1->GetBottomLeft().x / 1024, RD1->GetBottomLeft().y / 1024))]);

        //indices.reserve((GameObjectsArray.size()) * 6);
        indices.reserve((chunks.size()) * 6);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        

        m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
        m_Shader->Bind();
        //m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        m_Shader->SetUniform1iv("u_Texture", MAX_TEXTURES);
        
        

	}
	Scene::~Scene()
	{
        std::cout << "ALL CLEANED" << std::endl;
	}

    float angleToRot = 0.0f;
    float xView = 0.0f;
    float yView = 0.0f;

	void Scene::OnUpdate(GLFWwindow* window, float deltaTime)
	{
        if (perspective_mode) {
            horizontalAngle = mouseSpeed * float(1920 / 2 - xpos);
            verticalAngle = mouseSpeed * float(1080 / 2 - ypos);

            glm::vec3 direction(
                cos(verticalAngle) * sin(horizontalAngle),
                sin(verticalAngle),
                cos(verticalAngle) * cos(horizontalAngle)
            );

            glm::vec3 right = glm::vec3(
                sin(horizontalAngle - 3.14f / 2.0f),
                0,
                cos(horizontalAngle - 3.14f / 2.0f)
            );

            std::cout << position.x << " " << position.y << " " << position.z;
            std::cout << direction.x + position.x << " " << direction.y + position.y << " " << direction.z + position.z;
            std::cout << up.x << " " << up.y << " " << up.z << std::endl;
            // Up vector
            glm::vec3 up = glm::cross(right, direction);

            m_Proj = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 1.0f, 2000.0f);
            m_View = glm::lookAt(
                position,           // Camera is here
                position + direction, // and looks here : at the same position, plus "direction"
                up                  // Head is up (set to 0,-1,0 to look upside-down)
            );
            m_VP = m_Proj * m_View;
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            RD1->Jump();
            //m_View = glm::translate(glm::mat4(1.0f), glm::vec3(RD1->GetBottomLeft().x + 50, RD1->GetBottomLeft().y + 50, 0));
        }

        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            if (!RD1->IsReversed())
            {
                RD1->SetReversed(true);
                RD1->ReverseTexture();
            }
            m_View = glm::translate(glm::mat4(1.0f), glm::vec3(xView += 5, yView, 0));
            RD1->MoveLeft(5.0f);
        }

        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            if (RD1->IsReversed())
            {
                RD1->SetReversed(false);
                RD1->ReverseTexture();
            }
            m_View = glm::translate(glm::mat4(1.0f), glm::vec3(xView-=5, yView, 0));
            RD1->MoveRight(5.0f);
        }

        // Strafe up
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
         {
            m_View = glm::translate(glm::mat4(1.0f), glm::vec3(xView, yView += 5, 0));
            RD1->MoveUp(-5.0f);
        }

        // Strafe down
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
         {
            m_View = glm::translate(glm::mat4(1.0f), glm::vec3(xView, yView -= 5, 0));
            RD1->MoveUp(5.0f);
        }

        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
            RD1->ChangeSize(-9, -9);
        }

        if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
            RD1->ChangeSize(9, 9);
        }

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            RD1->SetRotationAngle(angleToRot+=3.0f);
        }

        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            RD1->SetRotationAngle(angleToRot-=3.0f);
        }


        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
            xView = 0;
            yView = 0;
            m_View = glm::translate(glm::mat4(1.0f), glm::vec3(xView, yView, 0));
            RD1->SetCurrentPosition(glm::vec3(1920 / 2, 1080 / 2, 0));
        }

        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            RD1->SetTextureID(FluxTXData.textureID);
        }

        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            RD1->SetTextureID(HelmieTXData.textureID);
        }

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            RD1->SetTextureID(RD1TXData.textureID);
        }

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            RD1->SetReversed(true);
        }

        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            RD1->SetReversed(false);
        }

        //if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {

        //    horizontalAngle += mouseSpeed * float(1920 / 2 - xpos);
        //    verticalAngle += mouseSpeed * float(1080 / 2 - ypos);

        //    glm::vec3 direction(
        //        cos(verticalAngle) * sin(horizontalAngle),
        //        sin(verticalAngle),
        //        cos(verticalAngle) * cos(horizontalAngle)
        //    );

        //    glm::vec3 right = glm::vec3(
        //        sin(horizontalAngle - 3.14f / 2.0f),
        //        0,
        //        cos(horizontalAngle - 3.14f / 2.0f)
        //    );


        //    // Up vector
        //    glm::vec3 up = glm::cross(right, direction);

        //    m_Proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
        //    m_View = glm::lookAt(
        //        position,           // Camera is here
        //        position + direction, // and looks here : at the same position, plus "direction"
        //        up                  // Head is up (set to 0,-1,0 to look upside-down)
        //    );
        //}



        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
            m_Proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
            m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0) );
        }

        for (const auto& ghost : ghosts)
        {
            if (abs(RD1->GetBottomLeft().x - ghost->GetBottomLeft().x) < 400 && abs(RD1->GetBottomLeft().y - ghost->GetBottomLeft().y) < 400) // в пределах видимости
            {
                if (RD1->GetBottomLeft().x > ghost->GetBottomLeft().x)
                    ghost->MoveRight(5.0f / 2);
                else ghost->MoveLeft(5.0f / 2);

                if (RD1->GetBottomLeft().y > ghost->GetBottomLeft().y)
                    ghost->MoveUp(5.0f / 2);
                else ghost->MoveUp(-5.0f / 2);
            }
        }

        // affect Dew with gravity
        //Gravity(RD1, RD1->GetYVelocity());


        // replace cursor with image

        glfwGetCursorPos(window, &xpos, &ypos);
        //std::cout << xpos << " " << ypos << std::endl;
        mouseCursor->SetXPosition(static_cast<float>(xpos) - xView);
        mouseCursor->SetYPosition(1080.0f - static_cast<float>(ypos) - yView);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
        {
            SpawnBullet();
        }

        //mouseCursor->PrintCoords();
        static int df = 0;
        if (static_cast<int>(RD1->GetBottomLeft().x) % 1025 == 0 || static_cast<int>(RD1->GetBottomLeft().y) % 1025 == 0 ||
            static_cast<int>(RD1->GetBottomRight().x) % 1025 == 0 || static_cast<int>(RD1->GetBottomRight().y) % 1025 == 0 ||
            static_cast<int>(RD1->GetTopLeft().x) % 1025 == 0 || static_cast<int>(RD1->GetTopLeft().y) % 1025 == 0 ||
            static_cast<int>(RD1->GetTopRight().x) % 1025 == 0 || static_cast<int>(RD1->GetTopRight().y) % 1025 == 0 )
        {
            if(chunks.find(std::make_pair(RD1->GetBottomLeft().x / 1024, RD1->GetBottomLeft().y / 1024)) == chunks.end() ) // chunk already exists
            {
                //store coords in memory (heap)
                std::pair<int, int> ChunkCoords = std::make_pair(RD1->GetBottomLeft().x / 1024, RD1->GetBottomLeft().y / 1024);
                chunks.insert({ ChunkCoords, (std::make_shared<Chunk>(glm::vec3((int)(RD1->GetBottomLeft().x / 1024) * 1024, (int)(RD1->GetBottomLeft().y / 1024) * 1024, 0), grassTXData, 3.0f, 1.0f, 1.0f, 1.0f)) }); // change to dynamic numbers
                GeneratePath(std::static_pointer_cast<Chunk>(chunks [ChunkCoords] ));

                //transmit coords to OpenGL container
                //GameObjectsArray.push_back(chunks[ChunkCoords]);
                //for (size_t i = 0; i < std::dynamic_pointer_cast<Chunk>(chunks[ChunkCoords])->GetpathElementCoords().size(); i++)
                //{
                //    GameObjectsArray.push_back(std::dynamic_pointer_cast<Chunk>(chunks[ChunkCoords])->GetpathElementCoords()[i]);
                //}
                //GameObjectsArray.push_back(ghosts.back());
            }
        }


	}
    



	void Scene::OnRender(GLFWwindow* window)
	{



        glEnable(GL_DEBUG_OUTPUT);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);

        starttime = glfwGetTime();

        size_t objCount = 0;

        objCount += chunks.size();
        objCount += ghosts.size();
        objCount += bullets.size();

        {
            LOG_DURATION("OnDirtSize")
                for (auto& it : chunks)
                {
                    objCount += it.second->GetpathElementCoords().size();
                }
        }


        const size_t MaxQuadCount = /*GameObjectsArray.size()*/ objCount + 2; // 2 -- RD1 and cursor
        const size_t MaxVertexCount = MaxQuadCount * 4;
        const size_t MaxIndexCount = MaxQuadCount * 6;

        //Vertex vertices[MaxVertexCount]; // (background tiles) + nets (12) + cursor, RD1, RustyBar, Floor, blackVeil; 17 obs * 4 vert = 68

        //unsigned int indices[MaxIndexCount];
        unsigned int offset = 0;
        for (size_t i = 0; i < MaxIndexCount; i += 6)
        {
            indices.push_back(0 + offset);
            indices.push_back(1 + offset);
            indices.push_back(2 + offset);
                                        
            indices.push_back(2 + offset);
            indices.push_back(3 + offset);
            indices.push_back(0 + offset);

            offset += 4;
        }

        std::unique_ptr<VertexArray> VAO = std::make_unique<VertexArray>();
        VAO->Bind();
        std::unique_ptr<VertexBuffer> VBO = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex) * MaxVertexCount); // buffer capability is 1000 quads (4000 Vertices), 
        //VBO->Bind();
        std::unique_ptr<IndexBuffer> IB = std::make_unique<IndexBuffer>(reinterpret_cast<const unsigned int*>(indices.data()), MaxIndexCount); // fix arguments, 
        IB->Bind();


        glEnableVertexArrayAttrib(VBO->GetID(), 0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));

        glEnableVertexArrayAttrib(VBO->GetID(), 1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));

        glEnableVertexArrayAttrib(VBO->GetID(), 2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoord));

        glEnableVertexArrayAttrib(VBO->GetID(), 3);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texID));

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 mvp = m_Proj * m_View * model;





        //BindTextures(GameObjectsArray); // most of the objects
        //FillVBO(GameObjectsArray, vertices);
        {
            LOG_DURATION("OnChunks")
            for (auto& it : chunks)
            {
                BindTextures(it.second);
                FillVBO(it.second, vertices);
            }
        }
        {
            LOG_DURATION("OnDirt")
                for (auto& it : chunks)
                {
                    auto tmp = it.second->GetpathElementCoords(); // no need to do run-time checks with dynamic_pointer_cast
                    for (size_t i = 0; i < tmp.size(); i++)
                    {
                        //tmp = std::dynamic_pointer_cast<Chunk>(it.second)->GetpathElementCoords()[i];
                        BindTextures(tmp[i]);
                        FillVBO(tmp[i], vertices);
                    }
                }
        }

        {
            LOG_DURATION("OnGhosts")
                for (auto& it : ghosts)
                {
                    BindTextures(it);
                    FillVBO(it, vertices);
                }

        }

        {
            LOG_DURATION("OnBullets")
                for (auto& it : bullets)
                {
                    BindTextures(it);
                    FillVBO(it, vertices);
                }

        }


        //GameObjectsArray.push_back(RD1); // Dew goes to Character function, where tex coords can be traced
        BindTextures(RD1);
        FillVBO(RD1, vertices);

        //GameObjectsArray.push_back(mouseCursor); // cursor goes as the last single GameObject
        BindTextures(mouseCursor);
        FillVBO(mouseCursor, vertices);



        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);


        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices.back()) * vertices.size(), (reinterpret_cast<const char*>(vertices.data()) ));

        glDrawElements(GL_TRIANGLES, IB->GetCount(), GL_UNSIGNED_INT, nullptr);


        endtime = glfwGetTime();
        delta = endtime - starttime;

        indices.clear();
        vertices.clear();


        //GameObjectsArray.erase(std::end(GameObjectsArray) - 1);
        //GameObjectsArray.erase(std::end(GameObjectsArray) - 1);

        //std::cout << GameObjectsArray.size() << std::endl;
        //std::cout << objCount << std::endl;
        //std::cout << RD1->GetBottomLeft().x << std::endl;
        //std::cout << RD1->GetBottomLeft().y << std::endl;
	}

    void Scene::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_P && action == GLFW_PRESS)
        {
            perspective_mode = true;
        }

        if (key == GLFW_KEY_O && action == GLFW_PRESS)
        {
            perspective_mode = false;
        }

        if (key == GLFW_KEY_Y && action == GLFW_PRESS)
        {
            position += direction * 30.0f;
        }

        if (key == GLFW_KEY_H && action == GLFW_PRESS)
        {
            position += right * 30.0f;
        }

        if (key == GLFW_KEY_U && action == GLFW_PRESS)
        {
            position -= direction * 30.0f;
        }

        if (key == GLFW_KEY_J && action == GLFW_PRESS)
        {
            position -= right * 30.0f;
        }
    }