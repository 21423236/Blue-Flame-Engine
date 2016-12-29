#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "BF/Graphics/TileMap.h"
#include "BF/Common.h"

namespace BF
{
	namespace IO
	{
		class BF_API BFMLoader
		{
			public:
				static Graphics::TileMapData* Load(const std::string& filename);
		};
	}
}