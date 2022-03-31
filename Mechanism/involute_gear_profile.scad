use <basic_functions.scad>

function fn_unit_involute_profile(
    angle, tooth_count,
    pressure_angle = 20,
    addendum_coefficient = 1,
    dedendum_coefficient = 1.25
) =
    min(
        1 + addendum_coefficient/tooth_count,
        max(
            1 - dedendum_coefficient/tooth_count,
            1 + (1/(/*2**/tooth_count*tan(pressure_angle)))
                * fn_radians_from_degrees(
                    asin(sin(tooth_count*angle))
                )
        )
    )
;

function fn_minimum_teeth_for_involute_profile(
    pressure_angle = 20,
    addendum_coefficient = 1
) =
    round(
        2 * addendum_coefficient
        / pow(sin(pressure_angle), 2)
    )
;

module involute_gear_profile(
    tooth_count,
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
            "Involute gear does not have enough teeth (has ",
            tooth_count, ", requires ", minimum_tooth_count, ")"
        )
    );
    step = 360 * $fs / tooth_count;
    polygon([
        for(phi = [0:step:360])
            fn_cartesian_from_polar(phi,
                let (
                    r = fn_unit_involute_profile(phi,
                        tooth_count, pressure_angle,        
                        addendum_coefficient, dedendum_coefficient
                    )
                )
                internal? 2 - r : r
            )
    ]);
}