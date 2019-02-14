#define STB_IMAGE_IMPLEMENTATION
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <stb_image.h>

#include <stdio.h>
#include <map>
#include <string>

#include "gamemath.h"
#include "variables.h"
#include "logging.h"
#include "gametexture.h"

std::map<std::string, texture*> loaded_textures;

//loads and returns a texture. if the texture is already loaded, it does not re-load it.
texture* load_get_texture(std::string tex_name)
{
	if (loaded_textures.find(tex_name) != loaded_textures.end())
	{
		//texture has been found; return it
		return loaded_textures[tex_name];
	}
	else
	{
		//texture could not be found; load it
		if (!load_texture(tex_name))
			printf("Could not load texture %s.\n", tex_name.c_str());
		else printf("Texture %s loaded.\n", tex_name.c_str());
	}
}

bool load_texture(std::string tex_name)
{
	std::vector<Decl> texDecl = get_all_decl_of_type("texture", assets);

	for (int i = 0; i < texDecl.size(); i++)
	{
		Decl decl = texDecl[i];
		if (decl.name == tex_name)
		{
			if (decl.parameters.find("location") == decl.parameters.end())
			{			printf("Tried to load texture %s, but it had no location parameter!", decl.name.c_str());
				return false;
			}
			else
			{
				std::string location = decl.parameters["location"].value;

				std::string directory = "C:/Users/Taylor/Documents/Programming/C++/diorama/diorama/";
				
				int width, height, nrChannels;
				unsigned char *data = stbi_load((directory + location).c_str(), &width, &height, &nrChannels, 0);

				if (data == NULL)
				{
					printf("STBI could not load texture %s. Could not find the location?\n", decl.name.c_str());
					return false;
				}

				GLuint gl_pointer;
				glGenTextures(1, &gl_pointer);
				glBindTexture(GL_TEXTURE_2D, gl_pointer);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				texture *tex = new texture();
				tex->name = tex_name;
				tex->location = location;
				tex->gl_pointer = gl_pointer;
				tex->size = vec2(width, height);

				stbi_image_free(data);
				glBindTexture(GL_TEXTURE_2D, 0);

				loaded_textures.insert(std::pair<std::string, texture*>(tex_name, tex));
				return true;
			}
		}
	}

	return false;
}
