 #ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/scene.h>
#include <stb/stb_image.h>

class Texture
{
public:
	unsigned int ID;
	aiTextureType type;
	std::string directory, path;

	Texture(std::string directory, std::string path, aiTextureType type);
	void generate();
	void load(bool flip = true);
	void bind();
protected:

private:

};
#endif