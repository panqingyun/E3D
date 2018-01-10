﻿//
//  E3DRenderObject.hpp
//  Created by 潘庆云 on 2017/1/17.
//

#ifndef Object_hpp
#define Object_hpp

#include "E3DComponent.hpp"
#include "../RenderSystem/Material/E3DMaterial.hpp"
#include "../Source/E3DVertex.h"

namespace E3DEngine
{
	typedef enum
	{
		eRI_LowMost,
		eRI_Normal,
		eRI_Transparent,
		eRI_TopMost,
		eRI_None,
	} eRenderIndex;


	class MinMaxAABB extends Object
	{
	private:
		vec3f    m_Min;
		vec3f    m_Max;

	public:
		MinMaxAABB() 
		{
			Init(); 
		}
		MinMaxAABB(const vec3f& _min, const vec3f& _max) : m_Min(_min), m_Max(_max) {}

		void Init();

		vec3f CalculateCenter() const { return (m_Max + m_Min) * 0.5f; }
		vec3f CalculateExtent() const { return (m_Max - m_Min) * 0.5f; }
		vec3f CalculateSize() const { return (m_Max - m_Min); }

		void Expand(float inValue);
		void Expand(const vec3f& inOffset);

		void Encapsulate(const vec3f& inPoint);
		void Encapsulate(const MinMaxAABB& other);

		bool IsInside(const vec3f& inPoint) const;
		void CalculateVertices(vec3f outVertices[8]) const;
		bool IsValid() const;

		const vec3f& GetMin() const { return m_Min; }
		const vec3f& GetMax() const { return m_Max; }
	};

	inline void MinMaxAABB::Expand(float inValue)
	{
		vec3f offset = vec3f(inValue, inValue, inValue);
		m_Min -= offset;
		m_Max += offset;
	}

	inline void MinMaxAABB::Expand(const vec3f& inOffset)
	{
		m_Min -= inOffset;
		m_Max += inOffset;
	}

	inline void MinMaxAABB::Encapsulate(const MinMaxAABB& other)
	{
		m_Min = min(m_Min, other.m_Min);
		m_Max = max(m_Max, other.m_Max);
	}

	inline void MinMaxAABB::Encapsulate(const vec3f& inPoint)
	{
		m_Min = min(m_Min, inPoint);
		m_Max = max(m_Max, inPoint);
	}


    class CTransform;
    class RenderObject extends Object
    {
    public:
        RenderObject();
		virtual ~RenderObject() override;
	public:
		int		nMaterialID;
		
	protected:
		virtual void prepareRender(float deltaTime);
		virtual void afterRender(float deltaTime);

	public:
		virtual void PrepareUpdate()
		{
		}
		virtual void AfterUpdate()
		{
		}
		virtual void Render(float deltaTime);
		virtual void Destory(RenderObject *obj);
        virtual void SetMaterialID(int ID);
		virtual void SetMaterial(Material *material);
		virtual void TransformChange() { }
		virtual void SetCamera(Camera * camera);

		virtual void SetDrawModule(DWORD module);
        void SetColor(long color);
        void SetIsBillborad(bool isBillboard);
        bool GetIsBillBoard();
		virtual void ClearVertexIndexBuffer() { }
		CTransform * GetTransform();
		void SetTransform(CTransform *_transform);
		MinMaxAABB GetBounds()
		{
			return m_AABB;
		}
    protected:
        long	m_nColor;
        bool	m_bIsBillboard;
		DWORD   m_nDrawModule;
		bool	m_bIsBufferData;
		std::vector<float*> vertexDatas;
		CTransform * transform;
		MinMaxAABB   m_AABB;
    public:
		// 材质
        Material	* pMaterial;
		// 索引数目
		DWORD		  m_nIndexSize;
		// 顶点数组
		std::vector<Vertex>		Vertices;
		// 索引数组
		std::vector<unsigned short>		Indices;
		// 渲染层级
		eRenderIndex			RenderIndex;
		// 开启深度测试
		bool					EnableDepthTest;
		// true 1次送入显卡后不再更改， false 每帧都向显卡发送数据
		bool					IsStaticDraw;
		Camera *				pCamera;
    };

}
    #endif /* Object_hpp */