#include "presenter/MockPresenter.h"   // <-- был "MockPresenter.h"
#include <iostream>

MockPresenter::MockPresenter()
{
	// Create a few fake saves
	for (int i = 0; i < 3; ++i) {
		SaveInfo s;
		s.id = "save_" + std::to_string(i+1);
		s.name = "Save slot " + std::to_string(i+1);
		s.created_at = NowIso();
		s.last_opened = NowIso();
		s.preview_texture = 0;
		saves_.push_back(s);
	}
	current_settings_.master_volume = 0.8f;
	current_settings_.graphics_quality = 2;
	current_settings_.fullscreen = true;
}

std::vector<SaveInfo> MockPresenter::ListSaves() { return saves_; }

void MockPresenter::LoadSave(const std::string& id)
{
	auto it = std::find_if(saves_.begin(), saves_.end(), [&](const SaveInfo& s){ return s.id == id; });
	if (it != saves_.end()) {
		it->last_opened = NowIso();
		std::cout << "[MockPresenter] Loaded save: " << it->name << "\n";
	} else {
		std::cout << "[MockPresenter] Save not found: " << id << "\n";
	}
}

void MockPresenter::DeleteSave(const std::string& id)
{
	auto it = std::remove_if(saves_.begin(), saves_.end(), [&](const SaveInfo& s){ return s.id == id; });
	if (it != saves_.end()) {
		std::cout << "[MockPresenter] Deleted save: " << id << "\n";
		saves_.erase(it, saves_.end());
	}
}

bool MockPresenter::CreateGame(const NewGameParams& params)
{
	if (params.name.empty()) return false;
	SaveInfo s;
	s.id = "save_new_" + std::to_string(saves_.size()+1);
	s.name = params.name + " (start)";
	s.created_at = NowIso();
	s.last_opened = NowIso();
	s.preview_texture = 0;
	saves_.insert(saves_.begin(), s);
	std::cout << "[MockPresenter] Created game '" << params.name << "' difficulty=" << params.difficulty << "\n";
	return true;
}

void MockPresenter::SaveSettings(const Settings& s)
{
	current_settings_ = s;
	std::cout << "[MockPresenter] Settings saved: volume=" << s.master_volume
			  << " quality=" << s.graphics_quality << " fs=" << s.fullscreen << "\n";
}

void MockPresenter::Quit()
{
	std::cout << "[MockPresenter] Quit requested\n";
	// В реальном презентере — выставить флаг закрытия окна в основном цикле.
}

std::string MockPresenter::NowIso()
{
	using namespace std::chrono;
	auto t = system_clock::now();
	auto tt = system_clock::to_time_t(t);
	std::tm tm;
#if defined(_WIN32)
	localtime_s(&tm, &tt);
#else
	localtime_r(&tt, &tm);
#endif
	std::ostringstream ss;
	ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
	return ss.str();
}
