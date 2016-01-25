#include <linux/input.h>
#include <linux/uinput.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <byteswap.h> /*swap*/

struct mouse
{
	uint32_t lastX;
	uint32_t lastY;
	int32_t deltaX;
	int32_t deltaY;
	uint32_t x;
	uint32_t y;
	
	int pressed;
};

#define device_message_size 22 /*this is in bytes*/

#define mouse_offset_x   1
#define mouse_offset_y   2
#define cmd_offset       0

#define button_pressed   426
#define button_released  170

/* this function parses buffer to obtain mouse movemnte details */
/* it also believes everything that buffer contains is true and beatifull */
void device_parser(uint16_t *buffer, struct mouse* mouse)
{
	int pressed = 0;
	/* update mouse information */
	mouse->deltaX = mouse->x - mouse->lastX;
	mouse->deltaY = mouse->y - mouse->lastY;
	
	mouse->lastX = mouse->x;
	mouse->lastY = mouse->y;
	
	mouse->x = __bswap_16(buffer[mouse_offset_x]);
	mouse->y = __bswap_16(buffer[mouse_offset_y]);
	
	if(buffer[cmd_offset] == (uint16_t)button_pressed){
		pressed = 1;
	}else if(buffer[cmd_offset] == (uint16_t)button_released){
		pressed = 0;
	} else{
		pressed = -1;
	}
	
	mouse->pressed = pressed;
}

void send_events(int fd, struct mouse* mouse)
{
	int ret;
	struct input_event button;
	struct input_event mouse_movement[2];
	struct input_event ev;

	memset(&button, 0, sizeof(button));

	/* on release press send a press and release */
	if(mouse->pressed == 0){		
		button.type = EV_KEY;
		button.code = BTN_LEFT;
		button.value = 1;
		ret = write(fd, &button, sizeof(button));
		if(ret < 0){
			printf("Coudln't send button event...\n");
			exit(4);
		}
		
		button.type = EV_KEY;
		button.code = BTN_LEFT;
		button.value = 0;
		ret = write(fd, &button, sizeof(button));
		if(ret < 0){
			printf("Coudln't send button event...\n");
			exit(4);
		}
	}

	memset(&mouse_movement, 0, sizeof(mouse_movement));

	mouse_movement[0].type = EV_ABS;
	mouse_movement[0].code = ABS_X;
	mouse_movement[0].value = mouse->lastX;
	mouse_movement[1].type = EV_ABS;
	mouse_movement[1].code = ABS_Y;
	mouse_movement[1].value = mouse->lastY;

	ret = write(fd, &mouse_movement, sizeof(mouse_movement));
	if(ret < 0){
		printf("Coudln't send mouse movement event...\n");
		exit(4);
	}
	
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

int uinput_init()
{
	int uFd;	
	struct uinput_user_dev uidev;
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
	uidev.absmax[ABS_X] = 3956;
	uidev.absmin[ABS_Y] = 0;
	uidev.absmax[ABS_Y] = 3956;

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
			printf("We were still able to read something - %d\n", (int)n_items);
			break;
		}

		device_parser(buffer, &mouse);
		send_events(uFd, &mouse);
		print_mouse_info(&mouse);
	}
	
	ret = ioctl(uFd, UI_DEV_DESTROY);
}

int main(int argc, char *argv[])
{
	int fd;
	char device[] = "/dev/hidraw0";
	
	if(argc < 1){
		printf("Not enough inputs!\n");
		printf("Use: mouseDriver <device>\n");
		printf("<device> = /dev/hidraw0, for example\n");
		exit(1);
	}
	
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
