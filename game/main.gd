extends Node

func _ready() -> void:
	DoorGrid2D.cons(Vector2i(0, 0), Vector2i(1, 1))

func _physics_process(delta: float) -> void:
	pass
