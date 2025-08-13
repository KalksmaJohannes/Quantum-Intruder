#pragma once

#define pixels_per_meter 40.0f

inline float toPixels(float meters){

    return meters * pixels_per_meter;

}

inline float toMeters(float pixels){

    return pixels / pixels_per_meter;

}
