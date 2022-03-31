use <involute_gear_profile.scad>

module involute_helical_gear(
    height, pitch_radius, center = false, twist_steps = 0,
    tooth_count, internal = false,
    pressure_angle = 20,
    addendum_coefficient = 1,
    dedendum_coefficient = 1.25
) {
    twist = twist_steps * 360 / tooth_count;
    linear_extrude(
        height = height, center = center,
        convexity = tooth_count,
        twist = twist, scale = 1
    ) {
        scale(pitch_radius) {
            $fs = $fs / pitch_radius;
            involute_gear_profile(
                tooth_count = tooth_count,
                internal = internal,
                pressure_angle = pressure_angle,
                addendum_coefficient = addendum_coefficient, 
                dedendum_coefficient = dedendum_coefficient
            );
        }
    }
}

module involute_spur_gear(
    height, pitch_radius, center = false,
    tooth_count, internal = false,
    pressure_angle = 20,
    addendum_coefficient = 1,
    dedendum_coefficient = 1.25
) {
    involute_helical_gear(
        height = height, pitch_radius = pitch_radius,
        center = center, twist_steps = 0,
        tooth_count = tooth_count,
        internal = internal,
        pressure_angle = pressure_angle,
        addendum_coefficient = addendum_coefficient,
        dedendum_coefficient = dedendum_coefficient
    );
}

module involute_herringbone_gear(
    height, pitch_radius, center = false, twist_steps = 0,
    tooth_count, internal = false,
    pressure_angle = 20,
    addendum_coefficient = 1,
    dedendum_coefficient = 1.25
) {
    if(center) {
        translate([0, 0, -height/2])
        involute_herringbone_gear(
            height = height, pitch_radius = pitch_radius,
            center = false, twist_steps = twist_steps,
            tooth_count = tooth_count,
            internal = internal,
            pressure_angle = pressure_angle,
            addendum_coefficient = addendum_coefficient,
            dedendum_coefficient = dedendum_coefficient
        );
    }
    else {
        union() {
            involute_helical_gear(
                height = height/2, pitch_radius = pitch_radius,
                center = false, twist_steps = twist_steps,
                tooth_count = tooth_count,
                internal = internal,
                pressure_angle = pressure_angle,
                addendum_coefficient = addendum_coefficient,
                dedendum_coefficient = dedendum_coefficient
            );
            translate([0, 0, height])
            mirror([0, 0, 1])
            involute_helical_gear(
                height = height/2, pitch_radius = pitch_radius,
                center = false, twist_steps = twist_steps,
                tooth_count = tooth_count,
                internal = internal,
                pressure_angle = pressure_angle,
                addendum_coefficient = addendum_coefficient,
                dedendum_coefficient = dedendum_coefficient
            );
        }
    }
}