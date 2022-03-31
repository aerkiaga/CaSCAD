module roller_bearing_roller(
    height, groove_width,
    contact_angle = 30, open_proportion = 0.4,
    side_tolerance = 0.05, vertical_tolerance = 0.2,
) {
    end_distance = vertical_tolerance + side_tolerance/tan(contact_angle);
    base_radius2 = open_proportion * groove_width/2;
    base_radius = base_radius2 - end_distance * tan(contact_angle);
    cylinder_radius = groove_width/2 - side_tolerance;
    closed_proportion = 1 - open_proportion;
    flap_width = closed_proportion * groove_width/2;
    flap_height = flap_width / tan(contact_angle);
    cone_height = flap_height + vertical_tolerance;
    
    rotate_extrude(angle = 360, convexity = 1)
    polygon([
        [0, height/2],
        [0, -height/2],
        [base_radius, -height/2],
        [cylinder_radius, -height/2 + cone_height],
        [cylinder_radius, height/2 - cone_height],
        [base_radius, height/2],
    ]);
}

module roller_bearing(
    height, radius, inner_proportion, outer_proportion,
    center = false,
    contact_angle = 30, open_proportion = 0.5,
    side_tolerance = 0.05, vertical_tolerance = 0.2
) {
    inner_radius = inner_proportion * radius;
    outer_radius = outer_proportion * radius;
    translate([0, 0, center ? 0 : height/2]) {
        groove_width = outer_radius - inner_radius;
        closed_proportion = 1 - open_proportion;
        flap_width = closed_proportion*groove_width/2;
        flap_height = flap_width / tan(contact_angle);
        
        rotate_extrude(angle = 360, convexity = 2)
        polygon([
            [outer_radius - flap_width, height/2],
            [outer_radius, height/2 - flap_height],
            [outer_radius, -height/2 + flap_height],
            [outer_radius - flap_width, -height/2],
            [radius, -height/2], [radius, height/2]
        ]);
        
        rotate_extrude(angle = 360, convexity = 2)
        polygon([
            [inner_radius + flap_width, -height/2],
            [inner_radius, -height/2 + flap_height],
            [inner_radius, height/2 - flap_height],
            [inner_radius + flap_width, height/2],
            [0, height/2], [0, -height/2]
        ]);
        
        track_radius = inner_radius + groove_width/2;
        track_length = 2 * PI * track_radius;
        n_rollers = floor(track_length / (1.2 * groove_width));
        step = 360 / n_rollers;
        for(phi = [0:step:360]) {
            rotate(phi, [0, 0, 1])
            translate([track_radius, 0, 0])
            roller_bearing_roller(
                height = height, groove_width = groove_width,
                contact_angle = contact_angle,
                open_proportion = open_proportion,
                side_tolerance = side_tolerance,
                vertical_tolerance = vertical_tolerance
            );
        }
    }
}

module roller_bearing_roller_2(
    height, groove_width,
    contact_angle = 30, open_proportion = 0.4,
    side_tolerance = 0.05, vertical_tolerance = 0.2,
) {
    end_distance = vertical_tolerance + side_tolerance/tan(contact_angle);
    base_radius2 = open_proportion * groove_width/2;
    base_radius = base_radius2 - side_tolerance;
    cylinder_radius = groove_width/2 - end_distance * tan(contact_angle);
    closed_proportion = 1 - open_proportion;
    flap_width = closed_proportion * groove_width/2;
    flap_height = flap_width / tan(contact_angle);
    cone_height = flap_height - vertical_tolerance;
    
    rotate_extrude(angle = 360, convexity = 1)
    polygon([
        [0, height/2],
        [0, -height/2],
        [cylinder_radius, -height/2],
        [base_radius, -height/2 + cone_height],
        [base_radius, height/2 - cone_height],
        [cylinder_radius, height/2],
    ]);
}

module roller_bearing_2(
    height, radius, inner_proportion, outer_proportion,
    center = false,
    contact_angle = 30, open_proportion = 0.5,
    side_tolerance = 0.05, vertical_tolerance = 0.2
) {
    inner_radius = inner_proportion * radius;
    outer_radius = outer_proportion * radius;
    translate([0, 0, center ? 0 : height/2]) {
        groove_width = outer_radius - inner_radius;
        closed_proportion = 1 - open_proportion;
        flap_width = closed_proportion*groove_width/2;
        flap_height = flap_width / tan(contact_angle);
        
        rotate_extrude(angle = 360, convexity = 2)
        polygon([
            [outer_radius, height/2],
            [outer_radius - flap_width, height/2 - flap_height],
            [outer_radius - flap_width, -height/2 + flap_height],
            [outer_radius, -height/2],
            [radius, -height/2], [radius, height/2]
        ]);
        
        rotate_extrude(angle = 360, convexity = 2)
        polygon([
            [inner_radius, -height/2],
            [inner_radius + flap_width, -height/2 + flap_height],
            [inner_radius + flap_width, height/2 - flap_height],
            [inner_radius, height/2],
            [0, height/2], [0, -height/2]
        ]);
        
        track_radius = inner_radius + groove_width/2;
        track_length = 2 * PI * track_radius;
        n_rollers = floor(track_length / (1.2 * groove_width));
        step = 360 / n_rollers;
        for(phi = [0:step:360]) {
            rotate(phi, [0, 0, 1])
            translate([track_radius, 0, 0])
            roller_bearing_roller_2(
                height = height, groove_width = groove_width,
                contact_angle = contact_angle,
                open_proportion = open_proportion,
                side_tolerance = side_tolerance,
                vertical_tolerance = vertical_tolerance
            );
        }
    }
}

module rotate_bearing(
    angle, radius,
    inner_proportion, outer_proportion
) {
    inner_radius = inner_proportion * radius;
    outer_radius = outer_proportion * radius;
    groove_width = outer_radius - inner_radius;
    inner_length = 2 * PI * inner_radius;
    track_radius = inner_radius + groove_width/2;
    track_length = 2 * PI * track_radius;
    roller_angle = angle * inner_length / 2 / track_length;
    rotate(roller_angle, [0, 0, 1])
        children();
}

/*intersection() {
    translate([0, 0, -2]) cube(10);
    roller_bearing(4, 10, 6, 9);
}*/

roller_bearing(4, 10, 0.6, 0.9);