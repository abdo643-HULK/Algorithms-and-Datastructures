use std::time::Instant;

use exercises::ex8::{BoyerMoore, BruteForce};

const TEST_CASES: i8 = 1;
const TEXT: &str = include_str!("big.txt");
const PATTERNS: [&'static str; 6] = [
    "a",
    "abacab",
    "ab",
    "def",
    "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
    "bacaabaccebabacabbb",
];

#[test]
fn test_patterns() {
    for (i, pattern) in PATTERNS.iter().enumerate() {
        println!("\n================== Run {i} ==================");
        brute_force_test(pattern);
        boyer_moore_test(pattern);
    }
}

fn brute_force_test(pattern: &str) {
    let now = Instant::now();

    let mut matches: usize = 0;
    for _ in 0..TEST_CASES {
        let mut index = 0;

        let b = BruteForce::new(pattern, TEXT);

        while let Some(i) = b.match_from(index) {
            index = i + 1;
            matches += 1;
        }
    }

    let elapsed = now.elapsed().as_millis();

    println!("Time taken: {elapsed}ms");
    println!("{matches}");
}

fn boyer_moore_test(pattern: &str) {
    let now = Instant::now();

    let mut matches: usize = 0;
    for _ in 0..TEST_CASES {
        let mut index = 0;

        let b = BoyerMoore::new(pattern, TEXT);

        loop {
            let m = b.match_from(index);
            match m {
                Some(i) => {
                    index = i + 1;
                    matches += 1;
                }
                None => break,
            }
        }
    }

    let elapsed = now.elapsed().as_millis();

    println!("Time taken: {elapsed}ms");
    println!("{matches}")
}
