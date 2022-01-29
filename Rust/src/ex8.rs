use std::cmp;

pub struct BruteForce<'a> {
    pattern: &'a str,
    text: &'a str,
}

impl<'a> BruteForce<'a> {
    pub fn new(pattern: &'a str, text: &'a str) -> BruteForce<'a> {
        BruteForce { pattern, text }
    }

    pub fn match_from(&self, start_index: usize) -> Option<usize> {
        let m = self.pattern.len();
        let n = self.text.len();
        let end = n - m;

        let text = self.text.as_bytes();
        let pattern = self.pattern.as_bytes();

        for i in start_index..end {
            let mut j = 0;

            while j < m && text[i + j] == pattern[j] {
                j += 1;
            }

            if j == m {
                return Some(i);
            }
        }

        return None;
    }
}

pub struct BoyerMoore<'a> {
    pattern: &'a str,
    text: &'a str,
    last: [i16; 256],
    matches: Vec<u8>,
}

impl<'a> BoyerMoore<'a> {
    pub fn new(pattern: &'a str, text: &'a str) -> BoyerMoore<'a> {
        let mut last = [-1; 256];
        let mut matches = vec![0; pattern.len()];

        BoyerMoore::calculate_last(&mut last, pattern);
        BoyerMoore::calculate_match_table(&mut matches, pattern);

        BoyerMoore {
            pattern,
            text,
            matches,
            last,
        }
    }

    fn calculate_last(last: &mut [i16], pattern: &str) {
        for (i, ascii_code) in pattern.bytes().enumerate() {
            last[ascii_code as usize] = i as i16;
        }
    }

    fn calculate_match_table(matches: &mut Vec<u8>, pattern: &str) {
        let m: usize = pattern.len();
        let bytes_pattern = pattern.as_bytes();

        for j in 0..m {
            let mut found = false;
            let mut s: usize = 0;
            let part_to_match = &pattern[j + 1..];

            while s <= j && !found {
                s += 1;
                if j <= 0 {
                    break;
                }

                let suffix_part = &pattern[j + 1 - s..m - s];

                let is_suffix = part_to_match.contains(suffix_part);

                if (is_suffix != false || j == m - 1)
                    && (s <= j && bytes_pattern[j] != bytes_pattern[j - s])
                {
                    found = true;
                }
            }

            while (j < s && s < m) && !found {
                let suffix_part = &pattern[0..m - s];

                if part_to_match.contains(suffix_part) != false {
                    found = true;
                    break;
                }

                s += 1;
            }

            matches[j] = if !found { m } else { s } as u8
        }
    }

    pub fn match_from(&self, start_index: usize) -> Option<usize> {
        let m = self.pattern.len();
        let n = self.text.len();

        let text = self.text.as_bytes();
        let pattern = self.pattern.as_bytes();

        let mut i = start_index + m - 1;
        let mut j = m - 1;

        loop {
            if pattern[j] == text[i] {
                if j == 0 {
                    return Some(i);
                }
                i -= 1;
                j -= 1;

                continue;
            }

            i += m - j - 1;

            let ascii_code = text[i] as usize;
            let max = cmp::max::<i16>(j as i16 - self.last[ascii_code], self.matches[j].into());

            i += max as usize;
            j = m - 1;

            if i > n - 1 {
                break;
            }
        }

        return None;
    }
}
