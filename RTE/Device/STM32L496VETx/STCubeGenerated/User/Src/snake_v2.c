#include "snake_v2.h"

#include "arm_2d.h"
#include "arm_2d_disp_adapters.h"
#include "arm_2d_scenes.h"

void SnakeGameEntry(void *param) {
	disp_adapter0_init();
	arm_2d_scene0_init(&DISP0_ADAPTER);
	arm_2d_scene1_init(&DISP0_ADAPTER);
	arm_2d_scene2_init(&DISP0_ADAPTER);
	while(1) {
		disp_adapter0_task();
	}

}