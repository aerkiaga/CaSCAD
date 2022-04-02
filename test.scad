module foo(x, y) {
    cylinder(x, d=y);
}

function bar(x) = 4;

b = bar(5);

foo(1, 1);
foo(2, 0.5);