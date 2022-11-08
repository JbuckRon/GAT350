#include "Engine.h"
#include <iostream>


float vertices[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};


int main(int argc, char** argv)
{
	LOG("Application Started...");
	neu::InitializeMemory();
	neu::SetFilePath("../Assets");


	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();
	LOG("Engine Initialized...");


	neu::g_renderer.CreateWindow("Neumont", 800, 600);
	LOG("Window Initialized...");


	//make scene
	auto scene = std::make_unique<neu::Scene>();
	rapidjson::Document document;
	bool success = neu::json::Load("scenes/basic.scn", document);
	if (!success)
	{
		LOG("error loading scene file %s.", "scenes/basic_lit.scn");
	}
	else
	{
		scene->Read(document);
		scene->Initialize();
	}


	// create vertex buffer

	//GLuint vbo = 0;
	//glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//// create vertex array
	//GLuint vao = 0;
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	//glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	std::shared_ptr<neu::VertexBuffer> vb = neu::g_resources.Get<neu::VertexBuffer>("box");
	vb->CreateVertexBuffer(sizeof(vertices), 36, vertices);
	vb->SetAttribute(0, 3, 8 * sizeof(float), 0);
	vb->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));
	vb->SetAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));

	// create shader
	std::shared_ptr<neu::Shader> vs = neu::g_resources.Get<neu::Shader>("shaders/basic.vert", GL_VERTEX_SHADER);
	std::shared_ptr<neu::Shader> fs = neu::g_resources.Get<neu::Shader>("shaders/basic.frag", GL_FRAGMENT_SHADER);


	


	// create program
	std::shared_ptr<neu::Program> program = neu::g_resources.Get<neu::Program>("shaders/basic.prog", GL_PROGRAM);
	program->Link();
	program->Use();

	//create texture
	std::shared_ptr<neu::Texture> texture1 = neu::g_resources.Get<neu::Texture>("textures/llama.jpg");
	//texture1->Bind();
	
	std::shared_ptr<neu::Texture> texture2 = neu::g_resources.Get<neu::Texture>("textures/wood.png");
	//texture2->Bind();




	
	// 1 0 0 0
	// 0 1 0 0
	// 0 0 1 0
	// 0 0 0 1

	glm::mat4 model{ 1 };
	glm::mat4 projection = glm::perspective(45.0f, neu::g_renderer.GetWidth() / (float)neu::g_renderer.GetHeight(), 0.01f, 100.0f);
	//mx = glm::scale(glm::vec3{ 0.5, 0.5, 0.5 });



	glm::vec3 cameraPosition{ 0, 2, 2 };

	//std::vector<neu::Transform> transforms;

	/*for (size_t i = 0; i < 10; i++)
	{
		transforms.push_back({ { neu::randomf(-10, 10), neu::randomf(-10, 10), neu::randomf(-10, 10)}, {neu::randomf(360), 90, 0} });
	}*/

	neu::Transform transforms[] =
	{
		{ {neu::randomf(-10, 10), neu::randomf(-10, 10), neu::randomf(-10, 10)}, {neu::randomf(360), 90, 0}},
		{ {2, 0, 0 }, { 0, 90, 90} },
		{ {0, 2, -2 }, { 45, 90, 0} },
		{ {-2, 1, 0 }, { 90, 90, 0} },
	};

	//model
	auto m = neu::g_resources.Get<neu::Model>("models/ogre.obj");

	//create material
	std::shared_ptr<neu::Material> material = neu::g_resources.Get<neu::Material>("materials/ogre.mtrl");
	material->Bind();
	


	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		auto actor = scene->GetActorFromName("Ogre");
		if (actor)
		{
			actor->m_transform.rotation.y += neu::g_time.deltaTime * 90.0f;
		}
		/*if (neu::g_inputSystem.GetKeyState(neu::key_W) == neu::InputSystem::KeyState::Pressed) cameraPosition.x -= 1;
		if (neu::g_inputSystem.GetKeyState(neu::key_A) == neu::InputSystem::KeyState::Pressed) cameraPosition.y -= 1;
		if (neu::g_inputSystem.GetKeyState(neu::key_S) == neu::InputSystem::KeyState::Pressed) cameraPosition.x += 1;
		if (neu::g_inputSystem.GetKeyState(neu::key_D) == neu::InputSystem::KeyState::Pressed) cameraPosition.y += 1;*/



		//glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3{ 0 ,0 ,0 }, glm::vec3{0, 1, 0 });

		//model = glm::eulerAngleXYX(0.0f, 0.0f,  0.0f);



		/*program->SetUniform("scale", std::sin(neu::g_time.time * 3));
		program->SetUniform("transform", model);

		material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });
		material->GetProgram()->SetUniform("scale", 0.5f);*/

		scene->Update();

		neu::g_renderer.BeginFrame();

		scene->Draw(neu::g_renderer);
		//m->m_vertexBuffer.Draw();
		/*for (size_t i = 0; i < 4; i++)
		{
			transforms[i].rotation += glm::vec3(0, 90 * neu::g_time.deltaTime, 0);
		}*/
			/*glm::mat4 mvp = projection * view;
			material->GetProgram()->SetUniform("mvp", mvp);*/
			//vb->Draw();

		//glDrawArrays(GL_TRIANGLES, 0, 36);

		neu::g_renderer.EndFrame();
	}
	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();
	return 0;
}
