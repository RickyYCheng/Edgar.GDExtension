# Edgar.GDExtension

Edgar.GDExtension is the Godot-Cpp binding library for [Edgar-Dotnet](https://github.com/OndrejNepozitek/Edgar-DotNet), implemented via C# Native Aot technology. It aims to provide Edgar usage opportunities for non-Godot-CSharp users.

Please note the following:
- All Godot object properties in this library are not stored. These objects are merely simple wrappers for C# GCHandle objects. Therefore, for any properties you need to use, please store them yourself.
- It is recommended to set RoomTemplateGrid2D.name to the resource path, which offers two benefits:
  1. Resource paths are unique;
  2. Relying on its caching mechanism, ResourceLoader.Load won't reload repeatedly.
- All strings are handled as UTF-8.

## Example

```gdscript
extends Node

func _ready() -> void:
	var doors := ManualDoorModeGrid2D.cons([
		DoorGrid2D.cons(Vector2i(0, 0), Vector2i(0, 1)),
		DoorGrid2D.cons(Vector2i(0, 1), Vector2i(1, 1)),
		DoorGrid2D.cons(Vector2i(1, 1), Vector2i(1, 0)),
		DoorGrid2D.cons(Vector2i(1, 0), Vector2i(0, 0)),
	])
	var room_template := RoomTemplateGrid2D.cons(
		"template",
		[Vector2i(0, 0), Vector2i(1, 0), Vector2i(1, 1), Vector2i(0, 1)],
		doors,
		[RoomTemplateGrid2D.IDENTITY]
	)
	var room_description := RoomDescriptionGrid2D.cons(false, [room_template])
	
	var level_description := LevelDescriptionGrid2D.cons()
	level_description.add_room("room 1", room_description)
	level_description.add_room("room 2", room_description)
	level_description.add_connection("room 1", "room 2")
	
	var generator := GraphBasedGeneratorGrid2D.cons(level_description)
	print(generator.generate_layout())
```
> output:
```text
{ "rooms": [{ "room": "room 1", "is_corridor": false, "position": (0, 0), "transformation": 0, "room_template": "template" }, { "room": "room 2",  "is_corridor": false, "position": (-1, 0), "transformation": 0, "room_template": "template" }] }
```
