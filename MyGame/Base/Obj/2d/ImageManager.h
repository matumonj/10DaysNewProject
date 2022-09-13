#pragma once
#include <map>
#include <string>
#include "Sprite.h"
#include "Texture.h"
class ImageManager  final {
private:
	ImageManager() = default;
	~ImageManager() = default;
	ImageManager(const ImageManager & r) = default;
	ImageManager& operator= (const ImageManager & r) = default;

public:

	enum texName {
		Wave1,
		Wave2,
		Wave3,
		Wave4,
		Wave5,
		Num,
		BG,
		Doll,
		IconGirl,
		IconCat,
		IconInu,
		IconBack,
		Target,
		White,
		Result,
		Title,
		Black,
	};
	enum tex2dName {
		Sushi,
	};
public:
	static ImageManager* GetIns();		//�擾�p

	void Load2D();
	void LoadTex2D();
	void Finalize();
};

