#include "fluid_common_render.hlsli"

//	Pixel
//	TODO: DX10: replace WorldViewProjection with m_WVP
float4 main_ps_4_0(PS_INPUT_RAYCAST input) : SV_Target
{
    return Raycast(input);
}