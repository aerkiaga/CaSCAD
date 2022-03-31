use <basic_functions.scad>
use <involute_gear_profile.scad>

$fs = 0.01;

module octoid_gear_profile(
    inner_proportion, twist_steps,
    pitch_angle, tooth_count,
    internal = false,
    pressure_angle = 20,
    addendum_coefficient = 1,
    dedendum_coefficient = 1.25
) {
    minimum_tooth_count = fn_minimum_teeth_for_involute_profile(
        pressure_angle, addendum_coefficient
    );
    assert(
        tooth_count >= minimum_tooth_count,
        str(
            "Octoid gear does not have enough teeth (has ",
            tooth_count, ", requires ", minimum_tooth_count, ")"
        )
    );
    pa_rad = pitch_angle * PI / 180;
    twist_angle = twist_steps * 360 / tooth_count;
    total_twist = twist_angle / (1 - inner_proportion);
    step = 360 * $fs / tooth_count;
    polygon([
        for(phi = [0:step:360])
            let (
                a = fn_unit_involute_profile(phi,
                    tooth_count, pressure_angle,        
                    addendum_coefficient, 
                    dedendum_coefficient
                ),
                r = tan(a * pitch_angle) * cos(pitch_angle),
                phi2 = phi -
                    total_twist * sin(pitch_angle)
                    * (sin(pitch_angle) - r)
            )
            fn_cartesian_from_polar(
                phi2,
                internal?
                    2 - r : r
            )
    ]);
}