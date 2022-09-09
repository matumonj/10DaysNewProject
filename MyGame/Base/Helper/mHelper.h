#pragma once
#include<math.h>
#define PI 3.14f
	namespace Easing {
		inline int EaseIn(int t) {
			return t * t;
		}
		inline float EaseOut(float t, float start, float end) {
			return (end - start) * (1.0f - cosf(t * PI / 2.0f)) + start;
		}
		inline float EaseInOut(int& t);
		inline float EaseOutIn(int& t);
	}
	namespace Percent {
		inline float GetParcent(float amount,float num) {
			return num / amount * 100.00f;
		}
	}


