
require ("demo/Charactor")

UITypeMap = {["UIPanel"] = UIPanel, ["UIImage"] = UIImage, ["UIButton"] = UIButton, ["Charactor"] = Charactor}

function parse_ui(config_table)
	local ui_element = UITypeMap[config_table["TypeName"]]:new()
	if (config_table["Image"]) then
		if (config_table["TypeName"] == "Charactor") then
			ui_element:loadTexture(data_dir..config_table["Image"])
			ui_element:setUI(true)
		else
			ui_element:setImage(data_dir..config_table["Image"])
		end
	end
	if (config_table["Name"]) then ui_element:setWidgetName(config_table["Name"]) end
	if (config_table["Pos"]) then ui_element:setPosition(config_table["Pos"]["x"], config_table["Pos"]["y"]) end
	if (config_table["Size"]) then ui_element:setContentSize(config_table["Size"]["width"], config_table["Size"]["height"]) end 
	
	if (config_table["Children"]) then
		for i, v in ipairs(config_table["Children"]) do
			child = parse_ui(v)
			if (child ~= nil) then
				ui_element:addChild(child)
			end
		end
	end
	
	return ui_element
end
