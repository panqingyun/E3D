﻿//
//  E3DCubeMapTexture.cpp
//
//  Created by 潘庆云 on 2017/5/9.
//

#include "E3DGLCubeMapTexture.hpp"
#include <src/Source/E3DDebug.h>

namespace E3DEngine
{		

	GL_CubeMapTexture::~GL_CubeMapTexture()
	{
		glDeleteTextures(1, &m_nTextureBuffer);
	}

	void GL_CubeMapTexture::createCubeMap(Texture2dData *up, Texture2dData *down, Texture2dData *left, Texture2dData *right, Texture2dData *front, Texture2dData *back)
	{
		glGenTextures(1, &m_nTextureBuffer);
		{
			// Allocate and bind an OpenGL texture
			glEnable(GL_TEXTURE_CUBE_MAP);
			//glActiveTexture(textureEnum);
			changeRgbModule(up); changeRgbModule(down); changeRgbModule(left);
			changeRgbModule(right); changeRgbModule(front); changeRgbModule(back);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_nTextureBuffer);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, right->rgbModule, right->width, right->height, 0, right->rgbModule, GL_UNSIGNED_BYTE, right->imgData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, left->rgbModule, left->width, left->height, 0, left->rgbModule, GL_UNSIGNED_BYTE, left->imgData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, up->rgbModule,  up->width, up->height, 0, up->rgbModule, GL_UNSIGNED_BYTE, up->imgData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, down->rgbModule, down->width, down->height, 0, down->rgbModule, GL_UNSIGNED_BYTE, down->imgData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, back->rgbModule, back->width, back->height, 0, back->rgbModule, GL_UNSIGNED_BYTE, back->imgData);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, front->rgbModule, front->width, front->height, 0, front->rgbModule, GL_UNSIGNED_BYTE, front->imgData);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
			glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			glGenerateMipmap(GL_LINEAR_MIPMAP_LINEAR);//GL_LINEAR_MIPMAP_LINEAR
		}
	}


	void GL_CubeMapTexture::changeRgbModule(TextureData *data)
	{
		DWORD  rgbModule = 0;
		if (data->rgbModule == PixelFormat::R8G8B8)
		{
			rgbModule = GL_RGB;
		}
		else if (data->rgbModule == PixelFormat::R8G8B8A8)
		{
			rgbModule = GL_RGBA;
		}
		else
		{
			// TODO
		}
		data->rgbModule = rgbModule;
	}

}
