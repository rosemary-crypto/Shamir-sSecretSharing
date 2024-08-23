use crate::utils::mod_inverse;

pub fn reconstruct_secret(shares: &[(i32, i32)], prime: i32) -> i32 {
    let mut result = 0;

    for (i, &(xi, yi)) in shares.iter().enumerate() {
        let mut li = 1;

        for (j, &(xj, _)) in shares.iter().enumerate() {
            if i != j {
                let numerator = (0 - xj + prime) % prime;
                let denominator = (xi - xj + prime) % prime;
                let denominator_inv = mod_inverse(denominator, prime);

                li = li * numerator % prime;
                li = li * denominator_inv % prime;
            }
        }

        result = (result + yi * li) % prime;
    }

    if result < 0 {
        result += prime;
    }

    result
}
