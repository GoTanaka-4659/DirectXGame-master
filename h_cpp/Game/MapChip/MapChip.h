#pragma once

enum CHIPTYPE {
	NONE,
	BLOCK
};

class MapChip
{
public:
	MapChip() {
		chipType = NONE;
	};

	~MapChip() {};

	CHIPTYPE chipType;
};

