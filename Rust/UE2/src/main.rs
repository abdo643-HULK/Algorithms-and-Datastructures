mod list;

use list::{LinkedList, List};

fn main() {
    let mut l = LinkedList::new();
    l.add_first(9);
    l.remove_first();
}
