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

	neu::g_gui.Initialize(neu::g_renderer);

	//create frame buffer texture
	auto texture = std::make_shared<neu::Texture>();
	texture->CreateTexture(512, 512);
	neu::g_resources.Add<neu::Texture>("fb_texture", texture);

	//create frame buffer
	auto framebuffer = neu::g_resources.Get<neu::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();


	//make scene
	auto scene = std::make_unique<neu::Scene>();
	rapidjson::Document document;
	bool success = neu::json::Load("Scenes/rtt.scn", document);
	if (!success)
	{
		LOG("error loading scene file %s.", "scenes/rtt.scn");
	}
	else
	{
		scene->Read(document);
		scene->Initialize();
	}

	
	// 1 0 0 0
	// 0 1 0 0
	// 0 0 1 0
	// 0 0 0 1

	glm::mat4 model{ 1 };
	glm::mat4 projection = glm::perspective(45.0f, neu::g_renderer.GetWidth() / (float)neu::g_renderer.GetHeight(), 0.01f, 100.0f);
	//mx = glm::scale(glm::vec3{ 0.5, 0.5, 0.5 });



	glm::vec3 cameraPosition{ 0, 2, 2 };



	//create material
	std::shared_ptr<neu::Material> material = neu::g_resources.Get<neu::Material>("Materials/ogre.mtrl");
	material->Bind();
	
	float x = 0;
	glm::vec3 rot { 0 , 0 , 0 };

	float ri = 1;
	float interp = 0.85f;

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		neu::g_gui.BeginFrame(neu::g_renderer);
		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		auto actor = scene->GetActorFromName("Ogre");
		if (actor)
		{
			actor->m_transform.rotation = math::EulerToQuaternion(rot);
		}


		actor = scene->GetActorFromName("Light");
		if (actor)
		{
		// move light using sin wave
			//actor->m_transform.position = pos;
		}
		

		auto material = neu::g_resources.Get<neu::Material>("Materials/multi.mtrl");
		if (material)
		{
			material->uv_offset += glm::vec2(neu::g_time.deltaTime);
		}

		auto program = neu::g_resources.Get<neu::Program>("shaders/fx/refraction.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("ri", ri);
		}

		ImGui::Begin("Transform");
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::DragFloat3("Refraction Index", &ri, 0.01f, 1, 3);
		ImGui::End();

		scene->Update();

		// render pass 1 (render to framebuffer)
		neu::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();

		// render pass 2 (render to screen)
		neu::g_renderer.RestoreViewport();

		neu::g_renderer.BeginFrame();

		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);

		neu::g_gui.Draw();
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
		neu::g_gui.EndFrame();
	}
	scene->RemoveAll();
	neu::Engine::Instance().Shutdown();
	return 0;
}
