#pragma once

#include "Mof.h"

// ?ړ??\?͈͂̔???
#define FIELD_HALF_X (9.0f)
#define FIELD_HALF_Z (14.0f)


enum ShotMode
{
	MODE_SINGLE,
	MODE_DOUBLE,
	MODE_TRIPPLE
};

enum EASING_TYPE {
	EASE_LINEAR,
	EASE_IN_SINE,
	EASE_OUT_SINE,
	EASE_INOUT_SINE,
};


struct ANIM_DATA
{
	float	Time;
	float	Value;
	EASING_TYPE	EasingType;
};


float	InterpolationAnim(float AnimTime, ANIM_DATA* AnimData, int cnt);

