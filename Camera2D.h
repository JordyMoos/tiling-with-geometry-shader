#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D
{
private:
	int screenWidth;
	int screenHeight;
	glm::vec2 position;
	glm::mat4 cameraMatrix;
	glm::mat4 orthoMatrix;
	float scale;
	bool changed;


public:
	Camera2D();
	~Camera2D();

	void Init(int newScreenWidth, int newScreenHeight);
	void Update();

	glm::vec2 ConvertScreenToWorld(glm::vec2 screenCoords);

	void SetPosition(const glm::vec2& newPosition)
	{
		position = newPosition;
		changed = true;
	}

	void SetScale(float newScale)
	{
		scale = newScale;
		changed = true;
	}

	glm::vec2 GetPosition() const
	{
		return position;
	}

	float GetScale() const
	{
		return scale;
	}

	glm::mat4 GetCameraMatrix()
	{
		return cameraMatrix;
	}
};
