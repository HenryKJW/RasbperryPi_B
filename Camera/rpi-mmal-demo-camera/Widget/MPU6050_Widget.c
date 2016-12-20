#include <stdio.h>
#include <stdlib.h>

#include "interface/vcos/vcos.h"

#include "interface/mmal/mmal.h"
#include "interface/mmal/util/mmal_default_components.h"
#include "interface/mmal/util/mmal_connection.h"

#include "vgfont.h"
#include "math.h"
#include "MPU6050_Widget.h"

static uint32_t  mpu6050_display_width, mpu6050_display_hight;

void set_display_screen(uint32_t display_width,uint32_t display_hight)
{
	mpu6050_display_width = display_width;
	mpu6050_display_hight = display_hight;
}

void draw_rect(GRAPHICS_RESOURCE_HANDLE res, uint32_t left_top_x, uint32_t left_top_y, uint32_t right_down_x, uint32_t right_down_y, uint32_t boardwidth, uint32_t fill_colour)
{
	graphics_resource_fill(res, left_top_x, left_top_y, right_down_x-left_top_x, boardwidth, fill_colour);
	graphics_resource_fill(res, left_top_x, left_top_y, boardwidth, right_down_y-left_top_y , fill_colour);
	graphics_resource_fill(res, left_top_x, right_down_y, right_down_x-left_top_x, boardwidth, fill_colour);
	graphics_resource_fill(res, right_down_x, left_top_y, boardwidth, right_down_y-left_top_y+boardwidth, fill_colour);
}

void draw_ruler(GRAPHICS_RESOURCE_HANDLE res, uint32_t left_top_x, uint32_t left_top_y, uint32_t right_down_x, uint32_t right_down_y, uint32_t boardwidth, uint32_t total_number, uint32_t number_mark, uint32_t ruler_axis, uint32_t fill_colour)
{
	uint32_t width, hight, draw_point;
	uint32_t i;

	width = right_down_x - left_top_x;
	hight  = right_down_y - left_top_y;

	if(ruler_axis==Ruler_X)
	{
		draw_point = width/total_number;

//	       printf("width=%d, hight=%d, draw_point=%d \n",width,hight,draw_point);

		for(i=0; i<=total_number; i++)
		{
			if(i%number_mark==0)
				graphics_resource_fill(res, left_top_x+(i*draw_point), left_top_y, 3, 20, fill_colour);
			else
				graphics_resource_fill(res, left_top_x+(i*draw_point), left_top_y, 1, 10, fill_colour);
		}
	}
	else if(ruler_axis==Ruler_Y)
	{
		draw_point = hight/total_number;

//	       printf("width=%d, hight=%d, draw_point=%d \n",width,hight,draw_point);

		for(i=0; i<=total_number; i++)
		{
			if(i%number_mark==0)
				graphics_resource_fill(res, left_top_x, left_top_y+(i*draw_point), 20, 3, fill_colour);
			else
				graphics_resource_fill(res, left_top_x, left_top_y+(i*draw_point), 10, 1, fill_colour);
		}
		
	}
}

void rotation_draw_rect(GRAPHICS_RESOURCE_HANDLE res, uint32_t left_top_x, uint32_t left_top_y, uint32_t right_down_x, uint32_t right_down_y, uint32_t boardwidth, uint32_t fill_colour, uint32_t angle)
{
	float rad=angle*(3.141596/180);
	float x,y,i;
	float cos_rad,sin_rad;
	float fcenter_x, fcenter_y;
	float counter_x, counter_y;

	x = right_down_x - left_top_x;//X lenght
	y = right_down_y - left_top_y;//Y lenght
	fcenter_x = left_top_x + x/2;//Center Point
	fcenter_y = left_top_y + y/2;
	
//	printf("left_top_x=%d, left_top_y=%d, right_down_x=%d, right_down_y=%d \n",left_top_x,left_top_y,right_down_x,right_down_y);
	counter_y = left_top_y -fcenter_y;
	cos_rad = cos(rad);
	sin_rad = sin(rad);
	for(i=left_top_x; i<right_down_x; i++)//top
	{
		counter_x = i -fcenter_x;		
		x = counter_x*cos_rad - counter_y*sin_rad;
		y = counter_y*cos_rad + counter_x*sin_rad;
		graphics_resource_fill(res, fcenter_x+x, fcenter_y+y, 1, boardwidth, fill_colour);
//		printf("ox=%f, oy=%f, x=%f, y=%f \n",i,,x,y);
	}
}

void draw_circle(GRAPHICS_RESOURCE_HANDLE res, uint32_t x, uint32_t y, uint32_t radius, uint32_t boardwidth, uint32_t fill_colour)
{
	float dx, dy;
	float r = radius * radius;

	graphics_resource_fill(res, x, y+radius, boardwidth, boardwidth, fill_colour);
	graphics_resource_fill(res, x, y-radius, boardwidth, boardwidth, fill_colour);
	graphics_resource_fill(res, x+radius, y, boardwidth, boardwidth, fill_colour);
	graphics_resource_fill(res, x-radius, y, boardwidth, boardwidth, fill_colour);

	dx=1;
	dy= sqrt((r - 1)+0.5);
	while(dx<dy)
	{
		graphics_resource_fill(res, x+dx, y+dy, boardwidth, boardwidth, fill_colour);
		graphics_resource_fill(res, x+dx, y-dy, boardwidth, boardwidth, fill_colour);
		graphics_resource_fill(res, x-dx, y+dy, boardwidth, boardwidth, fill_colour);
		graphics_resource_fill(res, x-dx, y-dy, boardwidth, boardwidth, fill_colour);
		graphics_resource_fill(res, x+dy, y+dx, boardwidth, boardwidth, fill_colour);
		graphics_resource_fill(res, x+dy, y-dx, boardwidth, boardwidth, fill_colour);
		graphics_resource_fill(res, x-dy, y+dx, boardwidth, boardwidth, fill_colour);
		graphics_resource_fill(res, x-dy, y-dx, boardwidth, boardwidth, fill_colour);
		dx+=1;
		dy= sqrt((r - dx*dx)+0.5);
	}
	if(dx==dy)
	{
		graphics_resource_fill(res, x+dx, y+dy, boardwidth, boardwidth, fill_colour);
		graphics_resource_fill(res, x+dx, y-dy, boardwidth, boardwidth, fill_colour);
		graphics_resource_fill(res, x-dx, y+dy, boardwidth, boardwidth, fill_colour);
		graphics_resource_fill(res, x-dx, y-dy, boardwidth, boardwidth, fill_colour);
	}
}
