#pragma once
#include "view/GameWindow.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <sstream>

// Simple in-memory presenter for local debugging.
// Implements IGamePresenter; simulates saves and simple operations.
class MockPresenter : public IGamePresenter {
public:
	MockPresenter();
	~MockPresenter() override = default;

	std::vector<SaveInfo> ListSaves() override;
	void LoadSave(const std::string& id) override;
	void DeleteSave(const std::string& id) override;
	bool CreateGame(const NewGameParams& params) override;
	void SaveSettings(const Settings& s) override;
	void Quit() override;

	// helper: generate timestamp
	static std::string NowIso();

private:
	std::vector<SaveInfo> saves_;
	Settings current_settings_;
};
