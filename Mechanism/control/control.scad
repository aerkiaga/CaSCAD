use <../cycloid_gear_types.scad>
use <../mesh_parallel_gear.scad>

// 0 or undef for full assembly
// 1 - 5 for individual pieces
do_piece = undef;

/*
Piece   Count   Description
1       1       Motor housing half 1
2       1       Motor housing half 2
3       1       Output segment
4       1       Sun gear
5       2       Planet gear
6       1       Helix, bottom
7       1       Helix, top
8       1       Fixed gear
9       15      Output shaft
10      15      Output adapter
11      15      Output housing
12      1       Base
*/

// set true for final render
// set false for faster viewing
high_detail = true;


$fs = high_detail ? 0.1 : $fs;
$fn = high_detail ? 100 : $fn;

module NEMA17_motor(length) {
    linear_extrude(length)
    polygon([
        /*[21.15, 15.5],
        [15.5, 21.15],
        [-15.5, 21.15],
        [-21.15, 15.5],
        [-21.15, -15.5],
        [-15.5, -21.15],
        [15.5, -21.15],
        [21.15, -15.5],*/
        [21.15, 16.5],
        [16.5, 21.15],
        [-16.5, 21.15],
        [-21.15, 16.5],
        [-21.15, -16.5],
        [-16.5, -21.15],
        [16.5, -21.15],
        [21.15, -16.5],
    ]);
    translate([0, 0, length])
    cylinder(2, d=22, false);
    translate([0, 0, length])
    difference() {
        cylinder(25, d=5, false);
        translate([4, 0, 15])
        cube([5, 5, 20], true);
    }
}

module bearing_606_2RS() {
    difference() {
        cylinder(6, d=17, false);
        translate([0, 0, -0.5])
        cylinder(7, d=6, false);
    }
}

module M3_bolt() {
    cylinder(20, d=3.4);
    mirror([0, 0, 1])
    cylinder(2, d=6);
}

module M3_hexagon_profile() {
    //radius = 3.2;
    radius = 3.5;
    polygon([ for(phi = [0:60:360]) [
        radius * cos(phi), radius * sin(phi)
    ]]);
}

module stacked_motors() {
    //small motor
    translate([-17, 0, 0])
    rotate(90, [0, 1, 0])
    NEMA17_motor(34);
    //large motor
    rotate(180, [0, 0, 1])
    translate([0, 0, -25 - 39 - 21.3 - 5])
    NEMA17_motor(39);
}

module m3_hole(y, z) {
    translate([0, y, z])
    rotate(90, [0, 1, 0]) {
        translate([0, 0, -20])
            cylinder(50, d=3.4, false);
        translate([0, 0, -20])
            cylinder(12, d=6, false);
        translate([0, 0, 20])
        mirror([0, 0, 1])
        linear_extrude(13)
            M3_hexagon_profile();
    }
}

module motor_housing() {
    difference() {
        translate([0, 0, -35.5])
            cube([38, 50, 130], true);
        stacked_motors();
        translate([-10, 0, 25])
            cube([20, 20, 12], true);
        translate([0, 0, -35])
            cube([30, 60, 24], true);
        m3_hole(20, 22);
        m3_hole(-20, 22);
        m3_hole(20, -95);
        m3_hole(-20, -95);
    }
}

module helix(
    turns = 4,
    inner_radius = 27,
    outer_radius = 60,
    turn_height = 40,
    height_proportion = 0.1
) {
    height = turn_height * turns;
    twist = 360 * turns;
    angle = height_proportion * 180;
    
    intersection() {
        linear_extrude(height, twist = twist, slices = turns * 3 * $fn, convexity = turns + 1)
        rotate(-angle, [0, 0, 1])
        projection()
        rotate_extrude(angle = 2 * angle, convexity = 1)
        polygon([
            [1.2*outer_radius, 1],
            [1.2*outer_radius, -1],
            [inner_radius, -1],
            [inner_radius, 1]
        ]);
        cylinder(height, r=outer_radius);
    }
}

module output_sector() {
    difference() {
        rotate(180, [1, 0, 0])
        intersection() {
            union() {
                translate([0, 0, -40])
                    helix(4, 45);
                rotate(90, [0, 1, 0])
                    cylinder(49, 3.5, 3.5);
            }
            rotate(90, [0, 1, 0])
                cylinder(60, 0, 20);
        }
        translate([0, 0, -10])
            cylinder(20, r=25, true);
        stacked_motors();
    }
}

sun_teeth = 16;
sun_radius = 5;
fixed_radius = 35;

fixed_teeth = sun_teeth * fixed_radius / sun_radius;
planet_radius = (fixed_radius - sun_radius) / 2;
planet_teeth = sun_teeth * planet_radius / sun_radius;

module fixed_helix() {
    difference() {
        translate([0, 0, -80])
            helix(4, 0);
        rotate(90, [0, 1, 0])
            cylinder(110, 0, 45);
        translate([0, 0, -32.5])
            cube([38, 50, 127], true);
        stacked_motors();
        translate([0, -sun_radius - planet_radius, -40])
            cylinder(20, 1.1*planet_radius, 1.1*    planet_radius);
        translate([0, sun_radius + planet_radius, -60])
            cylinder(20, 1.1*planet_radius, 1.1*    planet_radius);
    }
}

module fixed_gear() {
    difference() {
        translate([0, 0, -60])
        cycloid_spur_gear(130, fixed_radius, false,
            fixed_teeth, true, 44);
        translate([0, 0, -80])
        helix(4, 0, 60, 40, 0.2);
        for(phi = [-360:360/15:864]) {
            translate([0, 0, 40 * phi / 360])
            rotate(-phi, [0, 0, 1]) {
                translate([fixed_radius + 3, 0, 0])
                rotate(90, [0, 1, 0])
                translate([20, 0, 0]) {
                    M3_bolt();
                    translate([0, 0, -10])
                    cylinder(10, d=6);
                }
            }
        }
    }
}

module sun_gear() {
    difference() {
        translate([0, 0, -45])
        cycloid_spur_gear(20, sun_radius, false, sun_teeth);
        stacked_motors();
    }
}

module planet_gear(angle = 90) {
    translate([0, 0, -45])
    mesh_parallel_gear(sun_radius + planet_radius, angle,
        planet_teeth / fixed_teeth, true, planet_teeth)
    difference() {
        cycloid_spur_gear(20, planet_radius, false, planet_teeth);
        cylinder(4, d=17.1);
    }
}

module output_shaft() {
    difference() {
        rotate(90, [0, 1, 0])
        union() {
            difference() {
                cylinder(60, 0, 15);
                cylinder(50, 0, 15);
            }
            translate([0, 0, 60 + 3])
            cube([6/sqrt(2), 6/sqrt(2), 3], true);
        }
        translate([0, 0, -40])
        helix();
    }
}

module planet_bearing(angle = 90) {
    translate([0, 0, -47])
    mesh_parallel_gear(sun_radius + planet_radius, angle, 1, true, 1)
    color("pink")
        bearing_606_2RS();
}

module output_adapter() {
    rotate(90, [0, 1, 0])
    translate([0, 0, 60 + 7])
    union() {
        translate([0, 0, 1])
        difference() {
            cylinder(6, d=10, false);
            translate([0, 0, 6 - 4.7])
            linear_extrude(4.7 + 0.1)
            // M5 nut
            polygon([ for(phi = [0:60:360]) [
                4.12 * cos(phi), 4.12 * sin(phi)
            ]]);
        }
        cube([6/sqrt(2), 6/sqrt(2), 5], true);
    }
}

module output_housing() {
    angle = 720/15;
    inner_apotheme = 61;
    outer_apotheme = 67;
    outer_side = outer_apotheme * tan(angle/2) * 2;
    third_side = outer_apotheme * tan(angle/3);
    step = 40 * angle / 360;
    
    difference() {
        translate([outer_apotheme, 0, 0])
        rotate(-90, [0, 1, 0]) {
            linear_extrude(outer_apotheme - inner_apotheme,
                scale = [1, inner_apotheme / outer_apotheme],
                convexity = 4
            )
            difference() {
                polygon([
                    [40 - step/6, third_side/2],
                    [40 + step/6, -third_side/2],
                    [0 + step/3, -third_side],
                    [-40 + step/6, -third_side/2],
                    [-40 - step/6, third_side/2],
                    [0 - step/3, third_side]
                ]);
                circle(d=18);
                translate([20, 0, 0])
                M3_hexagon_profile();
                translate([-20, 0, 0])
                M3_hexagon_profile();
            }
            
            translate([0, 0, outer_apotheme - inner_apotheme])
            linear_extrude(10, convexity=4)
            difference() {
                union() {
                    translate([20, 0, 0])
                        circle(d=10);
                    translate([-20, 0, 0])
                        circle(d=10);
                }
                translate([20, 0, 0])
                M3_hexagon_profile();
                translate([-20, 0, 0])
                M3_hexagon_profile();
            }
            
            translate([0, 0, outer_apotheme - inner_apotheme + 10])
            linear_extrude(20, convexity=4)
            difference() {
                union() {
                    translate([20, 0, 0])
                        circle(d=10);
                    translate([-20, 0, 0])
                        circle(d=10);
                }
                translate([20, 0, 0])
                    circle(d=3.4);
                translate([-20, 0, 0])
                    circle(d=3.4);
            }
        }
        translate([0, 0, -50])
        cylinder(100, r=44);
    }
}

module structure_base() {
}

/// FULL ANIMATED ASSEMBLY ///
if(!do_piece) {
    motor_housing();
    color("pink") {
        stacked_motors();
        for(pair = [
            [20, 22], [-20, 22], [20, -95], [-20, -95]
        ]) {
            translate([-8, pair[0], pair[1]])
            rotate(90, [0, 1, 0])
                M3_bolt();
        }
    }
    output_sector();
    sun_gear();
    planet_gear(90);
    planet_bearing(90);
    planet_gear(270);
    planet_bearing(270);
    /*fixed_helix();
    fixed_gear();
    for(phi = [0:720/15:720]) {
        translate([0, 0, 40 * phi / 360])
        rotate(-phi, [0, 0, 1]) {
            output_shaft();
            translate([60, 0, 0])
            rotate(90, [0, 1, 0])
            color("pink")
                bearing_606_2RS();
            output_adapter();
            output_housing();
            translate([fixed_radius + 3, 0, 0])
            rotate(90, [0, 1, 0])
            color("pink") {
                if(phi < 720)
                translate([20, 0, 0])
                    M3_bolt();
                if(phi < 360)
                translate([-20, 0, 0])
                    M3_bolt();
            }
        }
    }*/
}

/// PIECE 1 ///
if(do_piece == 1) {
    rotate(90, [0, 1, 0])
    intersection() {
        motor_housing();
        translate([0, -25, -100])
        cube([40, 50, 150], false);
    }
}

/// PIECE 2 ///
if(do_piece == 2) {
    rotate(-90, [0, 1, 0])
    intersection() {
        motor_housing();
        translate([-40, -25, -100])
        cube([40, 50, 150], false);
    }
}

/// PIECE 3 ///
if(do_piece == 3) {
    output_sector();
}

/// PIECE 4 ///
if(do_piece == 4) {
    rotate(180, [0, 1, 0])
    sun_gear();
}

/// PIECE 5 ///
if(do_piece == 5) {
    rotate(180, [0, 1, 0])
    planet_gear();
}

/// PIECE 6 ///
if(do_piece == 6) {
    intersection() {
        fixed_helix();
        mirror([0, 0, 1])
        cylinder(100, r=100);
    }
}

/// PIECE 7 ///
if(do_piece == 7) {
    intersection() {
        fixed_helix();
        cylinder(100, r=100);
    }
}

/// PIECE 8 ///
if(do_piece == 8) {
    fixed_gear();
}

/// PIECE 9 ///
if(do_piece == 9) {
    rotate(-90, [0, 1, 0])
    output_shaft();
}

/// PIECE 10 ///
if(do_piece == 10) {
    rotate(90, [0, 1, 0])
    output_adapter();
}

/// PIECE 11 ///
if(do_piece == 11) {
    rotate(90, [0, 1, 0])
    output_housing();
}

/// PIECE 12 ///
if(do_piece == 12) {
    structure_base();
}