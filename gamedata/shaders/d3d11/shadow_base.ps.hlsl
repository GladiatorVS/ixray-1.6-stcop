#include "common.hlsli"

float4 main(p_shadow I) : SV_Target
{
#ifdef USE_AREF
    float4 C = s_base.Sample(smp_linear, I.tc0);
    clip(C.w - def_aref);
#endif

#ifdef USE_HWSMAP
    return 0;
#else
    return I.depth;
#endif
}