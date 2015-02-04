#include "core.h"


GLuint core::loadImg(const char* file){
    SDL_Surface* image = SDL_LoadBMP(file);
    GLuint texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, image->format->BytesPerPixel, image->w,image->h, 0, GL_BGR, GL_UNSIGNED_BYTE,image->pixels);
    SDL_FreeSurface(image);
    return texture;
};
void core::draw(GLuint texture, box position){
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(position.x,position.y,0);
    glTexCoord2f(1,0);
    glVertex3f(position.x + position.w,position.y,0);
    glTexCoord2f(1,1);
    glVertex3f(position.x + position.w,position.y + position.h,0);
    glTexCoord2f(0,1);
    glVertex3f(position.x,position.y+position.h,0);
    glEnd();
};
