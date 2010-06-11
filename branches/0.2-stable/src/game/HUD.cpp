#include "HUD.h"

HUD::HUD(VideoManager* videoManager, Resources* resources) {
	m_videoManager = videoManager;
	m_resources = resources;
	VideoMode videoMode = m_videoManager->getVideoMode();
	m_bounce = 0;
	reset();
}

void HUD::applyEffects(float health, int levelPoints) {
	m_bounce += m_videoManager->getFrameDeltaTime();
	float bounceState = (float) -cos(m_bounce / 800.0);
	float factor = bounceState < 0 ? bounceState * -1 : bounceState;

	float baseScale = m_videoManager->Scale * 0.15;

	if (health < 0.33) {
		m_resources->HealthIndicator->setMask(1.0, factor, 1.0, 1.0);
		m_resources->HealthIndicator->Scale = baseScale * (factor + 0.5);
	} else {
		m_resources->HealthIndicator->setMask(1.0, 1.0, 1.0, 1.0);
		m_resources->HealthIndicator->Scale = baseScale;
	}

	if (levelPoints > 0) {
		m_resources->LevelUpIndicator->setMask(1.0, factor, 1.0, 1.0);
		m_resources->LevelUpIndicator->Scale = baseScale * (factor + 0.5);
	} else {
		m_resources->LevelUpIndicator->setMask(1.0, 1.0, 1.0, 1.0);
		m_resources->LevelUpIndicator->Scale = baseScale;
	}
}

void HUD::drawMessages() {
	if (!m_messages.empty()) {
		int m_bottomBasePoint = m_videoManager->getVideoMode().Height
				- m_videoManager->RegularText->getIndent();

		int s = m_messages.size();
		for (int i = s - 1; i >= 0; i--) {
			m_messages[i]->draw(true, m_messages[i]->X
					+ m_videoManager->SmallText->getIndent(), m_bottomBasePoint
					- m_videoManager->RegularText->getHeight() - s
					* m_videoManager->SmallText->getHeight() + i
					* m_videoManager->SmallText->getHeight());
			m_messages[i]->AMask -= 0.0001f
					* m_videoManager->getFrameDeltaTime();

			if (m_messages[i]->AMask <= 0) {
				delete m_messages[i];
				m_messages.erase(m_messages.begin() + i);
			}
		}
	}
}

void HUD::drawExperience(float experience, int levelPoints) {
	int m_bottomBasePoint = m_videoManager->getVideoMode().Height
			- m_videoManager->RegularText->getIndent();

	VideoMode screen = m_videoManager->getVideoMode();
	const int barLen = screen.Width / 4;
	const int barLeft = 2 * screen.Width / 3;
	const int barHeight = m_videoManager->RegularText->getHeight() / 4;

	const int indX = screen.Width - screen.Width / 24;
	m_resources->LevelUpIndicator->X = indX;
	m_resources->LevelUpIndicator->Y = m_bottomBasePoint;

	m_resources->LevelUpIndicator->draw(false, false);

	GLfloat bcolor[] = { 1.0f, 1.0f, 1.0f, 0.3f };
	GLfloat fcolor1[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat fcolor2[] = { 0.0f, 1.0f, 1.0f, 1.0f };

	drawBar(barLeft, m_bottomBasePoint, barLen, barHeight, experience, bcolor,
			fcolor1, fcolor2);
}

void HUD::drawBar(int x, int y, int width, int height, float value,
		GLfloat* bcolor, GLfloat* fcolor1, GLfloat* fcolor2) {
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();

	glTranslatef(x, y, 0.0f);

	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glColor4fv(bcolor);

	glVertex3f(0.0f, -height, 0);
	glVertex3f(width, -height, 0);
	glVertex3f(width, height, 0);
	glVertex3f(0.0f, height, 0);

	glColor4fv(fcolor1);
	glVertex3f(0.0f, -height, 0);
	glColor4fv(fcolor2);
	glVertex3f(width * value, -height, 0);
	glVertex3f(width * value, height, 0);
	glColor4fv(fcolor1);
	glVertex3f(0.0f, height, 0);

	glEnd();

	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}

void HUD::drawHealth(float health) {
	int m_bottomBasePoint = m_videoManager->getVideoMode().Height
			- m_videoManager->RegularText->getIndent();

	VideoMode screen = m_videoManager->getVideoMode();
	const int barLeft = screen.Width / 12;
	const int barLen = screen.Width / 4;
	const int barHeight = m_videoManager->RegularText->getHeight() / 4;

	const int indX = screen.Width / 24;
	m_resources->HealthIndicator->X = indX;
	m_resources->HealthIndicator->Y = m_bottomBasePoint;

	m_resources->HealthIndicator->draw(false, false);

	GLfloat bcolor[] = { 1.0f, 1.0f, 1.0f, 0.3f };
	GLfloat fcolor1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat fcolor2[] = { 1.0f, 1.0f, 0.0f, 1.0f };

	drawBar(barLeft, m_bottomBasePoint, barLen, barHeight, health, bcolor,
			fcolor1, fcolor2);
}

void HUD::drawTime(GameState* gameState) {
	int m_bottomBasePoint = m_videoManager->getVideoMode().Height
			- m_videoManager->RegularText->getIndent();

	const int minutes = gameState->Time / 60000;
	const int seconds = (gameState->Time - minutes * 60000) / 1000;

	char *buf;
	sprintf(buf = new char[20], "%02d:%02d", minutes, seconds);
	m_videoManager->RegularText->draw(buf, m_videoManager->getVideoMode().Width
			/ 2, m_bottomBasePoint, TextManager::CENTER, TextManager::MIDDLE);
	delete[] buf;
}

void HUD::draw(GameState* gameState, float health, float experience,
		int totalExperience, int levelPoints, int ammo, int grenades) {
	VideoMode screen = m_videoManager->getVideoMode();

	drawMessages();
	drawTime(gameState);

	applyEffects(health, levelPoints);

	drawHealth(health);
	drawExperience(experience, levelPoints);

	if (gameState->Lost && !gameState->Paused) {
		int y = screen.Height / 4;
		m_videoManager->RegularText->draw("They have overcome...", screen.Width
				/ 2, y, TextManager::CENTER, TextManager::MIDDLE);
		char* buf;
		sprintf(buf = new char[30], "You have earned %i points.",
				totalExperience);
		m_videoManager->RegularText->draw(buf, screen.Width / 2, y
				+ m_videoManager->RegularText->getHeight(),
				TextManager::CENTER, TextManager::MIDDLE);
		delete[] buf;
	}

	if (gameState->Paused)
		m_videoManager->RegularText->draw("PAUSE", screen.Width / 2,
				screen.Height / 2, TextManager::CENTER, TextManager::MIDDLE);
}

void HUD::addMessage(std::string message) {
	m_messages.push_back(m_videoManager->SmallText->getObject(message.c_str(),
			0, 0, TextManager::LEFT, TextManager::MIDDLE));
}

void HUD::reset() {
	clearVector<TextObject*> (&m_messages);
}

HUD::~HUD() {
	reset();
}