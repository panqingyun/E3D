#pragma once
#include <include/Include.h>

//////////////////////////////////////////////////////////////////////////
// Mono global function
//////////////////////////////////////////////////////////////////////////

//  [12/8/2017 panqingyun]
// https://www.cnblogs.com/murongxiaopifu/p/4557365.html

#define CS_STRING MonoString*
#define CS_OBJECT MonoObject*
#define CPP_OBJECT void*
#define CS_BOOL	MonoBoolean
#define CS_ARRAY MonoArray*

#define VOID void

#define CPP_OBJ_PTR_NAME "CppObject"

template<typename T> inline T * getCppObject(CS_OBJECT obj)
{
	if (obj == nullptr)
	{
		return nullptr;
	}
	MonoClass *klass = mono_object_get_class(obj);
	MonoClassField *  field = mono_class_get_field_from_name(klass, CPP_OBJ_PTR_NAME);

	if (field == nullptr)
	{
		return nullptr;
	}
	void * value = nullptr;
	mono_field_get_value(obj, field, &value);
	return static_cast<T*>(value);
}

void RegisterMonoFunction();

#define TRANSFER_PROPERTY(_property)\
	m_pBehaviour->SetPropertyValue(#_property, &_property);

#define TRANSFER_FIELD_VALUE(_field)\
	m_pBehaviour->SetFieldValue(#_field, &_field);

#define TRANSFER_FIELD_OBJECT(_field)\
	m_pBehaviour->SetFieldValue(#_field, _field->GetMonoBehaviour()->GetMonoObject());

#define NEW_INSTANCE(_class)\
	m_pBehaviour->Create(NAME_SPACE, #_class);

#define _0_PARAM_FUNCTION(className, funcName)\
	className##_##funcName()

#define _1_PARAM_FUNCTION(className, funcName, paramType, paramName)\
	className##_##funcName(paramType paramName)

#define _2_PARAM_FUNCTION(className, funcName, param1Type, param1Name, param2Type, param2Name)\
	className##_##funcName(param1Type param1Name,param2Type param2Name)

#define _3_PARAM_FUNCTION(className, funcName, param1Type, param1Name, param2Type, param2Name, param3Type, param3Name)\
	className##_##funcName(param1Type param1Name,param2Type param2Name, param3Type param3Name)

#define _4_PARAM_FUNCTION(className, funcName, param1Type, param1Name, param2Type, param2Name, param3Type, param3Name, param4Type, param4Name)\
	className##_##funcName(param1Type param1Name,param2Type param2Name, param3Type param3Name, param4Type param4Name)

#define _5_PARAM_FUNCTION(className, funcName, param1Type, param1Name, param2Type, param2Name, param3Type, param3Name, param4Type, param4Name, param5Type, param5Name)\
	className##_##funcName(param1Type param1Name,param2Type param2Name, param3Type param3Name, param4Type param4Name, param5Type param5Name)


#define IMPL_GET_FUNCTION(className,funcName)\
	__internal_call_function static CS_OBJECT className##_funcName(CS_OBJECT cs_obj)\
	{\
		className * cpp_obj = static_cast<className*>(getCppObject(cs_obj));\
		if(cpp_obj == nullptr)\
		{\
			return nullptr;\
		}\
		if (cpp_obj->funcName() == nullptr)\
		{\
			return nullptr;\
		}\
		return cpp_obj->funcName()->GetMonoBehaviour()->GetMonoObject();\
	}

#define __STRINGIFY(x)   #x
#define REGISTER_INTERNAL_CALL(className, funcName)\
	mono_add_internal_call(__STRINGIFY( E3DEngine##.##className##:##:##funcName), className##_##funcName);

VOID _1_PARAM_FUNCTION(Camera			, renderCamera		, CS_OBJECT		, cs_obj);
VOID _1_PARAM_FUNCTION(Debug			, log_error			, CS_STRING		, err);
VOID _1_PARAM_FUNCTION(Debug			, log_warning		, CS_STRING		, warning);
VOID _1_PARAM_FUNCTION(Debug			, log_info			, CS_STRING		, info);
VOID _1_PARAM_FUNCTION(Render			, setVertex2Render	, CPP_OBJECT	, obj);
VOID _1_PARAM_FUNCTION(Scene			, changeScene		, UINT			, sceneId);
VOID _1_PARAM_FUNCTION(Scene			, destoryScene		, UINT			, sceneId);
VOID _4_PARAM_FUNCTION(Transform		, getPosition		, CS_OBJECT		, obj		, float&	, x, float&	, y, float&	, z);
VOID _4_PARAM_FUNCTION(Transform		, getRotation		, CS_OBJECT		, obj		, float&	, x, float&	, y, float&	, z);
VOID _4_PARAM_FUNCTION(Transform		, getScale			, CS_OBJECT		, obj		, float&	, x, float&	, y, float&	, z);
VOID _4_PARAM_FUNCTION(Transform		, setPosition		, CS_OBJECT		, obj		, float		, x, float	, y, float	, z);
VOID _4_PARAM_FUNCTION(Transform		, setScale			, CS_OBJECT		, obj		, float		, x, float	, y, float	, z);
VOID _4_PARAM_FUNCTION(Transform		, setRotation		, CS_OBJECT		, obj		, float		, x, float	, y, float	, z);
VOID _5_PARAM_FUNCTION(Camera			, setClearColor		, CS_OBJECT		, cs_boj	, float		, r, float	, g, float	, b, float, a);
CS_OBJECT _3_PARAM_FUNCTION(Box			, createBox			, float			, l			, float		, w, float	, h);
VOID _2_PARAM_FUNCTION(GameObject		, set_Material		, CS_OBJECT		, cs_boj	, CS_OBJECT	, material);
VOID _2_PARAM_FUNCTION(GameObject		, set_Active		, CS_OBJECT		, cs_boj	, CS_BOOL	, isActive);
VOID _2_PARAM_FUNCTION(RigidBody		, addRigidBody		, CS_OBJECT		, rigibody	, CS_OBJECT	, _collider);
VOID _2_PARAM_FUNCTION(GameObject		, set_LayerMask		, CS_OBJECT		, cs_boj	, UINT		, mask);
CS_OBJECT _2_PARAM_FUNCTION(GameObject	, addComponent		, CS_OBJECT		, obj		, CS_STRING	, class_name);
CS_OBJECT _1_PARAM_FUNCTION(GameObject	, get_Material		, CS_OBJECT		, cs_boj);
CS_BOOL _1_PARAM_FUNCTION(GameObject	, get_Active		, CS_OBJECT		, cs_boj);
UINT _1_PARAM_FUNCTION(Object			, get_ID			, CS_OBJECT		, cs_boj);
UINT _1_PARAM_FUNCTION(GameObject		, get_LayerMask		, CS_OBJECT		, cs_boj);
CS_OBJECT _1_PARAM_FUNCTION(Material	, createMaterial	, CS_STRING		, path);
CS_OBJECT _1_PARAM_FUNCTION(Render		, createRenderer	, UINT			, materialID);
CS_OBJECT _1_PARAM_FUNCTION(Camera		, createCamera		, CS_STRING		, name);
CS_OBJECT _0_PARAM_FUNCTION(Render		, createRendererWithoutParam);
VOID _0_PARAM_FUNCTION(Application		, exitApplication);
CS_OBJECT _0_PARAM_FUNCTION(Scene		, createScene);
VOID _1_PARAM_FUNCTION(GameObject		, removeComponent	, CS_OBJECT		, cs_obj);

CS_ARRAY _2_PARAM_FUNCTION(ParticleSystem	, createParticle	, CS_OBJECT		, cs_obj, CS_STRING		, path);
VOID _2_PARAM_FUNCTION(ParticleGroup		, SetEmitterEnable	, CS_OBJECT		, cs_obj, CS_BOOL		, enable);
CS_OBJECT _4_PARAM_FUNCTION(Camera			, screen2WorldPoint	, CS_OBJECT		, cs_obj, float&		, x		, float&, y, float&	, z);
VOID _1_PARAM_FUNCTION(GameObject			, destory			, CS_OBJECT		, cs_obj);
CS_OBJECT _2_PARAM_FUNCTION(GameObject		, findChildWithName , CS_OBJECT		, cs_obj, CS_STRING		, name);
CS_OBJECT _2_PARAM_FUNCTION(GameObject		, findChildWithID	, CS_OBJECT		, cs_obj, UINT			, id);
VOID _2_PARAM_FUNCTION(GameObject			, set_Name			, CS_OBJECT		, cs_obj, CS_STRING		, name);
CS_STRING _1_PARAM_FUNCTION(GameObject		, get_Name			, CS_OBJECT		, cs_obj);
CS_OBJECT _1_PARAM_FUNCTION(Sphere			, CreateSphere		, float			, r);