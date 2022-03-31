use <../octoid_gear_types.scad>
use <../mesh_bevel_gear.scad>
use <../gear_bearing.scad>

// 0 or undef for full assembly
// 1 - 5 for individual pieces
do_piece = undef;

// set true for final render
// set false for faster viewing
high_detail = true;


$fs = high_detail ? 0.3 : $fs;
$fn = high_detail ? 30 : $fn;

module half_elbow_mechanism(
    reverse = false, rotation = 0
) {
    angle = fn_bevel_angle_for_gear_ratio(1);
    height = sin(angle) * 15;
    radius = cos(angle) * 15;

    coef = 1.4;
    difference() {
        union() {
            intersection() {
                mirror([0, 0, 1]) cylinder(22, 20, 0);
                rotate(rotation, [0, 0, 1])
                octoid_helical_gear(
                    15, 0.7, false,
                    reverse ? -1 : 1,
                    angle, 17, addendum_coefficient = 0.6
                );
            }
            
            translate([0, 0, -9])
            rotate(rotation, [0, 0, 1])
            cylinder(2, 7, 6);
            
            intersection() {
                mirror([0, 0, 1]) cylinder(16, 12, 0);
                rotate(rotation, [0, 0, 1])
                octoid_helical_gear(
                    10.5, 0.5, false,
                    reverse ? 1 : -1,
                    angle, 17, addendum_coefficient = 0.6
                );
            }

            translate([0, 0, -coef*height])
                cylinder((coef-1)*height, 0.6*coef*radius, radius);
        
        
            translate([0, 0, -coef*height - 8])
                gear_bearing(
                    8, coef*radius, 0.6, false,
                    40, 6,
                    planet_tooth_count = 8,
                    rotation_angle = rotation,
                    tolerance = 0.2
                );
        }
        
        translate([0, 0, -coef*height - 8 - 0.1])
            cylinder(10 + 0.1, 2.75, 2.75); // M5 clearance hole, normal fit
                
        translate([0, 0, -coef*height + 2 - 0.1])
            cylinder(6, 2.75, 0);  
                
        translate([0, 0, -coef*height - 8 - 0.1])
        linear_extrude(4.7) // M5 hexagon nut height
        scale([4.4, 4.4]) // M5 hexagon nut radius
        polygon([
            for(phi = [0:60:360])
                [cos(phi), sin(phi)]
        ]);
                
        translate([0, 0, -coef*height - 3.3 - 0.1])
        linear_extrude(7, scale = 0)
        scale([4.4, 4.4])
        polygon([
            for(phi = [0:60:360])
                [cos(phi), sin(phi)]
        ]);
    }
}

module half_elbow_corners() {
    angle = fn_bevel_angle_for_gear_ratio(1);
    height = sin(angle) * 15;
    radius = cos(angle) * 15;
    
    coef = 1.4;
    inner_coord = 0.9*coef*radius/sqrt(2);
    
    translate([0, 0, -coef*height - 8])
    linear_extrude(8)
    for(phi = [0:90:360]) {
        rotate(2*phi, [0, 0, 1])
        scale([1, phi >= 180 ? -1 : 1, 1])
        difference() {
            offset(1)
            offset(-1)
            polygon([
                [coef*radius, 0],
                [coef*radius, 1.3*coef*radius],
                [-1, 1.3*coef*radius],
                [-1, 0.99*coef*radius],
                [1.11*inner_coord, 1.11*inner_coord],
                [0.9*coef*radius, 2]
            ]);
            translate([1.02*inner_coord, 1.6*inner_coord])
            circle(d=3.4); // M3 clearance hole, normal fit
        }
    }
}

module elbow_connector() {
    angle = fn_bevel_angle_for_gear_ratio(1);
    height = sin(angle) * 15;
    radius = cos(angle) * 15;
    
    coef = 1.4;
    inner_coord = 0.9*coef*radius/sqrt(2);
    clearance = 0.0;
    
    for(phi = [0:90:360]) {
        rotate(phi % 180 > 0 ? -90 : 0, [0, 1, 0])
        scale([phi % 180 > 0 ? -1 : 1, 1, 1])
        translate([0, 0, -coef*height - 12 - clearance])
        linear_extrude(4)
        scale([1, phi >= 180 ? -1 : 1, 1])
        difference() {
            offset(1)
            offset(-1)
            polygon([
                [1.5*coef*radius, 0],
                [1.5*coef*radius, 1.3*coef*radius],
                [-1, 1.3*coef*radius],
                [-1, 0.99*coef*radius],
                [1.11*inner_coord, 1.11*inner_coord],
                [0.9*coef*radius, 2]
            ]);
            translate([1.02*inner_coord, 1.6*inner_coord])
            circle(d=3.4); // M3 clearance hole, normal fit
        }
    }
    
    translate([
        coef*height + clearance,
        1.3*coef*radius,
        -coef*height - clearance
    ])
    mirror([0, 0, 1])
    rotate(90, [1, 0, 0])
    linear_extrude(2.6*coef*radius)
    {
        square(10);
        
        offset(5)
        offset(-5)
        square(12);
    }
}

module elbow_support() {
    angle = fn_bevel_angle_for_gear_ratio(1);
    height = sin(angle) * 15;
    radius = cos(angle) * 15;
    
    coef = 1.4;
    inner_coord = 0.9*coef*radius/sqrt(2);
    clearance = 0.0;
    
    for(phi = [0:90:180]) {
        rotate(phi % 180 > 0 ? -90 : 0, [0, 1, 0])
        scale([phi % 180 > 0 ? -1 : 1, 1, 1])
        translate([0, 0, -coef*height + clearance])
        linear_extrude(4)
        scale([-1, 1, 1])
        difference() {
            offset(1)
            offset(-1)
            polygon([
                [coef*radius, 0],
                [coef*radius, 1.5*coef*radius],
                [-1, 1.5*coef*radius],
                [-1, 0.99*coef*radius],
                [1.11*inner_coord, 1.11*inner_coord],
                [0.9*coef*radius, 2]
            ]);
            translate([1.02*inner_coord, 1.6*inner_coord])
            circle(d=3.4); // M3 clearance hole, normal fit
        }
    }
    
    translate([
        coef*radius - clearance,
        1.3*coef*radius + clearance,
        -coef*radius + clearance
    ])
    rotate(-90, [1, 0, 0])
    rotate(180, [0, 0, 1])
    linear_extrude(4 - clearance)
    offset(1)
    offset(-1)
    polygon([
        [-8, -8],
        [2*coef*radius - clearance, -8],
        [2*coef*radius - clearance, 8 - clearance],
        [8 - clearance, 2*coef*radius - clearance],
        [-8, 2*coef*radius - clearance]
    ]);
}

/// FULL ANIMATED ASSEMBLY ///
rotate(360 * $t, [0, 0, 1])
if(!do_piece) {
    half_elbow_mechanism(false, 360 * $t);
    half_elbow_corners();
    mesh_bevel_gear(0, 1, 17)
        half_elbow_mechanism(true, -360 * $t);
    rotate(90, [0, -1, 0])
        half_elbow_corners();
    elbow_connector();
    elbow_support();
    mirror([0, 1, 0])
        elbow_support();
}

/// PIECE 1 ///
if(do_piece == 1) {
    half_elbow_mechanism(false);
    half_elbow_corners();
}

/// PIECE 2 ///
if(do_piece == 2) {
    half_elbow_mechanism(true);
    half_elbow_corners();
}

/// PIECE 3 ///
if(do_piece == 3) {
    elbow_connector();
}

/// PIECE 4 ///
if(do_piece == 4) {
    rotate(-90, [1, 0, 0])
        elbow_support();
}

/// PIECE 5 ///
if(do_piece == 5) {
    rotate(90, [1, 0, 0])
    mirror([0, 1, 0])
        elbow_support();
}