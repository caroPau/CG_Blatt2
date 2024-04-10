#include "rgbimage.h"
#include "color.h"
#include "assert.h"

RGBImage::RGBImage( unsigned int Width, unsigned int Height): m_Width(Width), m_Height(Height)
{
    m_Image = new Color[m_Width*m_Height];
}

RGBImage::~RGBImage()
{
	delete [] m_Image;
}

void RGBImage::setPixelColor( unsigned int x, unsigned int y, const Color& c)
{
    if(x >  width() - 1){
        x = width() - 1;
    }
    if(y > height() - 1){
        y = height() - 1;
    }
    m_Image[x + y * width()] = c;

}

const Color& RGBImage::getPixelColor( unsigned int x, unsigned int y) const
{
    if(x >  width() - 1){
        x = width() - 1;
    }
    if(y > height() - 1){
        y = height() - 1;
    }

	return m_Image[x + y * width()];
}

unsigned int RGBImage::width() const
{
	return m_Width;
}
unsigned int RGBImage::height() const
{
	return m_Height;
}

unsigned char RGBImage::convertColorChannel(float v) {
    char color;
    if (v <= 0.0f) {
        color = 0;
    } else if (v >= 1.0f) {
        color = (char) 255;
    } else {
        color = (char) (255 * v);
    }
    return color;
}


bool RGBImage::saveToDisk( const char* Filename)
{
    unsigned char fileHeader[13] = {};
    unsigned char infoHeader[39] = {};
    unsigned int fileHeaderSize = 14;
    unsigned int infoHeaderSize = 40;
    unsigned int filesize = fileHeaderSize + infoHeaderSize + width() * height() * 3;

    // FileHeader befüllen
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
    fileHeader[2] = (unsigned char) (filesize);
    fileHeader[3] = (unsigned char) (filesize >> 8);
    fileHeader[4] = (unsigned char) (filesize >> 16);
    fileHeader[5] = (unsigned char) (filesize >> 24);
    fileHeader[10] = (unsigned char) (fileHeaderSize + infoHeaderSize);

    //Infoheader befüllen
    infoHeader[0] = (unsigned char) (infoHeaderSize);
    infoHeader[4] = (unsigned char) (width());
    infoHeader[5] = (unsigned char) (width() >> 8);
    infoHeader[6] = (unsigned char) (width() >> 16);
    infoHeader[7] = (unsigned char) (width() >> 24);
    infoHeader[8] = (unsigned char) (height());
    infoHeader[9] = (unsigned char) (height() >> 8);
    infoHeader[10] = (unsigned char) (height() >> 16);
    infoHeader[11] = (unsigned char) (height() >> 24);
    infoHeader[12] = (unsigned char) (1);
    infoHeader[14] = (24);

    // In File schreiben
    FILE* image = fopen(Filename, "wb");

    if(image != nullptr){
        fwrite(fileHeader, 1, fileHeaderSize, image);
        fwrite(infoHeader, 1, infoHeaderSize, image);
    }else{
        return false;
    }

    for(int x = 0; x <= width() -1; x++){
        for(int y = height() - 1; y >= 0; y--){
            unsigned char Pixel[] = {
                    convertColorChannel(getPixelColor(x, y).B),
                    convertColorChannel(getPixelColor(x, y).G),
                    convertColorChannel(getPixelColor(x, y).R)
            };
            fwrite(Pixel, sizeof(char), sizeof(Pixel), image);
        }
    }
    fclose(image);

	return true;
}
