extends Node

func _ready() -> void:
	pass

var door := DoorGrid2D.cons(Vector2i(0, 0), Vector2i(1, 1))

func _physics_process(delta: float) -> void:
	if Time.get_ticks_msec() > 3000 && door != null:
		door = null
