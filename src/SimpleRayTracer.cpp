//
//  SimpleRayTracer.cpp
//  SimpleRayTracer
//
//  Created by Philipp Lensing on 03.09.14.
//  Copyright (c) 2014 Philipp Lensing. All rights reserved.
//

#include "SimpleRayTracer.h"
#include "rgbimage.h"
#include <stdio.h>
#include <math.h>


Camera::Camera( float zvalue, float planedist, float width, float height, unsigned int widthInPixel, unsigned int heightInPixel )
{
	m_zvalue = zvalue;
    m_planedist = planedist;
    m_width = width;
    m_height = height;
    m_widthInPixel = widthInPixel;
    m_heightInPixel = heightInPixel;
    m_position = Vector(0.0f, 0.0f, m_zvalue);
}

Vector Camera::generateRay( unsigned int x, unsigned int y) const
{
    //Vector von der Kamera zur linken oberen Ecke des Bildes
	Vector topLeft = m_position + Vector(-m_width/2, m_height/2, m_planedist);
    // Vector von der linken oberen Ecke zum Punkt (x,y)
    Vector pixelCoord(x * (m_width / m_widthInPixel), y * -(m_height / m_heightInPixel), 0);
    // Position des Bildpunkts in der Szene
    Vector pixelPos = topLeft + pixelCoord;
    // Vector
    Vector ray = pixelPos - m_position;
    return ray.normalize();
}

Vector Camera::Position() const
{
	return m_position;
}

SimpleRayTracer::SimpleRayTracer(unsigned int MaxDepth)
{
	this->mMaxDepth = MaxDepth;
}


void SimpleRayTracer::traceScene( const Scene& SceneModel, RGBImage& Image)
{
    Camera camera(-8, 1, 1, 0.75, 640, 480);
	// Setze Pixelfarbe aller Pixel der Bildebene auf Schwarz
    for(int x = 0; x <= Image.width(); x++){
        for(int y = 0; y <= Image.height(); y++){
            Vector ray = camera.generateRay(x, y);
            Color pixelColor = trace(SceneModel, camera.Position(), ray, mMaxDepth);
            Image.setPixelColor(x, y, pixelColor);
        }
    }
}

Color SimpleRayTracer::localIllumination( const Vector& Surface, const Vector& Eye, const Vector& N, const PointLight& Light, const Material& Mtrl )
{
	return Mtrl.getDiffuseCoeff(Surface);
}

Color SimpleRayTracer::trace( const Scene& SceneModel, const Vector& o, const Vector& d, unsigned int depth)
{
    Color pixelColor = Color(0, 0, 0);

    return pixelColor;
}

