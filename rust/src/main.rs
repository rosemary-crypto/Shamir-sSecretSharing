mod secret_sharing;
mod utils;

use secret_sharing::share_generation;
use secret_sharing::share_reconstruction;

fn main() {
    let secret = 41;
    let n = 5;
    let k = 3;
    let prime = 257;

    // Generate shares
    let shares = share_generation::generate_shares(secret, n, k, prime);
    println!("Generated Shares: {:?}", shares);

    // Reconstruct secret using the first k shares
    let reconstructed_secret = share_reconstruction::reconstruct_secret(&shares[..k], prime);
    println!("Reconstructed Secret: {}", reconstructed_secret);
}
