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

	if(botA >= topB && topA < botB  && leftA < rightB && rightA > leftB)
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
int core::collisionComp(box a, box b){
    int leftA,leftB;
	int rightA,rightB;
	int topA, topB;
	int botA, botB;

	leftA = a.x;	leftB = b.x;
	rightA = a.x+a.w;	rightB = b.x+b.w;
	topA = a.y;	topB = b.y;
	botA = a.y+a.h;	botB = b.y + b.h;

	int ret = 0;

    if(botA > topB)
        ret+=2;
	return ret;
};
void core::renderText(int x, int y, string text, int fontSize){
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* textSurface;
    TTF_Font *font = TTF_OpenFont("assets/font.ttf", fontSize);
    textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    if(textSurface != 0){
        GLuint Texture = SDLSurfaceToTexture(textSurface);

        box pos;
        pos.x = x;
        pos.y = y;
        pos.w = textSurface->w;
        pos.h = textSurface->h;
        core::draw(Texture,pos);
        glDeleteTextures(1, &Texture);
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
	}
	else{
        cout << "failed to create string" << endl;
    }
};
void core::renderText(int x, int y, string text, int fontSize, int R, int G, int B){
    SDL_Color color = {R, G, B, 255};
    SDL_Surface* textSurface;
    TTF_Font *font = TTF_OpenFont("assets/font.ttf", fontSize);
    textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    if(textSurface != 0){
        GLuint Texture = SDLSurfaceToTexture(textSurface);

        box pos;
        pos.x = x;
        pos.y = y;
        pos.w = textSurface->w;
        pos.h = textSurface->h;
        core::draw(Texture,pos);
        glDeleteTextures(1, &Texture);
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
	}
	else{
        cout << "failed to create string" << endl;
    }
};
GLuint core::SDLSurfaceToTexture(SDL_Surface* surface)
{
    GLuint texture;
    GLint nOfColors;
    GLenum texture_format;

    // get the number of channels in the SDL surface
    nOfColors = surface->format->BytesPerPixel;

    if (nOfColors == 4)     // contains an alpha channel
    {
        if (surface->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    }
    else if (nOfColors == 3)
    {
        if (surface->format->Rmask == 0x000000ff)
            texture_format = GL_RGB;
        else
            texture_format = GL_BGR;
    }
    else
    {
        printf("Picture with less than 24-bit color depth detected.\n");
        return 0;
    }

    // Have OpenGL generate a texture object handle for us
    glGenTextures(1, &texture);

    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the texture's stretching properties
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Edit the texture object's image data using the information SDL_Surface gives us
    glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
    texture_format, GL_UNSIGNED_BYTE, surface->pixels);

    // Bind the texture to which subsequent calls refer to
    glBindTexture(GL_TEXTURE_2D, texture);

    return texture;
}
string core::toString(int number){
    stringstream ss;
    ss << number;
    return ss.str();
}
bool core::clickOn_LMB(box a, SDL_Event e){
	if(e.type == SDL_MOUSEBUTTONDOWN){
		int mx = e.button.x;
		int my = e.button.y;
		if(mx>a.x && mx < a.x+a.w && my>a.y && my <a.y+a.h && e.button.button==SDL_BUTTON_LEFT)
			return true;
		else
			return false;
	}
	else
		return false;
}
bool core::mouseOver(box a, SDL_Event e){
    int x = e.button.x;
    int y = e.button.y;
    if(x>a.x && x < a.x+a.w && y>a.y && y <a.y+a.h)
        return true;
    else
        return false;
}
