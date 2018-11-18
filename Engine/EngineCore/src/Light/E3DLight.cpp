﻿//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-3-21 PanQingyun. All rights reserved. *************************//
#include "E3DLight.hpp"
#include "../Scene/E3DSceneManager.hpp"
#include "../Source/E3DDebug.h"
#include "../Object/E3DTransform.hpp"
#include "../Camera/E3DCamera.h"
#include "../RenderSystem/E3DRenderSystem.hpp"
#include "../Source/Application.h"

namespace E3DEngine
{
	PointLight::PointLight()
	{
		Range = 0;
		Type = ePOINT_LIGHT;
		CREATE_BEHAVIOUR(PointLight);
		TRANSFER_FIELD_VALUE(Range);
		Light::setBehaviourDefaultValue();
	}

	void PointLight::MakeShadow()
	{
		// TODO 点光源创建透视投影摄像机

	}

	DirectionLight::DirectionLight()
	{
		Type = eDIRECTION_LIGHT;
		CREATE_BEHAVIOUR(DirectionLight);
	}

	void DirectionLight::MakeShadow()
	{
		CreateShadow = true; 
		// 平行光 创建正交投影摄像机
		vec3f trans = vec3f(165, 30, 170);
		shadowCamera = new E3DEngine::Camera(Transform->Position + trans, trans, vec3f(0, 1, 0), -110, 110, -110, 110, 1, 1000);
		shadowCamera->CreateBehaviour();
		TextureData tData;
		tData.width = 4096;
		tData.height = 4096;
		tData.target = RENDER_DEPTH;
		Render2Texture *rtt = GetRenderSystem()->GetTextureDataManager()->CreateRender2TextureSingleThread(&tData);
		shadowCamera->SetLayerMask(-1 & ~LD_SKYBOX & ~LD_OBJECT_COORD & ~LD_COORD & ~LD_NOSHADOW);
		shadowCamera->SetRenderTexture(rtt);
		shadowCamera->SetClearType(eCT_Depth);
		shadowCamera->SetClearColor(Color4(1, 1, 1, 1));
		shadowCamera->SetActive(true);
		shadowCamera->SetIsShadowCamera();
		shadowCamera->mName = "ShadowCamera";
		shadowCamera->Flag |= (DONT_SAVE | HIDE_IN_PROPERTY);
		ADD_IN_SCENE(shadowCamera);
	}

	void DirectionLight::OnCreateComplete()
	{
		Light::OnCreateComplete();
		SetDirection(mGameObject->Transform->Position);
		SceneManager::GetCurrentScene()->AddLight(this);
	}

	void DirectionLight::SetDirection(vec3f dir)
	{
		mDirection = dir;
	}

	vvision::vec3f &DirectionLight::GetDirection()
	{
		return mDirection;
	}

	SpotLight::SpotLight()
	{
		Type = ePOINT_LIGHT;
		CREATE_BEHAVIOUR(SpotLight);
		TRANSFER_FIELD_VALUE(Range);
		TRANSFER_FIELD_VALUE(SpotAngle);
		Light::setBehaviourDefaultValue();
	}

	void SpotLight::MakeShadow()
	{
		// 追光 透视投影摄像机
	}

	void Light::setBehaviourDefaultValue()
	{
		/*MonoObject * color = Convert::ToCSVector4(vec4f(Color.r, Color.g,Color.b,Color.a));
		mBehaviour->SetFieldValue("Color", color);
		TRANSFER_FIELD_VALUE(Intensity);*/
		//GameObject::setBehaviourDefaultValue();
	}

	void Light::OnCreateComplete()
	{
		SceneManager::GetCurrentScene()->AddLight(this);
	}

	E3DEngine::Camera * Light::GetShadowCamera()
	{
		return shadowCamera;
	}

	void Light::SetCreateShadow(void *cp, object value)
	{
		Light *light = static_cast<Light*>(cp);
		if (light == nullptr)
		{
			return;
		}

		light->CreateShadow = object_cast<bool>(value);
		if (light->CreateShadow)
		{
			light->MakeShadow();
		}
	}

	object Light::GetCreateShadow(void *cp)
	{
		Light *light = static_cast<Light*>(cp);
		if (light == nullptr)
		{
			return false;
		}

		return light->CreateShadow;
	}

}
