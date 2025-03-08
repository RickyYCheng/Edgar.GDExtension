extends Node

func _ready() -> void:
	#var doors := ManualDoorModeGrid2D.cons([
		#DoorGrid2D.cons(Vector2i(0, 0), Vector2i(0, 1)),
		#DoorGrid2D.cons(Vector2i(0, 1), Vector2i(1, 1)),
		#DoorGrid2D.cons(Vector2i(1, 1), Vector2i(1, 0)),
		#DoorGrid2D.cons(Vector2i(1, 0), Vector2i(0, 0)),
	#])
	#var room_template := RoomTemplateGrid2D.cons(
		#"template",
		#[Vector2i(0, 0), Vector2i(1, 0), Vector2i(1, 1), Vector2i(0, 1)],
		#doors,
		#[RoomTemplateGrid2D.IDENTITY]
	#)
	#var room_description := RoomDescriptionGrid2D.cons(false, [room_template])
	DoorGrid2D.new()
