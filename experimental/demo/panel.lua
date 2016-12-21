return {
	["TypeName"] = "UIPanel",
	["Name"] = "panel",
	["Pos"] = {
		["y"] = 450,
		["x"] = 1000,
	},
	["Size"] = {
		["height"] = 250,
		["width"] = 250,
	},
	["Image"] = "panel/bg.png",
	["Children"] = {
		[1] = {
			["TypeName"] = "UIImage",
			["Name"] = "top",
			["Pos"] = {
				["y"] = 250-18,
				["x"] = 0,
			},
			["Size"] = {
				["height"] = 18,
				["width"] = 250,
			},
			["Image"] = "panel/top.png",
		},
		[2] = {
			["TypeName"] = "UIImage",
			["Name"] = "bottom",
			["Pos"] = {
				["y"] = 0,
				["x"] = 0,
			},
			["Size"] = {
				["height"] = 18,
				["width"] = 250,
			},
			["Image"] = "panel/bottom.png",
		},
		[3] = {
			["TypeName"] = "UIImage",
			["Name"] = "left",
			["Pos"] = {
				["y"] = 0,
				["x"] = 0,
			},
			["Size"] = {
				["height"] = 250,
				["width"] = 26,
			},
			["Image"] = "panel/left.png",
		},
		[4] = {
			["TypeName"] = "UIImage",
			["Name"] = "right",
			["Pos"] = {
				["y"] = 0,
				["x"] = 250-20,
			},
			["Size"] = {
				["height"] = 250,
				["width"] = 20,
			},
			["Image"] = "panel/right.png",
		},
		[5] = {
			["TypeName"] = "UIImage",
			["Name"] = "left_top",
			["Pos"] = {
				["y"] = 250-47,
				["x"] = 0-12,
			},
			["Size"] = {
				["height"] = 58,
				["width"] = 64,
			},
			["Image"] = "panel/left_top.png",
		},
		[6] = {
			["TypeName"] = "UIImage",
			["Name"] = "left_bottom",
			["Pos"] = {
				["y"] = 0-12,
				["x"] = 0-12,
			},
			["Size"] = {
				["height"] = 42,
				["width"] = 64,
			},
			["Image"] = "panel/left_bottom.png",
		},
		[7] = {
			["TypeName"] = "UIImage",
			["Name"] = "right_top",
			["Pos"] = {
				["y"] = 250-47,
				["x"] = 250-48,
			},
			["Size"] = {
				["height"] = 58,
				["width"] = 59,
			},
			["Image"] = "panel/right_top.png",
		},
		[8] = {
			["TypeName"] = "UIImage",
			["Name"] = "right_bottom",
			["Pos"] = {
				["y"] = 0-12,
				["x"] = 250-48,
			},
			["Size"] = {
				["height"] = 42,
				["width"] = 59,
			},
			["Image"] = "panel/right_bottom.png",
		},
		[9] = {
			["TypeName"] = "UIButton",
			["Name"] = "rotate",
			["Pos"] = {
				["y"] = 20,
				["x"] = 125-40,
			},
			["Size"] = {
				["height"] = 26,
				["width"] = 79,
			},
			["Image"] = "panel/button_up.png",
		},
		[10] = {
			["TypeName"] = "UIButton",
			["Name"] = "close",
			["Pos"] = {
				["y"] = 250-24,
				["x"] = 250-24,
			},
			["Size"] = {
				["height"] = 24,
				["width"] = 24,
			},
			["Image"] = "panel/close.png",
		},
	},
}
