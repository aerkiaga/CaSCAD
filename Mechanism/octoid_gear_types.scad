use <octoid_gear_profile.scad>

module octoid_helical_gear(
    radius, inner_proportion, center = false, twist_steps = 0,
    pitch_angle, tooth_count, internal = false,
    pressure_angle = 20,
    addendum_coefficient = 1,
    dedendum_coefficient = 1.25
) {
    height_prop = cos(pitch_angle);
    
    twist = twist_steps * 360 / tooth_count;
    outer_proportion = 1 - inner_proportion;
    
    scale(radius)
    translate([0, 0, center ? 0 : -height_prop])
    linear_extrude(
        height = outer_proportion * height_prop,
        center = center,
        convexity = tooth_count,
        twist = twist, slices = abs(twist) / $fs / 10,
        scale = inner_proportion
    ) {
        octoid_gear_profile(
            inner_proportion = inner_proportion,
            twist_steps = twist_steps,
            pitch_angle = pitch_angle,
            tooth_count = tooth_count,
            internal = internal,
            pressure_angle = pressure_angle,
            addendum_coefficient = addendum_coefficient, 
            dedendum_coefficient = dedendum_coefficient
        );
    }
}

module octoid_spur_gear(
    radius, inner_proportion, center = false,
    pitch_angle, tooth_count, internal = false,
    pressure_angle = 20,
    addendum_coefficient = 1,
    dedendum_coefficient = 1.25
) {
    octoid_helical_gear(
        radius = radius, inner_proportion = inner_proportion,
        center = center, twist_steps = 0,
        pitch_angle = pitch_angle,
        tooth_count = tooth_count,
        internal = internal,
        pressure_angle = pressure_angle,
        addendum_coefficient = addendum_coefficient,
        dedendum_coefficient = dedendum_coefficient
    );
}