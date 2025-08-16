# Edgar.GDExtension

Edgar.GDExtension is the Godot-Cpp binding library for [Edgar-Dotnet](https://github.com/OndrejNepozitek/Edgar-DotNet), implemented via C# Native Aot technology. It aims to provide Edgar usage opportunities for non-Godot-CSharp users.

Please note the following:
- This library serves as a non-C# kernel for [Edgar.Godot](https://github.com/RickyYCheng/Edgar.Godot.git), designed to provide [Edgar](https://github.com/OndrejNepozitek/Edgar-DotNet) APIs for pure GDScript users (non-C#/.NET environments) while maintaining full compatibility with the C# APIs in [Edgar.Godot](https://github.com/RickyYCheng/Edgar.Godot.git). This allows seamless kernel replacement within [Edgar.Godot](https://github.com/RickyYCheng/Edgar.Godot.git) if needed.

- To use this library, you must compile it for your target platform, and the .NET SDK is required during compilation.

- All strings are handled in UTF-8 encoding.

## Example

```gdscript
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
				] 
			} 
		}, 
		{ 
			"res://assets/limit.tmj": { 
				"boundary": [Vector2(0.0, -16.0), Vector2(1136.0, -16.0), Vector2(1136.0, 976.0), Vector2(-16.0, 976.0), Vector2(-16.0, 0.0), Vector2(0.0, 0.0), Vector2(0.0, 960.0), Vector2(1120.0, 960.0), Vector2(1120.0, 0.0), Vector2(0.0, 0.0)], 
				"doors": [
					[Vector2(0.0, 864.0), Vector2(0.0, 848.0), Vector2(0.0, 832.0), Vector2(0.0, 816.0), Vector2(0.0, 800.0)]
				] 
			} 
		}
	]
	var generator := EdgarGodotGenerator.cons(nodes, edges, layers)
	var layout := generator.generate_layout()
	print(layout)
```
