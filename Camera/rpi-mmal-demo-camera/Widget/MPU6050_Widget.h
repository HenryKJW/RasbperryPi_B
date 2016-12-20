#ifndef MPU6050_Widget_h
#define MPU6050_Widget_h

//---------------------------------Asix-------------------------------------------------------

#define Ruler_X					1
#define Ruler_Y					2
//---------------------------------static picture----------------------------------------------
#define IMAGE1_Z_Order			1 //bigger is front
#define IMAGE1_Display_Offset_x	0
#define IMAGE1_Display_Offset_y	0

//roll - Center point moive
#define Roll_1_left_top_x				100
#define Roll_1_left_top_y				100
#define Roll_1_right_down_x			100
#define Roll_1_right_down_y			100

#define Roll_1_Text_left_top_x		-70
#define Roll_1_Text_left_top_y		120

//yaw
#define Yaw_1_left_top_x				80
#define Yaw_1_left_top_y				50
#define Yaw_1_right_down_x			Yaw_1_left_top_x + 1400
#define Yaw_1_right_down_y			Yaw_1_left_top_y + 50
#define Yaw_1_Ruler_Total_Number	180
#define Yaw_1_Ruler_Number_Mark	10
#define Yaw_1_Axis					Ruler_X

#define Yaw_1_Text_left_top_x		Yaw_1_right_down_x/2 -130
#define Yaw_1_Text_left_top_y		Yaw_1_right_down_y

//pitch
#define Pitch_1_left_top_x			10
#define Pitch_1_left_top_y			80
#define Pitch_1_right_down_x			Pitch_1_left_top_x + 50
#define Pitch_1_right_down_y			Pitch_1_left_top_y + 800
#define Pitch_1_Ruler_Total_Number	180
#define Pitch_1_Ruler_Number_Mark	10
#define Pitch_1_Axis					Ruler_Y

#define Pitch_1_Text_left_top_x		Pitch_1_right_down_x
#define Pitch_1_Text_left_top_y		Pitch_1_right_down_y/2 -50

//#define IMAGE1_Display_WIDTH	IMAGE1_WIDTH
//#define IMAGE1_Display_HEIGHT	IMAGE1_HEIGHT

//----------------------------------Dyname picture-------------------------------------------
#define IMAGE2_Z_Order			2 //bigger is front
#define IMAGE2_Display_Offset_x	0
#define IMAGE2_Display_Offset_y	0

//#define IMAGE2_Display_WIDTH	IMAGE2_WIDTH
//#define IMAGE2_Display_HEIGHT	IMAGE2_HEIGHT

void set_display_screen(uint32_t display_width,uint32_t display_hight);
void draw_rect(GRAPHICS_RESOURCE_HANDLE res, uint32_t left_top_x, uint32_t left_top_y, uint32_t right_down_x, uint32_t right_down_y, uint32_t boardwidth, uint32_t fill_colour);
void rotation_draw_rect(GRAPHICS_RESOURCE_HANDLE res, uint32_t left_top_x, uint32_t left_top_y, uint32_t right_down_x, uint32_t right_down_y, uint32_t boardwidth, uint32_t fill_colour, uint32_t angle);
void draw_ruler(GRAPHICS_RESOURCE_HANDLE res, uint32_t left_top_x, uint32_t left_top_y, uint32_t right_down_x, uint32_t right_down_y, uint32_t boardwidth, uint32_t total_number, uint32_t number_mark, uint32_t ruler_axis, uint32_t fill_colour);

void draw_circle(GRAPHICS_RESOURCE_HANDLE res, uint32_t x, uint32_t y, uint32_t radius, uint32_t boardwidth, uint32_t fill_colour);

#endif
