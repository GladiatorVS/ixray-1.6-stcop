// xrAPI.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "xrAPI.h"

XRCORE_API IRender_interface*	Render = nullptr;
XRCORE_API IRenderFactory*		RenderFactory = nullptr;
XRCORE_API CDUInterface*		DU = nullptr;
XRCORE_API xr_token*			vid_mode_token = nullptr;
XRCORE_API IUIRender*			UIRender = nullptr;

#ifndef	_EDITOR
XRCORE_API CGameMtlLibrary*		PGMLib = nullptr;
#endif

#ifdef DEBUG_DRAW
XRCORE_API IDebugRender*		DRender = nullptr;
#endif // DEBUG