#include "view/StoryWindow.h"
#include "imgui.h"
#include "imgui_internal.h"

StoryWindow::StoryWindow()
	: visible(false), currentPage(0), finished(false)
{
	// Тесты истории
	texts = {
		"В далёкой галактике люди создали первый зоопарк для инопланетных существ...",
		"Учёные привезли первых животных на новую планету...",
		"Но ухаживать за ними оказалось сложнее, чем казалось...",
		"Только настоящий директор сможет справиться с этой задачей...",
		"И теперь твоя миссия — построить лучший зоопарк!"
	};

	// Здесь можно добавить пути к картинкам
    images = {
        "assets/images/page1.png",
        "assets/images/page2.png",
        "assets/images/page3.png",
        "assets/images/page4.png",
        "assets/images/page5.png"
    };
}

void StoryWindow::render() {
	if (!visible || finished) return;
	
	ImGui::OpenPopup("История");

	ImGui::SetNextWindowSize(ImVec2(450.0f, 0.0f));
	if (ImGui::BeginPopupModal("История", nullptr,
								ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize))
	{
		ImGui::Columns(2, nullptr, false);

		// Картинка
		// ImGui::SetNextWindowSize(ImVec2(300.0f, 300.0f));
		ImGui::Text("[Картинка %d]", currentPage + 1);

		ImGui::NextColumn();

		// Текст
		// ImGui::SetNextWindowSize(ImVec2(600.0f, 300.0f));
		ImGui::TextWrapped("%s", texts[currentPage].c_str());

		ImGui::Columns(1);

		ImGui::Separator();

		// Управление страницами
		if (currentPage > 0) {
			if (ImGui::Button("Назад")) {
				currentPage--;
			}
		}
		ImGui::SameLine();
		if (currentPage < (int)texts.size() - 1) {
			if (ImGui::Button("Далее")) {
				currentPage++;
			}
		} else {
			if (ImGui::Button("Завершить")) {
				finished = true;
				visible = false;
				ImGui::CloseCurrentPopup();
			}
		}
	
		ImGui::SameLine();
		ImGui::Text("%d / %d страница", currentPage + 1, (int)texts.size());
	
		ImGui::EndPopup();
	}
}

void StoryWindow::setVisible(bool vis) {
	visible = vis;
	currentPage = 0;
	finished = false;
}

bool StoryWindow::isVisible() const {
	return false;
}

bool StoryWindow::isFinished() const {
	return visible;
}