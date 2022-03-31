use <octoid_gear_types.scad>
use <mesh_bevel_gear.scad>
use <bearing.scad>

$fs = 0.1;
$fn = 50;


/*ratio = 1;
twist = 1;
tooth_count = 17;
angle = fn_bevel_angle_for_gear_ratio(ratio);
color([0.3, 0.8, 1, 1])
rotate(360 * $t / tooth_count / ratio, [0, 0, 1])
    octoid_helical_gear(2, 0.5, false, twist, angle, tooth_count * ratio);
mesh_bevel_gear(0, ratio, tooth_count)
rotate(-360 * $t / tooth_count, [0, 0, 1])
    octoid_helical_gear(2, 0.5, false, -twist, 90 - angle, tooth_count);*/

angle = fn_bevel_angle_for_gear_ratio(1);
intersection() {
    sphere(14);
    octoid_helical_gear(15, 0.5, false, 1, angle, 21);
}

height = sin(angle) * 15;
radius = cos(angle) * 15;

coef = 1.4;

translate([0, 0, -coef*height])
    cylinder((coef-1)*height, 0.6*coef*radius, radius);

translate([0, 0, -coef*height - 6])
    roller_bearing(6, coef*radius, 0.6*coef*radius, 0.9*coef*radius);