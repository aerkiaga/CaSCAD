function fn_bevel_angle_for_gear_ratio(gear_ratio) =
    atan(gear_ratio)
;

module mesh_bevel_gear(
    direction_angle,
    gear_ratio = 1,
    tooth_count
) {
    rotate(direction_angle, [0, 0, 1])
    rotate(-90, [0, 1, 0])
    rotate(
        180/tooth_count
        + direction_angle/gear_ratio
        /*180 * (1 + 1/tooth_count)
        + direction_angle/gear_ratio*/,
        [0, 0, 1]
    )
    children();
}