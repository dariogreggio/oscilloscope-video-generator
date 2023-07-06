#include "compiler.h"
#include "GenericTypedefs.h"
#include "ep512.h"


#define isVBlank() 1		// :) v. PC_PIC
void _swap(WORD *, WORD *);

extern const char font4x6_basic[256][6];

BYTE textsize=1;
BYTE cursor_x,cursor_y;
BYTE textcolor=1,textbgcolor=0;
	
unsigned char drawPixel(WORD x, WORD y, BYTE c) {
	DWORD i;

	if(y>=Y_SIZE || x>=X_SIZE)
		return 0;

  while(!isVBlank())
  	ClrWdt();

  i=(X_SIZE/(8/BPP))*y +(x/(8/BPP));
#if BPP==2
	switch(x & 3) {
		case 0:
  		videoRAM[i] &= ~0b11000000;
  		videoRAM[i] |= (c & 3) << 6;
			break;
		case 1:
  		videoRAM[i] &= ~0b00110000;
  		videoRAM[i] |= (c & 3) << 4;
			break;
		case 2:
  		videoRAM[i] &= ~0b00001100;
  		videoRAM[i] |= (c & 3) << 2;
			break;
		case 3:
  		videoRAM[i] &= ~0b00000011;
  		videoRAM[i] |= c & 3;
			break;
		}
#endif
  
  return 1;
	}

static void drawHorizLine(WORD x1, WORD y,WORD x2,BYTE c) {

  while(x1<=x2)
    drawPixel(x1++,y,c);
  }

static void drawVertLine(WORD x, WORD y1,WORD y2,BYTE c) {
  
  while(y1<=y2)
    drawPixel(x,y1++,c);
  }
// è ancora da verificare la cosa che le linee hor/ver sforano di uno... ma poi può succedere che le oblique siano incomplete... 28/6/22

unsigned char drawRectangleFilled(WORD x1, WORD y1, WORD x2, WORD y2, BYTE c);
unsigned char drawLine(WORD x1, WORD y1, WORD x2, WORD y2, BYTE c) {
 	BOOL steep;
	short int dx,dy;
	short int err;
	short int ystep;
	short int xbegin;

  steep = abs(y2-y1) > abs(x2-x1);
  if(steep) {
    _swap(&x1, &y1);
    _swap(&x2, &y2);
    }
  if(x1>x2) {
    _swap(&x1, &x2);
    _swap(&y1, &y2);
    }

  dx = x2-x1;
  dy = abs(y2-y1);
  err = dx/2;
  ystep = y1<y2 ? 1 : -1;

  xbegin = x1;
  if(steep) {
    for(; x1<x2; x1++) {
      err -= dy;
      if(err < 0) {
        INT16 len = x1-xbegin;
        if(len) {
          if(textsize==1)
            drawVertLine(y1,xbegin,xbegin+len,c);
          else {
            while(len--) {
              drawRectangleFilled(y1,xbegin,y1+textsize,xbegin+textsize,c);
              xbegin++;
              }
            }
          }
        else {
          if(textsize==1)   // usare ALTRA size...
            drawPixel(y1,x1,c);
          else
            drawRectangleFilled(y1,x1,y1+textsize,x1+textsize,c);
          }
        xbegin = x1+1;
        y1 += ystep;
        err += dx;
        }
      }
    if(x1 > xbegin+1) {
      if(textsize==1)
        drawVertLine(y1,xbegin,x1,c);
      else {
        while(xbegin<=x1) {
          drawRectangleFilled(y1,xbegin,y1+textsize,xbegin+textsize,c);
          xbegin++;
          }
        }
      }
    } 
  else {
    for(; x1<x2; x1++) {
      err -= dy;
      if(err < 0) {
        INT16 len = x1-xbegin;
        if(len) {
          if(textsize==1)
            drawHorizLine(xbegin,y1,xbegin+len,c);
          else {
            while(len--) {
              drawRectangleFilled(xbegin,y1,xbegin+textsize,y1+textsize,c);
              xbegin++;
              }
            }
          }
        else {
          if(textsize==1)
            drawPixel(x1,y1,c);
          else
            drawRectangleFilled(x1,y1,x1+textsize,y1+textsize,c);
          }
        xbegin = x1+1;
        y1 += ystep;
        err += dx;
        }
      }
    if(x1 > xbegin+1) {
      if(textsize==1)
        drawHorizLine(xbegin,y1,x1,c);
      else {
        while(xbegin<=x1) {
          drawRectangleFilled(xbegin,y1,xbegin+textsize,y1+textsize,c);
          xbegin++;
          }
        }
      }
    }

	}

unsigned char drawRectangle(WORD x1, WORD y1, WORD x2, WORD y2, BYTE c) {
	WORD x,y;

	if(x1>x2 || y1>y2)
		return 0;
	if(textsize==1) {  // usare ALTRA size...
		drawHorizLine(x1,y1,x2,c);
		drawVertLine(x1,y1,y2,c);
		drawVertLine(x2,y1,y2,c);
		drawHorizLine(x1,y2,x2,c);
		}
	else {
		drawRectangleFilled(x1,y1,x2,y1+textsize,c);
		drawRectangleFilled(x1,y1,x1+textsize,y2,c);
		drawRectangleFilled(x2,y1,x2+textsize,y2,c);
		drawRectangleFilled(x1,y2,x2,y2+textsize,c);
		}
  
  return 1;
	}

unsigned char drawRectangleFilled(WORD x1, WORD y1, WORD x2, WORD y2, BYTE c) {
	WORD y;

	if(x1>x2 || y1>y2)
		return 0;
	for(y=y1; y<y2; y++)
		drawHorizLine(x1,y,x2,c);

  return 1;
	}



unsigned char screenCLS(BYTE c) {
	int x,y;

  BYTE *p=((BYTE*)videoRAM);
  for(y=0; y<Y_SIZE; y++) {
    while(!isVBlank())
      ;
    for(x=0; x<X_SIZE; x++) {
			DWORD i;

		  i=(X_SIZE/(8/BPP))*y +(x/(8/BPP));
#if BPP==2
			switch(x & 3) {
				case 0:
		  		videoRAM[i] &= ~0b11000000;
		  		videoRAM[i] |= (c & 3) << 6;
					break;
				case 1:
		  		videoRAM[i] &= ~0b00110000;
		  		videoRAM[i] |= (c & 3) << 4;
					break;
				case 2:
		  		videoRAM[i] &= ~0b00001100;
		  		videoRAM[i] |= (c & 3) << 2;
					break;
				case 3:
		  		videoRAM[i] &= ~0b00000011;
		  		videoRAM[i] |= c & 3;
					break;
				}
#endif
      }
    ClrWdt();
    }
    
	cursor_x=cursor_y=0;

  return 1;
	}

WORD getPixel(WORD x, WORD y) {
	int i;
  
      BYTE *p1;
  while(!isVBlank())
    ;
#if BPP==2
	switch(x & 3) {
		case 0:

// FARE!

      p1=((BYTE *)videoRAM)+((DWORD)X_SIZE)*y+x;
			break;
		case 1:
      p1=((BYTE *)videoRAM)+((DWORD)X_SIZE)*y+x;
			break;
		case 2:
      p1=((BYTE *)videoRAM)+((DWORD)X_SIZE)*y+x;
			break;
		case 3:
      p1=((BYTE *)videoRAM)+((DWORD)X_SIZE)*y+x;
			break;
		}
#endif
      return *p1;
  }
void scrollArea(WORD x1, WORD y1, WORD x2, WORD y2, short int dx, short int dy) {
  int x,y;
  
#if 0
      if(dy<0) {
        for(y=y1; y<y2; y++) {
          BYTE *p1,*p2;
          //if(dx<0) {
          //else
          p1=((BYTE *)videoRAM)+y*(X_SIZE +HORIZ_PORCH_VGA) +x1  +HORIZ_SHIFT_VGA;
          p2=((BYTE *)videoRAM)+(y+dy)*(X_SIZE +HORIZ_PORCH_VGA) +x1  +HORIZ_SHIFT_VGA  +dx;
          // per ora solo dy e su righe intere...
          while(!isVBlank())
            ;
          for(x=x1; x<x2; x++) {
            *p2++=*p1++;
            }
//          __delay_ns(SLOW_DMA);
          ClrWdt();
          }
        for(y=y2+dy; y<y2; y++) {// PULISCO COSì sempre! v. fillrect sotto...
          BYTE *p1;
          //if(dx<0) {
          //else
          p1=((BYTE *)videoRAM)+y*(X_SIZE +HORIZ_PORCH_VGA) +x1 +HORIZ_SHIFT_VGA +dx;
          while(!isVBlank())
            ;
          for(x=x1; x<x2; x++) {  // azz con O3 il compilatore traduce in memset()!!
            *p1++=Color565To332R(textbgcolor);
            }
          ClrWdt();
          }
        }
      else {
        for(y=y2-1; y>=y1; y--) {
          BYTE *p1,*p2;
          //if(dx<0) {
          //else
          p1=((BYTE *)videoRAM)+y*(X_SIZE +HORIZ_PORCH_VGA) +x1  +HORIZ_SHIFT_VGA;
          p2=((BYTE *)videoRAM)+(y+dy)*(X_SIZE +HORIZ_PORCH_VGA) +x1  +HORIZ_SHIFT_VGA  +dx;
          // per ora solo dy e su righe intere...
          // e ovviamente occhio alle sovrascritture!
          while(!isVBlank())
            ;
          for(x=x1; x<x2; x++) {
            *(p2+x)=*(p1+x);
            }
//          __delay_ns(SLOW_DMA);
          ClrWdt();
          }
        for(y=y2; y<y2+dy; y++) {// PULISCO COSì sempre! v. fillrect sotto...
          BYTE *p1;
          //if(dx<0) {
          //else
          p1=((BYTE *)videoRAM)+y*(X_SIZE +HORIZ_PORCH_VGA) +x1 +HORIZ_SHIFT_VGA +dx;
          while(!isVBlank())
            ;
          for(x=x1; x<x2; x++) {
            *p1++=Color565To332R(textbgcolor);
            }
          ClrWdt();
          }
        }
#endif
  }

 
unsigned char drawEllipse(WORD x0, WORD y0, WORD rx, WORD ry, BYTE color) {

//https://www.geeksforgeeks.org/midpoint-ellipse-drawing-algorithm/
  short int dx, dy, d1, d2, x, y;
  x = 0;
  y = ry;

  // Initial decision parameter of region 1
  d1 = (ry*ry) - (rx*rx*ry) + (rx*rx/4);
  dx = 2*ry*ry*x;
  dy = 2*rx*rx*y;

  // For region 1
  while(dx < dy) {

     // Print points based on 4-way symmetry
		if(textsize==1) {  // usare ALTRA size...
			drawPixel(x0+x, y0+y, color);
			drawPixel(x0-x, y0+y, color);
			drawPixel(x0+x, y0-y, color);
			drawPixel(x0-x, y0-y, color);
			}
		else {
			drawRectangleFilled(x0+x, y0+y, x0+x+textsize, y0+y+textsize, color);
			drawRectangleFilled(x0-x, y0+y, x0-x+textsize, y0+y+textsize, color);
			drawRectangleFilled(x0+x, y0-y, x0+x+textsize, y0-y+textsize, color);
			drawRectangleFilled(x0-x, y0-y, x0-x+textsize, y0-y+textsize, color);
			}

    // Checking and updating value of decision parameter based on algorithm
    if(d1<0) {
      x++;
      dx = dx + (2*ry*ry);
      d1 = d1 + dx + (ry*ry);
			}
    else {
      x++;
      y--;
      dx = dx + (2*ry*ry);
      dy = dy - (2*rx*rx);
      d1 = d1 + dx - dy + (ry*ry);
      }
    }
 
  // Decision parameter of region 2
  d2 = ((ry*ry) * ((x + 0.5) * (x + 0.5))) +
       ((rx*rx) * ((y-1) * (y-1))) -
       (rx*rx*ry*ry);
 
  // Plotting points of region 2
  while(y>=0) {

		if(textsize==1) {  // usare ALTRA size...
			drawPixel(x0+x, y0+y, color);
			drawPixel(x0-x, y0+y, color);
			drawPixel(x0+x, y0-y, color);
			drawPixel(x0-x, y0-y, color);
			}
		else {
			drawRectangleFilled(x0+x, y0+y, x0+x+textsize, y0+y+textsize, color);
			drawRectangleFilled(x0-x, y0+y, x0-x+textsize, y0+y+textsize, color);
			drawRectangleFilled(x0+x, y0-y, x0+x+textsize, y0-y+textsize, color);
			drawRectangleFilled(x0-x, y0-y, x0-x+textsize, y0-y+textsize, color);
			}
			
		// Checking and updating parameter value based on algorithm
		if(d2>0) {
      y--;
      dy = dy - (2*rx*rx);
      d2 = d2 + (rx*rx) - dy;
      }
    else {
      y--;
      x++;
      dx = dx + (2*ry*ry);
      dy = dy - (2*rx*rx);
      d2 = d2 + dx - dy + (rx*rx);
      }
	  }

  return 1;
  }

unsigned char drawCircle(WORD x0, WORD y0, WORD r, BYTE color) {
  short int f = 1 - r;
  short int ddF_x = 1;
  short int ddF_y = -2 * r;
  short int x=0;
  short int y=r;

  if(textsize==1) {  // usare ALTRA size...
    drawPixel(x0  , y0+r, color);
    drawPixel(x0  , y0-r, color);
    drawPixel(x0+r, y0  , color);
    drawPixel(x0-r, y0  , color);
    }
  else {
    drawRectangleFilled(x0  , y0+r, x0  +textsize, y0+r+textsize, color);
    drawRectangleFilled(x0  , y0-r, x0  +textsize, y0-r+textsize, color);
    drawRectangleFilled(x0+r, y0  , x0+r+textsize, y0  +textsize, color);
    drawRectangleFilled(x0-r, y0  , x0-r+textsize, y0  +textsize, color);
    }

  while(x<y) {
    if(f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
      }
    x++;
    ddF_x += 2;
    f += ddF_x;

    if(textsize==1) {  // usare ALTRA size...
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 - x, y0 + y, color);
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 - x, y0 - y, color);
      drawPixel(x0 + y, y0 + x, color);
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 + y, y0 - x, color);
      drawPixel(x0 - y, y0 - x, color);
      }
    else {
      drawRectangleFilled(x0 + x, y0 + y, x0 + x+textsize, y0 + y+textsize, color);
      drawRectangleFilled(x0 - x, y0 + y, x0 - x+textsize, y0 + y+textsize, color);
      drawRectangleFilled(x0 + x, y0 - y, x0 + x+textsize, y0 - y+textsize, color);
      drawRectangleFilled(x0 - x, y0 - y, x0 - x+textsize, y0 - y+textsize, color);
      drawRectangleFilled(x0 + y, y0 + x, x0 + y+textsize, y0 + x+textsize, color);
      drawRectangleFilled(x0 - y, y0 + x, x0 - y+textsize, y0 + x+textsize, color);
      drawRectangleFilled(x0 + y, y0 - x, x0 + y+textsize, y0 - x+textsize, color);
      drawRectangleFilled(x0 - y, y0 - x, x0 - y+textsize, y0 - x+textsize, color);
      }
    }
  return 1;
	}

unsigned char drawEllipseFilled(WORD x0, WORD y0, WORD rx, WORD ry, BYTE color) {
  short int x,y;
	WORD largestX = rx;
	DWORD radius2=rx*ry;
  
	// https://stackoverflow.com/questions/10322341/simple-algorithm-for-drawing-filled-ellipse-in-c-c
	int hh = ry * ry;
	int ww = rx * rx;
	int hhww = hh * ww;
	int x2 = rx;
	int dx = 0;

	// do the horizontal diameter 
	drawLine(x0-rx, y0, x0+rx, y0, color);
/*	for(x=-rx; x <= rx; x++) {
		(*drawPixelPtr)(x0+x, y0, color);
		}*/

// now do both halves at the same time, away from the diameter
	for(y=1; y <= ry; y++) {
    int x1 = x2 - (dx - 1);  // try slopes of dx - 1 or more
    for( ; x1 > 0; x1--)
      if(x1*x1*hh + y*y*ww <= hhww)
        break;

    dx = x2 - x1;  // current approximation of the slope
    x2 = x1;

		drawLine(x0-x2, y0+y, x0+x2, y0+y, color);
		drawLine(x0-x2, y0-y, x0+x2, y0-y, color);
/*    for(x=-x2; x <= x2; x++) {
				(*drawPixelPtr)(x0+x, y0+y, color);
				(*drawPixelPtr)(x0+x, y0-y, color);
			}*/
		}

return 1;

  }
unsigned char drawCircleFilled(WORD x0, WORD y0, WORD r, BYTE color) {
  short int x,y;
	WORD largestX = r;
	DWORD radius2=r*r;


//https://stackoverflow.com/questions/1201200/fast-algorithm-for-drawing-filled-circles
	for(y=0; y <= r; ++y) {
		DWORD y2=y*y;
    for(x=largestX; x >= 0; --x) {
			if((x * x) + y2 <= radius2) {
        short int xn,yn;
        xn=max((short int)x0-x,0);     // drawLine si schianta (credo loop infinito) se x negativo (che non può accettare!)
        yn=max((short int)y0-y,0);
				drawLine(xn, y0 + y, x0 + x, y0 + y, color);		// VERIFICARE! manca il 4° parm (coglione)
				drawLine(xn, yn, x0 + x, yn, color);
				largestX = x;
				break; // go to next y coordinate
				}
			}
		}

  return 1;
	}

#define MAX_FILL_STACK 500  //1000 con 1000 si schianta ancora... ah ovvio, per ogni chiamata sono 64 byte (v.disassembly..)
struct POINTS {
	WORD x,y;
	};
unsigned char floodFill(WORD x, WORD y, BYTE color, BYTE colorBorder, BYTE mode) {
  BYTE up,down;
  BYTE bg;
  struct POINTS pt;
	// provare non ricorsive https://stackoverflow.com/questions/1257117/a-working-non-recursive-floodfill-algorithm-written-in-c
	// https://medium.com/100-days-of-algorithms/day-82-flood-fill-ae03faa491c3
	// https://en.wikipedia.org/wiki/Flood_fill#Walk-based_filling_(Fixed-memory_method)
	// o usare color statico (salvare/recuperare textcolor) per non passarlo alla ricorsione!
  
//	fill_color=color;
//  stackdepth=0;
  
	if(mode) {
    
//    def flood_fill(x, y, canvas, color, bg=None):
    bg = colorBorder;// if bg is None else bg
    struct POINTS stack[MAX_FILL_STACK];
    //in generale sembra andare bene, 3/10/22; VERIFICARE la versione "colore del bordo"...
    int stack_ptr=0;
    
    pt.x=x; pt.y=y;
    stack[stack_ptr++]=pt;
    while(stack_ptr>0) {
      pt = stack[--stack_ptr];
      if(getPixel(pt.x,pt.y) != bg)
        continue;
      // find left boundary
      while(pt.x > 0 && getPixel(pt.x-1,pt.y) != bg)
        pt.x--;        
      // scan to right
      up=TRUE; down=TRUE;
      while(pt.x < X_SIZE && getPixel(pt.x,pt.y) != bg) {
        drawPixel(pt.x,pt.y,color);
    // detect color change above
        if((pt.y+1) < Y_SIZE) {
          if(up && getPixel(pt.x,pt.y+1) != bg) {
            struct POINTS pt2;
            pt2.x=pt.x; pt2.y=pt.y+1;
            stack[stack_ptr++]=pt2;
//                    stack.append((pt.x+1, pt.y));
            }
          up = getPixel(pt.x,pt.y+1) == bg;
          }
    // detect color change below
        if(pt.y>0) {
          if(down && getPixel(pt.x,pt.y-1) != bg) {
            struct POINTS pt2;
            pt2.x=pt.x; pt2.y=pt.y-1;
            stack[stack_ptr++]=pt2;
//                    stack.append((pt.x-1, pt.y));
            }
          down = getPixel(pt.x, pt.y-1) == bg;       
          }
        pt.x++;
        }
      if(stack_ptr>=MAX_FILL_STACK)
        return 0;
      }

  	return 1;
    }
  else {

    pt.x=x; pt.y=y;
    bg = getPixel(pt.x,pt.y);// if bg is None else bg
    struct POINTS stack[MAX_FILL_STACK];
    //sembra andare bene, 3/10/22: 500 dovrebbe bastare.. ogni cambio direzione conta 1...
    int stack_ptr=0;
    
    stack[stack_ptr++]=pt;
    while(stack_ptr>0) {
      pt = stack[--stack_ptr];
      if(getPixel(pt.x,pt.y) != bg)
        continue;
      // find left boundary
      while(pt.x > 0 && getPixel(pt.x-1,pt.y) == bg)
        pt.x--;        
      // scan to right
      up=TRUE; down=TRUE;
      while(pt.x < X_SIZE && getPixel(pt.x,pt.y) == bg) {
        drawPixel(pt.x,pt.y,color);
    // detect color change above
        if((pt.y+1) < Y_SIZE) {
          if(up && getPixel(pt.x,pt.y+1) == bg) {
            struct POINTS pt2;
            pt2.x=pt.x; pt2.y=pt.y+1;
            stack[stack_ptr++]=pt2;
//                    stack.append((pt.x+1, pt.y));
            }
          up = getPixel(pt.x,pt.y+1) != bg;
          }
    // detect color change below
        if(pt.y>0) {
          if(down && getPixel(pt.x,pt.y-1) == bg) {
            struct POINTS pt2;
            pt2.x=pt.x; pt2.y=pt.y-1;
            stack[stack_ptr++]=pt2;
//                    stack.append((pt.x-1, pt.y));
            }
          down = getPixel(pt.x, pt.y-1) != bg;       
          }
        pt.x++;
        }
      if(stack_ptr>=MAX_FILL_STACK)
        return 0;
      }

  return 1;
  }


  return 1;
  }

void _swap(WORD *a, WORD *b) {
	WORD t = *a; 
	*a = *b; 
	*b = t; 
	}


// Draw a character
void drawChar(WORD x, WORD y, unsigned char c, BYTE color, BYTE bg, BYTE size) {
	INT8 i,j;
	BYTE *fontPtr;

    if((x >= X_SIZE)            || // Clip right
       (y >= Y_SIZE)           || // Clip bottom
       ((x + 4 * size - 1) < 0) || // Clip left
       ((y + 6 * size - 1) < 0))   // Clip top
      return;

    fontPtr=(BYTE *)font4x6_basic+((UINT16)c)*6;
    for(i=0; i<6; i++) {
      BYTE line;
			line = *(fontPtr+i);
      for(j=0; j<8; j++, line <<= 1) {
        if(line & 0x80) {
          if(size == 1) 
						drawPixel(x+j, y+i, color);
          else
		        drawRectangleFilled(x+(j*size), y+(i*size), size, size, color);
        	} 
				else if(bg != color) {
          if(size == 1) 
						drawPixel(x+j, y+i, bg);
          else          
						drawRectangleFilled(x+(j*size), y+(i*size), size, size, bg);
      	  }
    	  }
  	  }

	}

size_t cwrite(BYTE c) {

    switch(c) {
      case '\n':
        cursor_y += 6;
        cursor_x  = 0;
        break;
      case '\r':
        break;
      // skip em
      default:
        if(((cursor_x + 4) >= X_SIZE)) { 	// Heading off edge?
          cursor_x  = 0;            // Reset x to zero
          cursor_y += 6; // Advance y one line
          }
        drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
        cursor_x += 4;
        break;
    	}

  return 1;
	}

