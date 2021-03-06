/* 
 * File:   opencv_demo.c
 * Author: Tasanakorn
 *
 * Created on May 22, 2013, 1:52 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include <opencv2/core/core_c.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "bcm_host.h"
#include "interface/vcos/vcos.h"

#include "interface/mmal/mmal.h"
#include "interface/mmal/util/mmal_default_components.h"
#include "interface/mmal/util/mmal_connection.h"

#include "vgfont.h"

#include "demo_dmp.h"

//#define Mmal_Graphic_1
#define Mmal_Graphic_2
//#define VC_Dispmanx

#ifdef VC_Dispmanx 
#include <stdarg.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#endif

#ifdef Mmal_Graphic_2
#include "MPU6050_Widget.h"
#endif

#define VIDEO_FPS 30 
#define VIDEO_WIDTH 1280
#define VIDEO_HEIGHT 720

#define MMAL_CAMERA_PREVIEW_PORT 0
#define MMAL_CAMERA_VIDEO_PORT 1
#define MMAL_CAMERA_CAPTURE_PORT 2

typedef struct {
    int video_width;
    int video_height;
    int preview_width;
    int preview_height;
    int opencv_width;
    int opencv_height;
    float video_fps;
    MMAL_POOL_T *camera_video_port_pool;
    CvHaarClassifierCascade *cascade;
    CvMemStorage* storage;
    IplImage* image;
    IplImage* image2;
    VCOS_SEMAPHORE_T complete_semaphore;
} PORT_USERDATA;

#ifdef VC_Dispmanx 
#define WIDTH   200
#define HEIGHT  200

#ifndef ALIGN_UP
#define ALIGN_UP(x,y)  ((x + (y)-1) & ~((y)-1))
#endif

typedef struct
{
    DISPMANX_DISPLAY_HANDLE_T   display;
    DISPMANX_MODEINFO_T         info;
    void                       *image;
    DISPMANX_UPDATE_HANDLE_T    update;
    DISPMANX_RESOURCE_HANDLE_T  resource;
    DISPMANX_ELEMENT_HANDLE_T   element;
    uint32_t                    vc_image_ptr;

} RECT_VARS_T;

static RECT_VARS_T  gRectVars;

static void FillRect( VC_IMAGE_TYPE_T type, void *image, int pitch, int aligned_height, int x, int y, int w, int h, int val )
{
    int         row;
    int         col;

    uint16_t *line = (uint16_t *)image + y * (pitch>>1) + x;

    for ( row = 0; row < h; row++ )
    {
        for ( col = 0; col < w; col++ )
        {
            line[col] = val;
        }
        line += (pitch>>1);
    }
}
#endif

static void video_buffer_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer) {
    static int frame_count = 0;
    static int frame_post_count = 0;
    static struct timespec t1;
    struct timespec t2;
    MMAL_BUFFER_HEADER_T *new_buffer;
    PORT_USERDATA * userdata = (PORT_USERDATA *) port->userdata;
    MMAL_POOL_T *pool = userdata->camera_video_port_pool;

    if (frame_count == 0) {
        clock_gettime(CLOCK_MONOTONIC, &t1);
    }
    frame_count++;

    //img = cvLoadImage("test.jpg",CV_LOAD_IMAGE_COLOR);
    mmal_buffer_header_mem_lock(buffer);
    memcpy(userdata->image->imageData, buffer->data, userdata->video_width * userdata->video_height);
    mmal_buffer_header_mem_unlock(buffer);
    //printf("img = %d w=%d, h=%d\n", img, img->width, img->height);

    if (vcos_semaphore_trywait(&(userdata->complete_semaphore)) != VCOS_SUCCESS) {
        vcos_semaphore_post(&(userdata->complete_semaphore));
        frame_post_count++;
    }

    if (frame_count % 10 == 0) {
        // print framerate every n frame
        clock_gettime(CLOCK_MONOTONIC, &t2);
        float d = (t2.tv_sec + t2.tv_nsec / 1000000000.0) - (t1.tv_sec + t1.tv_nsec / 1000000000.0);
        float fps = 0.0;

        if (d > 0) {
            fps = frame_count / d;
        } else {
            fps = frame_count;
        }
        userdata->video_fps = fps;
        printf("  Frame = %d, Frame Post %d, Framerate = %.0f fps \n", frame_count, frame_post_count, fps);
    }

    mmal_buffer_header_release(buffer);
    // and send one back to the port (if still open)
    if (port->is_enabled) {
        MMAL_STATUS_T status;

        new_buffer = mmal_queue_get(pool->queue);

        if (new_buffer)
            status = mmal_port_send_buffer(port, new_buffer);

        if (!new_buffer || status != MMAL_SUCCESS)
            printf("Unable to return a buffer to the video port\n");
    }
}

int main(int argc, char** argv) {
    MMAL_COMPONENT_T *camera = 0;
    MMAL_COMPONENT_T *preview = 0;
    MMAL_ES_FORMAT_T *format;
    MMAL_STATUS_T status;
    MMAL_PORT_T *camera_preview_port = NULL, *camera_video_port = NULL, *camera_still_port = NULL;
    MMAL_PORT_T *preview_input_port = NULL;
    MMAL_POOL_T *camera_video_port_pool;
    MMAL_CONNECTION_T *camera_preview_connection = 0;
    PORT_USERDATA userdata;
    int display_width, display_height;
    float pYawPitchRoll[3];

    printf("Running...\n");

    setupMPU6050DMP();
    bcm_host_init();

    userdata.preview_width = VIDEO_WIDTH / 1;
    userdata.preview_height = VIDEO_HEIGHT / 1;
    userdata.video_width = VIDEO_WIDTH / 1;
    userdata.video_height = VIDEO_HEIGHT / 1;
    userdata.opencv_width = VIDEO_WIDTH / 1;
    userdata.opencv_height = VIDEO_HEIGHT / 1;

    graphics_get_display_size(0, &display_width, &display_height);

#ifdef Mmal_Graphic_1
    float r_w, r_h;
    r_w = (float) display_width / (float) userdata.opencv_width;
    r_h = (float) display_height / (float) userdata.opencv_height;
#endif

    printf("Display resolution = (%d, %d)\n", display_width, display_height);

    /* setup opencv */
    userdata.cascade = (CvHaarClassifierCascade*) cvLoad("/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml", NULL, NULL, NULL);
    userdata.storage = cvCreateMemStorage(0);
    userdata.image = cvCreateImage(cvSize(userdata.video_width, userdata.video_height), IPL_DEPTH_8U, 1);
    userdata.image2 = cvCreateImage(cvSize(userdata.opencv_width, userdata.opencv_height), IPL_DEPTH_8U, 1);

    if (!userdata.cascade) {
        printf("Error: unable to load harrcascade\n");
    }
    //printf("Load cascade at %d\n", userdata.cascade);

    status = mmal_component_create(MMAL_COMPONENT_DEFAULT_CAMERA, &camera);
    if (status != MMAL_SUCCESS) {
        printf("Error: create camera %x\n", status);
        return -1;
    }

    camera_preview_port = camera->output[MMAL_CAMERA_PREVIEW_PORT];
    camera_video_port = camera->output[MMAL_CAMERA_VIDEO_PORT];
    camera_still_port = camera->output[MMAL_CAMERA_CAPTURE_PORT];

    {
        MMAL_PARAMETER_CAMERA_CONFIG_T cam_config = {
            { MMAL_PARAMETER_CAMERA_CONFIG, sizeof (cam_config)},
            .max_stills_w = VIDEO_WIDTH,
            .max_stills_h = VIDEO_HEIGHT,
            .stills_yuv422 = 0,
            .one_shot_stills = 0,
            .max_preview_video_w = VIDEO_WIDTH,
            .max_preview_video_h = VIDEO_HEIGHT,
            .num_preview_video_frames = 2,
            .stills_capture_circular_buffer_height = 0,
            .fast_preview_resume = 1,
            .use_stc_timestamp = MMAL_PARAM_TIMESTAMP_MODE_RESET_STC
        };

        mmal_port_parameter_set(camera->control, &cam_config.hdr);
    }

    format = camera_video_port->format;

    format->encoding = MMAL_ENCODING_I420;
    format->encoding_variant = MMAL_ENCODING_I420;

    format->es->video.width = userdata.video_width;
    format->es->video.height = userdata.video_width;
    format->es->video.crop.x = 0;
    format->es->video.crop.y = 0;
    format->es->video.crop.width = userdata.video_width;
    format->es->video.crop.height = userdata.video_height;
    format->es->video.frame_rate.num = VIDEO_FPS;
    format->es->video.frame_rate.den = 1;

    camera_video_port->buffer_size = userdata.preview_width * userdata.preview_height * 12 / 8;
    camera_video_port->buffer_num = 1;
    printf("  Camera video buffer_size = %d\n", camera_video_port->buffer_size);

    status = mmal_port_format_commit(camera_video_port);

    if (status != MMAL_SUCCESS) {
        printf("Error: unable to commit camera video port format (%u)\n", status);
        return -1;
    }

    format = camera_preview_port->format;

    format->encoding = MMAL_ENCODING_OPAQUE;
    format->encoding_variant = MMAL_ENCODING_I420;

    format->es->video.width = userdata.preview_width;
    format->es->video.height = userdata.preview_height;
    format->es->video.crop.x = 0;
    format->es->video.crop.y = 0;
    format->es->video.crop.width = userdata.preview_width;
    format->es->video.crop.height = userdata.preview_height;

    status = mmal_port_format_commit(camera_preview_port);

    if (status != MMAL_SUCCESS) {
        printf("Error: camera viewfinder format couldn't be set\n");
        return -1;
    }

    // create pool form camera video port
    camera_video_port_pool = (MMAL_POOL_T *) mmal_port_pool_create(camera_video_port, camera_video_port->buffer_num, camera_video_port->buffer_size);
    userdata.camera_video_port_pool = camera_video_port_pool;
    camera_video_port->userdata = (struct MMAL_PORT_USERDATA_T *) &userdata;

    status = mmal_port_enable(camera_video_port, video_buffer_callback);
    if (status != MMAL_SUCCESS) {
        printf("Error: unable to enable camera video port (%u)\n", status);
        return -1;
    }

    status = mmal_component_enable(camera);

    status = mmal_component_create(MMAL_COMPONENT_DEFAULT_VIDEO_RENDERER, &preview);
    if (status != MMAL_SUCCESS) {
        printf("Error: unable to create preview (%u)\n", status);
        return -1;
    }
    preview_input_port = preview->input[0];

    {
        MMAL_DISPLAYREGION_T param;
        param.hdr.id = MMAL_PARAMETER_DISPLAYREGION;
        param.hdr.size = sizeof (MMAL_DISPLAYREGION_T);
        param.set = MMAL_DISPLAY_SET_LAYER;
        param.layer = 0;
        param.set |= MMAL_DISPLAY_SET_FULLSCREEN;
        param.fullscreen = 1;
        status = mmal_port_parameter_set(preview_input_port, &param.hdr);
        if (status != MMAL_SUCCESS && status != MMAL_ENOSYS) {
            printf("Error: unable to set preview port parameters (%u)\n", status);
            return -1;
        }
    }

    status = mmal_connection_create(&camera_preview_connection, camera_preview_port, preview_input_port, MMAL_CONNECTION_FLAG_TUNNELLING | MMAL_CONNECTION_FLAG_ALLOCATION_ON_INPUT);
    if (status != MMAL_SUCCESS) {
        printf("Error: unable to create connection (%u)\n", status);
        return -1;
    }

    status = mmal_connection_enable(camera_preview_connection);
    if (status != MMAL_SUCCESS) {
        printf("Error: unable to enable connection (%u)\n", status);
        return -1;
    }

    if (1) {
        // Send all the buffers to the camera video port
        int num = mmal_queue_length(camera_video_port_pool->queue);
        int q;

        for (q = 0; q < num; q++) {
            MMAL_BUFFER_HEADER_T *buffer = mmal_queue_get(camera_video_port_pool->queue);

            if (!buffer) {
                printf("Unable to get a required buffer %d from pool queue\n", q);
            }

            if (mmal_port_send_buffer(camera_video_port, buffer) != MMAL_SUCCESS) {
                printf("Unable to send a buffer to encoder output port (%d)\n", q);
            }
        }
    }

    if (mmal_port_parameter_set_boolean(camera_video_port, MMAL_PARAMETER_CAPTURE, 1) != MMAL_SUCCESS) {
        printf("%s: Failed to start capture\n", __func__);
    }

    vcos_semaphore_create(&userdata.complete_semaphore, "mmal_opencv_demo-sem", 0);

#ifdef Mmal_Graphic_1
    int opencv_frames = 0;
    struct timespec t1;
    struct timespec t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);
#endif

#ifdef Mmal_Graphic_1
    GRAPHICS_RESOURCE_HANDLE img_overlay;
    GRAPHICS_RESOURCE_HANDLE img_overlay2;

    gx_graphics_init("/opt/vc/src/hello_pi/hello_font");

    gx_create_window(0, 640, 480, GRAPHICS_RESOURCE_RGBA32, &img_overlay);//userdata.opencv_width,userdata.opencv_height
    gx_create_window(0, display_width, 200, GRAPHICS_RESOURCE_RGBA32, &img_overlay2);
    graphics_resource_fill(img_overlay, 0, 0, GRAPHICS_RESOURCE_WIDTH, GRAPHICS_RESOURCE_HEIGHT, GRAPHICS_RGBA32(0xff, 0, 0, 0x55));
    graphics_resource_fill(img_overlay2, 0, 0, GRAPHICS_RESOURCE_WIDTH, GRAPHICS_RESOURCE_HEIGHT, GRAPHICS_RGBA32(0xff, 0, 0, 0x55));

    graphics_display_resource(img_overlay, 0, 1, 0, 0, display_width, display_height, VC_DISPMAN_ROT0, 1);
    char text[256];

    while (1) {
        GetMPU6050Data(pYawPitchRoll,NULL,NULL);
        if (vcos_semaphore_wait(&(userdata.complete_semaphore)) == VCOS_SUCCESS) {
            opencv_frames++;
            float fps = 0.0;
            if (1) {
                clock_gettime(CLOCK_MONOTONIC, &t2);
                float d = (t2.tv_sec + t2.tv_nsec / 1000000000.0) - (t1.tv_sec + t1.tv_nsec / 1000000000.0);
                if (d > 0) {
                    fps = opencv_frames / d;
                } else {
                    fps = opencv_frames;
                }

                printf("  OpenCV Frame = %d, Framerate = %.2f fps \n", opencv_frames, fps);
            }

            graphics_resource_fill(img_overlay, 0, 0, GRAPHICS_RESOURCE_WIDTH, GRAPHICS_RESOURCE_HEIGHT, GRAPHICS_RGBA32(0, 0, 0, 0x00));
            graphics_resource_fill(img_overlay2, 0, 0, GRAPHICS_RESOURCE_WIDTH, GRAPHICS_RESOURCE_HEIGHT, GRAPHICS_RGBA32(0, 0, 0, 0x00));

            if (1) {
                cvResize(userdata.image, userdata.image2, CV_INTER_LINEAR);
                CvSeq* objects = cvHaarDetectObjects(userdata.image2, userdata.cascade, userdata.storage, 1.4, 3, 0, cvSize(100, 100), cvSize(150, 150));
                CvRect* r;
                // Loop through objects and draw boxes
                if (objects != 0) {
                    if (objects->total > 0) {
                        int ii;
                        for (ii = 0; ii < objects->total; ii++) {
                            r = (CvRect*) cvGetSeqElem(objects, ii);

                            printf("  Face %d [%d, %d, %d, %d] [%d, %d, %d, %d]\n", ii, r->x, r->y, r->width, r->height, (int) ((float) r->x * r_w), (int) (r->y * r_h), (int) (r->width * r_w), (int) (r->height * r_h));

                            //graphics_resource_fill(img_overlay, r->x * r_w, r->y * r_h, r->width * r_w, r->height * r_h, GRAPHICS_RGBA32(0xff, 0, 0, 0x88));
                            //graphics_resource_fill(img_overlay, r->x * r_w + 8, r->y * r_h + 8, r->width * r_w - 16 , r->height * r_h - 16, GRAPHICS_RGBA32(0, 0, 0, 0x00));
                            graphics_resource_fill(img_overlay, r->x, r->y, r->width, r->height, GRAPHICS_RGBA32(0xff, 0, 0, 0x88));
                            graphics_resource_fill(img_overlay, r->x + 4, r->y + 4, r->width - 8, r->height - 8, GRAPHICS_RGBA32(0, 0, 0, 0x00));
                        }
                    } else {
                        //printf("No Face detected\n");
                    }
                } else {
                    printf("!! Face detectiona failed !!\n");
                }
            }
            sprintf(text, "Video = %.2f FPS, OpenCV = %.2f FPS - Yaw=%f, Pitch=%f, Roll=%f", userdata.video_fps, fps, pYawPitchRoll[0], pYawPitchRoll[1],pYawPitchRoll[2]);
            graphics_resource_render_text_ext(img_overlay2, 0, 0,
                    GRAPHICS_RESOURCE_WIDTH,
                    GRAPHICS_RESOURCE_HEIGHT,
                    GRAPHICS_RGBA32(0x00, 0xff, 0x00, 0xff), /* fg */
                    GRAPHICS_RGBA32(0, 0, 0, 0x00), /* bg */
                    text, strlen(text), 25);

	     //Green 
            graphics_resource_fill(img_overlay2, 0, 20, GRAPHICS_RESOURCE_WIDTH, 1, GRAPHICS_RGBA32(0,0xff,0,0xff));
			
            graphics_display_resource(img_overlay, 0, 1, 0, 0, display_width, display_height, VC_DISPMAN_ROT0, 1);
            graphics_display_resource(img_overlay2, 0, 2, 0, display_width / 16, GRAPHICS_RESOURCE_WIDTH, GRAPHICS_RESOURCE_HEIGHT, VC_DISPMAN_ROT0, 1);
        }
    }
#endif	
#ifdef Mmal_Graphic_2
    GRAPHICS_RESOURCE_HANDLE img_overlay1;
    GRAPHICS_RESOURCE_HANDLE img_overlay2;

    gx_graphics_init("/opt/vc/src/hello_pi/hello_font");

    set_display_screen(display_width, display_height);
    gx_create_window(0, display_width, display_height, GRAPHICS_RESOURCE_RGBA32, &img_overlay1);//userdata.opencv_width,userdata.opencv_height
    gx_create_window(0, display_width, display_height, GRAPHICS_RESOURCE_RGBA32, &img_overlay2);

    char text[256];
    uint32_t center_x=display_width/2, center_y=display_height/2;

   graphics_resource_fill(img_overlay1, 0, 0, GRAPHICS_RESOURCE_WIDTH, GRAPHICS_RESOURCE_HEIGHT, GRAPHICS_RGBA32(0, 0, 0, 0x00));
   //Yaw
   draw_ruler(img_overlay1, Yaw_1_left_top_x, Yaw_1_left_top_y, Yaw_1_right_down_x, Yaw_1_right_down_y, 0, Yaw_1_Ruler_Total_Number, Yaw_1_Ruler_Number_Mark, Yaw_1_Axis, GRAPHICS_RGBA32(0xff,0x00,0x00,0xff));
   //Pitch
   draw_ruler(img_overlay1, Pitch_1_left_top_x, Pitch_1_left_top_y, Pitch_1_right_down_x, Pitch_1_right_down_y, 0, Pitch_1_Ruler_Total_Number, Pitch_1_Ruler_Number_Mark, Pitch_1_Axis, GRAPHICS_RGBA32(0xff,0x00,0x00,0xff));
   //Roll
   draw_circle(img_overlay1, center_x, center_y, 50, 2, GRAPHICS_RGBA32(0xff,0x00,0x00,0xff));
   draw_rect(img_overlay1, center_x-Roll_1_left_top_x, center_y-Roll_1_left_top_y, center_x+Roll_1_right_down_x, center_y+Roll_1_right_down_y, 3, GRAPHICS_RGBA32(0x00,0xff,0x00,0xff));   
  
   graphics_display_resource(img_overlay1, 0, IMAGE1_Z_Order, IMAGE1_Display_Offset_x, IMAGE1_Display_Offset_y, GRAPHICS_RESOURCE_WIDTH, GRAPHICS_RESOURCE_HEIGHT, VC_DISPMAN_ROT0, 1);
   
    while (1) {
	GetMPU6050Data(pYawPitchRoll, NULL, NULL);

	if (vcos_semaphore_wait(&(userdata.complete_semaphore)) == VCOS_SUCCESS) {

	     graphics_resource_fill(img_overlay2, 0, 0, GRAPHICS_RESOURCE_WIDTH, GRAPHICS_RESOURCE_HEIGHT, GRAPHICS_RGBA32(0, 0, 0, 0x00));

	     //Yaw
            sprintf(text, "Yaw=%3.2f", pYawPitchRoll[0]);
	     graphics_resource_render_text_ext(img_overlay2, Yaw_1_Text_left_top_x, Yaw_1_Text_left_top_y,
                    GRAPHICS_RESOURCE_WIDTH,
                    GRAPHICS_RESOURCE_HEIGHT,
                    GRAPHICS_RGBA32(0xff, 0x00, 0x00, 0xff), // fg
                    GRAPHICS_RGBA32(0, 0, 0, 0x00), // bg
                    text, strlen(text), 25);

	     GetMPU6050Data(pYawPitchRoll, NULL, NULL);
	     //Pitch
            sprintf(text, "Pitch=%3.2f", pYawPitchRoll[1]);
	     graphics_resource_render_text_ext(img_overlay2, Pitch_1_Text_left_top_x, Pitch_1_Text_left_top_y,
                    GRAPHICS_RESOURCE_WIDTH,
                    GRAPHICS_RESOURCE_HEIGHT,
                    GRAPHICS_RGBA32(0xff, 0x00, 0x00, 0xff), // fg
                    GRAPHICS_RGBA32(0, 0, 0, 0x00), // bg
                    text, strlen(text), 25);

	     GetMPU6050Data(pYawPitchRoll, NULL, NULL);
	     //Roll
//	     rotation_draw_rect(img_overlay2, center_x-Roll_1_left_top_x, center_y-Roll_1_left_top_y-IMAGE2_Display_Offset_y, center_x+Roll_1_right_down_x, center_y+Roll_1_right_down_y-IMAGE2_Display_Offset_y, 3, GRAPHICS_RGBA32(0x00,0xff,0x00,0xff), 30);
            sprintf(text, "Roll=%3.2f", pYawPitchRoll[2]);
	     graphics_resource_render_text_ext(img_overlay2, center_x+Roll_1_Text_left_top_x, center_y+Roll_1_Text_left_top_y,
                    GRAPHICS_RESOURCE_WIDTH,
                    GRAPHICS_RESOURCE_HEIGHT,
                    GRAPHICS_RGBA32(0xff, 0x00, 0x00, 0xff), // fg
                    GRAPHICS_RGBA32(0, 0, 0, 0x00), // bg
                    text, strlen(text), 25);

	     graphics_display_resource(img_overlay2, 0, IMAGE2_Z_Order, IMAGE2_Display_Offset_x, IMAGE2_Display_Offset_y, GRAPHICS_RESOURCE_WIDTH, GRAPHICS_RESOURCE_HEIGHT, VC_DISPMAN_ROT0, 1);
        }
	
    }
#endif
#ifdef VC_Dispmanx
    RECT_VARS_T	*vars;
    uint32_t		screen = 0;
    int			ret;
    VC_RECT_T	src_rect;
    VC_RECT_T	dst_rect;
    VC_IMAGE_TYPE_T	type = VC_IMAGE_RGB565;
    int width = WIDTH, height = HEIGHT;
    int pitch = ALIGN_UP(width*2, 32);
    int aligned_height = ALIGN_UP(height, 16);
    VC_DISPMANX_ALPHA_T	alpha = { DISPMANX_FLAGS_ALPHA_FROM_SOURCE | DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS, 
                             120, /*alpha 0->255*/
                             0 };

    vars = &gRectVars;

    printf("Open display[%i]...\n", screen );
    vars->display = vc_dispmanx_display_open( screen );

    ret = vc_dispmanx_display_get_info( vars->display, &vars->info);
    assert(ret == 0);
    printf( "Display is %d x %d\n", vars->info.width, vars->info.height );

    vars->image = calloc( 1, pitch * height );
    assert(vars->image);

    FillRect( type, vars->image, pitch, aligned_height,  0,  0, width,      height,      0xFFFF );
    FillRect( type, vars->image, pitch, aligned_height,  0,  0, width,      height,      0xF800 );
    FillRect( type, vars->image, pitch, aligned_height, 20, 20, width - 40, height - 40, 0x07E0 );
    FillRect( type, vars->image, pitch, aligned_height, 40, 40, width - 80, height - 80, 0x001F );

    vars->resource = vc_dispmanx_resource_create( type,
                                                  width,
                                                  height,
                                                  &vars->vc_image_ptr );
    assert( vars->resource );
    vc_dispmanx_rect_set( &dst_rect, 0, 0, width, height);
    ret = vc_dispmanx_resource_write_data(  vars->resource,
                                            type,
                                            pitch,
                                            vars->image,
                                            &dst_rect );
    assert( ret == 0 );
    vars->update = vc_dispmanx_update_start( 10 );
    assert( vars->update );

    vc_dispmanx_rect_set( &src_rect, 0, 0, width << 16, height << 16 );

    vc_dispmanx_rect_set( &dst_rect, ( vars->info.width - width ) / 2,
                                     (vars->info.height - height ) / 2,
                                     width,
                                     height );

    vars->element = vc_dispmanx_element_add(vars->update,
                                                vars->display,
                                                2000,               // layer
                                                &dst_rect,
                                                vars->resource,
                                                &src_rect,
                                                DISPMANX_PROTECTION_NONE,
                                                &alpha,
                                                NULL,             // clamp
                                                VC_IMAGE_ROT0 );

    ret = vc_dispmanx_update_submit_sync( vars->update );
    assert( ret == 0 );

    printf( "Sleeping for 10 seconds...\n" );
    sleep( 10 );

    vars->update = vc_dispmanx_update_start( 10 );
    assert( vars->update );
    ret = vc_dispmanx_element_remove( vars->update, vars->element );
    assert( ret == 0 );
    ret = vc_dispmanx_update_submit_sync( vars->update );
    assert( ret == 0 );
    ret = vc_dispmanx_resource_delete( vars->resource );
    assert( ret == 0 );
    ret = vc_dispmanx_display_close( vars->display );
    assert( ret == 0 );
#endif

    return 0;
}

