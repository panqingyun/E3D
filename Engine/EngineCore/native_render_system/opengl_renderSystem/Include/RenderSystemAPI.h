#pragma once
#include "../../../include/EngineAPI.h"
/// <summary>
/// 创建RenderSystem
/// </summary>
/// <param name = "width"> 渲染视口宽度 </param>
/// <param name = "height"> 渲染视口高度 </param> 
void* CreateGLRenderSystem(NATIVE_WINDOW nativeWindow, int width, int height);