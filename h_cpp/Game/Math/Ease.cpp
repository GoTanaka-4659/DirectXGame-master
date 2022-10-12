#include "Ease.h"


float Ease::InQuad(float t, float totaltime, float max, float min)
{
	max -= min;
	t /= totaltime;
	return max * t * t + min;
}
float Ease::OutQuad(float t, float totaltime, float max, float min)
{
	max -= min;
	t /= totaltime;
	return -max * t * (t - 2) + min;
}
float Ease::InOutQuad(float t, float totaltime, float max, float min)
{
	max -= min;
	t /= totaltime;
	if (t / 2 < 1)
		return max / 2 * t * t + min;
	--t;
	return -max * (t * (t - 2) - 1) + min;
}
float Ease::InCubic(float t, float totaltime, float max, float min)
{
	max -= min;
	t /= totaltime;
	return max * t * t * t + min;
}
float Ease::OutCubic(float t, float totaltime, float max, float min)
{
	max -= min;
	t = t / totaltime - 1;
	return max * (t * t * t + 1) + min;
}
float Ease::InOutCubic(float t, float totaltime, float max, float min)
{
	max -= min;
	t /= totaltime;
	if (t / 2 < 1)
		return max / 2 * t * t * t + min;
	t -= 2;
	return max / 2 * (t * t * t + 2) + min;
}
float Ease::InQuart(float t, float totaltime, float max, float min)
{
	max -= min;
	t /= totaltime;
	return max * t * t * t * t + min;
}
float Ease::OutQuart(float t, float totaltime, float max, float min)
{
	max -= min;
	t = t / totaltime - 1;
	return -max * (t * t * t * t - 1) + min;
}
float Ease::InOutQuart(float t, float totaltime, float max, float min)
{
	max -= min;
	t /= totaltime;
	if (t / 2 < 1)
		return max / 2 * t * t * t * t + min;
	t -= 2;
	return -max / 2 * (t * t * t * t - 2) + min;
}
float Ease::InQuint(float t, float totaltime, float max, float min)
{
	max -= min;
	t /= totaltime;
	return max * t * t * t * t * t + min;
}
float Ease::OutQuint(float t, float totaltime, float max, float min)
{
	max -= min;
	t = t / totaltime - 1;
	return max * (t * t * t * t * t + 1) + min;
}
float Ease::InOutQuint(float t, float totaltime, float max, float min)
{
	max -= min;
	t /= totaltime;
	if (t / 2 < 1)
		return max / 2 * t * t * t * t * t + min;
	t -= 2;
	return max / 2 * (t * t * t * t * t + 2) + min;
}
float Ease::InSine(float t, float totaltime, float max, float min)
{
	max -= min;
	return -max * cos(t * PI / 2 / totaltime) + max + min;
}
float Ease::OutSine(float t, float totaltime, float max, float min)
{
	max -= min;
	return max * sin(t * PI / 2 / totaltime) + min;
}
float Ease::InOutSine(float t, float totaltime, float max, float min)
{
	max -= min;
	return -max / 2 * (cos(t * PI / totaltime) - 1) + min;
}
float Ease::InExp(float t, float totaltime, float max, float min)
{
	max -= min;
	return t == 0.0 ? min : max * pow(2, 10 * (t / totaltime - 1)) + min;
}
float Ease::OutExp(float t, float totaltime, float max, float min)
{
	max -= min;
	return t == totaltime ? max + min : max * (-pow(2, -10 * t / totaltime) + 1) + min;
}
float Ease::InOutExp(float t, float totaltime, float max, float min)
{
	if (t == 0.0)
		return min;
	if (t == totaltime)
		return max;
	max -= min;
	t /= totaltime;

	if (t / 2 < 1)
		return max / 2 * pow(2, 10 * (t - 1)) + min;
	--t;
	return max / 2 * (-pow(2, -10 * t) + 2) + min;

}
float Ease::InCirc(float t, float totaltime, float max, float min)
{
	max -= min;
	t /= totaltime;
	return -max * (sqrt(1 - t * t) - 1) + min;
}
float Ease::OutCirc(float t, float totaltime, float max, float min)
{
	max -= min;
	t = t / totaltime - 1;
	return max * sqrt(1 - t * t) + min;
}
float Ease::InOutCirc(float t, float totaltime, float max, float min)
{
	max -= min;
	t /= totaltime;
	if (t / 2 < 1)
		return -max / 2 * (sqrt(1 - t * t) - 1) + min;
	t -= 2;
	return max / 2 * (sqrt(1 - t * t) + 1) + min;
}
float Ease::InBack(float t, float totaltime, float max, float min, float s)
{
	max -= min;
	t /= totaltime;
	return max * t * t * ((s + 1) * t - s) + min;
}
float Ease::OutBack(float t, float totaltime, float max, float min, float s)
{
	max -= min;
	t = t / totaltime - 1;
	return max * (t * t * ((s + 1) * t * s) + 1) + min;
}
float Ease::InOutBack(float t, float totaltime, float max, float min, float s)
{
	max -= min;
	s *= 1.525;
	if (t / 2 < 1)
	{
		return max * (t * t * ((s + 1) * t - s)) + min;
	}
	t -= 2;
	return max / 2 * (t * t * ((s + 1) * t + s) + 2) + min;
}
float Ease::OutBounce(float t, float totaltime, float max, float min)
{
	max -= min;
	t /= totaltime;

	if (t < 1 / 2.75)
		return max * (7.5625 * t * t) + min;
	else if (t < 2 / 2.75)
	{
		t -= 1.5 / 2.75;
		return max * (7.5625 * t * t + 0.75) + min;
	}
	else if (t < 2.5 / 2.75)
	{
		t -= 2.25 / 2.75;
		return max * (7.5625 * t * t + 0.9375) + min;
	}
	else
	{
		t -= 2.625 / 2.75;
		return max * (7.5625 * t * t + 0.984375) + min;
	}
}
float Ease::InBounce(float t, float totaltime, float max, float min)
{
	return max - OutBounce(totaltime - t, totaltime, max - min, 0) + min;
}
float Ease::InOutBounce(float t, float totaltime, float max, float min)
{
	if (t < totaltime / 2)
		return InBounce(t * 2, totaltime, max - min, max) * 0.5 + min;
	else
		return OutBounce(t * 2 - totaltime, totaltime, max - min, 0) * 0.5 + min + (max - min) * 0.5;
}
float Ease::Linear(float t, float totaltime, float max, float min)
{
	return (max - min) * t / totaltime + min;
}


