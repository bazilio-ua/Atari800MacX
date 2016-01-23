/*
    GUILIB:  An example GUI framework library for use with SDL
    Copyright (C) 1997  Sam Lantinga

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Sam Lantinga
    5635-34 Springhouse Dr.
    Pleasanton, CA 94588 (USA)
    slouken@devolution.com
*/

#include <string.h>

#include <SDL/SDL.h>
#include "GUI_button.h"
#include "GUI_loadimage.h"


/* the check marks bitmap */
#include "the_checker.h"
SDL_Surface *checkmarks=NULL;



/* The default callback quits the GUI */
static GUI_status Default_ActiveProc(void *unused)
{
	return(GUI_QUIT);
}


GUI_Button:: GUI_Button(void *data, int x, int y, SDL_Surface *image,
			SDL_Surface *image2,GUI_ActiveProc activeproc)
 : GUI_Widget(data, x, y, image->w, image->h)
{
	if ( activeproc == NULL ) {
		ActiveProc = Default_ActiveProc;
	} else {
		ActiveProc = activeproc;
	}
	button = image;
	button2 = image2;
	freebutton = 0;
	for (int i=0;i<3; ++i ) {
  		pressed[i]=0;
	}
	enabled=1;
	buttonFont=NULL;
	freefont=0;
	flatbutton=0;
	is_checkable=0;
	checked=0;
}

GUI_Button:: GUI_Button(void *data, int x, int y, int w, int h,
			GUI_ActiveProc activeproc)
 : GUI_Widget(data, x, y, w, h)
{
	if ( activeproc == NULL ) {
		ActiveProc = Default_ActiveProc;
	} else {
		ActiveProc = activeproc;
	}
	button = NULL;
	button2 = NULL;
	freebutton = 0;
	for (int i=0;i<3; ++i ) {
  		pressed[i]=0;
	}
	enabled=1;
	buttonFont=NULL;
	freefont=0;
	flatbutton=0;
	is_checkable=0;
	checked=0;
}

GUI_Button::GUI_Button(void *data, int x, int y, int w, int h, char *text,
		       GUI_Font *font, int alignment, int is_checkbutton,
			   int fr, int fg, int fb, int br, int bg, int bb,
		       GUI_ActiveProc activeproc, 
			   int flat)
 : GUI_Widget(data,x,y,w,h)
{
	BL_R = fr;
	BL_B = fb;
	BL_G = fg;
	BT_R = br;
	BT_B = bb;
	BT_G = bg;
	if (fr > 20)
		BF_R = fr-20;
	else
		BF_R = 0;
	if (fg > 20)
		BF_G = fg-20;
	else
		BF_G = 0;
	if (fb > 20)
		BF_B = fb-20;
	else
		BF_B = 0;
	if (fr > 40)
		BS_R = fr-40;
	else
		BS_R = 0;
	if (fg > 40)
		BS_G = fg-40;
	else
		BS_G = 0;
	if (fb > 40)
		BS_B = fb-40;
	else
		BS_B = 0;

  if ( activeproc == NULL )
    ActiveProc = Default_ActiveProc;
  else
    ActiveProc = activeproc;

  if (font!=NULL)
  {
    buttonFont=font;
    freefont=0;
  }
  else
  {
   buttonFont=new GUI_Font();
   freefont=1;
  }
  flatbutton=flat;
  freebutton=1;
  button=NULL;
  button2=NULL;

  is_checkable=is_checkbutton;
  checked=0;
  if (is_checkable &&(checkmarks==NULL))
  {
    checkmarks=GUI_LoadImage(checker_w,checker_h,checker_pal,checker_data);
    SDL_SetColorKey(checkmarks,SDL_SRCCOLORKEY,0);
  }
  ChangeTextButton(-1,-1,-1,-1,text,alignment);

  for (int i=0;i<3; ++i ) {
  	pressed[i]=0;
  }
  enabled=1;
}

GUI_Button::~GUI_Button()
{
  if (freebutton)
  {
    if (button)
      delete button;
    if (button2)
      delete button2;
  }
  if (freefont)
    delete buttonFont;
}

/* Resize/reposition/change text */
void GUI_Button::ChangeTextButton(int x, int y, int w, int h, char* text, int alignment)
{
  if (x>=0)
    area.x=x;
  if (y>=0)
    area.y=y;
  if (w>=0)
    area.w=w;
  if (h>=0)
    area.h=h;

  if (freebutton)
  {
    if (button)
      SDL_FreeSurface(button);
    if (button2)
      SDL_FreeSurface(button2);
    if (flatbutton)
    {
      button=CreateTextButtonImage(BUTTON2D_UP,text,alignment);
      button2=CreateTextButtonImage(BUTTON2D_DOWN,text,alignment);
    }
    else
    {
      button=CreateTextButtonImage(BUTTON3D_UP,text,alignment);
      button2=CreateTextButtonImage(BUTTON3D_DOWN,text,alignment);
    }
  }
}

/* Show the widget  */
void GUI_Button:: Display(void)
{
	if (button)
	{
	  if ((button2!=NULL) && (pressed[0])==1)
	    SDL_BlitSurface(button2,NULL,screen,&area);
	  else
	    SDL_BlitSurface(button,NULL,screen,&area);
	}
	if (is_checkable)
	{
/*
**** OLD VERSION WITH TEXT CHECKMARK ****
	  if (checked)
	  {
	    buttonFont->SetTransparency(1);
	    buttonFont->SetColoring(255,0,0);
	    buttonFont->TextOut(screen,area.x+4,area.y+4,textmark);
	  }
*/
	  SDL_Rect src,dest=area;
	  src.x=8-(checked*8); src.y=0;
	  src.w=8; src.h=10;
	  dest.x+=4; dest.y+=4;
	  dest.w=8; dest.h=10;
	  SDL_BlitSurface(checkmarks,&src,screen,&dest);
	}
	if (!enabled)
	{
	  Uint8 *pointer;
	  int pixel=SDL_MapRGB(screen->format,0,0,0);;
	  Uint8 bytepp=screen->format->BytesPerPixel;

	  if (!SDL_LockSurface(screen))
	  {
	    for (int y=0;y<area.h;y+=2)
	    {
	      pointer=(Uint8*)screen->pixels+screen->pitch*(area.y+y)+(area.x*bytepp);
	      for (int x=0;x<area.w>>1;x++)
	      {
	        switch (bytepp)
	        {
	        case 1:
		  *((Uint8 *)(pointer)) = (Uint8)pixel;
		  pointer+=2;
		  break;
	        case 2:
		  *((Uint16 *)(pointer)) = (Uint16)pixel;
		  pointer+=4;
		  break;
	        case 3:  /* Format/endian independent */
		  Uint8 r, g, b;

		  r = (pixel>>screen->format->Rshift)&0xFF;
		  g = (pixel>>screen->format->Gshift)&0xFF;
		  b = (pixel>>screen->format->Bshift)&0xFF;
		  *((pointer)+screen->format->Rshift/8) = r; 
		  *((pointer)+screen->format->Gshift/8) = g;
		  *((pointer)+screen->format->Bshift/8) = b;
		  pointer+=6;
		  break;
	        case 4:
		  *((Uint32 *)(pointer)) = (Uint32)pixel;
		  pointer+=8;
		  break;
	        }
	      }
	    }
	    SDL_UnlockSurface(screen);
	  }
	}
}

/* Mouse hits activate us */
GUI_status GUI_Button:: MouseDown(int x, int y, int button)
{
	if (enabled &&(button==1))
	{
	  pressed[0]=1;
	  Redraw();
	}
	return GUI_PASS;
}

GUI_status GUI_Button::MouseUp(int x,int y,int button)
{
	if ((button==1) && (pressed[0]))
	{
	  pressed[0]=0;
	  if ((x>=0) && (y>=0))
	    if (ActiveProc(widget_data)==GUI_QUIT)
	      return GUI_QUIT;
	  Redraw();
	}
	return GUI_PASS;
}

GUI_status GUI_Button::MouseMotion(int x,int y,Uint8 state)
{
	if ((pressed[0]==1) && ((x<0) || (y<0)))
	{
	  pressed[0]=2;
	  Redraw();
	}
	if ((pressed[0]==2) && (x>=0) && (y>=0))
	{
	  pressed[0]=1;
	  Redraw();
	}
	return GUI_PASS;
}

void GUI_Button::Disable()
{
	enabled=0;
	Redraw();
}

void GUI_Button::Enable(int flag)
{
	enabled=flag;
	Redraw();
}

SDL_Surface* GUI_Button::CreateTextButtonImage(int style, char *text, int alignment)
{
  SDL_Rect fillrect;
  int th,tw,ty,tx=0;
  SDL_Surface *img=SDL_AllocSurface(SDL_SWSURFACE,area.w,area.h,
				    16,31 << 11,63 << 5,31,0);
  Uint32 color1=SDL_MapRGB(img->format,BL_R,BL_G,BL_B);
  Uint32 color2=SDL_MapRGB(img->format,BS_R,BS_G,BS_B);
  Uint32 color3=SDL_MapRGB(img->format,BF_R,BF_G,BF_B);
  Uint32 color4=SDL_MapRGB(img->format,BI2_R,BI2_G,BI2_B);

  if (img==NULL) return NULL;

  buttonFont->SetColoring(BT_R,BT_G,BT_B);
  buttonFont->SetTransparency(1);
  buttonFont->TextExtent(text,&tw,&th);
  if (tw>(area.w-(4+is_checkable*16)))
  {
    text[(area.w-(4+is_checkable*16))/buttonFont->CharWidth()]=0;
    buttonFont->TextExtent(text,&tw,&th);
  }
  if (th>(area.h-4))
  {
    text[0]=0;
  }
  switch (alignment)
  {
  case BUTTON_TEXTALIGN_LEFT:
    tx=4+(is_checkable*16);
    break;
  case BUTTON_TEXTALIGN_CENTER:
    tx=(area.w-tw) >> 1;
    break;
  case BUTTON_TEXTALIGN_RIGHT:
    tx=area.w-5-tw;
    break;
  }
  ty=(area.h-th) >> 1;

  switch (style)
  {
  case BUTTON3D_UP:
    fillrect.x=0; fillrect.y=0;
    fillrect.w=area.w; fillrect.h=2;
    SDL_FillRect(img,&fillrect,color1);
    fillrect.y=area.h-2;
    SDL_FillRect(img,&fillrect,color2);
    fillrect.x=0; fillrect.y=0;
    fillrect.w=2; fillrect.h=area.h;
    SDL_FillRect(img,&fillrect,color1);
    fillrect.x=area.w-2;
    SDL_FillRect(img,&fillrect,color2);
    fillrect.h=1; fillrect.w=1;
    SDL_FillRect(img,&fillrect,color1);
    fillrect.x=1;
    fillrect.y=area.h-1;
    SDL_FillRect(img,&fillrect,color2);
    fillrect.x=2; fillrect.y=2;
    fillrect.w=area.w-4; fillrect.h=area.h-4;
    SDL_FillRect(img,&fillrect,color3);
    buttonFont->TextOut(img,tx,ty,text);
    break;
  case BUTTON3D_DOWN:
    fillrect.x=0; fillrect.y=0;
    fillrect.w=area.w; fillrect.h=area.h;
    SDL_FillRect(img,&fillrect,color3);
    buttonFont->TextOut(img,tx+1,ty+1,text);
    break;
  case BUTTON2D_UP:
    fillrect.x=0; fillrect.y=0;
    fillrect.w=area.w; fillrect.h=area.h;
    SDL_FillRect(img,&fillrect,color3);
    buttonFont->TextOut(img,tx,ty,text);
    break;
  case BUTTON2D_DOWN:
    fillrect.x=0; fillrect.y=0;
    fillrect.w=area.w; fillrect.h=area.h;
    SDL_FillRect(img,&fillrect,color4);
    buttonFont->SetTransparency(0);
    buttonFont->SetColoring(BI1_R,BI1_G,BI1_B,BI2_R,BI2_G,BI2_B);
    buttonFont->TextOut(img,tx,ty,text);
    break;
  }
  return img;
}
