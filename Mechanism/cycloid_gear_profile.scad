use <basic_functions.scad>

function fn_unit_epicycloid(
    angle, lobe_count
) =
    [
        (1 + 1/lobe_count) * cos(angle)
        - cos((lobe_count + 1) * angle) / lobe_count,
        (1 + 1/lobe_count) * sin(angle)
        - sin((lobe_count + 1) * angle) / lobe_count
    ]
;

function fn_unit_hypocycloid(
    angle, lobe_count
) =
    [
        (1 - 1/lobe_count) * cos(angle)
        + cos((lobe_count - 1) * angle) / lobe_count,
        (1 - 1/lobe_count) * sin(angle)
        - sin((lobe_count - 1) * angle) / lobe_count
    ]
;

function fn_unit_cycloid_profile(
    angle, tooth_count
) =
    (angle % (360 / tooth_count) < 180 / tooth_count)?
        fn_unit_epicycloid(angle, 2 * tooth_count)
    :
        fn_unit_hypocycloid(angle, 2 * tooth_count);
;

module cycloid_gear_profile(
    tooth_count, internal = false, 
    outer_radius = undef
) {
    if(internal) {
        difference() {
            circle(outer_radius);
            cycloid_gear_profile(
                tooth_count = tooth_count,
                internal = false,
                outer_radius = undef
            );
        }
    }
    else {
        step = 360 / tooth_count / $fn;
        polygon([
            for(phi = [0:step:360])
                fn_unit_cycloid_profile(
                    phi,
                    tooth_count
                )
        ]);
    }
}