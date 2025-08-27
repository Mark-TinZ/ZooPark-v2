#pragma once

#include "view/View.h"
#include <string>
#include <vector>

class StoryWindow : public View {
public: 
	StoryWindow();
	void render() override;

	void setVisible(bool visible);
	bool isVisible() const;

	bool isFinished() const; // Закончился показ истории

private:
	bool visible;
	int currentPage;
	std::vector<std::string> texts;
	std::vector<std::string> images; // путь к картинке
	bool finished;
};