use <cycloid_gear_profile.scad>

module cycloid_helical_gear(
    height, pitch_radius, center = false, twist_steps = 0,
    tooth_count, internal = false, outer_radius = undef,
    tolerance = 0
) {
    twist = twist_steps * 360 / tooth_count;
    linear_extrude(
        height = height, center = center,
        convexity = tooth_count,
        twist = twist, scale = 1
    ) {
        offset(-tolerance)
        scale(pitch_radius) {
            //$fs = $fs / pitch_radius;
            cycloid_gear_profile(
                tooth_count = tooth_count,
                internal = internal,
                outer_radius = outer_radius / pitch_radius
            );
        }
    }
}

module cycloid_spur_gear(
    height, pitch_radius, center = false,
    tooth_count, internal = false, outer_radius = undef,
    tolerance = 0
) {
    cycloid_helical_gear(
        height = height, pitch_radius = pitch_radius,
        center = center, twist_steps = 0,
        tooth_count = tooth_count,
        internal = internal,
        outer_radius = outer_radius,
        tolerance = tolerance
    );
}

module cycloid_herringbone_gear(
    height, pitch_radius, center = false, twist_steps = 0,
    tooth_count, internal = false, outer_radius = undef,
    tolerance = 0
) {
    if(center) {
        translate([0, 0, -height/2])
        cycloid_herringbone_gear(
            height = height, pitch_radius = pitch_radius,
            center = false, twist_steps = twist_steps,
            tooth_count = tooth_count,
            internal = internal,
            outer_radius = outer_radius,
            tolerance = tolerance
        );
    }
    else {
        union() {
            cycloid_helical_gear(
                height = height/2, pitch_radius = pitch_radius,
                center = false, twist_steps = twist_steps,
                tooth_count = tooth_count,
                internal = internal,
                outer_radius = outer_radius,
                tolerance = tolerance
            );
            translate([0, 0, height])
            mirror([0, 0, 1])
            cycloid_helical_gear(
                height = height/2, pitch_radius = pitch_radius,
                center = false, twist_steps = twist_steps,
                tooth_count = tooth_count,
                internal = internal,
                outer_radius = outer_radius,
                tolerance = tolerance
            );
        }
    }
}