#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "model/Model.h"
#include "model/GameLogic.h"
#include "view/GameWindow.h"
#include "view/SettingsWindow.h"
#include "presenter/Presenter.h"
#include "view/ImGuiTheme.h"
#include "presenter/MockPresenter.h"

int main() {
	// Инициализация GLFW
	if (!glfwInit()) return -1;
	GLFWwindow* window = glfwCreateWindow(1280, 720, "MyProject", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Инициализация ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = NULL; // Отключает загрузку imgui.ini
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	// Загружаем шрифт и настраиваем его на кирилицу
	static const ImWchar ranges[] = {
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0,
	};
	io.Fonts->AddFontFromFileTTF("assets/fonts/SeymourOne-Regular.ttf", 20.0f, nullptr, ranges);

	// Применяем тему
	ImGuiTheme::StyleClassicSteam();

	// MVP
	Model model;
	GameLogic gameLogic;
	GameWindowUI gameWindowUI;          // <-- пропущенная ';' была
	MockPresenter mock;                 // простой презентер для отладки
	gameWindowUI.SetPresenter(&mock);   // <-- было gameUI.SetPresenter

	SettingsWindow settingsWindow;
	StoryWindow storyWindow;
	AnimalWindow animalWindow;

	Presenter presenter(model, gameLogic, gameWindowUI, settingsWindow, storyWindow, animalWindow);

	// Главный цикл
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		if (glfwWindowShouldClose(window)) {
			break;
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		presenter.handleInput();
		presenter.update();

		// Остальные окна рендерятся отдельно
        settingsWindow.render();
        storyWindow.render();
        animalWindow.render();

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	// Очистка
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}