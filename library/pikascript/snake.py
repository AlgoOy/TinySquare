import pikaRTThread
import TinySquare


class Game:
    def __init__(self):
        self.thd = pikaRTThread.Thread()
        self.evt = TinySquare.EvtKey()
        self.gfx = TinySquare.Gfx()
        self.task = pikaRTThread.Task()
        self.screen_region = TinySquare.Region(0, 0, 240, 240)
        self.width_block = 10
        self.height_block = 10
        self.bg_color = TinySquare.RGB(0xcf, 0xfd, 0xcb)
        self.txt_color = TinySquare.RGB(0x00, 0x00, 0x00)
        self.game_score = 0
        self.snake_speed = 400
        self.snake_direction = TinySquare.KEY_DIRECTION_RIGHT
        self.snake = [(2 , 2)]
        self.food = self.create_food()

    def game_over(self):
        while True:
            self.thd.mdelay(100)

    def create_food(self) -> list:
        self.task.platformGetTick()
        pos = [(self.task.tick % self.width_block), ((self.task.tick+2023) % (self.height_block-1))+1]
        if pos in self.snake:
            return self.create_food()
        return pos
    
    def eat_food(self, food: list, user_layer: TinySquare.LayerUser):
        self.snake.insert(0, (food[0], food[1]))
        user_layer.draw_userMap(food[0], food[1], 1)
        self.food = self.create_food()
        user_layer.draw_userMap(self.food[0], self.food[1], 2)

    def move_snake(self, head: tuple, user_layer: TinySquare.LayerUser):
        tail_pos = self.snake.pop()
        user_layer.draw_userMap(tail_pos[0], tail_pos[1], 0)
        self.snake.insert(0, head)
        user_layer.draw_userMap(head[0], head[1], 1)
    
    def update_direction(self):
        err = self.evt.update_key(0)
        while err != -2 and err != -1:
            if self.evt.get_event() != TinySquare.KEY_EVENT_PRESSED and self.evt.get_event() != TinySquare.KEY_EVENT_LONG_PRESSED:
                err = self.evt.update_key(0)
                continue
            else:
                if self.evt.get_direction() == TinySquare.KEY_DIRECTION_UP:
                    if self.snake_direction != TinySquare.KEY_DIRECTION_DOWN:
                        self.snake_direction = TinySquare.KEY_DIRECTION_UP
                elif self.evt.get_direction() == TinySquare.KEY_DIRECTION_DOWN:
                    if self.snake_direction != TinySquare.KEY_DIRECTION_UP:
                        self.snake_direction = TinySquare.KEY_DIRECTION_DOWN
                elif self.evt.get_direction() == TinySquare.KEY_DIRECTION_LEFT:
                    if self.snake_direction != TinySquare.KEY_DIRECTION_RIGHT:
                        self.snake_direction = TinySquare.KEY_DIRECTION_LEFT
                elif self.evt.get_direction() == TinySquare.KEY_DIRECTION_RIGHT:
                    if self.snake_direction != TinySquare.KEY_DIRECTION_LEFT:
                        self.snake_direction = TinySquare.KEY_DIRECTION_RIGHT
            return
        

    def logic(self, user_layer: TinySquare.LayerUser, text_layer: TinySquare.LayerText):
        user_layer.draw_userMap(self.food[0], self.food[1], 2)
        user_layer.draw_userMap(self.snake[0][0], self.snake[0][1], 1)    
        self.gfx.refresh()

        while True:
            self.update_direction()

            head_x, head_y = self.snake[0]
            if self.snake_direction == TinySquare.KEY_DIRECTION_UP:
                head_y -= 1
            elif self.snake_direction == TinySquare.KEY_DIRECTION_DOWN:
                head_y += 1
            elif self.snake_direction == TinySquare.KEY_DIRECTION_LEFT:
                head_x -= 1
            elif self.snake_direction == TinySquare.KEY_DIRECTION_RIGHT:
                head_x += 1

            if head_x == self.food[0] and head_y == self.food[1]:
                self.eat_food(self.food, user_layer)
                self.game_score += 100
                text_layer.print_num("Score: %d", self.game_score)
            else:
                if not ((0 <= head_x and head_x < self.width_block) and (1 <= head_y and head_y < self.height_block)) or (head_x, head_y) in self.snake:
                    self.game_over()
                    return
                else:
                    self.move_snake((head_x, head_y), user_layer)
            self.gfx.refresh()
            self.thd.mdelay(self.snake_speed)

    def welcome_stage(self):
        welcome_stage = TinySquare.Stage()
        welcome_stage.register_layer(TinySquare.LayerBGCL(TinySquare.BG_CL_NORMAL, self.bg_color, 255, self.screen_region, None, None))
        welcome_user_layer = TinySquare.LayerUser(self.width_block, self.height_block)
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
                                                  self.txt_color,
                                                  255,
                                                  TinySquare.Region(0, 192, 240, 24))
        welcome_stage.register_layer(welcome_text_layer)
        welcome_text_layer.print_str("%s", "Enter Any Key To Start")
        self.gfx.refresh()
        while True:
            self.thd.mdelay(100)
            self.evt.update_key(0)
            if self.evt.get_event() == TinySquare.KEY_EVENT_PRESSED or self.evt.get_event() == TinySquare.KEY_EVENT_LONG_PRESSED:
                break

    def setting_stage(self):
        setting_stage = TinySquare.Stage()
        self.gfx.switch_stage()
        setting_stage.register_layer(TinySquare.LayerBGCL(TinySquare.BG_CL_NORMAL, self.bg_color, 255, self.screen_region, None, None))
        setting_menu_layer = TinySquare.LayerMenu(("Easy", "Normal", "Hard"),
                                                  TinySquare.TEXT_FONT_16X24,
                                                  160,
                                                  30,
                                                  TinySquare.ItemFormat(self.bg_color, self.txt_color, 255),
                                                  TinySquare.ItemFormat(self.txt_color, self.bg_color, 255))
        setting_stage.register_layer(setting_menu_layer)
        self.gfx.refresh()
        menu_idx = setting_menu_layer.get_idx()
        while menu_idx == -1:
            menu_idx = setting_menu_layer.get_idx()
        if menu_idx == 0:
            self.snake_speed = 400
        elif menu_idx == 1:
            self.snake_speed = 300
        elif menu_idx == 2:
            self.snake_speed = 200

    def game_stage(self):
        game_stage = TinySquare.Stage()
        self.gfx.switch_stage()
        game_stage.register_layer(TinySquare.LayerBGCL(TinySquare.BG_CL_NORMAL, self.bg_color, 255, self.screen_region, None, None))
        game_stage.register_layer(TinySquare.LayerBGCL(TinySquare.BG_CL_BORDER, 
                                  TinySquare.RGB(0x00, 0x00, 0x00), 
                                  255, 
                                  TinySquare.Region(0, 0, 240, 24), 
                                  TinySquare.BorderOpacity(128, 128, 128, 128), 
                                  TinySquare.CornerOpacity(128, 128, 128, 128)))
        game_text_layer = TinySquare.LayerText(TinySquare.TEXT_FONT_6X8,
									           self.txt_color,
									           255,
                                               TinySquare.Region(0, 0, 240, 24))
        game_stage.register_layer(game_text_layer)
        game_text_layer.print_num("Score: %d", 0)
        game_user_layer = TinySquare.LayerUser(self.width_block, self.height_block)
        game_stage.register_layer(game_user_layer)
        self.gfx.refresh()
        self.logic(game_user_layer, game_text_layer)

    def run(self):
        self.welcome_stage()
        self.setting_stage()
        self.game_stage()