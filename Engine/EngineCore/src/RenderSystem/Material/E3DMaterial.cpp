﻿//
//  Material.cpp
//
//  Created by 潘庆云 on 2017/3/30.
//

#include "../Material/E3DMaterial.hpp"
#include "src/Source/EngineDelegate.h"

namespace E3DEngine
{
	Material::Material()
	{
		Color = 0xffffffff;
		Textures.clear();
		m_pBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
		NEW_INSTANCE(Material);
		Object::setBehaviourDefaultValue();
	}
	
	void Material::Destory()
	{
		for (std::map<UINT, Texture*>::iterator it = Textures.begin(); it != Textures.end(); ++it)
		{
			SAFE_DELETE(it->second);
		}
		Textures.clear();
	}

	void Material::CreateMaterial(MaterialConfig * config, ShaderConfig * sCfg)
	{
		pMaterialConfig = config;
		if (pMaterialConfig != nullptr)
		{
			if (sCfg == nullptr)
			{
				return;
			}
			Color = Convert::_16To10(pMaterialConfig->Color);
			CreateShader(sCfg);
			
			for (auto& sp : pShader->GetSamplerNameValue())
			{
				createTexture(sp.second, sp.first);
			}
		}
	}

	void Material::SetTexture(Texture * texture, int index)
	{
		
	}

	void Material::createTexture(std::string textureName, std::string textureUniform)
	{
		
	}

	void Material::createTexture(Texture *texture, std::string textureUniform)
	{
		
	}

	void Material::BindTexture()
	{
		for (auto & it : Textures)
		{
			if (it.second == nullptr)
			{
				continue;
			}
			it.second->ActiveBindTexture();
		}
	}

	void Material::CreateCubeTexture(std::string dirPath, std::string xPName, std::string xNName, std::string yPName, std::string yNName, std::string zPName, std::string ZNName)
	{

	}


	MonoBehaviour * Material::GetBehaviour()
	{
		return m_pBehaviour;
	}

	void Material::UseMaterial()
	{
		
	}
    
	void Material::InvalidMaterial()
	{
		
	}

    void Material::beforeUpdate()
    {
  
    }

	void Material::afterUpdate()
	{

	}

	void Material::parseShaderConfig(ShaderConfig *cfg)
	{

	}

    void Material::enableStencil()
    {
        
    }
    

}
