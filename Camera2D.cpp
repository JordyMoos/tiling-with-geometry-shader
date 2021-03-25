#include "Camera2D.h"

Camera2D::Camera2D() :
	position(0.0f, 0.0f), cameraMatrix(1.0f), orthoMatrix(1.0f)
	, scale(1.0f), changed(true)
	, screenWidth(500), screenHeight(500)
{

}

Camera2D::~Camera2D()
{
}

void Camera2D::Init(int newScreenWidth, int newScreenHeight)
{
	screenWidth = newScreenWidth;
	screenHeight = newScreenHeight;
	orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
}

void Camera2D::Update()
{
	if (!changed)
	{
		return;
	}

	glm::vec3 translate(-position.x + screenWidth / 2, -position.y + screenHeight / 2, 0.0f);
	cameraMatrix = glm::translate(orthoMatrix, translate);

	glm::vec3 scale(scale, scale, 0.0f);
	cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * cameraMatrix;

	changed = false;
}

glm::vec2 Camera2D::ConvertScreenToWorld(glm::vec2 screenCoords)
{
	screenCoords -= glm::vec2(screenWidth / 2, screenHeight / 2);
	screenCoords /= scale;
	screenCoords += position;

	return screenCoords;
}