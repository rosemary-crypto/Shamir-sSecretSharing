use rand::Rng;

pub fn generate_shares(secret: i32, n: usize, k: usize, prime: i32) -> Vec<(i32, i32)> {
    let mut rng = rand::thread_rng();
    let mut coefficients = vec![secret];
    
    // Generate random coefficients
    for _ in 1..k {
        coefficients.push(rng.gen_range(0..prime));
    }

    let mut shares = Vec::new();

    // Generate shares
    for x in 1..=n as i32 {
        let mut y = 0;
        let mut x_power = 1;

        for &coeff in &coefficients {
            y = (y + coeff * x_power) % prime;
            x_power = (x_power * x) % prime;
        }

        shares.push((x, y));
    }

    shares
}
