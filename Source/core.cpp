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
bool core::ticker(int* ticker, int sleep){
    if(*ticker >= sleep){
        *ticker = 0;
        return true;
    }
    *ticker+=1;
    return false;
};
void core::fillRectangle(box draw, double R, double G, double B){
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(R,G,B);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f(draw.x,draw.y,0);
    glTexCoord2f(1,0);
    glVertex3f(draw.x + draw.w,draw.y,0);
    glTexCoord2f(1,1);
    glVertex3f(draw.x + draw.w,draw.y + draw.h,0);
    glTexCoord2f(0,1);
    glVertex3f(draw.x,draw.y+draw.h,0);
    glEnd();
};
box core::getBox(vector<box> block){
    box temp;
    temp.x = block[0].x;
    temp.y = block[0].y;
    temp.w = block[0].w;
    temp.h = block[0].h;
    for(unsigned int i = 0; i < block.size(); i++){
        if(block[i].x < temp.x)
            temp.x = block[i].x;
        if(block[i].y < temp.y)
            temp.y = block[i].y;
        if(block[i].w + block[i].x > temp.w)
            temp.w = block[i].w + block[i].x;
        if(block[i].h + block[i].y > temp.h)
            temp.h = block[i].h + block[i].y;
    }
    return temp;
};
bool core::collision(box a, box b){
    int leftA,leftB;
	int rightA,rightB;
	int topA, topB;
	int botA, botB;

	leftA = a.x;	leftB = b.x;
	rightA = a.x+a.w;	rightB = b.x+b.w;
	topA = a.y;	topB = b.y;
	botA = a.y+a.h;	botB = b.y + b.h;

	if(botA >= topB && topA <= botB && leftA < rightB && rightA > leftB)
		return true;
	return false;
};
bool core::collisionR(box a, box b){
    int leftA,leftB;
	int rightA,rightB;
	int topA, topB;
	int botA, botB;

	leftA = a.x;	leftB = b.x;
	rightA = a.x+a.w;	rightB = b.x+b.w;
	topA = a.y;	topB = b.y;
	botA = a.y+a.h;	botB = b.y + b.h;

	if(botA > topB && topA < botB && leftA < rightB && rightA >= leftB)
		return true;
	return false;
};
bool core::collisionL(box a, box b){
    int leftA,leftB;
	int rightA,rightB;
	int topA, topB;
	int botA, botB;

	leftA = a.x;	leftB = b.x;
	rightA = a.x+a.w;	rightB = b.x+b.w;
	topA = a.y;	topB = b.y;
	botA = a.y+a.h;	botB = b.y + b.h;

	if(botA > topB && topA < botB && leftA <= rightB && rightA > leftB)
		return true;
	return false;
};
