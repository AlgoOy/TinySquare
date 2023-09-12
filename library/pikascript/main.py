import PikaStdLib
import TinySquare
import pikaRTThread


thd = pikaRTThread.Thread()
evt = TinySquare.EvtKey()
gfx = TinySquare.Gfx()

screen_region = TinySquare.Region(0, 0, 240, 240)

# welcome stage
stage = TinySquare.Stage()

stage.register_layer(TinySquare.LayerBGCL(TinySquare.BG_CL_NORMAL, TinySquare.RGB(0xcf, 0xfd, 0xcb), 255, screen_region, None, None))

user_layer = TinySquare.LayerUser(10, 10)
stage.register_layer(user_layer)

for i in range(4, 10):
	user_layer.draw_userMap(i, 1, 1)
for i in range(3, 7):
	user_layer.draw_userMap(i, i - 1, 1)
for i in range(0, 6):
	if (not i):
		user_layer.draw_userMap(i, 6, 2)
		continue
	user_layer.draw_userMap(i, 6, 1)

text_layer = TinySquare.LayerText(0, TinySquare.RGB(0x00, 0x00, 0x00), 255, TinySquare.Region(0, 0, 240, 240))

# setting stage


# game stage


gfx.refresh()

while True:
	direction = evt.get_direction()
	thd.mdelay(1000)
	evt.update_key(0)
