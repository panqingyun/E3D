﻿
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-2-8  PanQingyun. All rights reserved. *************************//

#include "../Object/E3DComponent.hpp"
#include "../Object/E3DGameObject.h"

void E3DEngine::Component::OnCollisionEnter(GameObject* go)
{
	MonoObject * mObj = go->GetMonoBehaviour()->GetMonoObject();
	m_pBehaviour->CallMethod("OnCollisionEnter", (void**)&mObj);
}

void E3DEngine::Component::SetGameObject(GameObject *go)
{
	this->gameObject = go;
	if (m_pBehaviour != nullptr)
	{
		m_pBehaviour->SetPropertyValue("gameObject", gameObject->m_pBehaviour->GetMonoObject());
	}
}

void E3DEngine::Component::SetPropertyValue(const char* name, void* value)
{
	if (m_pBehaviour != nullptr)
	{
		m_pBehaviour->SetPropertyValue(name, value);
	}
}
