pub fn mod_inverse(a: i32, m: i32) -> i32 {
    let (mut a, mut m) = (a as i64, m as i64);
    let (mut x0, mut x1) = (0, 1);

    while a > 1 {
        let q = a / m;
        let t = m;

        m = a % m;
        a = t;
        let t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if x1 < 0 {
        x1 += m;
    }

    x1 as i32
}