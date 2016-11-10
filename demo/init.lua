
require ("demo/charactor")
require ("demo/handler")
require ("demo/ui_parser")

function init()
	print ("start demo...")

	data_dir = "../data/"
	scene_dir = data_dir.."scene/2008/"
	char_dir = data_dir.."charactor/303/"
	scene_block = data_dir.."scene/2008_block.txt"

	print ("initialize scene...")
	scene = Scene:new(scene_dir, 11, 16, scene_block, 176, 320)

	print ("initialize camera...")
	camera = scene:getActiveCamera()
	camera:setPosition(2360, 1820)
	camera:setViewPort(1280, 720)

	print ("initialize charactor...")
	charactor = Charactor:new()
	charactor:register_anims()
	charactor:loadTexture(char_dir.."charactor.png")
	charactor:setPosition(3000, 2180)
	charactor:addEventListener(TE_MOUSE_RIGHT_DOWN, handle_charactor_move)
	charactor:play(charactor["anim"])
	scene:addChild(charactor)

	print ("initialize ui...")
	panel_table = require("demo/panel")
	sprite_table = require("demo/panel_sprite")
	ui_panel = parse_ui(panel_table)
	ui_charactor = parse_ui(sprite_table)
	ui_charactor:register_anims()
	ui_charactor:play(ui_charactor["anim"])
	ui_panel:addChild(ui_charactor)
	rotate_button = ui_panel:seekWidgetByName("rotate")
	rotate_button:addEventListener(TE_MOUSE_LEFT_DOWN, handle_rotate_button_down)
	rotate_button:addEventListener(TE_MOUSE_LEFT_UP, handle_rotate_button_up)
	scene:addChild(ui_panel)


	print ("initialize director...")
	director = Director:getInstance()
	director:setWindowSize(1280, 720)
	director:setActiveScene(scene)
	director:start()

	print ("end demo...")
end

function update()
	charactor:update()
end