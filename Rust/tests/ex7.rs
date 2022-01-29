use exercises::ex7::{
    ChainingHashset, MyChainingHashset, MyOrderedDoubleHashSet, OrderedDoubleHashSet,
};

#[test]
fn double_hashset() {
    let mut set = MyOrderedDoubleHashSet::new(7);

    for i in [15, 2, 43, 4, 18, 21] {
        set.insert(i);
    }
    println!("{set}");

    set.remove(21);
    println!("{set}");

    set.clear();
    println!("{set}");

    // set.insert(15);
    // set.insert(2);
    // set.insert(43);
    // set.insert(4);
    // set.insert(18);

    // set.insert(21);

    // println!("{set}");

    // set.remove(18);

    // println!("{set}");

    // set.clear();

    // println!("{set}");
}

#[test]
fn chaining_hashset() {
    let mut set = MyChainingHashset::new(5);
    set.insert(1);
    set.insert(1);
    set.insert(15);
    set.insert(17);
    set.insert(110);
    set.insert(159);
    set.insert(1);
    set.insert(159);
    set.insert(137);
    set.insert(207);

    println!("List: ");
    println!("{set}");

    set.remove(1);

    println!("List: ");
    println!("{set}");

    let size = set.size();
    println!("size: {size}\n");

    set.clear();
    println!("List: ");
    println!("{set}");

    let size = set.size();
    println!("size: {size}\n");
    set.clear();
}
