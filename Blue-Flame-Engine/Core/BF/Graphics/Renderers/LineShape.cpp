#include "LineShape.h"

namespace BF
{
	namespace Graphics
	{
		namespace Renderers
		{
			using namespace BF::Math;

			LineShape::LineShape() :
				thickness(0)
			{
			}

			LineShape::LineShape(const Vector2& startPoint, const Vector2& endPoint, float thickness, unsigned int zLayer, const Color& color) :
				Renderable(startPoint, Math::Rectangle(), zLayer, color, Type::Line), startPoint(startPoint), endPoint(endPoint), thickness(thickness)
			{
			}

			LineShape::~LineShape()
			{
			}
		}
	}
}