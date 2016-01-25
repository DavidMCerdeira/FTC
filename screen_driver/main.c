
#include <linux/input.h>
#include <linux/uinput.h> /*uidev*/
#include <stdint.h>
#include <stdio.h> /*printf*/
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> /*ioctl*/
#include <string.h> /**/
#include <unistd.h> /*__bswap_16*/
#include <byteswap.h> /*swap*/

struct mouse
{
	int32_t lastX;
	int32_t lastY;
	int32_t deltaX;
	int32_t deltaY;
	int32_t x;
	int32_t y;
	
	int pressed;
};

struct uinput_user_dev uidev;

/*define configgurations*/
//#define CALIBRATE
#define SMALL_SCREEN
#define INSENSITIITY 3
/*end of define configgurations*/

#define device_message_size 22 /*this is in bytes*/

#define mouse_buffer_offset_x   1
#define mouse_buffer_offset_y   2
#define cmd_buffer_offset       0

#define button_pressed   426 //0x01aa
#define button_released  170 //0x00aa

#define screen_zero_offset_x 140
#define screen_zero_offset_y 370

#define screen_max_x     (3944)
#define screen_max_y     (3907)

#ifdef BIG_SCREEN
	#define abs_max_x        1900
	#define abs_max_y        1080
#else
#ifdef SMALL_SCREEN
	#define abs_max_x        799
	#define abs_max_y        480
#endif
#endif

#define abs(a) (((a) < 0) ? -(a) : (a))

/* this function parses buffer to obtain mouse movemnte details */
/* it also believes everything that buffer contains is true and beatiful */
void device_parser(uint16_t *buffer, struct mouse* mouse)
{
	int pressed = 0;

	/* last data */		
	mouse->lastX = mouse->x;
	mouse->lastY = mouse->y;
	
	/*bytes come swapped for some reason*/	
#ifdef CALIBRATE
		mouse->x = __bswap_16(buffer[mouse_buffer_offset_x]);
		mouse->y = __bswap_16(buffer[mouse_buffer_offset_y]);
		printf("CALIBRATION X: %d, Y: %d\n", mouse->x, mouse->y);
#else
	
	//*		 
	mouse->x = (__bswap_16(buffer[mouse_buffer_offset_x]) - screen_zero_offset_x) / 
										((double)screen_max_x - screen_zero_offset_x) * abs_max_x;
	mouse->y = (__bswap_16(buffer[mouse_buffer_offset_y]) - screen_zero_offset_y) / 
										((double)screen_max_y - screen_zero_offset_y) * abs_max_y;
	//*/
	
	/* update mouse information */
	mouse->deltaX = mouse->x - mouse->lastX;
	mouse->deltaY = mouse->y - mouse->lastY;

	
	if((mouse->x <= 0) || (mouse->x > abs_max_x) || (abs(mouse->deltaX) < INSENSITIITY)){
		mouse->x = mouse->lastX;
		mouse->deltaX = 0;
	}
	if((mouse->y <= 0) || (mouse->y > abs_max_y) || (abs(mouse->deltaY) < INSENSITIITY)){
		mouse->y = mouse->lastY;
		mouse->deltaY = 0;
	}	

	
	if(buffer[cmd_buffer_offset] == (uint16_t)button_pressed){
		pressed = 1;
	}else if(buffer[cmd_buffer_offset] == (uint16_t)button_released){
		pressed = 0;
	} else{
		pressed = -1;
	}
	
	mouse->pressed = pressed;
#endif
}

void send_events(int fd, struct mouse* mouse)
{
	int ret;
	struct input_event button;
	struct input_event mouse_movement[2];
	struct input_event ev;
	static int pressed = 0;

	/*It's important that we move first*/
	//*
	if(mouse->x > 0 && mouse->y > 0){
		memset(&mouse_movement, 0, sizeof(mouse_movement));
		mouse_movement[0].type = EV_ABS;
		mouse_movement[0].code = ABS_X;
		mouse_movement[0].value = mouse->x;
		mouse_movement[1].type = EV_ABS;
		mouse_movement[1].code = ABS_Y;
		mouse_movement[1].value = mouse->y;

		ret = write(fd, &mouse_movement, sizeof(mouse_movement));
		if(ret < 0){
			printf("Coudln't send mouse movement event...\n");
			exit(4);
		}

	}//*/
	
	memset(&ev, 0, sizeof(struct input_event));
	ev.type = EV_SYN;
	ev.code = 0;
	ev.value = 0;
	ret = write(fd, &ev, sizeof(struct input_event));
	if(ret < 0){
		printf("Coudln't send sync...\n");
		exit(4);
    }
    
	//*
	if((mouse->pressed == 1) && (!pressed)){
		pressed = 1;
		memset(&button, 0, sizeof(button));	
		button.type = EV_KEY;
		button.code = BTN_LEFT;
		button.value = 1;
		ret = write(fd, &button, sizeof(button));
		if(ret < 0){
			printf("Coudln't send button event...\n");
			exit(4);
		}	
	}else if(mouse->pressed == 0){
		pressed = 0;
		button.type = EV_KEY;
		button.code = BTN_LEFT;
		button.value = 0;
		ret = write(fd, &button, sizeof(button));
		if(ret < 0){
			printf("Coudln't send button event...\n");
			exit(4);
		}
	}
	//*/
	
	memset(&ev, 0, sizeof(struct input_event));
	ev.type = EV_SYN;
	ev.code = 0;
	ev.value = 0;
	ret = write(fd, &ev, sizeof(struct input_event));
	if(ret < 0){
		printf("Coudln't send sync...\n");
		exit(4);
    }
}

int uinput_init()
{
	int uFd;	

	int ret;
	
	uFd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
	if(uFd < 0){
		printf("Something went wrong opening uinput system...\n");
		return -1;
	}
	
	ret = ioctl(uFd, UI_SET_EVBIT, EV_KEY);
	ret = ioctl(uFd, UI_SET_KEYBIT, BTN_LEFT);
	ret = ioctl(uFd, UI_SET_EVBIT, EV_ABS);
	ret = ioctl(uFd, UI_SET_ABSBIT, ABS_X);
	ret = ioctl(uFd, UI_SET_ABSBIT, ABS_Y);

	uidev.absmin[ABS_X] = 0;
	uidev.absmax[ABS_X] = abs_max_x;
	uidev.absmin[ABS_Y] = 0;
	uidev.absmax[ABS_Y] = abs_max_y;

	memset(&uidev, 0, sizeof(uidev));
	snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "FTC_TouchScreen");
	uidev.id.bustype = BUS_USB;
	uidev.id.vendor  = 0x1234;
	uidev.id.product = 0xfedc;
	uidev.id.version = 1;
	
	ret = write(uFd, &uidev, sizeof(uidev));	
	if(ret < 0){
		printf("Something went wrong writing uidev...\n");
		return -1;
	}
	
	ret = ioctl(uFd, UI_DEV_CREATE);
	if(ret < 0){
		printf("Something went wrong creating uidev...\n");
		return -1;
	}
	return uFd;
}

void print_mouse_info(struct mouse *mouse)
{
	printf("X: %d\n"
		   "Y: %d\n"
		   "lastX: %d\n"
		   "lastY: %d\n"
		   "deltaX: %d\n"
		   "deltaY: %d\n"
		   "Pressed: %d\n\n",
		   mouse->x,
		   mouse->y,
		   mouse->lastX,
		   mouse->lastY,
		   mouse->deltaX,
		   mouse->deltaY,
		   mouse->pressed);
}


void emulate_mouse(int fd)
{
	struct mouse mouse = {0, 0, 0, 0, 0};
	ssize_t n_items;	
	int ret;
	int uFd;
	uint16_t buffer[100];

	
	uFd = uinput_init();

	if(uFd < 0)
		return;
		
	printf("Running\n");
	
	/* this will last for ever!!!! */
	while(1){
		/* this aproach is inflexible but we at FTC don't care about that kinda of things */
		n_items = read(fd, (void*)buffer, device_message_size);
		/*too much information or too little*/
		if(n_items != device_message_size){
			printf("Something went horribly wrong and you are to blame!\n");
			printf("We were still able to read %d\n items", (int)n_items);
			break;
		}

		device_parser(buffer, &mouse);
		#ifndef CALIBRATE
			send_events(uFd, &mouse);
			print_mouse_info(&mouse);
		#endif
	}
	
	ret = ioctl(uFd, UI_DEV_DESTROY);
}

int main(int argc, char *argv[])
{
	int fd;
	char *device;
	
	if(argc < 2){
		printf("Not enough inputs!\n");
		printf("Use: mouseDriver <device>\n");
		printf("<device> = /dev/hidraw0, for example\n");
		exit(1);
	}
	
	device = argv[1];
	
	fd = open(device, O_RDONLY);
	if(fd < 0){
		printf("\nError(%d) opening device: %s\n", fd, device);
		printf("Try changing permissions: sudo chmod 666 %s\n\n", device);
		exit(2);
	}
	
	emulate_mouse(fd);
	close(fd);
	exit(3);
}
