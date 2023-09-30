# pikaPython library usage - Snake

- [pikaPython library usage - Snake](#pikapython-library-usage---snake)
  - [Greedy Snake](#greedy-snake)
    - [Renderings](#renderings)
    - [Reference data](#reference-data)
    - [Code analysis](#code-analysis)

## Greedy Snake

Taking the snake game as an example, we will introduce how to implement a multi-stage snake game in the Python language running environment.

### Renderings

- Start interface
   - <div align="center"> <img src="./image/snake_start.jpg" width = 300 /> </div>

- Difficulty selection
   - <div align="center"> <img src="./image/snake_difficulty.jpg" width = 300 /> </div>

- Game interface
   - <div align="center"> <img src="./image/snake_game.jpg" width = 300 /> </div>

### Reference data

<table>
  <tr>
    <th colspan="5"> Reference data </th>
  </tr>
  <tr>
    <th colspan="2"></th>
    <th> -Os optimization </th>
    <th> -Oz optimization </th>
    <th> Remark </th>
  </tr>
  <tr>
    <th rowspan="7"> Configuration </th>
    <th> Main frequency </th>
    <td style="text-align:center"> 80MHz </td>
    <td style="text-align:center"> 80MHz </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> Optimization level </th>
    <td style="text-align:center"> -Os -lto </td>
    <td style="text-align:center"> -Oz -lto </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> Screen </th>
    <td style="text-align:center"> 240 * 240 </td>
    <td style="text-align:center"> 240 * 240 </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> PFB </th>
    <td style="text-align:center"> 240 * 4 </td>
    <td style="text-align:center"> 240 * 4 </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> Heap </th>
    <td style="text-align:center"> 0x400 </td>
    <td style="text-align:center"> 0x400 </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> Stack </th>
    <td style="text-align:center"> 0x200 </td>
    <td style="text-align:center"> 0x200 </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> rt heap </th>
    <td style="text-align:center"> 0x6800 </td>
    <td style="text-align:center"> 0x6800 </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th rowspan="3"> Performance </th>
    <th> Startup interface FPS </th>
    <td style="text-align:center"> —— </td>
    <td style="text-align:center"> —— </td>
    <td style="text-align:center"> No refresh operation </td>
  </tr>
  <tr>
    <th> Difficulty selection FPS </th>
    <td style="text-align:center"> 23:41ms </td>
    <td style="text-align:center"> 20:48ms </td>
    <td style="text-align:center"> Fixed refresh area: 160 * 90 </td>
  </tr>
  <tr>
    <th> Game interface FPS </th>
    <td style="text-align:center"> 87:11ms </td>
    <td style="text-align:center"> 77:12ms </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th rowspan="4"> Program size </th>
    <th> Code </th>
    <td style="text-align:center"> 150648 </td>
    <td style="text-align:center"> 118912 </td>
    <td style="text-align:center"> Python virtual machine support </td>
  </tr>
  <tr>
    <th> RO-data </th>
    <td style="text-align:center"> 49400 </td>
    <td style="text-align:center"> 49328 </td>
    <td style="text-align:center"> 16x24 font file, 6x8 font file, Python virtual machine support </td>
  </tr>
  <tr>
    <th> RW-data </th>
    <td style="text-align:center"> 732 </td>
    <td style="text-align:center"> 728 </td>
    <td style="text-align:center"> —— </td>
  </tr>
  <tr>
    <th> ZI-data </th>
    <td style="text-align:center"> 33668 </td>
    <td style="text-align:center"> 33656 </td>
    <td style="text-align:center"> Including LCD buffer, PFB pool, rt heap, rt stack, stack, heap, snake resource, etc. </td>
  </tr>
</table>

### Code analysis

The source code for the snake game is located in snake.py under pikascript. In the Python running environment, the available layers are: background color layer, basic unit layer, user unit layer, text layer, menu layer, and number list layer. Compared with the C environment, there is no background layer, and at the same time, the degree of customization is relatively reduced.

- First, event control and image control need to be initialized
     ```python
     self.evt = TinySquare.EvtKey()
     self.gfx = TinySquare.Gfx()
     ```

- Initialize a stage through the stage class, and register the layer into the stage through the `register_layer` method
     ```python
     welcome_stage = TinySquare.Stage()
     welcome_stage.register_layer(TinySquare.LayerBGCL(TinySquare.BG_CL_NORMAL, self.bg_color, 255, self.screen_region, None, None))
     ```

- The initialization of the user layer class is relatively simple. You only need to specify the width and height. The custom drawing function of the user layer class requires a certain C language foundation to complete. Call `draw_userMap` to complete drawing of the user layer
     ```python
     welcome_user_layer = TinySquare.LayerUser(self.width_block, self.height_block)
     welcome_stage.register_layer(welcome_user_layer)
     welcome_user_layer.draw_userMap(1, 1, 1)
     ```

- The initialization of the text layer class is similar to that in the C environment, just specify the font, color, opacity and Region. The text is formatted in a C-like language.
     ```python
     welcome_text_layer = TinySquare.LayerText(TinySquare.TEXT_FONT_6X8,
                                                     self.txt_color,
                                                     255,
                                                     TinySquare.Region(0, 192, 240, 24))
     welcome_stage.register_layer(welcome_text_layer)
     welcome_text_layer.print_str("%s", "Enter Any Key To Start")
     ```

- When switching stages, you only need to define a stage class instance and then switch, and refresh operations can be performed according to the actual situation.
     ```python
     setting_stage = TinySquare.Stage()
     self.gfx.switch_stage()
     self.gfx.refresh()
     ```

- The customization options of the menu layer class are greatly reduced compared to the C language, but they are easier to use.
     ```python
     setting_menu_layer = TinySquare.LayerMenu(("Easy", "Normal", "Hard"),
                                                     TinySquare.TEXT_FONT_16X24,
                                                     160,
                                                     30,
                                                     TinySquare.ItemFormat(self.bg_color, self.txt_color, 255),
                                                     TinySquare.ItemFormat(self.txt_color, self.bg_color, 255))
     setting_stage.register_layer(setting_menu_layer)
     self.gfx.refresh()
     menu_idx = setting_menu_layer.get_idx()
     ```

- The use of TinySquare is very simple and easy to use. The above basically covers the basic functions of TinySquare in the python operating environment. For more information, please check the API documentation