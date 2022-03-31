module mesh_parallel_gear(
    center_distance, direction_angle,
    gear_ratio = 1, internal = false,
    tooth_count
) {
    rotate(direction_angle, [0, 0, 1])
    translate([center_distance, 0, 0])
    rotate(
        180/tooth_count
        + (internal? -1 : 1) * direction_angle/gear_ratio,
        [0, 0, 1]
    )
    mirror([1, 0, 0])
    children();
}