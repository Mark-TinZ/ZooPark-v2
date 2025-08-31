#include "view/GameWindow.h"   // <-- был "GameWindow.h"
#include <chrono>
#include <future>
#include <thread>
#include <sstream>
#include <cstring>             // <-- для std::strncpy

// --------------------------- Construction ---------------------------
GameWindowUI::GameWindowUI()
{
	new_game_params_.name = "New World";
	new_game_params_.difficulty = 1;
	new_game_params_.map_size = 64;
	std::strncpy(new_world_name_buf_, new_game_params_.name.c_str(), sizeof(new_world_name_buf_));
	new_world_name_buf_[sizeof(new_world_name_buf_)-1] = '\0';
}

GameWindowUI::~GameWindowUI() = default;

// --------------------------- Public modals control ---------------------------
void GameWindowUI::RequestModal(ModalType type) { pedding_modal_ = type; }
void GameWindowUI::ProcessPeddingModals() {
	switch (pedding_modal_)
	{
	case ModalType::NewGame:
		show_newgame_modal_ = true;
		ImGui::OpenPopup("New Game");
		break;
	case ModalType::LoadGame:
		show_load_modal_ = true;
		ImGui::OpenPopup("Load Game");
		break;
	case ModalType::Settings:
		show_settings_modal_ = true; 
		ImGui::OpenPopup("Settings");
		break;
	case ModalType::QuitConfirm:
		show_quit_modal_ = true; 
		ImGui::OpenPopup("Quit?");
		break;
	default:
		break;
	}
	pedding_modal_ = ModalType::None;
}
void GameWindowUI::CloseAllModals()
{
	show_newgame_modal_ = show_load_modal_ = show_settings_modal_ = show_quit_modal_ = false;
	ImGui::CloseCurrentPopup();
}

// --------------------------- Main render entry ---------------------------
void GameWindowUI::Render()
{
	DrawMainMenuBar(); // Отображение menubar
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	float menu_h = ImGui::GetFrameHeight();
	if (first_frame_setup_) {
		ImVec2 pos = viewport->Pos;
		ImVec2 size = viewport->Size;
		pos.y += menu_h;
		size.y -= menu_h;

		ImGui::SetNextWindowPos(pos);
		ImGui::SetNextWindowSize(size);
		ImGui::SetNextWindowViewport(viewport->ID);
		first_frame_setup_ = false;
	} else {
		ImVec2 pos = viewport->Pos;
		ImVec2 size = viewport->Size;
		pos.y += menu_h;
		size.y -= menu_h;

		ImGui::SetNextWindowPos(pos);
		ImGui::SetNextWindowSize(size);
		ImGui::SetNextWindowViewport(viewport->ID);
	}

	// Window flags to act as main full-screen canvas
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
							 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse; //| ImGuiWindowFlags_MenuBar;


	ImGui::Begin("MainGameWindow", nullptr, flags);


	// Layout: left info / center gameplay preview / right actions
	ImGui::BeginChild("MainLeft", ImVec2(240, -1), true);
	ImGui::TextWrapped("Game");
	ImGui::Separator();
	if (ImGui::Button("New Game", ImVec2(-1, 0))) RequestModal(ModalType::NewGame);
	if (ImGui::Button("Load Game", ImVec2(-1, 0))) RequestModal(ModalType::LoadGame);
	if (ImGui::Button("Settings", ImVec2(-1, 0))) RequestModal(ModalType::Settings);
	if (ImGui::Button("Quit", ImVec2(-1, 0))) RequestModal(ModalType::QuitConfirm);
	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("MainCenter", ImVec2(0, 0), false);
	ImGui::TextWrapped("**Тут крч будет привьюшка мира или просто слайд шоу с геймплеем, и показываться там будет всяко разано**");
	ImGui::Dummy(ImVec2(0, 8));
	ImGui::TextWrapped("Статус / информация / версия");
	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("MainRight", ImVec2(300, 0), true);
	ImGui::Text("Quick Actions");
	ImGui::Separator();
	// TODO: сделать быструю загрузку последнего сохранения
	if (presenter_) {
		if (ImGui::Button("Load Last Save", ImVec2(-1, 0))) {
			auto saves = presenter_->ListSaves();
			if (!saves.empty()) {
				presenter_->LoadSave(saves.front().id); // Загружает последний
			} else {
				error_message_ = "No saves available";
				show_error_modal_ = true;
			}
		}
	}
	ImGui::EndChild();

	ImGui::End(); // MainGameWindow

	ProcessPeddingModals();

	// Draw popups / modals
	DrawNewGameModal();
	DrawSavesLoadModal();
	DrawSettingsModal();
	DrawQuitConfirmModal();
	DrawErrorModalIfNeeded();

	// Note: UI should not directly do expensive IO; call presenter which may perform async I/O.
	// Example async pattern (comment): launch std::async in presenter to ListSaves() and when done copy
	// results into saves_cache_ protected by saves_mutex_. UI then reads saves_cache_ under lock.
}

// --------------------------- Menu bar ---------------------------
void GameWindowUI::DrawMainMenuBar()
{
	if (ImGui::BeginMainMenuBar()) { // Было: BeginMainMenuBar
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("New Game")) RequestModal(ModalType::NewGame);
			if (ImGui::MenuItem("Load Game")) RequestModal(ModalType::LoadGame);
			if (ImGui::MenuItem("Settings")) RequestModal(ModalType::Settings);
			if (ImGui::MenuItem("Quit")) RequestModal(ModalType::QuitConfirm);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			ImGui::MenuItem("About");
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar(); // Было: EndMainMenuBar
	}
}

// --------------------------- New Game modal ---------------------------
void GameWindowUI::DrawNewGameModal()
{
	if (!show_newgame_modal_) return;

	ImGui::SetNextWindowSize(ImVec2(520, 260), ImGuiCond_Appearing);
	if (ImGui::BeginPopupModal("New Game", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("Create a new game");
		ImGui::Separator();

		ImGui::InputText("World Name", new_world_name_buf_, IM_ARRAYSIZE(new_world_name_buf_));
		new_game_params_.name = std::string(new_world_name_buf_);

		ImGui::SliderInt("Difficulty", &new_game_params_.difficulty, 0, 5);
		ImGui::InputInt("Map Size", &new_game_params_.map_size);

		ImGui::Dummy(ImVec2(0, 8));
		ImGui::BeginGroup();
		if (ImGui::Button("Create", ImVec2(120, 0))) {
			if (!presenter_) {
				error_message_ = "Presenter not set!";
				show_error_modal_ = true;
			} else {
				// Synchronous create (fast): call presenter->CreateGame()
				bool ok = presenter_->CreateGame(new_game_params_);
				if (!ok) {
					error_message_ = "Failed to create game (presenter returned error)";
					show_error_modal_ = true;
				} else {
					// success -> close modal
					ImGui::CloseCurrentPopup();
					show_newgame_modal_ = false;
				}
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) {
			ImGui::CloseCurrentPopup();
			show_newgame_modal_ = false;
		}
		ImGui::EndGroup();

		ImGui::EndPopup();
	}
}

// --------------------------- Load saves modal ---------------------------
void GameWindowUI::DrawSavesLoadModal()
{
	if (!show_load_modal_) return;

	// When modal opens, refresh saves async (non-blocking)
	static bool requested_loads_refresh = false;
	if (!requested_loads_refresh) {
		requested_loads_refresh = true;
		// If presenter provides heavy IO, run it asynchronously and copy results to saves_cache_ safely.
		// Here we show an example pattern (uncomment for real async use):
		//
		// std::async(std::launch::async, [this]() {
		//     if (!presenter_) return;
		//     auto list = presenter_->ListSaves(); // potentially heavy
		//     std::lock_guard<std::mutex> lk(saves_mutex_);
		//     saves_cache_ = std::move(list);
		// });
		//
		// For simplicity we do synchronous call (ok for in-memory mock).
		if (presenter_) {
			auto list = presenter_->ListSaves();
			std::lock_guard<std::mutex> lk(saves_mutex_);
			saves_cache_ = std::move(list);
			selected_save_index_ = saves_cache_.empty() ? -1 : 0;
		}
	}

	ImGui::SetNextWindowSize(ImVec2(760, 420), ImGuiCond_Appearing);
	if (ImGui::BeginPopupModal("Load Game", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("Load saved game");
		ImGui::Separator();

		ImGui::Columns(2);
		ImGui::BeginChild("SaveList", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true);
		// left column: listbox
		std::vector<std::string> names;
		{
			std::lock_guard<std::mutex> lk(saves_mutex_);
			for (auto &s : saves_cache_) names.push_back(s.name);
		}

		ImGui::BeginChild("##savelist", ImVec2(-FLT_MIN, 300), true, ImGuiWindowFlags_HorizontalScrollbar);
		for (int i = 0; i < (int)names.size(); ++i) {
			bool selected = (i == selected_save_index_);
			if (ImGui::Selectable(names[i].c_str(), selected)) {
				selected_save_index_ = i;
			}
			// опционально: прокрутка к выбранному элементу при смене
			if (selected) ImGui::SetScrollHereY();
		}
		ImGui::EndChild();

		ImGui::NextColumn();

		// right column: preview + metadata + actions
		{
			std::lock_guard<std::mutex> lk(saves_mutex_);
			if (selected_save_index_ >= 0 && selected_save_index_ < (int)saves_cache_.size()) {
				const SaveInfo &si = saves_cache_[selected_save_index_];
				ImGui::Text("Name: %s", si.name.c_str());
				ImGui::Text("Created: %s", si.created_at.c_str());
				ImGui::Text("Last opened: %s", si.last_opened.c_str());
				ImGui::Dummy(ImVec2(0,6));
				ImGui::Text("Preview:");
				ImGui::Separator();

				// If preview_texture != 0, we can show it with ImGui::Image
				if (si.preview_texture != 0) {
					// ImGui expects void* texture ID for OpenGL: cast via intptr_t
					ImGui::Image((ImTextureID)(uintptr_t)si.preview_texture, ImVec2(256,144));
				} else {
					ImGui::TextDisabled("[No preview texture]");
					ImGui::Dummy(ImVec2(256, 144));
				}

				ImGui::Dummy(ImVec2(0,4));
				if (ImGui::Button("Load", ImVec2(120,0))) {
					if (presenter_) {
						presenter_->LoadSave(si.id); // synchronous; if heavy, presenter's LoadSave should spawn thread
						ImGui::CloseCurrentPopup();
						show_load_modal_ = false;
						requested_loads_refresh = false; // reset for next open
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Delete", ImVec2(120,0))) {
					// open confirm delete
					confirm_delete_open_ = true;
					delete_target_id_ = si.id;
					delete_target_name_ = si.name;
				}
			} else {
				ImGui::Text("No save selected");
			}
		}
		ImGui::Columns(1);

		ImGui::Separator();
		if (ImGui::Button("Close", ImVec2(120,0))) {
			ImGui::CloseCurrentPopup();
			show_load_modal_ = false;
			requested_loads_refresh = false;
		}

		// Delete confirmation modal (nested)
		if (confirm_delete_open_) {
			ImGui::OpenPopup("Confirm Delete");
			confirm_delete_open_ = false;
		}
		if (ImGui::BeginPopupModal("Confirm Delete", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Text("Delete save '%s' ?", delete_target_name_.c_str());
			ImGui::Separator();
			if (ImGui::Button("Yes", ImVec2(120,0))) {
				if (presenter_) {
					// Danger: DeleteSave may do file IO. Use async in presenter or call here async.
					// Example safe async pattern (comment):
					//
					// std::async(std::launch::async, [this,id=delete_target_id_](){
					//     presenter_->DeleteSave(id);
					//     // After deletion completes, refresh saves_cache_ on UI thread:
					//     // Either signal a flag and refresh next frame, or use thread-safe queue to push event.
					// });
					//
					presenter_->DeleteSave(delete_target_id_);
					// Refresh cache synchronously (ok for mock); in real app request async refresh
					if (presenter_) {
						std::lock_guard<std::mutex> lk(saves_mutex_);
						saves_cache_ = presenter_->ListSaves();
						selected_save_index_ = saves_cache_.empty() ? -1 : 0;
					}
				}
				ImGui::CloseCurrentPopup(); // close confirm delete
			}
			ImGui::SameLine();
			if (ImGui::Button("No", ImVec2(120,0))) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::EndPopup();
	}
}

// --------------------------- Settings modal ---------------------------
void GameWindowUI::DrawSettingsModal()
{
	if (!show_settings_modal_) return;

	ImGui::SetNextWindowSize(ImVec2(520, 300), ImGuiCond_Appearing);
	if (ImGui::BeginPopupModal("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("Game Settings");
		ImGui::Separator();

		// Load current settings from presenter only once when modal opens:
		static bool loaded_from_presenter = false;
		if (!loaded_from_presenter) {
			// If presenter had method to GetSettings(), we'd call it. For now assume caller injected settings.
			loaded_from_presenter = true;
		}

		ImGui::SliderFloat("Master Volume", &settings_ui_.master_volume, 0.0f, 1.0f);
		ImGui::Combo("Graphics Quality", &settings_ui_.graphics_quality, "Low\0Medium\0High\0Ultra\0");
		ImGui::Checkbox("Fullscreen", &settings_ui_.fullscreen);

		ImGui::Dummy(ImVec2(0,8));
		if (ImGui::Button("Save", ImVec2(120, 0))) {
			if (presenter_) {
				presenter_->SaveSettings(settings_ui_); // synchronous; presenter may save to disk async internally
			} else {
				error_message_ = "Presenter not set";
				show_error_modal_ = true;
			}
			ImGui::CloseCurrentPopup();
			show_settings_modal_ = false;
			loaded_from_presenter = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) {
			ImGui::CloseCurrentPopup();
			show_settings_modal_ = false;
			loaded_from_presenter = false;
		}
		ImGui::EndPopup();
	}
}

// --------------------------- Quit confirm modal ---------------------------
void GameWindowUI::DrawQuitConfirmModal()
{
	if (!show_quit_modal_) return;

	ImGui::SetNextWindowSize(ImVec2(360, 140), ImGuiCond_Appearing);
	if (ImGui::BeginPopupModal("Quit?", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("Are you sure you want to quit?");
		ImGui::Separator();
		if (ImGui::Button("Yes", ImVec2(120, 0))) {
			// Safe termination should be done through presenter
			if (presenter_) {
				presenter_->Quit(); // Presenter is responsible to request app close on main loop
			} else {
				// Fallback: call platform close (not recommended)
				// glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
			}
			ImGui::CloseCurrentPopup();
			show_quit_modal_ = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("No", ImVec2(120, 0))) {
			ImGui::CloseCurrentPopup();
			show_quit_modal_ = false;
		}
		ImGui::EndPopup();
	}
}

// --------------------------- Error modal ---------------------------
void GameWindowUI::DrawErrorModalIfNeeded()
{
	if (!show_error_modal_) return;
	ImGui::SetNextWindowSize(ImVec2(480, 140), ImGuiCond_Appearing);
	if (ImGui::BeginPopupModal("Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::TextWrapped("%s", error_message_.c_str());
		ImGui::Separator();
		if (ImGui::Button("OK", ImVec2(120, 0))) {
			ImGui::CloseCurrentPopup();
			show_error_modal_ = false;
			error_message_.clear();
		}
		ImGui::EndPopup();
	} else {
		// open modal the first time
		ImGui::OpenPopup("Error");
	}
}
