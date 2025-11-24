extends Node

func _ready() -> void:
	var nodes : Dictionary = { 
		"_GraphNode_00000": { 
			"edgar_layer": 1, 
			"is_corridor_room": false, 
			"position_offset": Vector2(400.0, 280.0) 
		}, 
		"_GraphNode_00001": { 
			"edgar_layer": 0, 
			"is_corridor_room": false, 
			"position_offset": Vector2(80.0, 100.0) 
		}, 
		"_GraphNode_28080": { 
			"edgar_layer": 0, 
			"is_corridor_room": false, 
			"position_offset": Vector2(400.0, 100.0) 
		}, 
		"_GraphNode_28096": { 
			"edgar_layer": 0, 
			"is_corridor_room": false, 
			"position_offset": Vector2(740.0, 100.0)
		} 
	}
	var edges : Array[Dictionary] = [
		{ "from_node": "_GraphNode_00001", "to_node": "_GraphNode_28080" }, 
		{ "from_node": "_GraphNode_28080", "to_node": "_GraphNode_28096" }, 
		{ "from_node": "_GraphNode_00001", "to_node": "_GraphNode_00000" }
	]
	var layers : Array[Dictionary] = [
		{ 
			"res://assets/basic.tmj": { 
				"boundary": [Vector2(0.0, 256.0), Vector2(0.0, 0.0), Vector2(256.0, 0.0), Vector2(256.0, 256.0)], 
				"doors": [
					[Vector2(256.0, 96.0), Vector2(256.0, 80.0), Vector2(256.0, 64.0), Vector2(256.0, 48.0), Vector2(256.0, 32.0)], 
					[Vector2(0.0, 160.0), Vector2(0.0, 176.0), Vector2(0.0, 192.0), Vector2(0.0, 208.0), Vector2(0.0, 224.0)]
				],
				"transformations": [0, 1, 2, 3, 4, 5, 6, 7]
			} 
		}, 
		{ 
			"res://assets/limit.tmj": { 
				"boundary": [Vector2(0.0, -16.0), Vector2(1136.0, -16.0), Vector2(1136.0, 976.0), Vector2(-16.0, 976.0), Vector2(-16.0, 0.0), Vector2(0.0, 0.0), Vector2(0.0, 960.0), Vector2(1120.0, 960.0), Vector2(1120.0, 0.0), Vector2(0.0, 0.0)], 
				"doors": [
					[Vector2(0.0, 864.0), Vector2(0.0, 848.0), Vector2(0.0, 832.0), Vector2(0.0, 816.0), Vector2(0.0, 800.0)]
				],
				# no transformations (default [Identity])
			} 
		}
	]
	var generator := EdgarGodotGenerator.cons(nodes, edges, layers)
	var layout_1 := generator.generate_layout()
	var layout_2 := generator.generate_layout()
	print(layout_1, "\n")
	print(layout_2, "\n")
	prints("[layout comparison]", var_to_str(layout_1) == var_to_str(layout_2), "\n")
	
	print("==================================================", "\n")
	
	var seeded_layout_1 := generator.generate_layout_with_seed_injection(42)
	var seeded_layout_2 := generator.generate_layout_with_seed_injection(42)
	print(seeded_layout_1, "\n")
	print(seeded_layout_2, "\n")
	prints("[layout comparison]", var_to_str(seeded_layout_1) == var_to_str(seeded_layout_2), "\n")
