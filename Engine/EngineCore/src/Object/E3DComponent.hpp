﻿
//********************************** Effect 3D Engine **************************************************//
//******************* Copyright (c) 2017-2-8  PanQingyun. All rights reserved. *************************//

#ifndef E3DComponent_hpp
#define E3DComponent_hpp

#include "../Source/Interface.h"
#include "../Mono/MonoScriptManager.h"
#include "../Object/E3DObject.h"

namespace E3DEngine
{
    class GameObject;
	class CTransform;
	// 组件类， 目的是方便拓展， 可以挂在Object上
    class Component : public Object
    {
    public:
		Component()
		{
			gameObject = nullptr;
			Transform = nullptr;
			NotStart = true;
		}

		virtual void OnCreate() 
		{
		}

		virtual void OnCreateComplete()
		{

		}

		virtual void Awake()
		{
			if (m_pBehaviour != nullptr)
			{
				m_pBehaviour->Awake();
			}
		}
        virtual void Start()
		{
			if (m_pBehaviour != nullptr)
			{
				m_pBehaviour->Start();
			}
        }
        virtual void Update(float deltaTime)
		{
			if (m_pBehaviour != nullptr)
			{
				m_pBehaviour->Update(deltaTime);
			}
        }
		virtual void LateUpdate(float deltaTime)
		{
			if (m_pBehaviour != nullptr)
			{
				m_pBehaviour->LateUpdate(deltaTime);
			}
		}
        virtual void Destory()
        {
			if (m_pBehaviour != nullptr)
			{
				m_pBehaviour->Destory();
			}
        }
		virtual void OnEnable()
		{
			if (m_pBehaviour != nullptr)
			{
				m_pBehaviour->OnEnable();
			}
		}
		virtual void OnDisable()
		{
			if (m_pBehaviour != nullptr)
			{
				m_pBehaviour->OnDisable();
			}
		}
		virtual void OnCollisionEnter(GameObject* go);
		virtual void SetGameObject(GameObject *go);
		GameObject * GetGameObject()
		{
			return gameObject;
		}

		virtual void SetPropertyValue(const char* name, void* value);
    public:
        GameObject *	gameObject;
		std::string 	_Tag;
		CTransform *    Transform;
		bool			NotStart;
    };
}

#endif /* CComponent_hpp */
