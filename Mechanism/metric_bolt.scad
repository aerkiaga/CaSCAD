default_pitch_lookup_table = [
    // M  P
    [0, undef], [1, 0.25],
    [2, 0.4], [3, 0.5],
    [4, 0.7], [5, 0.8],
    [6, 1.0], [7, 1.0],
    [8, 1.25], [9, undef],
    [10, 1.5], [11, undef],
    [12, 1.75], [13, undef],
    [14, 2.0], [15, undef],
    [16, 2.0], [17, undef],
    [18, 2.5], [19, undef],
    [20, 2.5],
];

/*
pitch can be actual pitch in mm,
or undef for default value
*/

module metric_bolt(
    nominal_diameter, pitch = undef, length,
    generate_thread = true
) {
    pitch = pitch ? pitch
        : default_pitch_lookup_table[nominal_diameter][1];
    mirror([0, 0, 1])
    if(generate_thread) {
        
    } else {
        cylinder(length, nominal_diameter, nominal_diameter);
    }
}

// M2x15
metric_bolt(2, undef, 15, false);