#include <stdlib.h>
#include <iostream>
#include <vector>
#include "SDL_opengl.h"
#include "SDL_mixer.h"
#include "../system/Texture.h"
#include "../system/ImageUtility.h"
#include "../system/Sound.h"
#include "StandardBullet.h"
#include "LaserBullet.h"

#ifndef WEAPON_H_
#define WEAPON_H_

class Weapon {
private:
	int m_fireDelay;
	int m_reload;
	Texture *m_droppedTex;
	Texture *m_bulletTex;
	Sound* m_shotSound;
	Sound* m_reloadSound;
	int m_reloadSndCh;
public:
	Weapon(BulletType Type, std::string droppedImage, Sound* shotSound,
			Sound* reloadSound);
	void setBulletImage(std::string image);
	void process(int deltaTime);
	std::vector<Bullet*> *fire(float x, float y);
	bool reload(float timeMod);
	void pickup();
	float getReloadState();
	void deleteResources();
	Texture *getDroppedTex();
	~Weapon();
	BulletType Type;
	std::string Name;
	int FireDelayTime;
	int ReloadTime;
	int AmmoClipSize;
	int Ammo;
	float Damage;
	float BulletSpeed;
	float FireRange;
	float ReturnForce;
	int BulletsAtOnce;

	bool Poisoned;
};

#endif /* WEAPON_H_ */
