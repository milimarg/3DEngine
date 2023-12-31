#include <SFML/Graphics.hpp>
#include "../../includes/math/vector.hpp"
#include "../../includes/core/engineCore.hpp"

static sf::Color getColor(float lum)
{
    int pixelBw = (int)(13.0f * lum);

    static const int oldMin = 1;
    static const int oldMax = 12;
    static const int newMin = 0;
    static const int newMax = 255;
    const int newValue = (((pixelBw - oldMin) * (newMax - newMin)) / (oldMax - oldMin)) + newMin;
    if (pixelBw >= oldMin && pixelBw <= oldMax) {
        return (sf::Color(newValue, newValue, newValue, newValue));
    }
    return (sf::Color::Black);
}

void Engine3D::applyLightOnTriangle(vector3 &normal, triangle &tri)
{
    static vector3 lightDirection = vector3(0.0f, 0.0f, -1.0f).normal();
    float dp = std::max(0.1f, normal.dotProduct(lightDirection));

    Math::applyMatrixOnTriangle(tri, projectionMatrix);
    tri.color = getColor(dp);
    for (int i = 0; i < TRIANGLE_POINTS; i++) {
        tri.points[i] /= tri.points[i].w;
    }
    Math::scaleTriangleToWindowSize(tri, windowSize);
}
