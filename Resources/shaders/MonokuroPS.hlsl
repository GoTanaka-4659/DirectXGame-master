float4 main() : SV_TARGET
{
    float4 glayScale;
    float Y = 0.299f * glayScale.r + 0.587 * glayScale.g + 0.114f * glayScale.b;
    glayScale.r = Y;
    glayScale.g = Y;
    glayScale.b = Y;
	
    return glayScale;
}