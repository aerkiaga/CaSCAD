function fn_radians_from_degrees(angle) =
    angle * PI / 360
;

function fn_cartesian_from_polar(angle, radius) =
    [radius * cos(angle), radius * sin(angle)]
;