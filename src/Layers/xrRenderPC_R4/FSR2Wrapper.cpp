#include "stdafx.h"

#include "FSR2Wrapper.h"

Fsr2Wrapper g_Fsr2Wrapper;

void Fsr2Wrapper::Create(Fsr2Wrapper::ContextParameters params)
{
    if(m_created) {
        Destroy();
    }

    if(RFeatureLevel < D3D_FEATURE_LEVEL_11_0) {
        return;
    }

    m_contextParams = params;

    // Setup DX11 interface.
    m_scratchBuffer.resize(ffxFsr2GetScratchMemorySizeDX11());
    FfxErrorCode errorCode = ffxFsr2GetInterfaceDX11(&m_contextDesc.callbacks, params.device, m_scratchBuffer.data(), m_scratchBuffer.size());
    R_ASSERT(errorCode == FFX_OK);

    // This adds a ref to the device. 
    // The reference will get freed in ffxFsr2ContextDestroy
    m_contextDesc.device = ffxGetDeviceDX11(params.device);
    m_contextDesc.maxRenderSize = params.maxRenderSize;
    m_contextDesc.displaySize = params.displaySize;

    // You should config the flags you need based on your own project
    m_contextDesc.flags = FFX_FSR2_ENABLE_HIGH_DYNAMIC_RANGE;

    if(params.fpMessage) {
        m_contextDesc.flags |= FFX_FSR2_ENABLE_DEBUG_CHECKING;
        m_contextDesc.fpMessage = params.fpMessage;
    }

    ffxFsr2ContextCreate(&m_context, &m_contextDesc);

    m_created = true;
}

void Fsr2Wrapper::Destroy()
{
    if(!m_created) {
        return;
    }

    m_created = false;
    ffxFsr2ContextDestroy(&m_context);
}

bool Fsr2Wrapper::Draw(const DrawParameters& params)
{
    if(!m_created) {
        Msg("! Fsr2Wrapper not created. Need use linear filter");
        return false;
    }

    FfxFsr2DispatchDescription dispatchParameters = {};
    dispatchParameters.commandList = params.deviceContext;

    dispatchParameters.color = ffxGetResourceDX11(&m_context, params.unresolvedColorResource, L"FSR2_InputColor");
    dispatchParameters.depth = ffxGetResourceDX11(&m_context, params.depthbufferResource, L"FSR2_InputDepth");

    dispatchParameters.motionVectors = ffxGetResourceDX11(&m_context, params.motionvectorResource, L"FSR2_InputMotionVectors");
    dispatchParameters.exposure = ffxGetResourceDX11(&m_context, nullptr, L"FSR2_InputExposure");

    dispatchParameters.reactive = ffxGetResourceDX11(&m_context, params.reactiveMapResource, L"FSR2_InputReactiveMap");
    dispatchParameters.transparencyAndComposition = ffxGetResourceDX11(&m_context, params.transparencyAndCompositionResource, L"FSR2_TransparencyAndCompositionMap");

    dispatchParameters.output = ffxGetResourceDX11(&m_context, params.resolvedColorResource, L"FSR2_OutputUpscaledColor", FFX_RESOURCE_STATE_UNORDERED_ACCESS);

    dispatchParameters.jitterOffset.x = params.cameraJitterX;
    dispatchParameters.jitterOffset.y = params.cameraJitterY;

    dispatchParameters.motionVectorScale.x = -float(params.renderWidth * 0.5f);
    dispatchParameters.motionVectorScale.y = float(params.renderHeight * 0.5f);

    dispatchParameters.reset = params.cameraReset;

    dispatchParameters.enableSharpening = params.enableSharpening;
    dispatchParameters.sharpness = params.sharpness;

    dispatchParameters.frameTimeDelta = params.frameTimeDelta;

    dispatchParameters.preExposure = 1.0f;

    dispatchParameters.renderSize.width = params.renderWidth;
    dispatchParameters.renderSize.height = params.renderHeight;

    dispatchParameters.cameraFar = params.farPlane;
    dispatchParameters.cameraNear = params.nearPlane;

    dispatchParameters.cameraFovAngleVertical = params.fovH;

    dispatchParameters.viewSpaceToMetersFactor = 1.0f;
    dispatchParameters.autoTcThreshold = 0.1f;
    dispatchParameters.autoTcScale = 1.0f;
    dispatchParameters.autoReactiveScale = 5.0f;
    dispatchParameters.autoReactiveMax = 0.9f;

    // EXPERIMENTAL feature, auto-generate reactive mask
    // Turn it off if you don't unresolvedOpaqueResource it

    if(params.unresolvedOpaqueResource) {
        dispatchParameters.enableAutoReactive = true;
        dispatchParameters.colorOpaqueOnly = ffxGetResourceDX11(&m_context, params.unresolvedOpaqueResource, L"FSR2_InputColor");
    }

    FfxErrorCode errorCode = ffxFsr2ContextDispatch(&m_context, &dispatchParameters);

    if(errorCode != FFX_OK) {
        Msg("! ffxFsr2ContextDispatch not valid. Need use linear filter");
        return false;
    }

    return true;
}

Fsr2Wrapper::~Fsr2Wrapper()
{
    Destroy();
}
