#pragma once
#include <string>
#include <vector>
#include <functional>
#include <mutex>
#include <optional>
#include <cstdint>
#include <GL/gl.h> // GLuint
#include "imgui.h"

// --- Data structures required by UI / Presenter API ---
struct SaveInfo {
	std::string id;
	std::string name;
	std::string created_at;
	std::string last_opened;
	GLuint preview_texture = 0; // OpenGL texture id (0 == none)
};

struct NewGameParams {
	std::string name;
	int difficulty = 1; // 0..N
	int map_size = 64;  // example
	// add other params as needed
};

struct Settings {
	float master_volume = 1.0f;
	int graphics_quality = 2; // 0..3
	bool fullscreen = true;
	// add other settings fields
};

// --- Presenter interface that UI will call (implement in game logic) ---
class IGamePresenter {
public:
	virtual ~IGamePresenter() = default;

	// NOTE: these functions might block (IO). Prefer async wrapper in Presenter.
	virtual std::vector<SaveInfo> ListSaves() = 0;
	virtual void LoadSave(const std::string& id) = 0;
	virtual void DeleteSave(const std::string& id) = 0;
	virtual bool CreateGame(const NewGameParams& params) = 0;
	virtual void SaveSettings(const Settings& s) = 0;
	virtual void Quit() = 0;
};

// --- GameWindowUI: ImGui-only view. Presenter injected via pointer. ---
class GameWindowUI {
public:
	explicit GameWindowUI();
	~GameWindowUI();

	// Render the entire main menu (call each frame from your UI loop)
	void Render();

	// Attach presenter (can be changed at runtime). Presenter must outlive UI.
	void SetPresenter(IGamePresenter* presenter) { presenter_ = presenter; }

	// Convenience API to open/close particular modal windows
	void CloseAllModals();

	// State setters/getters (optional)
	void SetFullscreenByDefault(bool fs) { fullscreen_by_default_ = fs; }

private:
	// Модальные окна
	enum class ModalType {
		None,
		NewGame,
		LoadGame,
		Settings,
		QuitConfirm
	};

	// Используется для хранение запроса
	ModalType pedding_modal_ = ModalType::None;

	void RequestModal(ModalType type); // Создания запроса на вызов модального окна
	void ProcessPeddingModals(); // Вызов модальных окан


	// Функции отрисовки
	void DrawMainMenuBar();
	void DrawPlayPanel();
	void DrawSavesLoadModal();
	void DrawNewGameModal();
	void DrawSettingsModal();
	void DrawQuitConfirmModal();
	void DrawErrorModalIfNeeded();

	// Указатель на показ (UI)
	IGamePresenter* presenter_ = nullptr;

	// UI состояние:
	bool fullscreen_by_default_ = true;
	bool show_load_modal_ = false;
	bool show_newgame_modal_ = false;
	bool show_settings_modal_ = false;
	bool show_quit_modal_ = false;

	// Load modal state
	std::vector<SaveInfo> saves_cache_;
	int selected_save_index_ = -1;
	std::mutex saves_mutex_; // protect saves_cache_ when async-loaded

	// New game form state
	NewGameParams new_game_params_;
	char new_world_name_buf_[128];

	// Settings
	Settings settings_ui_; // editable copy

	// Error reporting
	bool show_error_modal_ = false;
	std::string error_message_;

	// Confirmation for deletion
	bool confirm_delete_open_ = false;
	std::string delete_target_id_;
	std::string delete_target_name_;

	// Flags for first-time layout setup
	bool first_frame_setup_ = true;
};