use <octoid_gears.scad>

function fn_choose_octoid_cut_radius(
    pitch_angle, tooth_count,
    addendum_coefficient = 1,
    dedendum_coefficient = 1.25
) =
    let (addendum_angle = fn_octoid_addendum_or_dedendum_angle(
        addendum_coefficient, pitch_angle, tooth_count
    ))
    let (dedendum_angle = fn_octoid_addendum_or_dedendum_angle(
        dedendum_coefficient, pitch_angle, tooth_count
    ))
    min(
        cos(addendum_angle), cos(dedendum_angle)
    )
;

module octoid_gear_tooth_profile(
    pitch_angle, tooth_count,
    pressure_angle = 20,
    addendum_coefficient = 1,
    dedendum_coefficient = 1.25
) {
    chosen_radius = fn_choose_octoid_cut_radius(
        pitch_angle = pitch_angle,
        tooth_count = tooth_count,
        addendum_coefficient = addendum_coefficient,
        dedendum_coefficient = dedendum_coefficient
    );
    projection(cut = false)
    translate([0, 0, chosen_radius])
    rotate(pitch_angle, [0, 1, 0])
    octoid_bevel_tooth(
        pitch_angle = pitch_angle,
        tooth_count = tooth_count,
        pressure_angle = pressure_angle,
        addendum_coefficient = addendum_coefficient,
        dedendum_coefficient = dedendum_coefficient
    );
}

module twist_bevel_tooth(
    pitch_angle, chosen_radius, twist_angle,
    inner_empty_ratio = 0.5,
) {
    hull() {
        for(r = [inner_empty_ratio:$fs:chosen_radius]) {
            scale([
                r / chosen_radius,
                r / chosen_radius,
                r / chosen_radius
            ])
            rotate(
                twist_angle * (chosen_radius - r)
                / (chosen_radius - inner_empty_ratio),
                [0, 0, 1]
            )
            rotate(-pitch_angle, [0, 1, 0])
            translate([0, 0, -chosen_radius])
            linear_extrude(0.1 * $fs * chosen_radius / r)
            children();
        }
        rotate(-pitch_angle, [0, 1, 0])
        translate([0, 0, -chosen_radius])
        linear_extrude(
            0.1 * $fs * (1 - chosen_radius % $fs)
        )
        children();
    }
}

module octoid_spiral_bevel_tooth(
    pitch_angle, tooth_count,
    inner_empty_ratio = 0.5,
    twist_steps = 0,
    pressure_angle = 20,
    addendum_coefficient = 1,
    dedendum_coefficient = 1.25
) {
    chosen_radius = fn_choose_octoid_cut_radius(
        pitch_angle = pitch_angle,
        tooth_count = tooth_count,
        addendum_coefficient = addendum_coefficient,
        dedendum_coefficient = dedendum_coefficient
    );
    twist_angle = twist_steps * 360 / tooth_count;
    addendum_angle = fn_octoid_addendum_or_dedendum_angle(
        addendum_coefficient, pitch_angle, tooth_count
    );
    dedendum_angle = fn_octoid_addendum_or_dedendum_angle(
        dedendum_coefficient, pitch_angle, tooth_count
    );
    intersection() {
        difference() {
            twist_bevel_tooth(
                pitch_angle = pitch_angle,
                chosen_radius = chosen_radius,
                twist_angle = twist_angle,
                inner_empty_ratio = inner_empty_ratio
            )
            //offset(r = -0.005)
            octoid_gear_tooth_profile(
                pitch_angle = pitch_angle,
                tooth_count = tooth_count,
                pressure_angle = pressure_angle,
                addendum_coefficient = addendum_coefficient,
                dedendum_coefficient = dedendum_coefficient
            );
            twist_bevel_tooth(
                pitch_angle = pitch_angle,
                chosen_radius = chosen_radius,
                twist_angle = twist_angle,
                inner_empty_ratio = inner_empty_ratio
            )
            difference() {
                translate([-chosen_radius * sin(dedendum_angle), 0, 0])
                if(twist_steps > 0) {
                    mirror([0, 1, 0])
                        square([
                            chosen_radius * sin(addendum_angle + dedendum_angle),
                            chosen_radius * sin(addendum_angle + dedendum_angle)
                        ], center = false);
                } else {
                    square([
                        chosen_radius * sin(addendum_angle + dedendum_angle),
                        chosen_radius * sin(addendum_angle + dedendum_angle)
                    ], center = false);
                }
                octoid_gear_tooth_profile(
                    pitch_angle = pitch_angle,
                    tooth_count = tooth_count,
                    pressure_angle = pressure_angle,
                    addendum_coefficient = addendum_coefficient,
                    dedendum_coefficient = dedendum_coefficient
                );
            }
            sphere(1.01 * inner_empty_ratio);
        }
        sphere(0.99);
    }
}

module octoid_spiral_bevel_gear(
    pitch_angle, tooth_count,
    inner_empty_ratio = 0.5,
    twist_steps = 0,
    pressure_angle = 20,
    addendum_coefficient = 1,
    dedendum_coefficient = 1.25
) {
    dedendum_angle = fn_octoid_addendum_or_dedendum_angle(
        dedendum_coefficient, pitch_angle, tooth_count
    );
    difference() {
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
    for(angle = [0:360/tooth_count:360]) {
        rotate(angle, [0, 0, 1]) octoid_spiral_bevel_tooth(
            pitch_angle = pitch_angle,
            tooth_count = tooth_count,
            inner_empty_ratio = inner_empty_ratio,
            twist_steps = twist_steps,
            pressure_angle = pressure_angle,
            addendum_coefficient = addendum_coefficient,
            dedendum_coefficient = dedendum_coefficient
        );
    }
}