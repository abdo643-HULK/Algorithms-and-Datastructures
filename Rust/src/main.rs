mod ex2;

use ex2::{LinkedList, List};

fn main() {
    let mut l = LinkedList::new();
    l.add_first(9);
    l.remove_first();
}
