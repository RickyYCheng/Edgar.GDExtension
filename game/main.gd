extends Node

func _ready() -> void:
	var door := DoorGrid2D.cons(Vector2i(0, 0), Vector2i(1, 1))
	var doors := ManualDoorModeGrid2D.cons([door])

func _physics_process(delta: float) -> void:
	pass
