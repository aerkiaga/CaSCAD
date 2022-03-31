function fn_octoid_addendum_or_dedendum_angle(
    coefficient, pitch_angle, tooth_count
) =
    atan(coefficient * 2 * sin(pitch_angle) / tooth_count)
;

module octoid_bevel_tooth(
    pitch_angle, tooth_count,
    pressure_angle = 20,
    addendum_coefficient = 1,
    dedendum_coefficient = 1.25
) {
    addendum_angle = fn_octoid_addendum_or_dedendum_angle(
        addendum_coefficient, pitch_angle, tooth_count
    );
    dedendum_angle = fn_octoid_addendum_or_dedendum_angle(
        dedendum_coefficient, pitch_angle, tooth_count
    );
    difference() {
        intersection() {
            sphere(1);
            translate([0, 0,
                -1/tan(pitch_angle + addendum_angle)
            ]) {
                cylinder(
                    1/tan(pitch_angle + addendum_angle),
                    1, 0, false
                );
                mirror([0, 0, 1]) cylinder(
                    1, 1, 1, false
                );
            }
        }
        translate([0, 0,
            -10/tan(pitch_angle - dedendum_angle)
        ]) {
            cylinder(
                10/tan(pitch_angle - dedendum_angle),
                10, 0, false
            );
            mirror([0, 0, 1]) cylinder(
                1, 1, 1, false
            );
        }
        rotate(-90/tooth_count, [0, 0, 1])
        rotate(90-pitch_angle, [0, 1, 0])
        rotate(90-pressure_angle, [1, 0, 0])
            cylinder(1, 2, 2, false);
        rotate(90/tooth_count, [0, 0, 1])
        rotate(90-pitch_angle, [0, 1, 0])
        rotate(-90+pressure_angle, [1, 0, 0])
            cylinder(1, 2, 2, false);
        rotate(-90, [0, 1, 0])
            cylinder(1, 2, 2, false);
    }
}

module octoid_raw_bevel_gear(
    pitch_angle, tooth_count,
    pressure_angle = 20,
    addendum_coefficient = 1,
    dedendum_coefficient = 1.25
) {
    dedendum_angle = fn_octoid_addendum_or_dedendum_angle(
        dedendum_coefficient, pitch_angle, tooth_count
    );
    intersection() {
        sphere(1);
        translate([0, 0,
            -10/tan(pitch_angle - dedendum_angle)
        ]) {
            cylinder(
                10/tan(pitch_angle - dedendum_angle),
                10, 0, false
            );
            mirror([0, 0, 1]) cylinder(
                1, 1, 1, false
            );
        }
    }
    for(angle = [0:360/tooth_count:360]) {
        rotate(angle, [0, 0, 1]) octoid_bevel_tooth(
            pitch_angle = pitch_angle,
            tooth_count = tooth_count,
            pressure_angle = pressure_angle,
            addendum_coefficient = addendum_coefficient,
            dedendum_coefficient = dedendum_coefficient
        );
    }
}

module octoid_bevel_gear(
    pitch_angle, tooth_count,
    inner_empty_ratio = 0.5,
    pressure_angle = 20,
    addendum_coefficient = 1,
    dedendum_coefficient = 1.25
) {
    difference() {
        octoid_raw_bevel_gear(
            pitch_angle = pitch_angle,
            tooth_count = tooth_count,
            pressure_angle = pressure_angle,
            addendum_coefficient = addendum_coefficient,
            dedendum_coefficient = dedendum_coefficient
        );
        translate([0, 0, -inner_empty_ratio / cos(pitch_angle)]) {
            cylinder(
                10/tan(90 - pitch_angle),
                0, 10, false
            );
            translate([0, 0, 10/tan(90 - pitch_angle)]) cylinder(
                10, 10, 10, false
            );
        }
    }
}