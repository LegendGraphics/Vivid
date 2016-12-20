require ("demo/utils")

Direction = {[0] = "east", [1] = "northeast", [2] = "north", [3] = "northwest", [4] = "west", [5] = "southwest", [6] = "south", [7] = "southeast"}
Status = {"stand", "run"}

Charactor = Sprite:new()
Charactor["dir"] = 0
Charactor["status"] = "stand"
Charactor["anim"] = Charactor["status"]..Charactor["dir"]

function Charactor:new()
	return Charactor:clone()
end

function Charactor:register_anims()
	for index, value in pairs(Direction) do 
		local anim = Animation:new(char_dir.."stand/"..value)
		self:registerAnimation("stand"..index, anim)

		local anim = Animation:new(char_dir.."run/"..value)
		self:registerAnimation("run"..index, anim)	
	end
end

function Charactor:angle(x, y)
	local angle = math.atan2(y, x)
	if (angle < 0) then
		angle = angle + 2 * math.pi
	end
	return angle * 180.0 / math.pi
end

function Charactor:direction_mapping(angle)
	local num = math.modf(angle / 45)
	local rest = math.fmod(angle, 45)
	if (rest / 45 <= 0.5) then
		return num
	else
		return math.fmod(num + 1, 8)
	end
end

function Charactor:update_status(status, dir_num)
	if (self["status"] == status and self["dir"] == dir_num) then
		return
	else 
		self:stop(self["anim"])
		self["status"] = status
		self["dir"] = dir_num
		self["anim"] = self["status"]..self["dir"]
		self:play(self["anim"])
	end
end

function Charactor:move_to(x, y)
	self["tx"] = x
	self["ty"] = y
end

function Charactor:arrived(cur_pos, target_pos)
	if ((target_pos - cur_pos):length() < 5) then
		return true
	else
		return false
	end
end

function Charactor:moving(dx, dy)
	local cur_pos = self:getPosition()
	local moving_pos = Vec2:new(cur_pos:x() + dx, cur_pos:y() + dy)
	return moving_pos
end


function Charactor:update()
	-- wait for input
	if (self["tx"] == nil or self["ty"] == nil) then return end

	local target_pos = Vec2:new(self["tx"], self["ty"])

	local cur_pos = self:getPosition()

	local dir = (target_pos - cur_pos):normalize()
	local angle = self:angle(dir:x(), dir:y())
	local dir_num = self:direction_mapping(angle)

	if (self:arrived(cur_pos, target_pos)) then
		self:update_status("stand", dir_num) 
	else
		self:update_status("run", dir_num)
	end

	if (self["status"] == "run") then	
		local v = 200
		local delta_time = director:getDeltaTime()

		local dx = v*dir:x()*delta_time
		local dy = v*dir:y()*delta_time

		local moving_pos = self:moving(dx, dy)

		if (scene:isBlocked(moving_pos:x(), moving_pos:y())) then
			self:update_status("stand", dir_num) 
			self["tx"] = nil
			self["ty"] = nil
		else
			self:setPosition(moving_pos:x(), moving_pos:y())
			local cpos = camera:getPosition()
			camera:setPosition(cpos:x()+dx, cpos:y()+dy)
		end
		
	end

end


function Charactor:clone()
	local new_charactor = Sprite:new()
	new_charactor["dir"] = 0
	new_charactor["status"] = "stand"
	new_charactor["anim"] = new_charactor["status"]..new_charactor["dir"]
	new_charactor.register_anims = Charactor.register_anims
	new_charactor.angle = Charactor.angle
	new_charactor.direction_mapping = Charactor.direction_mapping
	new_charactor.move_to = Charactor.move_to
	new_charactor.arrived = Charactor.arrived
	new_charactor.moving = Charactor.moving
	new_charactor.update_status = Charactor.update_status
	new_charactor.update = Charactor.update
	return new_charactor
end

return Charactor