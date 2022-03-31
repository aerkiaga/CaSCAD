use <cycloid_gear_types.scad>
use <mesh_parallel_gear.scad>

module gear_bearing(
    height, radius, inner_proportion, center = false,
    inner_tooth_count, planet_count,
    planet_tooth_count = 4, separation_coefficient = 1.1,
    rotation_angle = 0, tolerance = 0
) {  
    assert(
        (2 * (inner_tooth_count + planet_tooth_count))
        % planet_count == 0,
        "For gear bearings, planet_count must divide 2 * (inner_tooth_count + planet_tooth_count) evenly"
    );
    
    inner_max_radius = inner_proportion * radius;
    inner_pitch_radius = inner_max_radius
        / (1 - 0.5 * PI / inner_tooth_count);
    rotate(rotation_angle, [0, 0, 1])
    cycloid_herringbone_gear(
        height, inner_pitch_radius, center,
        1, inner_tooth_count, false
    );
    
    outer_tooth_count = inner_tooth_count
        + 2 * planet_tooth_count;
    outer_pitch_radius = inner_pitch_radius
        * outer_tooth_count / inner_tooth_count;
    rotate(
        planet_tooth_count * 180 / outer_tooth_count,
        [0, 0, 1]
    )
    cycloid_herringbone_gear(
        height, outer_pitch_radius, center,
        -1, outer_tooth_count, true, radius
    );
    
    planet_pitch_radius = inner_pitch_radius
        * planet_tooth_count / inner_tooth_count;
    planet_max_radius = planet_pitch_radius
        * (1 + 0.5 * PI / planet_tooth_count);
    planet_ring_radius =
        (inner_pitch_radius + outer_pitch_radius) / 2;
    ideal_planet_angle = 2 * asin(
        separation_coefficient *
        planet_max_radius / planet_ring_radius
    );
    max_planet_count = floor(360 / ideal_planet_angle);
    
    assert(
        planet_count <= max_planet_count,
        "Too many planets on gear bearing, can't avoid overlap"
    );
    
    planet_angle = 360 / planet_count;
    planet_ratio = inner_tooth_count / planet_tooth_count;
    carrier_ratio = 
        1 / (1 + outer_tooth_count / inner_tooth_count);
    rotate(rotation_angle, [0, 0, 1])
    for(phi = [0:planet_angle:360]) {
        mesh_parallel_gear(
            planet_ring_radius,
            phi - rotation_angle * (1 - carrier_ratio),
            planet_tooth_count / inner_tooth_count,
            false, planet_tooth_count
        )
        cycloid_herringbone_gear(
            height, planet_pitch_radius, center,
            1, planet_tooth_count, false,
            tolerance = tolerance
        );
    }
}