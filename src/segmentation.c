#include"segmentation.h"
#include"pixelBMP.h"





/*void segmentation_ligne(SDL_Surface *image, SDL_PixelFormat *fmt)
{

    int i,j;
    int line = 0;// mark the presence of line, here it has not
    int black = 0;// mark the presence of black pixel
    int begin;// line of the beginning of black pixel's presence
    int end;// line of end of it
    for(i=0;i<image->w;i++)
    {
        for(j=0;i<image->h;j++)
        {
            Uint8 r,g,b;
            SDL_GetRGB(getpixel(image,i,j),fmt,&r,&g,&b);
            if(r == 0)
            {
                black=1;
                break;
            }
        }
        if(black && !line)
        {
            line=1;
            begin=j;

            for(i=0;i<image->w;i++)
            {
                int pos = j-1;
                if(pos>=0)
                {
                    putpixel(image,i,pos,SDL_MapRGB(fmt,0,0,0));
                }
            }
        }
        if(!black && line)
        {
            line =0;
            end=j;
            for(i=0;i<image->w;i++)
            {
                int pos =j+1;
                if(pos<image->h)
                {
                    putpixel(image,i,j,SDL_MapRGB(fmt,0,0,0));
                }
            }
            segmentation_columns(image,begin,end,fmt);
        }
        black=0;
    }
}

void segmentation_columns(SDL_Surface* image, int begin_line, int
end_line,SDL_PixelFormat *fmt)
{

    int end_c = 0;// mark the end of an encounter with a caracter
    int black = 0;// trace first line of the caracter
    int end_black = 0;// trace last line of the caracter
    int white = 0;// if all this columns is white

    //loop from b_line to e_line
    //in wich there is another loop for all the columns

    for(int x = 0; x <image-> w; x++)// through the columns
    {
        white = 1;

        for(int y = begin_line; y < end_line; y++)// through the lines
        {
            Uint8 r,g,b;
            SDL_GetRGB(getpixel(image,x,y),fmt, &r, &g, &b);

            if(r==0 && end_c==0)// first encounter with a cararcter
            {
                end_c = 1;// the begin of caracter is here
                black = 1;// must trace first line
                break;
            }
            if(r==0)// if the caracter in not finished yet
            {
                white = 0;
                break;
            }
            // had encountered a character but now it's its end with y,
            // also verify if this column has not black pixel
            // with the white satement
            if(b == 255 && end_c==1 && white==1 && y == end_line - 1)
            {
                end_c = 0;// the end of caracter is here
                end_black = 1;// must trace the last line
                break;
            }
        }

        if(end_c==1 && black==1)// color the previous column of the caracter
        {
            black = 0;// first line was traced, so make back the statement
            for(int y = begin_line; y < end_line; y++)
            {
                if(x - 1 > 0)//previous column
                {
                    //change color of column
                    putpixel(image, x - 1, y, SDL_MapRGB(fmt, 0,
                    0,0));

                }
            }
        }
        if(end_c==0 && end_black==1)// color the next column of the caracter
        {
            end_black = 0;// last line was traced, so make back the statement
            for(int y = begin_line; y < end_line; y++)
            {
                putpixel(image, x, y,SDL_MapRGB(fmt, 0,0,0));
            }
        }
    }
}*/
