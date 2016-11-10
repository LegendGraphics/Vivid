
dir_number = 0
function handle_rotate_button_down(event)
	if (rotate_button:isInWidget(event:getX(), event:getY())) then
		dir_number = dir_number + 1
		if (dir_number == 8) then dir_number = 0 end
		ui_charactor:update_status(ui_charactor["status"], dir_number)
		rotate_button:setImage(data_dir.."panel/button_down.png")
	end
end

function handle_rotate_button_up(event)
	rotate_button:setImage(data_dir.."panel/button_up.png")
end

function handle_charactor_move(event)
	x = event:getX()
	y = event:getY()
	wx, wy = convert_screen_to_world(x, y)
	charactor:move_to(wx, wy)
end

function convert_screen_to_world(x, y)
	wsize = director:getWindowSize()
	ox = x
	oy = wsize.height - y

	camera_pos = camera:getPosition()
	wx = camera_pos:x() + ox
	wy = camera_pos:y() + oy

	return wx, wy
end
