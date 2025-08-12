#include "DebugDraw.h"

DebugDraw::DebugDraw(sf::RenderWindow& window) : m_window(window) {}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    sf::ConvexShape polygon(vertexCount);
    for (int32 i = 0; i < vertexCount; ++i) {
        polygon.setPoint(i, sf::Vector2f(toPixels(vertices[i].x), toPixels(vertices[i].y)));
    }
    polygon.setFillColor(sf::Color::Transparent);
    polygon.setOutlineThickness(1.0f);
    polygon.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255));
    m_window.draw(polygon);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    sf::ConvexShape polygon(vertexCount);
    for (int32 i = 0; i < vertexCount; ++i) {
        polygon.setPoint(i, sf::Vector2f(toPixels(vertices[i].x), toPixels(vertices[i].y)));
    }
    polygon.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, 60));
    polygon.setOutlineThickness(1.0f);
    polygon.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255));
    m_window.draw(polygon);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
    sf::CircleShape circle(toPixels(radius));
    circle.setOrigin(toPixels(radius), toPixels(radius));
    circle.setPosition(toPixels(center.x), toPixels(center.y));
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(1.0f);
    circle.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255));
    m_window.draw(circle);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
    sf::CircleShape circle(toPixels(radius));
    circle.setOrigin(toPixels(radius), toPixels(radius));
    circle.setPosition(toPixels(center.x), toPixels(center.y));
    circle.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, 60));
    circle.setOutlineThickness(1.0f);
    circle.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255));
    m_window.draw(circle);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(toPixels(p1.x), toPixels(p1.y)), sf::Color(color.r * 255, color.g * 255, color.b * 255)),
        sf::Vertex(sf::Vector2f(toPixels(p2.x), toPixels(p2.y)), sf::Color(color.r * 255, color.g * 255, color.b * 255))
    };
    m_window.draw(line, 2, sf::Lines);
}

void DebugDraw::DrawTransform(const b2Transform& xf) {
    float lineLength = 0.4f;

    b2Vec2 p1 = xf.p, p2;

    // Red (x-axis)
    p2 = p1 + lineLength * xf.q.GetXAxis();
    DrawSegment(p1, p2, b2Color(1, 0, 0));

    // Green (y-axis)
    p2 = p1 + lineLength * xf.q.GetYAxis();
    DrawSegment(p1, p2, b2Color(0, 1, 0));
}

void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color){
    sf::CircleShape point(toPixels(size));
    point.setOrigin(toPixels(size), toPixels(size));
    point.setPosition(toPixels(p.x), toPixels(p.y));
    point.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255));
    m_window.draw(point);
}
