import PikaStdLib
import TinySquare
import pikaRTThread
import snake

t1 = (1, 2)
t_list = [(1,11), (3, 4), (5, 6), (1, 2)]

if t1 in t_list:
	print("t1 in t_list")

while True:
	snake.Game().run()


thd = pikaRTThread.Thread()
evt = TinySquare.EvtKey()
gfx = TinySquare.Gfx()

screen_region = TinySquare.Region(0, 0, 240, 240)

game_score = 0
snake_speed = 200
snake_direction = TinySquare.KEY_DIRECTION_RIGHT


# welcome stage
welcome_stage = TinySquare.Stage()

welcome_stage.register_layer(TinySquare.LayerBGCL(TinySquare.BG_CL_NORMAL, TinySquare.RGB(0xcf, 0xfd, 0xcb), 255, screen_region, None, None))

welcome_user_layer = TinySquare.LayerUser(10, 10)
welcome_stage.register_layer(welcome_user_layer)

for i in range(4, 10):
	welcome_user_layer.draw_userMap(i, 1, 1)
for i in range(3, 7):
	welcome_user_layer.draw_userMap(i, i - 1, 1)
for i in range(0, 6):
	if (not i):
		welcome_user_layer.draw_userMap(i, 6, 2)
		continue
	welcome_user_layer.draw_userMap(i, 6, 1)

welcome_text_layer = TinySquare.LayerText(TinySquare.TEXT_FONT_6X8,
										  TinySquare.RGB(0x00, 0x00, 0x00),
										  255,
										  TinySquare.Region(0, 192, 240, 24))
welcome_stage.register_layer(welcome_text_layer)
welcome_text_layer.print_str("%s", "Enter Any Key To Start")

gfx.refresh()

while True:
	thd.mdelay(100)
	evt.update_key(0)
	if evt.get_event() == TinySquare.KEY_EVENT_PRESSED or evt.get_event() == TinySquare.KEY_EVENT_LONG_PRESSED:
		break


# setting stage
setting_stage = TinySquare.Stage()
gfx.switch_stage()

setting_stage.register_layer(TinySquare.LayerBGCL(TinySquare.BG_CL_NORMAL, TinySquare.RGB(0xcf, 0xfd, 0xcb), 255, screen_region, None, None))

setting_menu_layer = TinySquare.LayerMenu(("Easy", "Normal", "Hard"),
										  TinySquare.TEXT_FONT_16X24,
										  160,
										  30,
										  TinySquare.ItemFormat(TinySquare.RGB(0xcf, 0xfd, 0xcb), TinySquare.RGB(0x00, 0x00, 0x00), 255),
										  TinySquare.ItemFormat(TinySquare.RGB(0x00, 0x00, 0x00), TinySquare.RGB(0xcf, 0xfd, 0xcb), 255))
setting_stage.register_layer(setting_menu_layer)
gfx.refresh()

menu_idx = setting_menu_layer.get_idx()
while menu_idx == -1:
	menu_idx = setting_menu_layer.get_idx()

if menu_idx == 0:
	snake_speed = 200
elif menu_idx == 1:
	snake_speed = 150
elif menu_idx == 2:
	snake_speed = 100


# game stage
game_stage = TinySquare.Stage()
gfx.switch_stage()

game_stage.register_layer(TinySquare.LayerBGCL(TinySquare.BG_CL_NORMAL, TinySquare.RGB(0xcf, 0xfd, 0xcb), 255, screen_region, None, None))

game_stage.register_layer(TinySquare.LayerBGCL(TinySquare.BG_CL_BORDER, 
											   TinySquare.RGB(0x00, 0x00, 0x00), 
											   255, 
											   TinySquare.Region(0, 0, 240, 24), 
											   TinySquare.BorderOpacity(128, 128, 128, 128), 
											   TinySquare.CornerOpacity(128, 128, 128, 128)))

game_text_layer = TinySquare.LayerText(TinySquare.TEXT_FONT_6X8,
									   TinySquare.RGB(0x00, 0x00, 0x00),
									   255,
									   TinySquare.Region(0, 0, 240, 24))
game_stage.register_layer(game_text_layer)
game_text_layer.print_num("Score：%d", game_score)

game_user_layer = TinySquare.LayerUser(10, 10)
game_stage.register_layer(game_user_layer)



gfx.refresh()